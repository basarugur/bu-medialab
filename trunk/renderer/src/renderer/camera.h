//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"
#include "sampler.h"
#include "ray.h"

namespace scene
{
	class Camera
	{
		public:
			Camera(const space::Point3& p,const space::Vector3& d);
			
			//method, which determines the appropriate ray to trace for a particular sample position 
			//on the image plane given particular image formation process that it is simulating.
			virtual float generate_ray(const output::Sampler*,Ray&) = 0; 		
			virtual float generate_rayr(const output::Sampler*,Ray&) = 0;
			const space::Point3& position() { return m_position; };		
			
		private:
			space::Point3 m_position;
			space::Vector3 m_dir;
	};

	//Perspective camera.
	class Perspective : public Camera
	{
	public:
		Perspective(const space::Point3& p,const space::Vector3& d) : Camera(p,d) 
		{
		};

		virtual float generate_ray(const output::Sampler*,Ray&);
		virtual float generate_rayr(const output::Sampler*,Ray&);
	};

};

#endif