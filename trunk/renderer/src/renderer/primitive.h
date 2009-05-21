//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "shape.h"
#include "film.h"
#include "light.h"
#include "material.h"
#include "octree.h"
#include "kdtree.h"
#include "vector3.h"
#include "matrix.h"

#include <cmath>

namespace acc 
{
	class KdtreeNode;
	class Kdtree;
}

namespace scene
{
	class Primitive;
	class GeomPrimitive;

	class Transformation 
	{
		public:
			Transformation() {
				m_transform.identity();
			};

			void rotate(double x,double y,double z,int angle) 
			{
				double c = cos(degtorad(angle));
				double s = sin(degtorad(angle));

				m_rotation.setcell(0,0,x*x*(1-c)+c);
				m_rotation.setcell(0,1,x*y*(1-c)-z*s);
				m_rotation.setcell(0,2,x*z*(1-c)+y*s);
				m_rotation.setcell(0,3,0);

				m_rotation.setcell(1,0,y*x*(1-c)+z*s);
				m_rotation.setcell(1,1,y*y*(1-c)+c);
				m_rotation.setcell(1,2,y*z*(1-c)-x*s);
				m_rotation.setcell(1,3,0);

				m_rotation.setcell(2,0,x*z*(1-c)-y*s);
				m_rotation.setcell(2,1,y*z*(1-c)+x*s);
				m_rotation.setcell(2,2,z*z*(1-c)+c);
				m_rotation.setcell(2,3,0);

				m_rotation.setcell(3,0,0);
				m_rotation.setcell(3,1,0);
				m_rotation.setcell(3,2,0);
				m_rotation.setcell(3,3,1);

				m_transform = m_rotation * m_transform;
			}
			
			void rotate(double x,double y,double z,double angle) 
			{
				double c = cos(angle);
				double s = sin(angle);

				m_rotation.setcell(0,0,x*x*(1-c)+c);
				m_rotation.setcell(0,1,x*y*(1-c)-z*s);
				m_rotation.setcell(0,2,x*z*(1-c)+y*s);
				m_rotation.setcell(0,3,0);

				m_rotation.setcell(1,0,y*x*(1-c)+z*s);
				m_rotation.setcell(1,1,y*y*(1-c)+c);
				m_rotation.setcell(1,2,y*z*(1-c)-x*s);
				m_rotation.setcell(1,3,0);

				m_rotation.setcell(2,0,x*z*(1-c)-y*s);
				m_rotation.setcell(2,1,y*z*(1-c)+x*s);
				m_rotation.setcell(2,2,z*z*(1-c)+c);
				m_rotation.setcell(2,3,0);

				m_rotation.setcell(3,0,0);
				m_rotation.setcell(3,1,0);
				m_rotation.setcell(3,2,0);
				m_rotation.setcell(3,3,1);

				m_transform = m_rotation * m_transform;
			}

			void scale(double x,double y,double z) 
			{
				m_scale.setcell(0,0,x); m_scale.setcell(0,1,0);	m_scale.setcell(0,2,0);	m_scale.setcell(0,3,0);
				m_scale.setcell(1,0,0); m_scale.setcell(1,1,y);	m_scale.setcell(1,2,0);	m_scale.setcell(1,3,0);
				m_scale.setcell(2,0,0); m_scale.setcell(2,1,0);	m_scale.setcell(2,2,z);	m_scale.setcell(2,3,0);
				m_scale.setcell(3,0,0); m_scale.setcell(3,1,0);	m_scale.setcell(3,2,0);	m_scale.setcell(3,3,1);

				m_transform = m_scale * m_transform;
			}

			void translate(double x,double y,double z) 
			{
				m_translate.setcell(0,0,1); m_translate.setcell(0,1,0);	m_translate.setcell(0,2,0);	m_translate.setcell(0,3,x);
				m_translate.setcell(1,0,0); m_translate.setcell(1,1,1);	m_translate.setcell(1,2,0);	m_translate.setcell(1,3,y);
				m_translate.setcell(2,0,0); m_translate.setcell(2,1,0);	m_translate.setcell(2,2,1);	m_translate.setcell(2,3,z);
				m_translate.setcell(3,0,0); m_translate.setcell(3,1,0);	m_translate.setcell(3,2,0);	m_translate.setcell(3,3,1);

				m_transform = m_translate * m_transform;
			}

			space::Point3 apply(space::Point3& p) {
				return m_transform * p;
			}

			scene::Shape* apply(scene::Shape* s) {
				
				if (s->can_intersect() == false)
				{
					std::vector<scene::Triangle*> list = s->refine();
					std::vector<scene::Triangle*> list2;
					for(int i=0;i<list.size();i++)
					{
						space::Vector3 v1 = m_transform * static_cast<space::Vector3>(list[i]->a());
						space::Vector3 v2 = m_transform * static_cast<space::Vector3>(list[i]->b());
						space::Vector3 v3 = m_transform * static_cast<space::Vector3>(list[i]->c());
					
						scene::Triangle* t = new scene::Triangle(scene::Vertex(v1),scene::Vertex(v2),scene::Vertex(v3));
						list2.push_back(t);
					}		

					scene::Shape* rets = new scene::TriangleMesh(list2);

					return rets;

				} else {
					return NULL;
				}
			}

		private:

			space::Matrix m_rotation;
			space::Matrix m_scale;
			space::Matrix m_translate;
			space::Matrix m_transform;
	};

	class Intersection 
	{
		public:
			Intersection() { 				
			};			

			DifferentialGeometry* dg() const { return &m_dg; };			
		private:			
			mutable DifferentialGeometry m_dg;			
	};

	class Primitive
	{
		public:	
			Primitive(){};
			
			virtual bool can_intersect() const = 0;				
			virtual const std::vector<Triangle*>& refine() const = 0;				
			virtual bool intersect(const Ray&,Intersection*) const = 0;
			virtual bool intersectp(const Ray&) const = 0;
			virtual Material* material() const = 0;
			virtual BBox object_bound() const = 0;
	};

	class Aggregate
	{
		public:
			Aggregate();
					
			bool intersect(const Ray&,Intersection*) const;
			bool intersectp(const Ray&) const;	
			
			void add_primitive(Primitive*);
			void post();
		private:
			std::vector<Primitive*> m_primitives;
			std::vector<Triangle*> m_list;

			//bsp tree 
			acc::Kdtree* m_tree;
			

	};

	class GeomPrimitive : public Primitive
	{
		public:
			GeomPrimitive(Shape* s,Material* m,Transformation* t) {
				
				m_transform = t;
				m_material  = m;
				m_shape = m_transform->apply(s);
				
			};

			virtual bool can_intersect() const {
				return m_shape->can_intersect();
			}

			virtual const std::vector<Triangle*>& refine() const {
				return m_shape->refine();
			}
		
			virtual bool intersect(const Ray& r,Intersection* isect) const {				
				return false;		
			};

			virtual bool intersectp(const Ray& r) const {
				return false;
			};

			virtual Material* material() const {
				return m_material;
			}

			virtual BBox object_bound() const {
				return m_shape->object_bound();
			};

		private:
			Shape* m_shape;
			Material* m_material;
			Transformation* m_transform;
	};


};

#endif