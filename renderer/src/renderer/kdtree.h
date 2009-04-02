//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef KDTREE_H
#define KDTREE_H

#include "shape.h"
#include "primitive.h"

namespace scene
{
	class Intersection;
	class Ray;	
}

namespace acc
{
		class KdtreeNode
		{
			public:
				KdtreeNode() {
					m_left = NULL;
					m_right = NULL;
					m_box = new scene::BBox();
				};				

				void set_depth(int d) const { m_depth = d; };
				int depth() const { return m_depth; };
				
				void add_face(const scene::Triangle* t) const { m_data.push_back(t); };
				const std::vector<const scene::Triangle*>& facelist() const { return m_data; };
				void clearlist() const { m_data.clear(); };
				
				void set_center(const space::Vector3& v) const { m_center = v; };
				const space::Vector3& center() const { return m_center; };

				void set_bounds(const space::Point3& min,const space::Point3& max) const {
					m_bounds[0] = min;
					m_bounds[1] = max;
				}		

				bool is_leaf()	const { return ((m_left==NULL) && (m_right== NULL)); };				
				bool is_empty()	const { return (m_data.size()==0); };
				bool is_parent() const { return !((m_left==NULL) && (m_right==NULL)); };
				scene::BBox* box() const { return m_box; };

				void set_left(KdtreeNode* n) { m_left = n; }
				void set_right(KdtreeNode* n) { m_right = n; }

				KdtreeNode* left() const { return m_left; }
				KdtreeNode* right() const { return m_right; }

				const space::Point3* bounds() const { return m_bounds; };

				//Smits’ algorithm (optimized version)
				bool intersect(const scene::Ray& r,float* t0,float* t1) const
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

					*t0 = tmin;
					*t1 = tmax;
					return ( (tmin < r.maxt()) && (tmax > r.mint()) );					
				}
				
				void calculate_bounds(std::vector<scene::Triangle*>&) const;

			private:
				mutable int m_depth;
				mutable std::vector<const scene::Triangle*> m_data;
				mutable space::Vector3 m_center;
				mutable space::Point3 m_bounds[2];
				mutable KdtreeNode* m_left;
				mutable KdtreeNode* m_right;
				mutable scene::BBox* m_box;
		};

		class Kdtree
		{
			public:	
				Kdtree(){
					m_root = new KdtreeNode();
				};

				KdtreeNode* root() const { return m_root; };
				bool intersect(const scene::Ray&,scene::Intersection*) const;
				bool intersectp(const scene::Ray&) const;	
				void build(int maxdepth,int threshold,std::vector<scene::Triangle*>& list);
			private:
				KdtreeNode* m_root;
				bool examine(const scene::Ray& r,scene::Intersection* isect) const;		
				bool examine_shadow(const scene::Ray& r) const;
				acc::KdtreeNode* build_recursion(std::vector<scene::Triangle*> list,int depth);
				void split(const std::vector<scene::Triangle*>& list,std::vector<scene::Triangle*>&,std::vector<scene::Triangle*>&,double,int);
				void intersect_nodes(acc::KdtreeNode*,scene::Ray,float*,float*,scene::Intersection* isect,double& mint,bool& hitted,int depth = 0) const;
				void intersect_nodes(acc::KdtreeNode*,scene::Ray,float*,float*,double& mint,bool& hitted,int depth = 0) const;

		};
};

#endif