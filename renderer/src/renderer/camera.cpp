#include "camera.h"

namespace scene
{
	//p eye point, d is up vector, t is target point
	Camera::Camera(const space::Point3& p,const space::Vector3& d,const space::Point3& t) : m_position(p),m_dir(d),m_target(t)
	{
		space::Vector3 v(t.x()-p.x(),t.y()-p.y(),t.z()-p.z());
		space::Vector3 u = d ^ v;
		space::Vector3 w = v ^ u;

		m_v = v.normalize();
		m_u = u.normalize();
		m_w = w.normalize();

		m_transform.translate(p.x(),p.y(),p.z());
		m_position = m_transform.apply(m_position);
	}

	float Perspective::generate_ray(const output::Sampler* s,Ray& r)
	{		
		space::Point3 p1(0,0,-2);
		space::Vector3 dir = s->view() - p1;		
		r = Ray(position(),apply_transform(dir),0,1e30);
		return 0.f;
	}
	
	float Perspective::generate_rayr(const output::Sampler* s,Ray& r) 
	{
		space::Point3 p1(0,0,-2);
		space::Vector3 dir = s->viewr() - p1;
		r = Ray(position(),apply_transform(dir),0,1e30);
		return 0.f;
	}

	float Perspective::generate_rays(const output::Sampler* s,Ray* rays,space::Vector3* l,int size)
	{
		space::Point3 pix = s->view();
		space::Point3 p1(0,0,-2);

		double sw = s->screen()->width();
		double sh = s->screen()->height();

		double incx = s->width()  / sw;
		double incy = s->height() / sh;

		for(int i=0;i<size;i++) {
			space::Vector3 v(incx*l[i].x(),incy*l[i].y(),l[i].z());
			space::Vector3 dir = (pix + v) - p1;
			rays[i] = Ray(position(),apply_transform(dir),0,1e30);			
		}
		
		return 0.f;
	}
};