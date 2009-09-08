#include "camera.h"
#include "GL/glut.h"

Camera::Camera(const Point3& p) : m_position(p)
{
	m_upvector = Vector3(0,1,0);

	m_is_selected = false;
}
Camera::Camera()
{
	m_position = Point3(0,0,0);;
	m_look_at_point = Point3(0,0,-10);
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

void Camera::draw()
{
    glPushMatrix();

	// calculate camera totation
	Matrix rotationMat;
	Vector3 vz_ = (m_look_at_point - m_position).normalize();
	Vector3 vx_ = ( vz_^m_upvector ).normalize();
	Vector3 vy_ = m_upvector;

	rotationMat.setcell(0,0, vx_.x() );
	rotationMat.setcell(0,1, vx_.y() );
	rotationMat.setcell(0,2, vx_.z() );

	rotationMat.setcell(1,0, vy_.x());
	rotationMat.setcell(1,1, vy_.y());
	rotationMat.setcell(1,2, vy_.z());

	rotationMat.setcell(2,0, -(vz_.x()));
	rotationMat.setcell(2,1, -(vz_.y()));
	rotationMat.setcell(2,2, -(vz_.z()));

	Rotation4 rot_;
	rot_.setFromMatrix(rotationMat);

	glTranslatef( m_position.x(), m_position.y(), m_position.z() );
	double x_ = rot_.ax();
	double y_ = rot_.ay();
	double z_ = rot_.az();
	double ang_ = rot_.theta();
	glRotatef(-ang_, x_, y_, z_);

	double lngth_ = (m_look_at_point - m_position).length();

	GLUquadric* qdr_ =  gluNewQuadric();
	gluQuadricDrawStyle(qdr_, GLU_FILL);

	glColor3f(0.1,0.1,0.1);
	if(m_is_selected)
        glColor3f(1,0.3,0.3);

	glRotatef(180,1.0,0.0,0.0);
	glTranslatef(0.0,0.0,-1.5);
	gluCylinder(qdr_,0.5,0.5,1.5,10,10);
	glTranslatef(0.0,0.0,1.5);
	glutSolidCone(0.5,0.75,10,10);
	glRotatef(180,-1.0,0.0,0.0);

	glLineWidth(3);

	glBegin(GL_LINES);
        glVertex3f(0,0,0); glVertex3f(0,-2,-1);
        glVertex3f(0,0,0); glVertex3f(0.5,-2,0.5);
        glVertex3f(0,0,0); glVertex3f(-0.5,-2,0.5);
	glEnd();

	glColor3f(0,0,1);
	if(m_is_selected)
        glColor3f(1,0.3,0.3);
	glBegin(GL_LINES);
        glVertex3f(0,0,0); glVertex3f(0,0,-lngth_);
	glEnd();

	glLineWidth(1);

	glTranslatef(0,0,-lngth_);
	gluSphere(qdr_,0.3,10,10);
	glTranslatef(0,0,lngth_);

	glPopMatrix();
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
