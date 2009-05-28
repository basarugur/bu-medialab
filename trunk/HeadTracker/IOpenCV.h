///-----------------------------------------------------------------------------
///
/// \file	IOpenCV.h
/// \author	Basar Ugur
/// \brief	Image porocessing interface using OpenCV library,
///         mainly used for tracking LEDs by Optical Flow algorithm
/// \note
///-----------------------------------------------------------------------------

#include "cv.h"
#include "highgui.h"

#define TABLE_SCREEN_CENTER cvPoint(336, 236)
#define STEREO true

using namespace std;

int ideal_int, int_tol, ideal_hue, hue_tol, top_hat_int, gain = 100;

IplImage *imageL, *imageR, //*imageBuf,
         *grey = 0, *prev_greyL = 0, *prev_greyR = 0,
         *pyramid = 0, *prev_pyramidL = 0, *prev_pyramidR = 0,
         *swap_temp;

CvPoint         roi_centerL, roi_centerR, roi_2;

CvPoint2D32f    cornersL[3], prev_cornersL[3],
                cornersR[3], prev_cornersR[3]; // triangle points

CvVideoWriter   *videoWriterL = NULL,
                *videoWriterR = NULL; // for saving videos of the frames.

int corner_ctr[3];                          // number of img points belonging to a corner (for averaging)
int new_crn_idxL = 0, new_crn_idxR = 0,     // new corner indices to be added to the system
    flags = 0;                              // optical flow algorithm function flags
char status[3];                             // optical flow algorithm point tracking status (bad==0 / good>0)
const CvSize win_size = {10, 10};           // optical flow algorithm window size

class IOpenCV // OpenCV interface
{
public:
    int w0, h0, image_ctr;

    CvSize frame_size;

    IOpenCV(CvSize _frame_size)
    {
        frame_size = _frame_size;

        imageL = imageR = 0; // imageBuf = 0;

        image_ctr = 0;
        roi_centerL = cvPoint(410, 270);
        roi_centerR = cvPoint(410, 270),
        roi_2 = cvPoint(50, 50);

        ideal_int = 200;
        int_tol = 50;
        ideal_hue = 60;
        hue_tol = 30;
        top_hat_int = 90;

        // print a welcome message, and the OpenCV version
        printf ("Welcome to MediaLab head tracking demo, using OpenCV version %s (%d.%d.%d).\n",
                 CV_VERSION, CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

        printf( "\tPress ESC to quit the program\n" );

        // allocate all the buffers
        // imageL = cvCreateImage( cvGetSize(frame), 8, 3 );
        imageL = cvCreateImage( frame_size, 8, 3 );
        imageL->origin = 0; // frame->origin;

        imageR = cvCreateImage( frame_size, 8, 3 );
        imageR->origin = 0 ; // frame2->origin;
        // imageBuf = cvCreateImage( frame_size, 8, 3 );

        // LK flow related initializations:
        grey = cvCreateImage( frame_size, 8, 1 );
        prev_greyL = cvCreateImage( frame_size, 8, 1 );
        prev_greyR = cvCreateImage( frame_size, 8, 1 );
        pyramid = cvCreateImage( frame_size, 8, 1 );
        prev_pyramidL = cvCreateImage( frame_size, 8, 1 );
        prev_pyramidR = cvCreateImage( frame_size, 8, 1 );

        cvNamedWindow( "MediaLab Demo - L", CV_WINDOW_AUTOSIZE );
        cvMoveWindow("MediaLab Demo - L", 0, 768);
        if (STEREO)
        {
            cvNamedWindow( "MediaLab Demo - R", CV_WINDOW_AUTOSIZE );
            cvMoveWindow("MediaLab Demo - R", 100, 868);
        }
        /*
        cvCreateTrackbar("Ideal Intensity", "MediaLab Demo - L", &ideal_int, 255, on_trackbar);
        cvCreateTrackbar("Intensity Tol.", "MediaLab Demo - L", &int_tol, 90, on_trackbar);
        cvCreateTrackbar("Ideal Hue", "MediaLab Demo - L", &ideal_hue, 360, on_trackbar);
        cvCreateTrackbar("Hue Tol.", "MediaLab Demo - L", &hue_tol, 30, on_trackbar);
        cvCreateTrackbar("Top-Hat Intensity Threshold", "MediaLab Demo - L", &top_hat_int, 255, on_trackbar);
        */
        cvCreateTrackbar("Gain", "MediaLab Demo - L", &gain, 500, on_trackbar);

        cvSetMouseCallback( "MediaLab Demo - L", on_mouseL, 0 );
        if (STEREO)
            cvSetMouseCallback( "MediaLab Demo - R", on_mouseR, 0 );
    };

    ~IOpenCV()
    {
        cvReleaseImage(&imageL);
        cvReleaseImage(&imageR);
        // cvReleaseImage(&imageBuf);
        cvReleaseImage(&grey);
        cvReleaseImage(&prev_greyL);
        cvReleaseImage(&prev_greyR);
        cvReleaseImage(&pyramid);
        cvReleaseImage(&prev_pyramidL);
        cvReleaseImage(&prev_pyramidR);

        cvDestroyWindow("MediaLab Demo - L");
        if (STEREO)
            cvDestroyWindow("MediaLab Demo - R");
    };

    static bool in_vicinity_or_null(CvPoint pt1, CvPoint pt2, int vic_dist = 10)
    {
        return ( (pt1.x > pt2.x - vic_dist && pt1.x < pt2.x + vic_dist &&
                  pt1.y > pt2.y - vic_dist && pt1.y < pt2.y + vic_dist) || // either in the vicinity
                 (pt2.x == 0 && pt2.y == 0) ); // or not assigned

    }

    static int get_intensity(const char* rgb)
    {
        return ( (unsigned char)rgb[0] + (unsigned char)rgb[1] + (unsigned char)rgb[2] ) * .333f;
    }

    static int get_hue(const char* rgb)
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

    static void copy_pixel(char* dst, float val)
    {
        dst[0] = val; dst[1] = val; dst[2] = val;
    }

    static void copy_pixel(char* dst, char* src, float factor = 1)
    {
        dst[0] = src[0] * factor;
        dst[1] = src[1] * factor;
        dst[2] = src[2] * factor;
    }

    static void filter_image(IplImage *src, IplImage *dst, int xs, int xe, int ys, int ye)
    {
        int th_rad_o = 4, th_rad_i = 2, // top hat filter radii
            nx_e, nx_s, ny_e, ny_s,
            avg_i, avg_o, avg_i_ctr, avg_o_ctr,
            max_i, min_o,
            th_hue_tol = 15;
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
                            //max_i = max( max_i, get_intensity(&src->imageData[ny*src->width*3 + nx*3]) );
                            avg_i += get_hue(&src->imageData[ny*src->width*3 + nx*3]);
                            avg_i_ctr++;
                        }
                        else
                        {
                            min_o = min( min_o, get_intensity(&src->imageData[ny*src->width*3 + nx*3]) );
                            /*avg_o += get_intensity(&src->imageData[ny*src->width*3 + nx*3]);
                            avg_o_ctr++;*/
                        }

                avg_i /= avg_i_ctr ;
                //if ( max_i - min_o > top_hat_int )
                if ( (avg_i > 60 - th_hue_tol && avg_i < 60 + th_hue_tol) && min_o < 30 )
                    copy_pixel(&dst->imageData[y*src->width*3 + x*3], &src->imageData[y*src->width*3 + x*3]);
                else
                    copy_pixel(&dst->imageData[y*src->width*3 + x*3], 40.f);
            }

        for (int y = ys; y < ye; y++)
            for (int x = xs; x < xe; x++)
                copy_pixel(&src->imageData[y*src->width*3 + x*3], &dst->imageData[y*src->width*3 + x*3]);
    }

    static void apply_threshold(IplImage *src, IplImage* dst,
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
            cvLine( dst, cvPointFrom32f(corners[i]), cvPointFrom32f(corners[(i+1)%3]), CV_RGB( 255*(i==0), 255*(i==1), 255*(i==2) ), 1, CV_AA, 0 );

        roi_center = cvPoint( (corners[0].x+corners[1].x+corners[2].x) * 0.3333f,
                              (corners[0].y+corners[1].y+corners[2].y) * 0.3333f );

      //  cvLine( dst, roi_center, TABLE_SCREEN_CENTER, CV_RGB(255,255,255), 1, CV_AA, 0 );

        cvShowImage(window_name, dst);
    }

    static void on_mouseL( int event, int x, int y, int flags, void* param )
    {
        if( !imageL ) return;

        if( imageL->origin ) y = imageL->height - y;

        if( event == CV_EVENT_LBUTTONDOWN )
        {
            /* roi_centerL = cvPoint(x,y);
            for (int i=0; i<3; i++)
                prev_cornersL[i] = cvPoint2D32f(0, 0);*/
            cornersL[new_crn_idxL] = prev_cornersL[new_crn_idxL] = cvPoint2D32f(x, y);
            new_crn_idxL = (++new_crn_idxL)%3;
        }
    }

    static void on_mouseR( int event, int x, int y, int flags, void* param )
    {
        if( !imageR ) return;

        if( imageR->origin ) y = imageL->height - y;

        if( event == CV_EVENT_LBUTTONDOWN )
        {
            /*roi_centerR = cvPoint(x,y);
            for (int i=0; i<3; i++)
                prev_cornersR[i] = cvPoint2D32f(0, 0);*/
            cornersR[new_crn_idxR] = prev_cornersR[new_crn_idxR] = cvPoint2D32f(x, y);
            new_crn_idxR = (++new_crn_idxR)%3;
        }
    }

    static void on_trackbar(int foo)
    {
        // cvCopy( imageL, imageBuf, 0 );
        // apply_threshold(imageL, imageBuf, roi_centerL, cornersL, prev_cornersL, "MediaLab Demo - L");
    }

    bool process_images(uint8_t *left_image, uint8_t *right_image)
    {
        int k, c;

        CvVideoWriter* cvCreateVideoWriter( const char* filename, int fourcc, double fps, CvSize frame_size, int is_color = 1 );

        imageL->imageData = (char*)left_image; // copy left image

        // cvCopy( imageL, imageBuf, 0 );
        // apply_threshold(imageL, imageBuf, roi_centerL, cornersL, prev_cornersL, "MediaLab Demo - L");
        cvCvtColor( imageL, grey, CV_BGR2GRAY );
        cvCalcOpticalFlowPyrLK( prev_greyL, grey, prev_pyramidL, pyramid,
                                prev_cornersL, cornersL, 3, win_size, 3, status, 0,
                                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
        flags |= CV_LKFLOW_PYR_A_READY;
        for( k = 0; k < 3; k++ )
        {
            if( !status[k] )
                continue;

            cvCircle( imageL, cvPointFrom32f(cornersL[k]), 3, CV_RGB(255*(k==0), 255*(k==1), 255*(k==2)), -1, 8,0);
            prev_cornersL[k] = cornersL[k];
        }
        cvShowImage("MediaLab Demo - L", imageL);
        CV_SWAP( prev_greyL, grey, swap_temp );
        CV_SWAP( prev_pyramidL, pyramid, swap_temp );

        if (STEREO)
        {
//           if (dc1394_set_pan(rh, nid[0], 0) == DC1394_SUCCESS )
//           frame2 = cvQueryFrame( capture );
//
//           if (!frame2)
//              break;
//
//           cvCopy( frame2, imageR, 0 );
            imageR->imageData = (char*)right_image; // copy right image

            cvCvtColor( imageR, grey, CV_BGR2GRAY );
            cvCalcOpticalFlowPyrLK( prev_greyR, grey, prev_pyramidR, pyramid,
                                    prev_cornersR, cornersR, 3, win_size, 3, status, 0,
                                    cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
            flags |= CV_LKFLOW_PYR_A_READY;
            for( k = 0; k < 3; k++ )
            {
                if( !status[k] )
                    continue;

                cvCircle( imageR, cvPointFrom32f(cornersR[k]), 3, CV_RGB(255*(k==0), 255*(k==1), 255*(k==2)), -1, 8,0);
                prev_cornersR[k] = cornersR[k];
            }
            cvShowImage("MediaLab Demo - R", imageR);

            CV_SWAP( prev_greyR, grey, swap_temp );
            CV_SWAP( prev_pyramidR, pyramid, swap_temp );

            // cvCopy( imageR, imageBuf, 0 );
            // apply_threshold(imageR, imageBuf, roi_centerR, cornersR, prev_cornersR, "MediaLab Demo - R");
        }

        // if user started saving videos, save current image.
        if (videoWriterL != NULL)
            cvWriteFrame(videoWriterL, imageL);
        if (STEREO && videoWriterR != NULL)
            cvWriteFrame(videoWriterR, imageR);

        c = cvWaitKey(10);
        if( (char)c == 27 )
            return false; // EXIT
        else if ((char)c == 's' || (char)c == 'S')
        {   // save
            char fName[32];
            sprintf(fName, "points-%03.0f-L.jpg", (float)(++image_ctr));
            cvSaveImage(fName, imageL);
//            fprintf(fptr, "points-%03.0f-L.jpg: %01.2f %01.2f, %01.2f %01.2f, %01.2f %01.2f\n",
//                    (float)image_ctr,
//                    cornersL[0].x, cornersL[0].y, cornersL[1].x, cornersL[1].y, cornersL[2].x, cornersL[2].y);

            if (STEREO)
            {
                sprintf(fName, "points-%03.0f-R.jpg", (float)(image_ctr));
                cvSaveImage(fName, imageR);
//                fprintf(fptr, "points-%03.0f-R.jpg: %01.2f %01.2f, %01.2f %01.2f, %01.2f %01.2f\n",
//                        (float)image_ctr,
//                        cornersR[0].x, cornersR[0].y, cornersR[1].x, cornersR[1].y, cornersR[2].x, cornersR[2].y);
            }
            return true;
        }
        else if ((char)c == 'v' || (char)c == 'V') // Start / stop saving video
        {
            if (videoWriterL == NULL) // if null, create.
                videoWriterL = cvCreateVideoWriter( "left.avi", CV_FOURCC('D','I','V','X'), 25,
                                                    cvSize(640, 480), 1 );
            else
            {
                cvReleaseVideoWriter(&videoWriterL);
                videoWriterL = NULL;
            }

            // Do the same for the right frame;
            if (STEREO)
            {
                if (videoWriterR == NULL) // if null, create
                    videoWriterR = cvCreateVideoWriter( "right.avi", CV_FOURCC('D','I','V','X'), 25,
                                                        cvSize(640, 480), 1 );
                else
                {
                    cvReleaseVideoWriter(&videoWriterR);
                    videoWriterR = NULL;
                }
            }
        }

        return true;
    }
};
