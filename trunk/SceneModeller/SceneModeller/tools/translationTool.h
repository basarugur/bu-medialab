#ifndef TRANSLATE_TOOL_H
#define TRANSLATE_TOOL_H

#include "../core/transformation.h"
#include "../core/camera.h"
#include "../core/light.h"
#include "../core/vertex.h"
#include "../core/triangle.h"

#include <iostream>

#include "../common.h"

class SMTranslationTool
{
public:
	SMTranslationTool(Camera* cm) : m_camera(cm)
	{
		m_transform = NULL;
		m_light = NULL;
		m_translating_camera = NULL;

		m_vertex = NULL;
		m_face  = NULL;

	};
	~SMTranslationTool();

	void setViewport(int mx_,int my_){
		double ratio = (double)mx_ / (double)my_;
		m_x_ratio = ratio/(double)mx_;
		m_y_ratio = (double)1.0/ (double)my_; 
	};
	void startTranslate(Transformation* tr_,int sx_,int sy_)
	{
		m_translating_camera = NULL;
		m_light = NULL;
		m_transform = tr_;
		m_star_translation = tr_->translation();
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startTranslate(Vertex* vr_,int sx_,int sy_)
	{
		m_vertex = vr_;
		m_light = NULL;
		m_translating_camera = NULL;
		m_transform = NULL;

		m_star_translation = Vector3(vr_->x(),vr_->y(),vr_->z());
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startTranslate(Triangle* tr_,int sx_,int sy_)
	{
		m_face = tr_;
		m_light = NULL;
		m_translating_camera = NULL;
		m_transform = NULL;

		Point3 md_= m_face->mid();
		m_star_translation = Vector3(md_.x(),md_.y(),md_.z());
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startTranslate(Light* lg_,int sx_,int sy_)
	{
		m_light = lg_;
		m_translating_camera = NULL;
		m_transform = NULL;
		m_star_translation = Vector3(m_light->p().x(),m_light->p().y(),m_light->p().z());
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startTranslate(Camera* cm_,int sx_,int sy_)
	{
		m_translating_camera = cm_;
		m_transform = NULL;
		m_light = NULL;
		m_star_translation = Vector3(m_translating_camera->position().x(),
			                         m_translating_camera->position().y(),
									 m_translating_camera->position().z());
		m_star_translation_2 = Vector3(m_translating_camera->atPoint().x(),
			                         m_translating_camera->atPoint().y(),
									 m_translating_camera->atPoint().z());
		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startMoveTarget(Camera* cm_,int sx_,int sy_)
	{
		m_translating_camera = cm_;
		m_transform = NULL;
		m_light = NULL;
		m_star_translation = Vector3(m_translating_camera->atPoint().x(),
			m_translating_camera->atPoint().y(),
			m_translating_camera->atPoint().z());

		m_start_x = sx_ ; 
		m_start_y = sy_ ;

		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		transX_ = (dir_^m_camera->upVector()).normalize();
		transY_ = m_camera->upVector();

		m_dist = orthogonalDistanceToCamera();
	}
	void startMoveCamera(Camera* cm_,int sx_,int sy_)
	{
		m_translating_camera = cm_;
		m_transform = NULL;
		m_light = NULL;
		m_star_translation = Vector3(m_translating_camera->position().x(),
			m_translating_camera->position().y(),
			m_translating_camera->position().z());

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
		m_light = NULL;
		m_translating_camera = NULL;
		m_vertex = NULL;
		m_face  = NULL;
	}
	void translate(int x_,int y_)
	{
		if(m_transform != NULL)
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			m_transform->translation() = m_star_translation+deltaY_*transY_+deltaX_*transX_;
		}
		else if( m_light != NULL)
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			Vector3 vc_ = m_star_translation+deltaY_*transY_+deltaX_*transX_;

			m_light->setPos(Point3(vc_.x(),vc_.y(),vc_.z()));
		}
		else if( m_translating_camera!= NULL )
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			Vector3 vc1_ = m_star_translation+deltaY_*transY_+deltaX_*transX_;
			Vector3 vc2_ = m_star_translation_2+deltaY_*transY_+deltaX_*transX_;

			m_translating_camera->setPosition(Point3(vc1_.x(),vc1_.y(),vc1_.z()));
			m_translating_camera->setAtPoint(Point3(vc2_.x(),vc2_.y(),vc2_.z()));
		}
		else if( m_vertex != NULL)
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			Vector3 vc_ = m_star_translation+deltaY_*transY_+deltaX_*transX_;

			m_vertex->setX(vc_.x());
			m_vertex->setY(vc_.y());
			m_vertex->setZ(vc_.z());
		}
		else if( m_face != NULL)
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			Vector3 vc_ =deltaY_*transY_+deltaX_*transX_;

			Vertex* vr1_ = m_face->a();
			Vertex* vr2_ = m_face->b();
			Vertex* vr3_ = m_face->c();

			vr1_->setX(vc_.x()+vr1_->x());
			vr1_->setY(vc_.y()+vr1_->y());
			vr1_->setZ(vc_.z()+vr1_->z());

			vr2_->setX(vc_.x()+vr2_->x());
			vr2_->setY(vc_.y()+vr2_->y());
			vr2_->setZ(vc_.z()+vr2_->z());

			vr3_->setX(vc_.x()+vr3_->x());
			vr3_->setY(vc_.y()+vr3_->y());
			vr3_->setZ(vc_.z()+vr3_->z());

			m_start_x = x_;
			m_start_y = y_;
		}
	}
	void moveCamera(int x_,int y_)
	{
		if(m_translating_camera != NULL)
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			Point3 newPos_ = m_translating_camera->position()+deltaY_*transY_+deltaX_*transX_;

			Vector3 dir1_ = (m_translating_camera->position()-m_translating_camera->atPoint()).normalize();

			m_translating_camera->setPosition(newPos_);

			Vector3 dir2_ = (m_translating_camera->position()-m_translating_camera->atPoint()).normalize();

			if(!(dir1_ == dir2_))
			{
				double acos_ = acos(dir1_*dir2_);
				dir1_ = (dir1_^dir2_).normalize();

				Vector3 nwNorm_ = RotateVectorAroundVector(m_translating_camera->upVector(),dir1_,acos_);
				m_translating_camera->setUpVector(nwNorm_);
			}

			m_start_x = x_;
			m_start_y = y_;
		}
	}
	void moveTarget(int x_,int y_)
	{
		if(m_translating_camera != NULL)
		{
			double deltaX_ = m_x_ratio*(double)(x_ - m_start_x)*m_dist; // window coordinate system
			double deltaY_ = m_y_ratio*(double)(m_start_y - y_)*m_dist; //is reversed

			Point3 newPos_ = m_translating_camera->atPoint()+deltaY_*transY_+deltaX_*transX_;

			//
			Vector3 dir1_ = (m_translating_camera->atPoint()-m_translating_camera->position()).normalize();

			m_translating_camera->setAtPoint(newPos_);

			Vector3 dir2_ = (m_translating_camera->atPoint()-m_translating_camera->position()).normalize();

			if ( !(dir1_ == dir2_) )
			{
				double acos_ = acos(dir1_*dir2_);
				dir1_ = (dir1_^dir2_).normalize();

				Vector3 nwNorm_ = RotateVectorAroundVector(m_translating_camera->upVector(),dir1_,acos_);
				m_translating_camera->setUpVector(nwNorm_);
			}
			//

			m_start_x = x_;
			m_start_y = y_;
		}
	}
	double orthogonalDistanceToCamera()
	{
		Vector3 dir_ = (m_camera->atPoint()-m_camera->position()).normalize();
		double a_ = dir_.x();
		double b_ = dir_.y();
		double c_ = dir_.z();

		double d_ = -(a_ * m_camera->position().x() + b_ * m_camera->position().y() + c_ * m_camera->position().z());

		return a_ * m_star_translation.x() + b_ * m_star_translation.y() + c_ * m_star_translation.z() + d_;
	}


private:
	Transformation *m_transform;
	Camera* m_camera;
	Light* m_light;
	Camera* m_translating_camera;
	Vertex* m_vertex;
	Triangle* m_face;

	double m_dist;

	Vector3 transX_;
	Vector3 transY_;

	Vector3 m_star_translation;
	Vector3 m_star_translation_2;
	int m_start_x;
	int m_start_y;

	double m_x_ratio;
	double m_y_ratio;
};



#endif // SCENEMODELLER_H
