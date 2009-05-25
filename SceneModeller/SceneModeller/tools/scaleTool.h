#ifndef SCALE_TOOL_H
#define SCALE_TOOL_H

#include "../core/transformation.h"
#include "../core/camera.h"

#include <iostream>

class SMScaleTool
{
public:
	SMScaleTool(Camera* cm) : m_camera(cm)
	{
		m_transform = NULL;

	};
	~SMScaleTool();

	void setViewport(int mx_,int my_){
		double ratio = (double)mx_ / (double)my_;
		m_x_ratio = ratio/(double)mx_;
		m_y_ratio = (double)1.0/ (double)my_; 
	};
	void startScale(Transformation* tr_,int sx_,int sy_)
	{
		m_transform = tr_;
		m_star_scale = tr_->scale();
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void release()
	{
		m_transform = NULL;
	}
	void scale(int x_,int y_)
	{
		if(m_transform != NULL)
		{
			double deltaX_ = 0.8*m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = 0.8*m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			m_transform->scale() = m_star_scale+deltaY_*transY_+deltaX_*transX_;
		}
	}
	double orthogonalDistanceToCamera()
	{
		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		double a_ = dir_.x();
		double b_ = dir_.y();
		double c_ = dir_.z();

		double d_ = -(a_ * m_camera->position().x() + b_ * m_camera->position().y() + c_ * m_camera->position().z());

		return a_ * m_transform->translation().x() + b_ * m_transform->translation().y() + c_ * m_transform->translation().z() + d_;
	}

private:
	Transformation *m_transform;
	Camera* m_camera;

	double m_dist;

	Vector3 transX_;
	Vector3 transY_;

	Vector3 m_star_scale;
	int m_start_x;
	int m_start_y;

	double m_x_ratio;
	double m_y_ratio;
};



#endif // SCENEMODELLER_H
