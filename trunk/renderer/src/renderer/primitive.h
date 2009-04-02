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

namespace acc 
{
	class KdtreeNode;
	class Kdtree;
}

namespace scene
{
	class Primitive;
	class GeomPrimitive;

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
			GeomPrimitive(Shape* s,Material* m) :m_shape(s),m_material(m) {

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

		private:
			Shape* m_shape;
			Material* m_material;			
	};


};

#endif