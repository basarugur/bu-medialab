#include "camera.h"

namespace scene
{
	Camera::Camera(const space::Point3& p,const space::Vector3& d) : m_position(p),m_dir(d)
	{

	}

	float Perspective::generate_ray(const output::Sampler* s,Ray& r)
	{		
		r = Ray(position(),(s->view() - position()),0,1e30);
		return 0.f;
	}
	
	float Perspective::generate_rayr(const output::Sampler* s,Ray& r) {
		r = Ray(position(),(s->viewr() - position()),0,1e30);
		return 0.f;
	}
};