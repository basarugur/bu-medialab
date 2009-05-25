#include "camera.h"

Camera::Camera(const Point3& p) : m_position(p)
{
	m_upvector = Vector3(0,1,0);

	m_is_selected = false;
}
Camera::Camera()
{
	m_position = Point3(0,0,0);;
	m_at_point = Point3(0,0,-10);
	m_upvector = Vector3(0,1,0);
	m_name = "new camera";

	m_is_selected = false;
}

//p eye point, d is up vector, t is target point
Camera::Camera(const Point3& p,const Vector3& d,const Point3& t) : m_position(p),m_dir(d),m_target(t)
{
	Vector3 v(t.x()-p.x(),t.y()-p.y(),t.z()-p.z());
	Vector3 u = d ^ v;
	Vector3 w = v ^ u;

	m_v = v.normalize();
	m_u = u.normalize();
	m_w = w.normalize();

	m_transform.translate(p.x(),p.y(),p.z());
	m_position = m_transform.apply(m_position);
}

float Perspective::generate_ray(const Sampler* s,Ray& r)
{		
	Point3 p1(0,0,-25);
	Vector3 dir = s->view() - p1;		
	r = Ray(position(),apply_transform(dir),0,1e30);
	return 0.f;
}

float Perspective::generate_rayr(const Sampler* s,Ray& r) 
{
	Point3 p1(0,0,-25);
	Vector3 dir = s->viewr() - p1;
	r = Ray(position(),apply_transform(dir),0,1e30);
	return 0.f;
}

float Perspective::generate_rays(const Sampler* s,Ray* rays,Vector3* l,int size)
{
	Point3 pix = s->view();
	Point3 p1(0,0,-25);

	double sw = s->screen()->width();
	double sh = s->screen()->height();

	double incx = s->width()  / sw;
	double incy = s->height() / sh;

	for(int i=0;i<size;i++) {
		Vector3 v(incx*l[i].x(),incy*l[i].y(),l[i].z());
		Vector3 dir = (pix + v) - p1;
		rays[i] = Ray(position(),apply_transform(dir),0,1e30);			
	}

	return 0.f;
}
