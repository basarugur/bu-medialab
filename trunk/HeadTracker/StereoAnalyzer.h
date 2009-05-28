///-----------------------------------------------------------------------------
///
/// \file	StereoAnalyzer.h
/// \author	M. Resid Cizmeci & Basar Ugur
/// \brief	Stereo Vision Analyzer for obtaining 3D vector correspondences
/// \note
///-----------------------------------------------------------------------------


#include "cv.h"
#include "../StereoViewer/geometry.h"

class StereoAnalyzer
{
public:
	StereoAnalyzer(void);
	StereoAnalyzer(double _hfow, double _width, double _height, double _camdist);
	bool computePosition(CvPoint2D32f left, CvPoint2D32f right, Point& p);

	bool findLocationVector(CvPoint2D32f* leftImagePoints, CvPoint2D32f* rightImagePoints,
                             Point& headPosition, Point& lookVector, const Matrix4x4 coord_trans_4x4);

	~StereoAnalyzer(void);

private:
	double hfow;
	double vfow;
	double width;
	double height;
	double camdist;
};
