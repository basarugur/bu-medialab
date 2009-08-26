
#ifndef EDITING_CAMERA_H
#define EDITING_CAMERA_H

#include "../core/camera.h"


class SM_API_EXPORT  EditingCamera : public Camera
{
public:
	EditingCamera(const Point3& p) : Camera(p)
	{
	}
	EditingCamera() : Camera()  
	{
		
	};
	~EditingCamera()
	{

	};

	void setToCamera(Camera* cmr_);

	void moveForvard(double scale_);
	void returnPhi(double scale_);
	void returnTheta(double scale_);

	void setPosition(Point3 pos_);
	void setUpVector(Vector3 up_);

	void zoomIn(double fctr=1);
	void zoomOut(double fctr=1);

	//void TumbleY(double fctr=1);
	//void TumbleX(double fctr=1);

	virtual float generate_ray(const Sampler*,Ray&){return 0; };
	virtual float generate_rayr(const Sampler*,Ray&) { return 0; };		
	virtual float generate_rays(const Sampler*,Ray*,Vector3*,int){ return 0; };


};

#endif