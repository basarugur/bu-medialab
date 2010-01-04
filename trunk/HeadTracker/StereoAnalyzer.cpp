#include "StereoAnalyzer.h"
#include <math.h>
#include <iostream>
#include <limits>

using namespace std;



StereoAnalyzer::StereoAnalyzer(void)
{
	double _hfow = 43.0;
	double _width = 640.0;
	double _height = 480.0;

	camdist = 12.0;

	hfow = _hfow * M_PI / 180.0;
	width = _width;
	height = _height;

	vfow = 2 * atan((height/width) * tan(hfow/2));
}

StereoAnalyzer::StereoAnalyzer(double _hfow, double _width, double _height, double _camdist)
{
	hfow = _hfow * M_PI / 180.0;
	width = _width;
	height = _height;

	camdist = _camdist;

	vfow = 2 * atan((height/width) * tan(hfow/2));

}
StereoAnalyzer::~StereoAnalyzer(void)
{
}

bool StereoAnalyzer::computePosition(CvPoint2D32f left, CvPoint2D32f right, CvPoint3D32f& p)
{
	double alpha;

	double c;

	double dleft, dright;

	double tanbetaright, tanbetaleft;

	double temp1, temp2;

	if(left.x == right.x)
	{
		//POINT AT INFINITY

		p = cvPoint3D32f( 0.0, 0.0, std::numeric_limits<double>::max() );

		return false;
	}

	c = fabs(((left.y + right.y)/2) - (height/2));
	alpha = atan((c/(width/2)) * tan(hfow/2));

	//cout <<"alpha "  << alpha << endl;

	dleft = left.x - (width/2);
	dright = right.x - (width/2);

	if(c != 0.0)
	{
		if(fabs(dright)!= 0.0)
			tanbetaright = c/(fabs(dright)*sin(alpha));
		if(fabs(dleft)!= 0.0)
			tanbetaleft = c/(fabs(dleft)*sin(alpha));
	}
	else
	{
		if(fabs(dright)!= 0.0)
			tanbetaright = (width/2)/(fabs(dright)*tan(hfow/2));
		if(fabs(dleft)!= 0.0)
			tanbetaleft = (width/2)/(fabs(dleft)*tan(hfow/2));
	}

	/*cout <<"right "  << tanbetaright << endl;
	cout <<"left "  << tanbetaleft << endl;

	cout <<"right "  << atan(tanbetaright) * 180.0 / PI<< endl;
	cout <<"left "  << atan(tanbetaleft) * 180.0 / PI<< endl;*/




	if(dleft < 0.0 && dright < 0.0)
	{
		temp1 = camdist/((tanbetaleft/tanbetaright)-1.0);

		temp2 = temp1 * tanbetaleft;

		p = cvPoint3D32f( (camdist * 0.5f) + temp1,
                          temp2 * sin(alpha),
                          temp2 * cos(alpha) );
    }

	else if(dleft > 0.0 && dright > 0.0)
	{
		temp1 = camdist/((tanbetaright/tanbetaleft)-1.0);

		temp2 = temp1 * tanbetaright;

		p = cvPoint3D32f( -1 * ((camdist/2) + temp1),
                          temp2 * sin(alpha),
                          temp2 * cos(alpha) );

	}

	else
	{
		if(dleft == 0.0 || dright == 0.0)
		{
			if(dleft == 0.0 && dright != 0.0)
			{
				temp2 = camdist * tanbetaright;

				p = cvPoint3D32f( camdist/2,
                                  temp2 * sin(alpha),
                                  temp2 * cos(alpha) );

			}

			else if(dleft != 0.0 && dright == 0.0)
			{
				temp2 = camdist * tanbetaleft;

				p = cvPoint3D32f( -1 * (camdist/2),
                                  temp2 * sin(alpha),
                                  temp2 * cos(alpha) );
			}


		}
		else
		{

			temp1 = camdist/((tanbetaright/tanbetaleft)+1.0);

			temp2 = temp1 * tanbetaright;

			p = cvPoint3D32f( temp1 - (camdist/2),
                              temp2 * sin(alpha),
                              temp2 * cos(alpha) );

		}

	}


	if( (((left.y + right.y)/2) - (height/2))>0.0)
	{
		p = cvPoint3D32f( p.x, -1.0 * p.y, p.z );
	}

	return true;

}

bool StereoAnalyzer::findLocationVector(CvPoint2D32f* leftImagePoints,
                                        CvPoint2D32f* rightImagePoints,
                                        CvPoint3D32f& headPosition,
                                        CvPoint3D32f& lookVector,
                                        CvMat& M_coord_trans)
{
	CvPoint3D32f led1, led2, led3;	//front LED

    if(!computePosition(leftImagePoints[0], rightImagePoints[0], led1))
		return false;

	if(!computePosition(leftImagePoints[1], rightImagePoints[1], led2))
		return false;

	if(!computePosition(leftImagePoints[2], rightImagePoints[2], led3))
		return false;

    // may need to handle
	// leds positions and orientation

	float center[4] = { (led1.x + led2.x + led3.x) * 0.3333333f,
                        (led1.y + led2.y + led3.y) * 0.3333333f,
                        (led1.z + led2.z + led3.z) * 0.3333333f,
                        1.f };

    CvMat V_center = cvMat(4, 1, CV_32FC1, center);

//  cout << "CC: " << center.x() << " " << center.y() << " " << center.z() << endl;

    CvMat *V_head_position = cvCreateMat( 4, 1, CV_32FC1 );

    cvMatMul( &M_coord_trans, &V_center, V_head_position );

    // Set homogeneous coordinates:
    float invLast = cvmGet( V_head_position, 3, 0 );

    headPosition = cvPoint3D32f( cvmGet( V_head_position, 0, 0 ) * invLast,
                                 cvmGet( V_head_position, 1, 0 ) * invLast,
                                 cvmGet( V_head_position, 2, 0 ) * invLast );

//	cout << "HP: " << headPosition.x() << " " << headPosition.y() << " " << headPosition.z() << endl;

	float triangle_altitude[4] = { led3.x - (led1.x + led2.x) * 0.5f,
                                   led3.y - (led1.y + led2.y) * 0.5f,
                                   led3.z - (led1.z + led2.z) * 0.5f,
                                   1.f };

    CvMat V_triangle_altitude = cvMat( 4, 1, CV_32FC1, triangle_altitude );

    cvMatMul( &M_coord_trans, &V_triangle_altitude, &V_triangle_altitude );

    // Set homogeneous coordinates:
    invLast = cvmGet( &V_triangle_altitude, 3, 0 );

	lookVector = cvPoint3D32f( cvmGet( &V_triangle_altitude, 0, 0 ) * invLast,
                               cvmGet( &V_triangle_altitude, 1, 0 ) * invLast,
                               cvmGet( &V_triangle_altitude, 2, 0 ) * invLast );

	return true;

}
