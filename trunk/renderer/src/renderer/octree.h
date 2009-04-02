//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef OCTREE_H
#define OCTREE_H

#include <vector>

#include "shape.h"
#include "vector3.h"

#define TOLERANCE 0.001
#define MAX_OCTREE_DEPTH 20

template<class T> inline T max(T a, T b) { return (a>b)  ?  a:b; };
template<class T> inline T min(T a, T b) { return (a<b)  ?  a:b; };

template<class T> inline T max(T v1, T v2, T v3)	{	return max(v1,max(v2,v3));	};
template<class T> inline T min(T v1, T v2, T v3)	{	return min(v1,min(v2,v3));	};

inline bool isIn( double value, double lower, double upper, bool includeBoundaries = true )
{
	if(includeBoundaries)
		return (lower-TOLERANCE < value) && (value < upper+TOLERANCE);
	else
		return (lower+TOLERANCE < value) && (value < upper-TOLERANCE);
}

namespace acc
{
		class OctreeNode
		{
			public:
				OctreeNode() : m_child(NULL) {};
				~OctreeNode() {
					if (m_child != NULL)
						delete[] m_child;
				};

				void set_depth(int d) const { m_depth = d; };
				int depth() const { return m_depth; };
				
				void add_face(const scene::Triangle* t) const { m_data.push_back(t); };
				const std::vector<const scene::Triangle*>& facelist() const { return m_data; };
				void clearlist() const { m_data.clear(); };
				
				void set_center(const space::Vector3& v) const { m_center = v; };
				const space::Vector3& center() const { return m_center; };
				
				void set_childs(OctreeNode* n) const { m_child = n; };
				OctreeNode* child() const { return m_child; };

				bool is_leaf()	{ return (m_child==NULL); };
				bool is_parent()	{ return (m_child!=NULL); };
				bool is_empty()	{ return (m_data.size()==0); };

				void set_bounds(const space::Point3& min,const space::Point3& max) const {
					m_bounds[0] = min;
					m_bounds[1] = max;
				}			

				const space::Point3* bounds() const { return m_bounds; };

				//Smits’ algorithm
				bool intersect(const scene::Ray& r,float t0,float t1)
				{
					float tmin,tymin,tzmin;
					float tmax,tymax,tzmax;

					tmin = (bounds()[r.sign(0)].x() - r.origin().x()) * r.inv_direction().x();
					tmax = (bounds()[1-r.sign(0)].x() - r.origin().x()) * r.inv_direction().x();

					tymin = (bounds()[r.sign(1)].y() - r.origin().y()) * r.inv_direction().y();
					tymax = (bounds()[1-r.sign(1)].y() - r.origin().y()) * r.inv_direction().y();

					if ( ( tmin > tymax) || (tymin > tmax) ) return false;
					if (tymin > tmin) tmin = tymin;
					if (tymax < tmax) tmax = tymax;

					tzmin = (bounds()[r.sign(2)].z() - r.origin().z()) * r.inv_direction().z();
					tzmax = (bounds()[1-r.sign(2)].z() - r.origin().z()) * r.inv_direction().z();

					if ( ( tmin > tzmax) || (tzmin > tmax) ) return false;
					if (tzmin > tmin) tmin = tzmin;
					if (tzmax < tmax) tmax = tzmax;

					return ( (tmin < t1) && (tmax > t0) );

				}

			private:
				mutable int m_depth;
				mutable std::vector<const scene::Triangle*> m_data;
				mutable space::Vector3 m_center;
				mutable space::Point3 m_bounds[2];
				mutable OctreeNode* m_child;
		};

		class Octree
		{
			public:
				Octree() : m_depth(0) {					
					m_root  = new OctreeNode();
					m_root->set_depth(0);
				};

				~Octree() {
					m_depth = 0;
					delete m_root;
				};
				
				void calculate_half_dims(int maxdepth = MAX_OCTREE_DEPTH )	{
					
					for(std::size_t i=0;i<maxdepth;i++)
						m_halfdims[i+1] = m_halfdims[i] / 2.0;
				};

				bool contains(OctreeNode* node,const space::Vector3& point) {
					
					space::Vector3 &hd = m_halfdims[node->depth()];
					return isIn(point.x() - node->center().x(), -hd.x(), hd.x())
								&& isIn(point.y() - node->center().y(), -hd.y(), hd.y())
								&& isIn(point.z() - node->center().z(), -hd.z(), hd.z());
				}

				void subdivide( OctreeNode *node ) {

					node->set_childs(new OctreeNode[8]);

					for( int i=0; i<8; i++ )
						node->child()[i].set_depth(node->depth() + 1);

					// define the centers of the children
					space::Vector3 nc = node->center();
					space::Vector3 hd = m_halfdims[node->child()->depth()];
					node->child()[0].set_center(space::Vector3(nc.x() + hd.x(), nc.y() + hd.y(), nc.z() + hd.z()));
					node->child()[1].set_center(space::Vector3(nc.x() - hd.x(), nc.y() + hd.y(), nc.z() + hd.z()));
					node->child()[2].set_center(space::Vector3(nc.x() - hd.x(), nc.y() - hd.y(), nc.z() + hd.z()));
					node->child()[3].set_center(space::Vector3(nc.x() + hd.x(), nc.y() - hd.y(), nc.z() + hd.z()));
					//
					node->child()[4].set_center(space::Vector3(nc.x() + hd.x(), nc.y() + hd.y(), nc.z() - hd.z()));
					node->child()[5].set_center(space::Vector3(nc.x() - hd.x(), nc.y() + hd.y(), nc.z() - hd.z()));
					node->child()[6].set_center(space::Vector3(nc.x() - hd.x(), nc.y() - hd.y(), nc.z() - hd.z()));
					node->child()[7].set_center(space::Vector3(nc.x() + hd.x(), nc.y() - hd.y(), nc.z() - hd.z()));
				}

				bool inside(const acc::OctreeNode* node,const scene::Triangle* triangle) const;

				void set_depth(int d) { m_depth = d; };
				int depth() { return m_depth; };
				space::Vector3* halfdims(){ return m_halfdims; };
				OctreeNode* root() { return m_root; };
			private:
				int m_depth;
				space::Vector3 m_halfdims[MAX_OCTREE_DEPTH];
				OctreeNode * m_root;
		};
};

#endif