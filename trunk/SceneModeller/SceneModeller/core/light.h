


#ifndef LIGHT_H
#define LIGHT_H

#include "film.h"
#include "vector3.h"
#include "point3.h"
#include "shape.h"
#include "diffgeometry.h"

enum LightType
{
	POINT_LIGHT = 0,
	AREA_LIGHT = 1,
	SKY_LIGHT = 2
};


class Light
{
	public:	

		Light()
		{
			m_p = Point3(0,0,0);

			m_is_selected = false;
		}

		Light(Point3& p,Vector3& d) : m_p(p), m_d(d) {
			m_coeff  = 1.0;
		};

		virtual TRadiance l(const Ray& v,DifferentialGeometry* dg) const = 0;						
		virtual TRadiance s(const Ray& v,DifferentialGeometry* dg) const {			
			double r = 0;
			double g = 0;
			double b = 0;

			Point3 c;
			Point3 p = dg->p();

			r = 0.3*dg->material()->ambientcolor().r*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r;
			g = 0.3*dg->material()->ambientcolor().g*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g;
			b = 0.3*dg->material()->ambientcolor().b*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b;				

			return TRadiance(r,g,b);			
		}
		virtual bool intersect(const Ray& r) const = 0;
		virtual Point3 pick_point() const = 0;
		virtual LightType type() const = 0;
		const Point3& p() const { return m_p; };
		const Vector3& d() const { return m_d; };
		void set_coeff(double p) { m_coeff = p; };
		double coeff() { return m_coeff; };

		Light(Point3& p) : m_p(p) {};

		

		void setPos(Point3 p_){ m_p = p_; };

		bool isSelected() { return m_is_selected; }
		void select(bool bl_) { m_is_selected = bl_ ; }

	protected:
		Point3 m_p;
		bool m_is_selected;

		Vector3 m_d;
		double m_coeff;
};

class SkyLight : public Light 
{
public:
	SkyLight(Point3& p,Vector3& d) : Light(p,d) {};

	virtual TRadiance l(const Ray& v,DifferentialGeometry* dg) const {

		Point3 c;
		Point3 p = dg->p();

		double r = dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r;
		double g = dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g;
		double b = dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b;			
		return TRadiance(r,g,b);

	};

	virtual bool intersect(const Ray& r) const {
		return false;
	};

	virtual Point3 pick_point() const {
		return Point3();
	};

	LightType type() const {
		return SKY_LIGHT;
	}
};

class PointLight : public Light
{
	public:
		PointLight(Point3& p) : Light(p) {};

		PointLight() : Light() {};

		PointLight(Point3& p,Vector3& d) : Light(p,d) {};

		virtual TRadiance l(const Ray& v,DifferentialGeometry* dg) const {

			double r = 0;
			double g = 0;
			double b = 0;			
			double shade = 0;
			double spec  = 0;
			Vector3 dir = dg->p() - p();
			Vector3 d = v.direction();				
			Point3 c;
			Point3 p = dg->p();


			shade = (dir * dg->n()) / (dir.length() * dg->n().length());				
			Vector3 reflect = (dir - 2.0*dg->n()*(dir*dg->n())).normalize();
			double dot = d*reflect;

			if (shade > 0) shade = 0; else shade = -shade;
			if (dot > 0) dot = 0; else dot = -dot;

			spec = powf(dot,100);

			r = dg->material()->ambientcolor().r*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r + dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r*shade + dg->material()->speccolor().r*spec;
			g = dg->material()->ambientcolor().g*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g + dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g*shade + dg->material()->speccolor().g*spec;
			b = dg->material()->ambientcolor().b*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b + dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b*shade + dg->material()->speccolor().b*spec;					

			if (r > 1.0) r = 1.0;
			if (g > 1.0) g = 1.0;
			if (b > 1.0) b = 1.0;


			return TRadiance(r,g,b);			
		}

		virtual bool intersect(const Ray& r) const {
			return false;
		}

		virtual Point3 pick_point() const {
			return Point3();
		}

					


		LightType type() const {
			return POINT_LIGHT;
		}

		Point3&  position(){ return m_p; }
};

class AreaLight : public Light
{
	public:
		AreaLight(Point3& pp) : Light(pp) {	
			m_w = 2;
			m_h = 2;
		};

		AreaLight() : Light() {	
			m_w = 2;
			m_h = 2;
		};

		AreaLight(Point3& pp,Vector3& v) : Light(pp,v) {

			m_w = 2;
			m_h = 2;
			m_sample = 10;

			Vertex a(p().x()+m_w,p().y(),p().z()-m_h);
			Vertex b(p().x()-m_w,p().y(),p().z()-m_h);
			Vertex c(p().x()+m_w,p().y(),p().z()+m_h);

			Vertex d(p().x()-m_w,p().y(),p().z()-m_h);
			Vertex e(p().x()-m_w,p().y(),p().z()+m_h);
			Vertex f(p().x()+m_w,p().y(),p().z()+m_h);

			m_fa = new Triangle(a,b,c);
			m_fb = new Triangle(d,e,f);

			srand(100);

		};


		virtual TRadiance l(const Ray& v,DifferentialGeometry* dg) const {

			double r=0,g=0,b=0;

			double shade = 0;
			double spec  = 0;
			Vector3 dir = dg->p() - p();
			Vector3 d = v.direction();				
			Point3 c;
			Point3 p = dg->p();



			shade = (dir * dg->n()) / (dir.length() * dg->n().length());				
			Vector3 reflect = (dir - 2.0*dg->n()*(dir*dg->n())).normalize();
			double dot = d*reflect;

			if (shade > 0) shade = 0; else shade = -shade;
			if (dot > 0) dot = 0; else dot = -dot;

			spec = powf(dot,100);

			r = 0.3*dg->material()->ambientcolor().r*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r  + 1.0*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r*shade + 0.9*dg->material()->speccolor().r*spec;
			g = 0.3*dg->material()->ambientcolor().g*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g  + 1.0*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g*shade + 0.9*dg->material()->speccolor().g*spec;
			b = 0.3*dg->material()->ambientcolor().b*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b  + 1.0*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b*shade + 0.9*dg->material()->speccolor().b*spec;					

			if (r > 1.0) r = 1.0;
			if (g > 1.0) g = 1.0;
			if (b > 1.0) b = 1.0;

			return TRadiance(r,g,b);	

		}

		virtual bool intersect(const Ray& r) const {
			float t = 0;
			return  ( (m_fa->intersectp(r,&t)) || (m_fb->intersectp(r,&t)) );				
		}

		virtual Point3 pick_point() const {
			return rand_point();
		}

		LightType type() const {
			return AREA_LIGHT;
		}

		Point3&  position(){ return m_p; }
		double& w(){ return m_w; }
		double& h(){ return m_h; }

		void setW(double w_){ m_w = w_ ; }
		void setH(double h_){ m_h = h_ ; }

	private:
		double m_w;
		double m_h;

		Triangle* m_fa;
		Triangle* m_fb;
		double m_sample;
		Point3 rand_point() const
		{
			return Point3(p().x() + (m_w*random()-(m_w / 2.0)),p().y(),p().z() + (m_h*random()-(m_h / 2.0)));
		}
};




#endif