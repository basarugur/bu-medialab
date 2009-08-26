#ifndef ROTATION_TOOL_H
#define ROTATION_TOOL_H

#include "../core/transformation.h"
#include "../core/camera.h"

#include <iostream>

#include "../common.h"

class SM_API_EXPORT SMRotationTool
{
public:
	SMRotationTool(Camera* cm) : m_camera(cm)
	{
		m_transform = NULL;

		m_rotating_camera = NULL;

	};
	~SMRotationTool();

	void setViewport(int mx_,int my_){
		double ratio = (double)mx_ / (double)my_;
		m_x_ratio = ratio/(double)mx_;
		m_y_ratio = (double)1.0/ (double)my_; 
	};
	void startRotate(Transformation* tr_,int sx_,int sy_)
	{
		m_transform = tr_;
		m_rotating_camera = NULL;
		m_star_rotation = tr_->rotation();
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

	
		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startRotate(Camera* cm_,int sx_,int sy_)
	{
		m_transform = NULL;
		m_rotating_camera = cm_ ; 


		//m_start_direction = cm_->atPoint()-cm_->position();
		//m_target_dist = m_start_direction.length();
		//m_start_direction = m_start_direction.normalize();
		//m_start_upvector = cm_->upVector();
	
		m_start_delta_vector = cm_->atPoint()-cm_->position();
		m_start_up_vector = cm_->upVector();

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
		m_rotating_camera = NULL;
	}
	void rotate(int x_,int y_)
	{
		if(m_transform != NULL)
		{
			double deltaX_ =0.08*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ =0.08*(double)(y_ - m_start_y)*m_dist; //is reversed

			Rotation4 rotX_(transX_.x(),transX_.y(),transX_.z(),deltaY_);
			Rotation4 rotY_(transY_.x(),transY_.y(),transY_.z(),deltaX_);

			Rotation4 rot_ = rotX_*rotY_;
			m_transform->rotation() = m_star_rotation*rot_;

		}
		else if(m_rotating_camera != NULL)
		{
			double deltaX_ = 0.08*(double)(m_start_x - x_); // window coordinate system
		    double deltaY_ = 0.08*(double)(m_start_y - y_); //is reversed
			Vector3 delta_ =  m_start_delta_vector;
			delta_ =  RotateVectorAroundVector(delta_,transX_,deltaX_*3.0);
			delta_ =  RotateVectorAroundVector(delta_,transY_,deltaY_*3.0);
			m_rotating_camera->setAtPoint(m_rotating_camera->position()+delta_);
			delta_ =  m_start_up_vector;
			delta_ =  RotateVectorAroundVector(delta_,transX_,deltaX_*3.0);
			delta_ =  RotateVectorAroundVector(delta_,transY_,deltaY_*3.0);
			m_rotating_camera->setUpVector(delta_.normalize());
		}
	}
	double orthogonalDistanceToCamera()
	{
		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		double a_ = dir_.x();
		double b_ = dir_.y();
		double c_ = dir_.z();

		double d_ = -(a_ * m_camera->position().x() + b_ * m_camera->position().y() + c_ * m_camera->position().z());

		if(m_transform != NULL)
			return a_ * m_transform->translation().x() + b_ * m_transform->translation().y() + c_ * m_transform->translation().z() + d_;

		return a_ * m_rotating_camera->position().x() + b_ * m_rotating_camera->position().y() + c_ * m_rotating_camera->position().z() + d_;
	}


private:
	Transformation *m_transform;
	Camera* m_camera;

	Camera* m_rotating_camera;

	//double  m_target_dist;
	//Vector3 m_start_direction;
	//Vector3 m_start_cross;
	//Vector3 m_start_upvector;

	Vector3 m_start_delta_vector;
	Vector3 m_start_up_vector;

	double m_dist;

	Vector3 transX_;
	Vector3 transY_;

	Rotation4 m_star_rotation;
	int m_start_x;
	int m_start_y;

	double m_x_ratio;
	double m_y_ratio;
};



#endif // SCENEMODELLER_H
