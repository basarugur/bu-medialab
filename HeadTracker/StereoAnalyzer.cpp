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

	hfow = _hfow * PI / 180.0;
	width = _width;
	height = _height;

	vfow = 2 * atan((height/width) * tan(hfow/2));
}

StereoAnalyzer::StereoAnalyzer(double _hfow, double _width, double _height, double _camdist)
{
	hfow = _hfow * PI / 180.0;
	width = _width;
	height = _height;

	camdist = _camdist;

	vfow = 2 * atan((height/width) * tan(hfow/2));

}
StereoAnalyzer::~StereoAnalyzer(void)
{
}

bool StereoAnalyzer::computePosition(CvPoint2D32f left, CvPoint2D32f right, Point3& p)
{
	double alpha;

	double c;

	double dleft, dright;

	double tanbetaright, tanbetaleft;

	double temp1, temp2;

	if(left.x == right.x)
	{
		//POINT AT INFINITY

		p = Point3( 0.0, 0.0, std::numeric_limits<double>::max() );

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

		p = Point3( (camdist/2) + temp1,
                    temp2 * sin(alpha),
                    temp2 * cos(alpha) );
    }

	else if(dleft > 0.0 && dright > 0.0)
	{
		temp1 = camdist/((tanbetaright/tanbetaleft)-1.0);

		temp2 = temp1 * tanbetaright;

		p = Point3( -1 * ((camdist/2) + temp1),
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

				p = Point3( camdist/2,
                            temp2 * sin(alpha),
                            temp2 * cos(alpha) );

			}

			else if(dleft != 0.0 && dright == 0.0)
			{
				temp2 = camdist * tanbetaleft;

				p = Point3( -1 * (camdist/2),
                            temp2 * sin(alpha),
                            temp2 * cos(alpha) );
			}


		}
		else
		{

			temp1 = camdist/((tanbetaright/tanbetaleft)+1.0);

			temp2 = temp1 * tanbetaright;

			p = Point3( temp1 - (camdist/2),
                        temp2 * sin(alpha),
                        temp2 * cos(alpha) );

		}

	}


	if( (((left.y + right.y)/2) - (height/2))>0.0)
	{
		p = Point3( p.x(), -1.0 * p.y(), p.z() );
	}

	return true;

}

bool StereoAnalyzer::findLocationVector(CvPoint2D32f* leftImagePoints, CvPoint2D32f* rightImagePoints,
                                        Point3& headPosition, Vector3& lookVector, Matrix coord_trans)
{
	Point3 led1, led2, led3;	//front LED

    if(!computePosition(leftImagePoints[0], rightImagePoints[0], led1))
		return false;

	if(!computePosition(leftImagePoints[1], rightImagePoints[1], led2))
		return false;

	if(!computePosition(leftImagePoints[2], rightImagePoints[2], led3))
		return false;

    //may need to handle
	//leds positions and orientation

	//double * position = new double[3];
	Point3 center = (led1 + led2 + led3) * 0.3333333f;

//    cout << "CC: " << center.x() << " " << center.y() << " " << center.z() << endl;

	headPosition = coord_trans * center;

//	cout << "HP: " << headPosition.x() << " " << headPosition.y() << " " << headPosition.z() << endl;

	// adjustment may be needed
	//headPosition = position;

    //double *  vector = new double[3];
    Point3 triangle_mid = (led1 + led2) * 0.5;

    Vector3 height_vec = coord_trans * led3 - coord_trans * triangle_mid;

	lookVector = height_vec;

	return true;

}
