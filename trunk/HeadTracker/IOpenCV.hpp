///-----------------------------------------------------------------------------
///
/// \file	IOpenCV.h
/// \author	Basar Ugur
/// \brief	Image processing interface using OpenCV library,
///         mainly used for tracking LEDs by Optical Flow algorithm
/// \note
///-----------------------------------------------------------------------------

#include "cv.h"
#include "highgui.h"
#include <vector>
#include <algorithm>

#define MAX_CORNER 3

#define STEREO true

#define max3(a,b,c) a>b?(a>c?a:c):(b>c?b:c)

using namespace std;

int ideal_int, int_tol, ideal_hue, hue_tol, top_hat_int;

extern int gain;

IplImage *imageL, *imageR,
         *imageLShow, *imageRShow,
         *grey = 0, *prev_greyL = 0, *prev_greyR = 0,
         *pyramid = 0, *prev_pyramidL = 0, *prev_pyramidR = 0,
         *swap_temp;

CvSize          roi_size;

CvPoint2D32f    cornersL[MAX_CORNER], prev_cornersL[MAX_CORNER],
                cornersR[MAX_CORNER], prev_cornersR[MAX_CORNER]; // triangle points

CvVideoWriter   *videoWriterL = NULL,
                *videoWriterR = NULL; // for saving videos of the frames.

int corner_ctr[3];                          // number of img points belonging to a corner (for averaging)
int new_crn_idxL = 0, new_crn_idxR = 0,     // new corner indices to be added to the system
    flags = 0;                              // optical flow algorithm function flags
char status[3];                             // optical flow algorithm point tracking status (bad==0 / good>0)
const CvSize win_size = {10, 10};           // optical flow algorithm window size

enum trigger
{
    t_none = 0,
    t_left = 1,
    t_right = 2
};

struct simple_event
{
    trigger flag;
    int x, y;
};

simple_event reset_corners;

bool comp_CvPoint2D32f( CvPoint2D32f p1, CvPoint2D32f p2 )
{
    if ( fabs(p1.y-p2.y) < 10 )
        return ( p1.x < p2.x );
    else
        return ( p1.y < p2.y );
}

/**
*   OpenCV library interface
*/
class IOpenCV
{
public:
    int w0, h0, image_ctr;

    CvSize frame_size;

    IOpenCV(CvSize _frame_size)
    {
        frame_size = _frame_size;

        imageL = imageR = 0; // imageBuf = 0;

        image_ctr = 0;

        roi_size = cvSize(100, 100);

        ideal_int = 200;
        int_tol = 50;
        ideal_hue = 60;
        hue_tol = 30;
        top_hat_int = 90;

        reset_corners.flag = t_none;

        // print a welcome message, and the OpenCV version
        printf ("Welcome to MediaLab head tracking demo, using OpenCV version %s (%d.%d.%d).\n",
                 CV_VERSION, CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

        printf( "\tPress ESC to quit the program\n" );

        // allocate all the buffers
        imageL = cvCreateImage( frame_size, 8, 3 );
        imageL->origin = 0; // frame->origin;
        imageLShow = cvCreateImage( frame_size, 8, 3 );

        imageR = cvCreateImage( frame_size, 8, 3 );
        imageR->origin = 0 ; // frame2->origin;
        imageRShow = cvCreateImage( frame_size, 8, 3 );

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

        cvDestroyAllWindows();
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

    static void sort_corners( CvPoint2D32f* corners, CvPoint2D32f* prev_corners )
    {
        vector<CvPoint2D32f> tp;

        for (int c=0; c<MAX_CORNER; c++)
            tp.push_back( corners[c] );

        sort( tp.begin(), tp.end(), comp_CvPoint2D32f );

        for (int c=0; c<MAX_CORNER; c++)
        {
            cout << "T " << c << ": " << tp[c].x << ", " << tp[c].y << endl;
            prev_corners[c] = corners[c] = tp[c];
        }
    }

    static void find_corners( IplImage* im, CvPoint roi_center,
                              CvPoint2D32f* corners, CvPoint2D32f* prev_corners )
    {

        IplImage *src = cvCreateImage( roi_size, 8, 1 );

        int y_start = max(0, roi_center.y - roi_size.height/2),
            y_end = min(im->height, roi_center.y + roi_size.height/2),
            x_start = max(0, roi_center.x - roi_size.width/2),
            x_end = min(im->width, roi_center.x + roi_size.width/2);

        printf("Limits: %d %d %d %d\n", y_start, y_end, x_start, x_end);

        for (int i=y_start; i<y_end; i++)
            for (int j=x_start; j<x_end; j++)
            {
                src->imageData[(i-y_start) * src->widthStep + (j-x_start)] =
                    max3( (unsigned char)(im->imageData[i * im->widthStep + j*3 ]),
                          (unsigned char)(im->imageData[i * im->widthStep + j*3 + 1]) ,
                          (unsigned char)(im->imageData[i * im->widthStep + j*3 + 2]) );
            }

        IplImage* eig = cvCreateImage( roi_size, 32, 1 );
        IplImage* temp = cvCreateImage( roi_size, 32, 1 );
        double quality = 0.01;
        double min_distance = 10;

        int count = MAX_CORNER;
        cvGoodFeaturesToTrack( src, eig, temp, corners, &count,
                               quality, min_distance, 0, 3, 0, 0.04 );

        for (int i=0; i<3; i++)
        {
            prev_corners[i] = corners[i] = cvPoint2D32f(x_start + corners[i].x, y_start + corners[i].y);

            cout << "C " << i << ": " << corners[i].x << ", " << corners[i].y << endl;
        }

        sort_corners(corners, prev_corners);

        /*FILE* fptr;

        fptr = fopen("dst-r.pgm", "wb");
        fprintf(fptr, "P2\n%d %d\n255\n", src->width, src->height);
        for (int i=0; i<src->height; i++)
        {
            for (int j=0; j<src->width; j++)
                fprintf(fptr, "%d ", (unsigned char)(src->imageData[i * src->widthStep + j]) );
            fprintf(fptr, "\n");
        }

        fclose(fptr);*/

        if (!STEREO || reset_corners.flag == t_right)
        {
            reset_corners.flag = t_none;
        }

        cvReleaseImage(&src);

    }

    static void on_mouseL( int event, int x, int y, int flags, void* param )
    {
        if( !imageL ) return;

        if( imageL->origin )
            y = imageR->height - y;

        if( event == CV_EVENT_MBUTTONDOWN )
        {
            find_corners(imageL, cvPoint(x, y), cornersL, prev_cornersL);

            find_corners(imageR, cvPoint(x - 20, y), cornersR, prev_cornersR);
        }

        if( event == CV_EVENT_LBUTTONDOWN )
        {
            cornersL[new_crn_idxL] = prev_cornersL[new_crn_idxL] = cvPoint2D32f(x, y);
            new_crn_idxL = (++new_crn_idxL)%3;
        }

    }

    static void on_mouseR( int event, int x, int y, int flags, void* param )
    {
        if( !imageR ) return;

        if( imageR->origin )
            y = imageR->height - y;

        if( event == CV_EVENT_MBUTTONDOWN )
        {
            find_corners(imageR, cvPoint(x, y), cornersR, prev_cornersR);

            find_corners(imageL, cvPoint(x + 20, y), cornersL, prev_cornersL);
        }

        if( event == CV_EVENT_LBUTTONDOWN )
        {
            cornersR[new_crn_idxR] = prev_cornersR[new_crn_idxR] = cvPoint2D32f(x, y);
            new_crn_idxR = (++new_crn_idxR)%3;
        }
    }

    static void on_trackbar(int foo)
    {

    }

    bool process_images(uint8_t *left_image, uint8_t *right_image)
    {
        int k, c;

        CvVideoWriter* cvCreateVideoWriter( const char* filename, int fourcc, double fps, CvSize frame_size, int is_color = 1 );

        /// copy left image
        imageL->imageData = (char*)left_image;
        cvCopy( imageL, imageLShow, 0 );

        /// convert to gray scale
        cvCvtColor( imageL, grey, CV_BGR2GRAY );

        /// calculate optical flow by previous frame
        cvCalcOpticalFlowPyrLK( prev_greyL, grey, prev_pyramidL, pyramid,
                                prev_cornersL, cornersL, 3, win_size, 3, status, 0,
                                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
        flags |= CV_LKFLOW_PYR_A_READY;
        for( k = 0; k < 3; k++ )
        {
            if( !status[k] )
                continue;

            cvCircle( imageLShow, cvPointFrom32f(cornersL[k]), 3, CV_RGB(255*(k==0), 128*(k==1), 255*(k==2)), -1, 8,0);
            prev_cornersL[k] = cornersL[k];
        }

        cvShowImage("MediaLab Demo - L", imageLShow);

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
            cvCopy( imageR, imageRShow, 0 );

            cvCvtColor( imageR, grey, CV_BGR2GRAY );

            /// calculate optical flow by previous frame
            cvCalcOpticalFlowPyrLK( prev_greyR, grey, prev_pyramidR, pyramid,
                                    prev_cornersR, cornersR, 3, win_size, 3, status, 0,
                                    cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
            flags |= CV_LKFLOW_PYR_A_READY;
            for( k = 0; k < 3; k++ )
            {
                if( !status[k] )
                    continue;

                cvCircle( imageRShow, cvPointFrom32f(cornersR[k]), 3, CV_RGB(255*(k==0), 128*(k==1), 255*(k==2)), -1, 8,0);
                prev_cornersR[k] = cornersR[k];
            }

            cvShowImage("MediaLab Demo - R", imageRShow);

            CV_SWAP( prev_greyR, grey, swap_temp );
            CV_SWAP( prev_pyramidR, pyramid, swap_temp );

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
