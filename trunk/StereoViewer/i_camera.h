#include "cv.h"
#include "highgui.h"
#include "stdio.h"
#include <algorithm>
#include <math.h>
//#include "dc1394_control.h"

#define TABLE_SCREEN_CENTER cvPoint(325, 400)

IplImage *image0 = 0, *image1 = 0, *image2 = 0;
CvCapture* capture = 0;
CvSize size;

int  w0, h0,i;
int  ideal_int, int_tol, ideal_hue, hue_tol;
int  l,level = 4;
int  l_comp;
int block_size = 1000;
float  parameter;
double rezult, min_rezult;
CvFilter filter = CV_GAUSSIAN_5x5;
CvConnectedComp *cur_comp, min_comp;
CvSeq *comp;
CvMemStorage *storage;

CvPoint roi_center = {410, 270},
        roi_2 = {50, 50};
CvPoint2D32f corners[3], prev_corners[3];  // triangle points
int corner_ctr[3];        // number of img points belonging to a corner (for averaging)

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

void ON_SEGMENT(int a)
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
        y_end = min(image0->height, roi_center.y + roi_2.y),
        x_start = max(0, roi_center.x - roi_2.x),
        x_end = min(image0->width, roi_center.x + roi_2.x);

    for (int y = y_start; y < y_end; y++)
        for (int x = x_start; x < x_end; x++)
        {
            intensity = get_intensity( &image0->imageData[y*image0->width*3 + x*3] );
            if (intensity > ideal_int - int_tol && intensity < ideal_int + int_tol &&
                (hue = get_hue(&image0->imageData[y*image0->width*3 + x*3])) > ideal_hue - hue_tol && hue < ideal_hue + hue_tol )
            {
                image1->imageData[y*image0->width*3 + x*3 + 0] = 255;
                image1->imageData[y*image0->width*3 + x*3 + 1] = 255;
                image1->imageData[y*image0->width*3 + x*3 + 2] = 255;
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
                image1->imageData[y*image0->width*3 + x*3 + 0] = 0;
                image1->imageData[y*image0->width*3 + x*3 + 1] = 0;
                image1->imageData[y*image0->width*3 + x*3 + 2] = 0;
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
        cvLine( image1, cvPointFrom32f(corners[i]), cvPointFrom32f(corners[(i+1)%3]), CV_RGB( 255*(i==0), 255*(i==1), 255*(i==2) ), 1, CV_AA, 0 );

    roi_center = cvPoint( (corners[0].x+corners[1].x+corners[2].x) * 0.3333f,
                          (corners[0].y+corners[1].y+corners[2].y) * 0.3333f );

    cvLine( image1, roi_center, TABLE_SCREEN_CENTER, CV_RGB(255,255,255), 1, CV_AA, 0 );

    cvShowImage("MediaLab Demo", image1);
}

void on_mouse( int event, int x, int y, int flags, void* param )
{
    if( !image0 )
        return;

    if( image0->origin )
        y = image0->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        roi_center = cvPoint(x,y);
        for (i=0; i<3; i++)
            prev_corners[i] = cvPoint2D32f(0, 0);
    }
}

void init_fiwi_camera()
{
    /*raw1394handle_t rh = dc1394_create_handle( 0 );
    int num_cam;
    nodeid_t* nid = dc1394_get_camera_nodes(rh, &num_cam, 0);*/

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

    ideal_int = 200;
    int_tol = 30;
    ideal_hue = 60;
    hue_tol = 30;

    cvNamedWindow( "MediaLab Demo", CV_WINDOW_AUTOSIZE );
    //cvNamedWindow( "MediaLab Demo - Right Frame", CV_WINDOW_AUTOSIZE );
    cvCreateTrackbar("Ideal Intensity", "MediaLab Demo", &ideal_int, 255, ON_SEGMENT);
    cvCreateTrackbar("Intensity Tol.", "MediaLab Demo", &int_tol, 50, ON_SEGMENT);
    cvCreateTrackbar("Ideal Hue", "MediaLab Demo", &ideal_hue, 360, ON_SEGMENT);
    cvCreateTrackbar("Hue Tol.", "MediaLab Demo", &hue_tol, 30, ON_SEGMENT);

    cvSetMouseCallback( "MediaLab Demo", on_mouse, 0 );
}

void check_camera()
{
    IplImage *frame = 0, *frame2 = 0;
    int k, c;

    /*if (dc1394_set_pan(rh, nid[0], 0) == DC1394_SUCCESS )
    {
        frame2 = cvQueryFrame( capture );
        if (frame2)
            cvShowImage("MediaLab Demo - Right Frame", frame2);
    }
    sleep(0.033);*/
    //if (dc1394_set_pan(rh, nid[0], 1) == DC1394_SUCCESS)
    frame = cvQueryFrame( capture );

    if( !frame )
        return;

    if( !image0 )
    {
        // allocate all the buffers
        image0 = cvCreateImage( cvGetSize(frame), 8, 3 );
        cvResizeWindow("MediaLab Demo", image0->width, image0->height + 190);
        cvMoveWindow("MediaLab Demo", 1024, 0);
        image0->origin = frame->origin;
        image1 = cvCreateImage( cvGetSize(frame), 8, 3 );
    }

    cvCopy( frame, image0, 0 );
    cvCopy( image0, image1, 0 );

    ON_SEGMENT(1);

    cvWaitKey(10);
}

void release_camera()
{
    cvReleaseImage(&image0);
    cvReleaseImage(&image1);

    //dc1394_destroy_handle(rh);
    cvReleaseCapture( &capture );
    cvDestroyWindow("MediaLab Demo");
}
