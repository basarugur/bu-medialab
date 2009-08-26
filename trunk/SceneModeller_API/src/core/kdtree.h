//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef KDTREE_H
#define KDTREE_H

#include "shape.h"
#include "primitive.h"


class Intersection;
class Ray;	

	class SM_API_EXPORT KdtreeNode
	{
		public:
			KdtreeNode() {
				m_left = NULL;
				m_right = NULL;
				m_box = new BBox();
			};				

			void set_depth(int d) const { m_depth = d; };
			int depth() const { return m_depth; };
			
			void add_face(const Triangle* t) const { m_data.push_back(t); };
			const std::vector<const Triangle*>& facelist() const { return m_data; };
			void clearlist() const { m_data.clear(); };
			
			void set_center(const Vector3& v) const { m_center = v; };
			const Vector3& center() const { return m_center; };

			void set_bounds(const Point3& min,const Point3& max) const {
				m_bounds[0] = min;
				m_bounds[1] = max;
			}		

			bool is_leaf()	const { return ((m_left==NULL) && (m_right== NULL)); };				
			bool is_empty()	const { return (m_data.size()==0); };
			bool is_parent() const { return !((m_left==NULL) && (m_right==NULL)); };
			BBox* box() const { return m_box; };

			void set_left(KdtreeNode* n) { m_left = n; }
			void set_right(KdtreeNode* n) { m_right = n; }

			KdtreeNode* left() const { return m_left; }
			KdtreeNode* right() const { return m_right; }

			const Point3* bounds() const { return m_bounds; };

			//Smits’ algorithm (optimized version)
			bool intersect(const Ray& r,float* t0,float* t1) const
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
			
			void calculate_bounds(std::vector<Triangle*>&) const;

		private:
			mutable int m_depth;
			mutable std::vector<const Triangle*> m_data;
			mutable Vector3 m_center;
			mutable Point3 m_bounds[2];
			mutable KdtreeNode* m_left;
			mutable KdtreeNode* m_right;
			mutable BBox* m_box;
	};

	class SM_API_EXPORT Kdtree
	{
		public:	
			Kdtree(){
				m_root = new KdtreeNode();
			};

			KdtreeNode* root() const { return m_root; };
			bool intersect(const Ray&,Intersection*) const;
			bool intersectp(const Ray&) const;	
			void build(int maxdepth,int threshold,std::vector<Triangle*>& list);
		private:
			KdtreeNode* m_root;
			bool examine(const Ray& r,Intersection* isect) const;		
			bool examine_shadow(const Ray& r) const;
			KdtreeNode* build_recursion(std::vector<Triangle*> list,int depth);
			void split(const std::vector<Triangle*>& list,std::vector<Triangle*>&,std::vector<Triangle*>&,double,int);
			void intersect_nodes(KdtreeNode*,Ray,float*,float*,Intersection* isect,double& mint,bool& hitted,int depth = 0) const;
			void intersect_nodes(KdtreeNode*,Ray,float*,float*,double& mint,bool& hitted,int depth = 0) const;

	};


#endif