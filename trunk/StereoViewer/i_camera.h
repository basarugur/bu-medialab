#include "cv.h"
#include "highgui.h"
#include "stdio.h"
#include <algorithm>
#include <math.h>
#include "dc1394_control.h"

IplImage *imageL = 0, *imageR = 0, *imageBuf = 0;
CvCapture* capture = 0;

int  ideal_int, int_tol, ideal_hue, hue_tol, top_hat_int;
int  l, level = 4;
int  l_comp;

#define STEREO true
#define SHOW_BOTH_WINDOWS true
#define ROI_HALF 50

CvPoint table_center = {336, 236},
        roi_centerL = {410, 270}, roi_centerR = {410, 270},
        roi_2 = {ROI_HALF, ROI_HALF};

CvPoint2D32f cornersL[3], prev_cornersL[3],
             cornersR[3], prev_cornersR[3];  // LED triangle corners on the image

float M_data[4][4] = { {0.76537,    0.47926,  0.45804, -114.63},
                       {0.57352,   -0.57671, -0.65950,  123.04},
                       {0.0068819,  0.62096, -0.43108,  162.72},
                       {0,          0,        0,        1} };
Matrix4x4 coord_trans_4x4(M_data);

int corner_ctr[3]; // number of img points belonging to a corner (for averaging)

Point headPosition, lookVector; // actual 3D points

raw1394handle_t rh; // firewire camera handle
nodeid_t* nid; // camera node ids array

int intensity[ROI_HALF*2][ROI_HALF*2], hue[ROI_HALF*2][ROI_HALF*2]; // buffers;

using namespace std;

bool in_vicinity_or_null(CvPoint pt1, CvPoint pt2, int vic_dist = 10)
{
    return ( (pt1.x > pt2.x - vic_dist && pt1.x < pt2.x + vic_dist &&
              pt1.y > pt2.y - vic_dist && pt1.y < pt2.y + vic_dist) || // either in the vicinity
             (pt2.x == 0 && pt2.y == 0) ); // or not assigned

}

int get_intensity(const char* rgb)
{
    return ( (unsigned char)rgb[0] + (unsigned char)rgb[1] + (unsigned char)rgb[2] ) * .333f;
}

int get_hue(const char* rgb)
{
    int r = (unsigned char)rgb[2],
        g = (unsigned char)rgb[1],
        b = (unsigned char)rgb[0];
    int mx = max( r, max(g, b) ),
        mn = min( r, min(g, b) );

    if (mx == mn) return 0;
    if (mx == r) return (int)(60 * (float)(g-b) / (mx-mn) + 360) % 360;
    if (mx == g) return (int)(60 * (float)(b-r) / (mx-mn) + 120);
    if (mx == b) return (int)(60 * (float)(r-g) / (mx-mn) + 240);
}

void copy_pixel(char* dst, float val)
{
    dst[0] = val; dst[1] = val; dst[2] = val;
}

void copy_pixel(char* dst, char* src, float factor = 1)
{
    dst[0] = src[0] * factor;
    dst[1] = src[1] * factor;
    dst[2] = src[2] * factor;
}

void filter_image(IplImage *src, IplImage *dst, int xs, int xe, int ys, int ye)
{
    int th_rad_o = 5, th_rad_i = 1, // top hat filter radii
        nx_e, nx_s, ny_e, ny_s,
        avg_i, avg_o, avg_i_ctr, avg_o_ctr,
        max_i, min_o,
        th_hue_tol = 15;

    for (int y = ys; y < ye; y++)
        for (int x = xs; x < xe; x++)
        {
            intensity[y-ys][x-xs] = get_intensity(&src->imageData[y*src->width*3 + x*3]);
            hue[y-ys][x-xs] = get_hue(&src->imageData[y*src->width*3 + x*3]);
        }

    for (int y = ys; y < ye; y++)
        for (int x = xs; x < xe; x++)
        {
            ny_s = max(ys, y - th_rad_o); ny_e = min(ye, y + th_rad_o);
            nx_s = max(xs, x - th_rad_o); nx_e = min(xe, x + th_rad_o);
            avg_i = avg_o = avg_i_ctr = avg_o_ctr = 0;
            max_i = 0; min_o = 255;
            for (int ny = ny_s; ny < ny_e; ny++)
                for (int nx = nx_s; nx < nx_e; nx++)
                    if (abs(nx-x) + abs(ny-y) < th_rad_i) // nearer neighbors
                    {
                        max_i = max( max_i, intensity[ny-ys][nx-xs] );
                        avg_i += hue[ny-ys][nx-xs];
                        avg_i_ctr++;
                    }
                    else
                    {
                        min_o = min( min_o, intensity[ny-ys][nx-xs] );
                        /*avg_o += get_intensity(&src->imageData[ny*src->width*3 + nx*3]);
                        avg_o_ctr++;*/
                    }

            if (avg_i_ctr != 0)
                avg_i /= avg_i_ctr;
            //if ( max_i - min_o > top_hat_int )
            if ( (avg_i > 60 - th_hue_tol && avg_i < 60 + th_hue_tol) && min_o < 30 && max_i > ideal_int)
                copy_pixel(&dst->imageData[y*src->width*3 + x*3], &src->imageData[y*src->width*3 + x*3]);
            else
                copy_pixel(&dst->imageData[y*src->width*3 + x*3], 40.f);
        }

    for (int y = ys; y < ye; y++)
        for (int x = xs; x < xe; x++)
            copy_pixel(&src->imageData[y*src->width*3 + x*3], &dst->imageData[y*src->width*3 + x*3]);
}

void apply_threshold(IplImage *src, IplImage* dst,
                     CvPoint& roi_center, CvPoint2D32f* corners, CvPoint2D32f* prev_corners,
                     char* window_name)
{
    int i;
    // init corners:
    for (i=0; i<3; i++)
    {
        corners[i] = cvPoint2D32f(0, 0);
        corner_ctr[i] = 0;
    }

    CvSize src_size, dst_size;

    uchar *src_data = 0;
    uchar *dst_data = 0;
    int src_step = 0, dst_step = 0;
    int intensity, hue;
   /* cvGetRawData( image[0], &src_data, &src_step, &src_size );
    cvGetRawData( image[1], &dst_data, &dst_step, &dst_size );
*/
    int y_start = max(0, roi_center.y - roi_2.y),
        y_end = min(src->height, roi_center.y + roi_2.y),
        x_start = max(0, roi_center.x - roi_2.x),
        x_end = min(src->width, roi_center.x + roi_2.x);

    filter_image(src, dst, x_start, x_end, y_start, y_end);

    for (int y = y_start; y < y_end; y++)
        for (int x = x_start; x < x_end; x++)
        {
            intensity = get_intensity( &src->imageData[y*src->width*3 + x*3] );
            if (intensity > ideal_int - int_tol && intensity < ideal_int + int_tol &&
                (hue = get_hue(&src->imageData[y*src->width*3 + x*3])) > ideal_hue - hue_tol && hue < ideal_hue + hue_tol )
            {
                dst->imageData[y*src->width*3 + x*3 + 0] = 255;
                dst->imageData[y*src->width*3 + x*3 + 1] = 255;
                dst->imageData[y*src->width*3 + x*3 + 2] = 255;
                for (i=0; i<3; i++)
                    // if in vicinity or null, assign by online averaging
                    if ( in_vicinity_or_null(cvPoint(x, y), cvPointFrom32f(corners[i])) &&
                         in_vicinity_or_null(cvPoint(x, y), cvPointFrom32f(prev_corners[i]), 20) )
                    {
                        // on line averaging:
                        corners[i] = cvPoint2D32f((corners[i].x * corner_ctr[i] + x) / (corner_ctr[i]+1),
                                                  (corners[i].y * corner_ctr[i] + y) / (corner_ctr[i]+1));
                        corner_ctr[i] = corner_ctr[i] + 1; // increment # img points
                        //printf("%d\t%d\t-\t%d\t%d\n", i, corner_ctr[i], corners[i].x, corners[i].y);
                        break;
                    }
            }
            else
            {
                dst->imageData[y*src->width*3 + x*3 + 0] = 0;
                dst->imageData[y*src->width*3 + x*3 + 1] = 0;
                dst->imageData[y*src->width*3 + x*3 + 2] = 0;
            }
        }

    //printf("%3.2f %3.2f %3.2f\n", corners[0].x, corners[1].x, corners[2].x);
    for (i=0; i<3; i++)
    {
        if (corners[i].x > 0)
            prev_corners[i] = corners[i];
        else
            corners[i] = prev_corners[i];
    }

    for (i=0; i<3; i++)
        cvLine( dst, cvPointFrom32f(corners[i]), cvPointFrom32f(corners[(i+1)%3]), CV_RGB( 255*(i==2), 255*(i==1), 255*(i==0) ), 1, CV_AA, 0 );

    roi_center = cvPoint( (corners[0].x+corners[1].x+corners[2].x) * 0.3333f,
                          (corners[0].y+corners[1].y+corners[2].y) * 0.3333f );

    //cvLine( dst, roi_center, table_center, CV_RGB(255,255,255), 1, CV_AA, 0 );

    /*cvPyrSegmentation(image0, image1, storage, &comp,
                      level, threshold1+1, threshold2+1);
*/

    /*l_comp = comp->total;

    i = 0;
    min_comp.value = cvScalarAll(0);
    while(i<l_comp)
    {
        cur_comp = (CvConnectedComp*)cvGetSeqElem ( comp, i );
        if(fabs(255- min_comp.value.val[0])>
           fabs(255- cur_comp->value.val[0]) &&
           fabs(min_comp.value.val[1])>
           fabs(cur_comp->value.val[1]) &&
           fabs(min_comp.value.val[2])>
           fabs(cur_comp->value.val[2]) )
           min_comp = *cur_comp;
        i++;
    }*/

    if (window_name == "MediaLab Demo" || SHOW_BOTH_WINDOWS)
        cvShowImage(window_name, dst);
}

void on_mouseL( int event, int x, int y, int flags, void* param )
{
    if( !imageL ) return;

    if( imageL->origin ) y = imageL->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        roi_centerL = cvPoint(x,y);
        roi_centerR = cvPoint(x-5,y);

        for (int i=0; i<3; i++)
            prev_cornersL[i] = cvPoint2D32f(0, 0);
    }
}

void on_mouseR( int event, int x, int y, int flags, void* param )
{
    if( !imageR ) return;

    if( imageR->origin ) y = imageL->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        roi_centerR = cvPoint(x,y);
        roi_centerL = cvPoint(x+5,y);

        for (int i=0; i<3; i++)
            prev_cornersR[i] = cvPoint2D32f(0, 0);
    }
}

void on_trackbar(int foo)
{
    cvCopy( imageL, imageBuf, 0 );
    apply_threshold(imageL, imageBuf, roi_centerL, cornersL, prev_cornersL, "MediaLab Demo");
}

void check_fiwi_camera();

void init_fiwi_camera()
{
    rh = dc1394_create_handle( 0 );
    int num_cam;
    nid = dc1394_get_camera_nodes(rh, &num_cam, 0);
    printf("Video Set: %d - %d\n", dc1394_set_video_format(rh, *nid, COLOR_FORMAT7_RAW16), DC1394_SUCCESS);

    capture = cvCaptureFromCAM( CV_CAP_ANY );

    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        return;
    }

    /* print a welcome message, and the OpenCV version */
    printf ("Welcome to MediaLab head tracking demo, using OpenCV version %s (%d.%d.%d).\n",
             CV_VERSION, CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

    printf( "\tPress ESC to quit the program\n" );

    ideal_int = 140;
    int_tol = 90;
    ideal_hue = 60;
    hue_tol = 30;
    top_hat_int = 90;

    cvNamedWindow( "MediaLab Demo", CV_WINDOW_AUTOSIZE );
    if (STEREO && SHOW_BOTH_WINDOWS)
        cvNamedWindow( "MediaLab Demo - R", CV_WINDOW_AUTOSIZE );
    cvCreateTrackbar("Ideal Intensity", "MediaLab Demo", &ideal_int, 255, on_trackbar);
    cvCreateTrackbar("Intensity Tol.", "MediaLab Demo", &int_tol, 50, on_trackbar);
    cvCreateTrackbar("Ideal Hue", "MediaLab Demo", &ideal_hue, 360, on_trackbar);
    cvCreateTrackbar("Hue Tol.", "MediaLab Demo", &hue_tol, 30, on_trackbar);
    cvCreateTrackbar("Top-Hat Intensity Threshold", "MediaLab Demo", &top_hat_int, 255, on_trackbar);

    cvSetMouseCallback( "MediaLab Demo", on_mouseL, 0 );
    if (STEREO && SHOW_BOTH_WINDOWS)
        cvSetMouseCallback( "MediaLab Demo - R", on_mouseR, 0 );

    cvWaitKey(10);
}

void check_fiwi_camera()
{
    int k, c;

    if (dc1394_set_pan(rh, nid[0], 1) == DC1394_SUCCESS)
    {
        freopen("dump.txt", "a+", stdout); // surpassing highgui's "icvRetrieveFrame.." message
        imageL = cvQueryFrame( capture );
        stdout = fopen("/dev/tty", "w"); // and we're.. back
    }
    else
        printf("(!) Couldn't apply panning.\n");

    if( !imageL )
    {
        printf("(!) Couldn't get the frame.\n");
        return;
    }

    if( !imageBuf )
    {
        cvResizeWindow("MediaLab Demo", imageL->width, imageL->height + 230);
        cvMoveWindow("MediaLab Demo", 1024, 0);

        imageBuf = cvCreateImage( cvGetSize(imageL), 8, 3 );
    }

    cvCopy( imageL, imageBuf, 0 );

    apply_threshold(imageL, imageBuf, roi_centerL, cornersL, prev_cornersL, "MediaLab Demo");

    sleep(0.033); // to prevent stereo panning glitches (?)

    if (STEREO)
    {
        if (dc1394_set_pan(rh, nid[0], 0) == DC1394_SUCCESS )
        {
            freopen("dump.txt", "a+", stdout); // surpassing highgui's "icvRetrieveFrame.." message
            imageR = cvQueryFrame( capture );
            stdout = fopen("/dev/tty", "w"); // and we're.. back
        }

        if (!imageR)
            return;

        cvCopy( imageR, imageBuf, 0 );
        apply_threshold(imageR, imageBuf, roi_centerR, cornersR, prev_cornersR, "MediaLab Demo - R");
    }

    c = cvWaitKey(500); // wait for processing
}

void release_camera()
{
    cvReleaseImage(&imageL);
    cvReleaseImage(&imageR);
    cvReleaseImage(&imageBuf);

    dc1394_destroy_handle(rh);
    cvReleaseCapture( &capture );
    cvDestroyWindow("MediaLab Demo");
    if (STEREO && SHOW_BOTH_WINDOWS)
        cvDestroyWindow("MediaLab Demo - R");
}
