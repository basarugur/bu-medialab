


#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "shape.h"
#include "film.h"
#include "light.h"
#include "material.h"
#include "vector3.h"
#include "transformation.h"
#include "kdtree.h"

class KdtreeNode;
class Kdtree;


class Primitive
{
	public:	
		Primitive(){};

			
		virtual Material* material() const = 0;

		virtual bool can_intersect() const = 0;				
		virtual const std::vector<Triangle*>& refine() const = 0;				
		virtual bool intersect(const Ray&,Intersection*) const = 0;
		virtual bool intersectp(const Ray&) const = 0;
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
	Kdtree* m_tree;


};

#endif