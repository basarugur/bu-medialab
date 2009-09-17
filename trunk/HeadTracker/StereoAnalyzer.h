///-----------------------------------------------------------------------------
///
/// \file	StereoAnalyzer.h
/// \author	M. Resid Cizmeci & Basar Ugur
/// \brief	Stereo Vision Analyzer for obtaining 3D vector correspondences
///         Requires the class definitions from "geometry.h" in StereoViewer
/// \note
///-----------------------------------------------------------------------------


#include "cv.h"
#include "../SceneModeller_API/src/core/matrix.h"

class StereoAnalyzer
{
public:
	StereoAnalyzer(void);
	StereoAnalyzer(double _hfow, double _width, double _height, double _camdist);
	bool computePosition(CvPoint2D32f left, CvPoint2D32f right, Point3& p);

	bool findLocationVector(CvPoint2D32f* leftImagePoints, CvPoint2D32f* rightImagePoints,
                             Point3& headPosition, Vector3& lookVector, Matrix coord_trans);

	~StereoAnalyzer(void);

private:
	double hfow;
	double vfow;
	double width;
	double height;
	double camdist;
};
