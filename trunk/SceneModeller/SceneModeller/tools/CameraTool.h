#ifndef CAMERA_TOOL_H
#define CAMERA_TOOL_H

#include "../core/transformation.h"
#include "../editing/EditingCamera.h"


#include <iostream>

enum CameraToolType
{
	PAN_TOOL = 0,
	ROTATE_TOOL = 1,
	ZOOM_TOOL = 3,
	NO_TOOL = 4
};

class SMCameraTool
{
public:
	SMCameraTool(EditingCamera* cm) : m_camera(cm)
	{
		m_type = NO_TOOL;
	};
	~SMCameraTool(){};

	void setViewport(int mx_,int my_){
		double ratio = (double)mx_ / (double)my_;
		m_x_ratio = ratio/(double)mx_;
		m_y_ratio = (double)1.0/ (double)my_; 
	};
	void startAction(int sx_,int sy_)
	{
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_star_position = m_camera->position();
		m_start_upvector = m_camera->upVector();

		m_start_direct = dir_;
		m_start_atpoint = m_camera->atPoint();

		m_dist = (m_camera->atPoint()-m_camera->position()).length();
	}
	void release()
	{
		m_type = NO_TOOL;
	}
	void setType( CameraToolType typ_)
	{
		m_type = typ_ ; 
	}
	CameraToolType getType()
	{
		return m_type ; 
	}
	void takeAction(int x_,int y_)
	{
		double deltaX_;
		double deltaY_;
		Vector3 delta_;
		switch(m_type)
		{
		case PAN_TOOL:
			deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
		    deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed
		    delta_  = deltaY_*transY_+deltaX_*transX_;
			m_camera->setPosition(m_star_position-delta_);
			m_camera->setAtPoint(m_start_atpoint-delta_);
			break;
		case ROTATE_TOOL:
			deltaX_ = m_x_ratio*(double)(m_start_x - x_); // window coordinate system
		    deltaY_ = m_y_ratio*(double)(m_start_y - y_); //is reversed
			delta_ =  m_star_position-m_start_atpoint;
			delta_ =  RotateVectorAroundVector(delta_,m_start_upvector,deltaX_*3.0);
			delta_ =  RotateVectorAroundVector(delta_,m_start_direct^m_start_upvector,deltaY_*3.0);
			m_camera->setPosition(m_start_atpoint+delta_);
			m_camera->setAtPoint(m_camera->position()+(-delta_.normalize()*m_dist));
			break;
		case ZOOM_TOOL:
			deltaY_ = 0.003*(double)(m_start_y - y_)*((m_camera->atPoint()-m_camera->position()).length());
			m_camera->setPosition(m_star_position+deltaY_*m_start_direct);
			break;
		}
	}

	//;Rotate the point (x,y,z) around the vector (u,v,w)
	//Function RotatePointAroundVector(x#,y#,z#,u#,v#,w#,a#)
	//ux#=u*x
	//uy#=u*y
	//uz#=u*z
	//vx#=v*x
	//vy#=v*y
	//vz#=v*z
	//wx#=w*x
	//wy#=w*y
	//wz#=w*z
	//sa#=Sin(a)
	//ca#=Cos(a)
	//x#=u*(ux+vy+wz)+(x*(v*v+w*w)-u*(vy+wz))*ca+(-wy+vz)*sa
	//y#=v*(ux+vy+wz)+(y*(u*u+w*w)-v*(ux+wz))*ca+(wx-uz)*sa
	//z#=w*(ux+vy+wz)+(z*(u*u+v*v)-w*(ux+vy))*ca+(-vx+uy)*sa
	//End Function

	Vector3 RotateVectorAroundVector(Vector3 trg_,Vector3 bse_,double angle)
	{
		double x = trg_.x() ;
		double y = trg_.y() ;
		double z = trg_.z() ;
		double u = bse_.x() ;
		double v = bse_.y() ;
		double w = bse_.z() ;
		double ux=u*x ;
		double uy=u*y ;
		double uz=u*z ;
		double vx=v*x ;
		double vy=v*y ;
		double vz=v*z ;
		double wx=w*x ;
		double wy=w*y ;
		double wz=w*z ;
		double sa = sin(angle);
		double ca = cos(angle);

		x=u*(ux+vy+wz)+(x*(v*v+w*w)-u*(vy+wz))*ca+(-wy+vz)*sa;
		y=v*(ux+vy+wz)+(y*(u*u+w*w)-v*(ux+wz))*ca+(wx-uz)*sa;
		z=w*(ux+vy+wz)+(z*(u*u+v*v)-w*(ux+vy))*ca+(-vx+uy)*sa;

		return Vector3(x,y,z);
	}

private:

	CameraToolType m_type;
	EditingCamera* m_camera;

	Vector3 transX_;
	Vector3 transY_;

	Point3 m_star_position;
	Point3 m_start_atpoint;
	Vector3 m_start_upvector;
	Vector3 m_start_direct;
	

	int m_start_x;
	int m_start_y;

	double m_x_ratio;
	double m_y_ratio;

	double m_dist;
};



#endif // SCENEMODELLER_H
