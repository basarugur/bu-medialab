//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"
#include "sampler.h"
#include "ray.h"
#include "primitive.h"

namespace scene
{
	class Camera
	{
		public:
			Camera(const space::Point3& p,const space::Vector3& d,const space::Point3& t);
			
			//method, which determines the appropriate ray to trace for a particular sample position 
			//on the image plane given particular image formation process that it is simulating.
			virtual float generate_ray(const output::Sampler*,Ray&) = 0; 		
			virtual float generate_rayr(const output::Sampler*,Ray&) = 0;
			virtual float generate_rays(const output::Sampler*,Ray*,space::Vector3*,int) = 0;
			const space::Point3& position() { return m_position; };		
			
		private:
			space::Point3 m_position;
			space::Vector3 m_dir;
			space::Point3 m_target;

		protected:
			space::Vector3 apply_transform(const space::Vector3& p) {
				space::Vector3 v = p.x() * m_u +  p.y() * m_w + p.z() * m_v;						
				return v;
			}

			space::Vector3 m_u;
			space::Vector3 m_v;
			space::Vector3 m_w;

			scene::Transformation m_transform;
	};

	//Perspective camera.
	class Perspective : public Camera
	{
		public:
			Perspective(const space::Point3& p,const space::Vector3& d,const space::Point3& t) : Camera(p,d,t) 
			{			
			};

			virtual float generate_ray(const output::Sampler*,Ray&);
			virtual float generate_rayr(const output::Sampler*,Ray&);		
			virtual float generate_rays(const output::Sampler*,Ray*,space::Vector3*,int);
	};

};

#endif