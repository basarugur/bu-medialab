//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef LIGHT_H
#define LIGHT_H

#include "film.h"
#include "vector3.h"
#include "point3.h"
#include "shape.h"

namespace scene
{
	class Light
	{
		public:	
			Light(space::Point3& p,space::Vector3& d) : m_p(p), m_d(d) {
				m_coeff  = 1.0;
			};
			
			virtual output::TRadiance l(const Ray& v,DifferentialGeometry* dg) const = 0;						
			virtual output::TRadiance s(const Ray& v,DifferentialGeometry* dg) const {			
				double r = 0;
				double g = 0;
				double b = 0;
				
				space::Point3 c;
				space::Point3 p = dg->p();

				r = 0.3*dg->material()->ambientcolor().r*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r;
				g = 0.3*dg->material()->ambientcolor().g*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g;
				b = 0.3*dg->material()->ambientcolor().b*dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b;				

				return output::TRadiance(r,g,b);			
			}
			virtual bool intersect(const Ray& r) const = 0;
			virtual space::Point3 pick_point() const = 0;
			virtual int type() const = 0;
			const space::Point3& p() const { return m_p; };
			const space::Vector3& d() const { return m_d; };
			void set_coeff(double p) { m_coeff = p; };
			double coeff() { return m_coeff; };
		private:
			space::Point3 m_p;
			space::Vector3 m_d;
			double m_coeff; 
	};

	class SkyLight : public Light 
	{
		public:
			SkyLight(space::Point3& p,space::Vector3& d) : Light(p,d) {};

			virtual output::TRadiance l(const Ray& v,DifferentialGeometry* dg) const {
				
				space::Point3 c;
				space::Point3 p = dg->p();

				double r = dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).r;
				double g = dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).g;
				double b = dg->material()->diffcolor(dg->u(),dg->v(),dg->w()).b;			
				return output::TRadiance(r,g,b);

			};

			virtual bool intersect(const Ray& r) const {
				return false;
			};

			virtual space::Point3 pick_point() const {
				return space::Point3();
			};

			virtual int type() const { 
				return 2; 
			};
	};

	class PointLight : public Light
	{
		public:
			PointLight(space::Point3& p,space::Vector3& d) : Light(p,d) {};
						
			virtual output::TRadiance l(const Ray& v,DifferentialGeometry* dg) const {
							
				double r = 0;
				double g = 0;
				double b = 0;			
				double shade = 0;
				double spec  = 0;
				space::Vector3 dir = dg->p() - p();
				space::Vector3 d = v.direction();				
				space::Point3 c;
				space::Point3 p = dg->p();

				
				shade = (dir * dg->n()) / (dir.length() * dg->n().length());				
				space::Vector3 reflect = (dir - 2.0*dg->n()*(dir*dg->n())).normalize();
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


				return output::TRadiance(r,g,b);			
			}
			
			virtual bool intersect(const Ray& r) const {
				return false;
			}

			virtual space::Point3 pick_point() const {
				return space::Point3();
			}

			virtual int type() const {
				return 0;
			}
	};

	class AreaLight : public Light
	{
		public:
			AreaLight(space::Point3& pp,space::Vector3& v) : Light(pp,v) {
					
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


			virtual output::TRadiance l(const Ray& v,DifferentialGeometry* dg) const {
			
				double r=0,g=0,b=0;

				double shade = 0;
				double spec  = 0;
				space::Vector3 dir = dg->p() - p();
				space::Vector3 d = v.direction();				
				space::Point3 c;
				space::Point3 p = dg->p();
				

				
				shade = (dir * dg->n()) / (dir.length() * dg->n().length());				
				space::Vector3 reflect = (dir - 2.0*dg->n()*(dir*dg->n())).normalize();
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

				return output::TRadiance(r,g,b);	

			}

			virtual bool intersect(const Ray& r) const {
				float t = 0;
				return  ( (m_fa->intersectp(r,&t)) || (m_fb->intersectp(r,&t)) );				
			}

			virtual space::Point3 pick_point() const {
				return rand_point();
			}

			virtual int type() const {
				return 1;
			}

		private:
			Triangle* m_fa;
			Triangle* m_fb;
			double m_w;
			double m_h;
			double m_sample;
			space::Point3 rand_point() const
			{
				return space::Point3(p().x() + (m_w*random()-(m_w / 2.0)),p().y(),p().z() + (m_h*random()-(m_h / 2.0)));
			}
	};
};



#endif