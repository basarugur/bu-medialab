


#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "vertex.h"
#include "normal3.h"
#include "point3.h"
#include "material.h"

#include "bbox.h"
#include "ray.h"
//#include "diffgeometry.h"

class  DifferentialGeometry;

class SM_API_EXPORT Triangle
{
	public:
		Triangle(Vertex* a,Vertex* b,Vertex* c) 
		{
			m_a = a ; m_b=b; m_c=c ;

			Point3 mid((m_a->x() + m_b->x() + m_c->x())/(double)3,
					          (m_a->y() + m_b->y() + m_c->y())/(double)3,
					          (m_a->z() + m_b->z() + m_c->z())/(double)3);

			m_midpoint = mid;

			Vector3 v = ((*m_c - *m_a) ^ (*m_b - *m_a)).normalize();
			
			m_n = Normal3(v.x(),v.y(),v.z());

			m_selected = false;
		};
		Triangle(Vertex a,Vertex b,Vertex c) 
		{
			m_material = NULL;

			m_v[0] = a;
			m_v[1] = b;
			m_v[2] = c;

			Point3 mid((m_a->x() + m_b->x() + m_c->x())/(double)3,
				(m_a->y() + m_b->y() + m_c->y())/(double)3,
				(m_a->z() + m_b->z() + m_c->z())/(double)3);

			m_midpoint = mid;

			//A triangle has a,b,c vertices, for cw ordered vertices, the normal is (b-a) x (c-a).
			//Since, rhino sorts the vertices in ccw order, we calculate the normals as (c-a) x (b-a). 
			//We use face forwarding which recalculate the normals. If the normal looks back we negate
			//the vector and send it to the light to make proper calculation.
			Vector3 v = ((m_v[2] - m_v[0]) ^ (m_v[1] - m_v[0])).normalize();

			m_n = Normal3(v.x(),v.y(),v.z());
		};
		Triangle()
		{

		}
		void restoreNormalAndMidPoint()
		{
			Point3 mid((m_a->x() + m_b->x() + m_c->x())/3,
					          (m_a->y() + m_b->y() + m_c->y())/3,
					          (m_a->z() + m_b->z() + m_c->z())/3);

			m_midpoint = mid;

			Vector3 v = ((*m_c - *m_a) ^ (*m_b - *m_a)).normalize();
			
			m_n = Normal3(v.x(),v.y(),v.z());
		}

		
		Vertex* a() const { return m_a; }; 
		Vertex* b() const { return m_b; }; 
		Vertex* c() const { return m_c; }; 	

		Vertex* v(int i) 
		{
			if(i==0) return m_a;
			if(i==1) return m_b;
			return m_c;
		}

		const Normal3& n() const { return m_n; };
		const Point3& mid() const { return m_midpoint; };

		bool isSelected(){ return m_selected; }
		void select(bool bl_){ m_selected = bl_; }

		void setA(Vertex* a){ m_a = a ;  };
		void setB(Vertex* b){ m_b = b ;  };
		void setC(Vertex* c){ m_c = c ;  };


		void set_material(Material* m) { m_material = m;};
		const Material* material() const { return m_material; };

		void set_box(BBox b) { m_box = b; };


		//Fast minimum storage ray / triangle intersection. ( Tomas Moller )
		bool intersect(const Ray& r,float *hit,DifferentialGeometry* dg) const;

		bool intersectp(const Ray& r,float *hit) const
		{
			Vector3 dir = r.direction();
			Vector3 org(r.origin().x(),r.origin().y(),r.origin().z());
			Vector3 e1 = (m_v[1] - m_v[0]);
			Vector3 e2 = (m_v[2] - m_v[0]);
			Vector3 pvec = dir ^ e2;
			double det = e1 * pvec;

			if (det  == 0) {				
				return false;
			}

			double inv_det = 1.0 / det;
			Vector3 tvec = org - m_v[0];
			double u = (tvec * pvec) * inv_det;

			if ((u<0.0) || (u>1.0)) {				
				return false;
			}

			Vector3 qvec = tvec ^ e1;
			double v = (dir * qvec) * inv_det;

			if ((v<0.0) || ((v+u)>1.0)) {			
				return false;
			}

			*hit = (e2 * qvec)*inv_det;
			return true;
		};

	public:
		Vertex* m_a;
		Vertex* m_b;
		Vertex* m_c;
		Normal3 m_n;
		Point3 m_midpoint;
		bool m_selected;

		Vertex m_v[3];
		Material* m_material;
		BBox m_box;
};

#endif