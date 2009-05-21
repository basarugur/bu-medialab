//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "material.h"
#include "vector3.h"
#include "normal3.h"
#include "point3.h"
#include "ray.h"

namespace scene
{
	class DifferentialGeometry;
	class Triangle;	

	class Shape
	{
		public:	
			Shape() {};						
			virtual BBox object_bound() const = 0;
			virtual bool can_intersect() const = 0;
			virtual const std::vector<Triangle*>& refine() const = 0;

			virtual bool intersect(const scene::Ray& r,float *hit,DifferentialGeometry* d) const {
				return  false;
			};
			virtual bool intersectp(const scene::Ray& r) const {
				return false;
			};
	};

	class DifferentialGeometry 
	{
		public:
			DifferentialGeometry() { 
				m_u = 0.0;
				m_v = 0.0;
				m_shape = NULL;
			}

			DifferentialGeometry(const space::Point3& p, const space::Vector3& dpdu,
				 				 const space::Vector3& dpdv,const Shape* s, float u=0.0, float v=0.0,float w=0.0)
								 : m_p(p),m_dpdu(dpdu),m_dpdv(dpdv)
			{
				space::Vector3 vv = (dpdu ^ dpdv).normalize();
				m_n = space::Normal3(vv.x(),vv.y(),vv.z());
				m_u = u;
				m_v = v;
				m_w = w;
				m_shape = s;
			}

			void set_material(Material* m) { m_material = m; };
			Material* material() const { return m_material; };
			void setnormal(const space::Normal3& normal) const { m_n = normal; };
			void setp(const space::Point3& point) const { m_p = point; };
			void setuv(const space::Vector3& u,const space::Vector3&  v) { m_dpdu = u; m_dpdv = v; };	
			void setuv(float u,float v,float w) { m_u = u; m_v = v; m_w = w; };
			const space::Normal3& n() const { return m_n; };
			const space::Point3& p() const { return m_p; };
			float u() const { return m_u; };
			float v() const { return m_v; };
			float w() const { return m_w; };

		private:
			mutable space::Point3 m_p;
			mutable space::Normal3 m_n;
			scene::Material* m_material;
			space::Vector3 m_dpdu,m_dpdv;			
			const Shape* m_shape;
			float m_u,m_v,m_w;
	};

	class Vertex : public space::Vector3
	{
		public:
			Vertex(double _x=0,double _y=0,double _z=0) : space::Vector3(_x,_y,_z)
			{};
			Vertex(space::Vector3 v) : space::Vector3(v) 
			{};
	};

	class Triangle
	{
		public:
			Triangle(Vertex a,Vertex b,Vertex c) 
			{
				m_material = NULL;

				m_v[0] = a;
				m_v[1] = b;
				m_v[2] = c;

				space::Point3 mid((m_v[0].x() + m_v[1].x() + m_v[2].x())/3,
						          (m_v[0].y() + m_v[1].y() + m_v[2].y())/3,
						          (m_v[0].z() + m_v[1].z() + m_v[2].z())/3);

				m_midpoint = mid;

				//A triangle has a,b,c vertices, for cw ordered vertices, the normal is (b-a) x (c-a).
				//Since, rhino sorts the vertices in ccw order, we calculate the normals as (c-a) x (b-a). 
				//We use face forwarding which recalculate the normals. If the normal looks back we negate
				//the vector and send it to the light to make proper calculation.
				space::Vector3 v = ((m_v[2] - m_v[0]) ^ (m_v[1] - m_v[0])).normalize();
				
				m_n = space::Normal3(v.x(),v.y(),v.z());	
			};

			//Fast minimum storage ray / triangle intersection. ( Tomas Moller )
			bool intersect(const Ray& r,float *hit,DifferentialGeometry* dg) const
			{
				space::Vector3 dir = r.direction();
				space::Vector3 org(r.origin().x(),r.origin().y(),r.origin().z());
				space::Vector3 e1 = (m_v[1] - m_v[0]);
				space::Vector3 e2 = (m_v[2] - m_v[0]);
				space::Vector3 pvec = dir ^ e2;
				double det = e1 * pvec;
				
				//(det > -ZERO && det < ZERO)
				if (det == 0) {
					dg = NULL;
					*hit = 1e30;				
					return false;
				}

				double inv_det = 1.0 / det;
				space::Vector3 tvec = org - m_v[0];
				double u = (tvec * pvec) * inv_det;

				if ((u<0.0) || (u>1.0)) {
					dg = NULL;
					*hit = 1e30;				
					return false;
				}

				space::Vector3 qvec = tvec ^ e1;
				double v = (dir * qvec) * inv_det;
				
				if ((v<0.0) || ((v+u)>1.0)) {
					dg = NULL;
					*hit = 1e30;				
					return false;
				}

				double t = (e2 * qvec)*inv_det;
				//face forwarding
				space::Normal3 fn;

				if (n()*r.direction()>0) fn = space::Normal3(-n().x(),-n().y(),-n().z()); 
				else fn = space::Normal3(n().x(),n().y(),n().z());
				space::Point3 p = r.origin() + (r.direction()*t);

				float u_ = p.x() - m_box.min().x();
				float v_ = p.y() - m_box.min().y();
				float w_ = p.z() - m_box.min().z();

				dg->setp(p);
				dg->setnormal(fn);
				dg->set_material(m_material);				
				dg->setuv(u_,v_,w_);
				*hit = t;
				return true;
			};

			bool intersectp(const Ray& r,float *hit) const
			{
				space::Vector3 dir = r.direction();
				space::Vector3 org(r.origin().x(),r.origin().y(),r.origin().z());
				space::Vector3 e1 = (m_v[1] - m_v[0]);
				space::Vector3 e2 = (m_v[2] - m_v[0]);
				space::Vector3 pvec = dir ^ e2;
				double det = e1 * pvec;
				
				if (det  == 0) {				
					return false;
				}

				double inv_det = 1.0 / det;
				space::Vector3 tvec = org - m_v[0];
				double u = (tvec * pvec) * inv_det;

				if ((u<0.0) || (u>1.0)) {				
					return false;
				}

				space::Vector3 qvec = tvec ^ e1;
				double v = (dir * qvec) * inv_det;
				
				if ((v<0.0) || ((v+u)>1.0)) {			
					return false;
				}

				*hit = (e2 * qvec)*inv_det;
				return true;
			};
			
			const Vertex& a() const { return m_v[0]; }; 
			const Vertex& b() const { return m_v[1]; }; 
			const Vertex& c() const { return m_v[2]; }; 			
			const Vertex& v(int i) const { return m_v[i]; };
			const space::Normal3& n() const { return m_n; };
			const space::Point3& mid() const { return m_midpoint; };

			void set_material(scene::Material* m) { m_material = m;};
			const scene::Material* material() const { return m_material; };

			void set_box(scene::BBox b) { m_box = b; };

		private:
			Vertex m_v[3];
			space::Normal3 m_n;
			space::Point3 m_midpoint;
			scene::Material* m_material;
			scene::BBox m_box;
	};

	class TriangleMesh : public Shape
	{
		public:
			TriangleMesh(const std::string& str) 
			{
				m_filename = str;
				load();
				calculatebounds();
			};

			TriangleMesh(std::vector<Triangle*> m_list) 
			{
				m_facelist = m_list;
				calculatebounds();
			}
	
			virtual BBox object_bound() const;
			virtual bool can_intersect() const { return false; }
			virtual const std::vector<Triangle*>& refine() const { return m_facelist; }
			virtual bool intersect(const scene::Ray& r,float *hit,DifferentialGeometry* d) const {
				//
				return false;
			};
			virtual bool intersectp(const scene::Ray& r) const {
				//
				return false;
			};
		private:
			mutable std::vector<Triangle*> m_facelist;
			std::string m_filename;
			double max_x,max_y,max_z;
			double min_x,min_y,min_z;	
			
			bool load();
			void calculatebounds();
	};
};

#endif