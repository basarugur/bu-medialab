


#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"
#include "sampler.h"
#include "ray.h"
#include "primitive.h"


class Camera
{
	public:
		Camera();
		Camera(const Point3& p);

		Camera(const Point3& p,const Vector3& d,const Point3& t);

		//method, which determines the appropriate ray to trace for a particular sample position 
		//on the image plane given particular image formation process that it is simulating.
		virtual float generate_ray(const Sampler*,Ray&){return 0 ; }; 		
		virtual float generate_rayr(const Sampler*,Ray&){return 0 ; };
		virtual float generate_rays(const Sampler*,Ray*,Vector3*,int){return 0 ; };
	
		virtual void setPosition(Point3 pos_) { m_position = pos_; }
		virtual void setUpVector(Vector3 up_){ m_upvector = up_; }

		
		virtual Point3 position(){ return m_position; }
		virtual Vector3 upVector(){ return m_upvector; }
		virtual void setAtPoint(Point3 pnt_ ){ 
			m_at_point = pnt_;
		}


		virtual void setName(std::string st_){ m_name = st_; }
		virtual std::string getName() { return m_name; }
		virtual Point3 atPoint(){
			return m_at_point;
		};

		void select(bool bl_){ m_is_selected = bl_; }
		bool isSelected() { return m_is_selected; }


	protected:
		bool m_is_selected;
		Point3 m_position;
		Vector3 m_upvector;
		Point3 m_at_point;
		std::string m_name;

		Vector3 apply_transform(const Vector3& p) {
			Vector3 v = p.x() * m_u +  p.y() * m_w + p.z() * m_v;						
			return v;
		}
		Vector3 m_u;
		Vector3 m_v;
		Vector3 m_w;
		Transformation m_transform;

		Vector3 m_dir;
		Point3 m_target;
};

//Perspective camera.
class Perspective : public Camera
{
public:
	Perspective(const Point3& p,const Vector3& d,const Point3& t) : Camera(p,d,t) 
	{			
	};
	Perspective(const Point3& p) : Camera(p) 
	{			
	};

	virtual float generate_ray(const Sampler*,Ray&);
	virtual float generate_rayr(const Sampler*,Ray&);		
	virtual float generate_rays(const Sampler*,Ray*,Vector3*,int);
};



#endif