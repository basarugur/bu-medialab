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

	double camdist = 12.0;

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

bool StereoAnalyzer::computePosition(CvPoint2D32f left, CvPoint2D32f right, Point& p)
{
	double alpha;

	double c;

	double dleft, dright;

	double tanbetaright, tanbetaleft;

	double temp1, temp2;

	if(left.x == right.x)
	{
		//POINT AT INFINITY

		p.x = 0.0;
		p.y = 0.0;
		p.z = std::numeric_limits<double>::max();

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

		p.y = temp2 * sin(alpha);

		p.z = temp2 * cos(alpha);

		p.x = (camdist/2) + temp1;

	}

	else if(dleft > 0.0 && dright > 0.0)
	{
		temp1 = camdist/((tanbetaright/tanbetaleft)-1.0);

		temp2 = temp1 * tanbetaright;

		p.y = temp2 * sin(alpha);

		p.z = temp2 * cos(alpha);

		p.x = -1 * ((camdist/2) + temp1);

	}

	else
	{
		if(dleft == 0.0 || dright == 0.0)
		{
			if(dleft == 0.0 && dright != 0.0)
			{
				temp2 = camdist * tanbetaright;

				p.y = temp2 * sin(alpha);

				p.z = temp2 * cos(alpha);

				p.x = camdist/2;
			}

			else if(dleft != 0.0 && dright == 0.0)
			{
				temp2 = camdist * tanbetaleft;

				p.y = temp2 * sin(alpha);

				p.z = temp2 * cos(alpha);

				p.x = -1 * (camdist/2);
			}


		}
		else
		{

			temp1 = camdist/((tanbetaright/tanbetaleft)+1.0);

			temp2 = temp1 * tanbetaright;

			p.y = temp2 * sin(alpha);

			p.z = temp2 * cos(alpha);

			p.x = temp1 - (camdist/2);
		}

	}


	if((((left.y + right.y)/2) - (height/2))>0.0)
	{
		p.y = -1.0 * p.y;
	}

	return true;

}

bool StereoAnalyzer::findLocationVector(CvPoint2D32f* leftImagePoints, CvPoint2D32f* rightImagePoints,
                                        Point& headPosition, Point& lookVector, const Matrix4x4 coord_trans)
{
	Point led1, led2, led3;	//front LED

	if(!computePosition(leftImagePoints[0], rightImagePoints[0], led1))
		return false;

	if(!computePosition(leftImagePoints[1], rightImagePoints[1], led2))
		return false;

	if(!computePosition(leftImagePoints[2], rightImagePoints[2], led3))
		return false;

	//may need to handle
	//leds positions and orientation

	//double * position = new double[3];
	headPosition = coord_trans * ((led1 + led2 + led3) * 0.3333333f);
	// adjustment may be needed
	//headPosition = position;


	//double *  vector = new double[3];
	lookVector = coord_trans * led3 - coord_trans * ( (led1 + led2) * 0.5f );
	// adjustment may be needed
	//lookVector = vector;


	return true;



}
