#include "kdtree.h"

struct FaceLessFunctor
{
	FaceLessFunctor(int index) : axis(index){};

	bool operator()(const scene::Triangle* f0, const scene::Triangle* f1) const
	{
		return f0->mid().v(axis) < f1->mid().v(axis);
	}

	int axis;
};

struct BoxLessFunctor
{
	BoxLessFunctor(int index) : axis(index){};

	bool operator()(const acc::KdtreeNode* f0, const acc::KdtreeNode* f1) const
	{
		return f0->center().v(axis) < f1->center().v(axis);
	}

	int axis;
};

namespace acc
{
	
	bool Kdtree::intersect(const scene::Ray& r,scene::Intersection* isect) const {
		return examine(r,isect);
	}
	bool Kdtree::intersectp(const scene::Ray& r) const {
		return examine_shadow(r);
	}

	void Kdtree::build(int maxdepth,int threshold,std::vector<scene::Triangle*>& list)
	{		
		delete m_root;
		m_root = build_recursion(list,0);		
	}

	void Kdtree::split(const std::vector<scene::Triangle*>& list,std::vector<scene::Triangle*>& leftlist,std::vector<scene::Triangle*>& rightlist,double median,int axis)
	{
		for(int i=0;i<list.size();i++)
		{
			if (list[i]->mid().v(axis) < median)
				leftlist.push_back(list[i]);
			else
				rightlist.push_back(list[i]);
		}
	}

	acc::KdtreeNode* Kdtree::build_recursion(std::vector<scene::Triangle*> list,int depth)
	{
		if (depth < 21)
		{
			if(list.size() == 0)
				return NULL;
			else {
				if(list.size() > 2)
				{
					int axis = depth % 3;	
					acc::KdtreeNode* node = new acc::KdtreeNode();
					node->set_depth(depth);
					node->calculate_bounds(list);					

					std::sort(list.begin(),list.end(),FaceLessFunctor(axis));
					double m = list[0]->mid().v(axis) + ((list[list.size()-1]->mid().v(axis) - list[0]->mid().v(axis)) / 2.0);					

					std::vector<scene::Triangle*> l;
					std::vector<scene::Triangle*> r;
					split(list,l,r,m,axis);

					node->set_left(build_recursion(l,depth+1));
					node->set_right(build_recursion(r,depth+1));
					return node;

				} else {

					acc::KdtreeNode* node = new acc::KdtreeNode();
					node->set_depth(depth);
					node->calculate_bounds(list);
					for(int i=0;i<list.size();i++)
						node->add_face(list[i]);

					return node;
				}
			}
		} else {

			acc::KdtreeNode* node = new acc::KdtreeNode();
			node->set_depth(depth);
			node->calculate_bounds(list);
			for(int i=0;i<list.size();i++)
				node->add_face(list[i]);

			return node;

		}
	}
	
	//for primary ray
	void Kdtree::intersect_nodes(acc::KdtreeNode* node,scene::Ray ray,float* rmin,float* rmax,scene::Intersection* isect,double& mint,bool& hitted,int depth) const
	{			
		if (node != NULL)
		{
				if (node->box()->intersectp(ray,rmin,rmax))			
				{
					if(mint < *rmin)
						return;

					if(node->is_leaf() && !node->is_empty()) {

						float dist = 0;
						scene::DifferentialGeometry* dg = new scene::DifferentialGeometry();

						for(int j=0;j<node->facelist().size();j++)
						{
							const scene::Triangle* face = node->facelist()[j];

							if (face->intersect(ray,&dist,dg) == true)
							{
								if ((mint > dist) && (dist > RAY_EPSILON))
								{		
									mint = dist;
									isect->dg()->setp(dg->p());
									isect->dg()->setnormal(dg->n());							
									isect->dg()->set_material(dg->material());
									isect->dg()->setuv(dg->u(),dg->v(),dg->w());
									hitted = true;
								}
							}						
						}				

						delete dg;
					} else if (node->is_parent()){
						int axis = depth % 3;
						if (ray.direction().v(axis) > 0) {
							intersect_nodes(node->left(),ray,rmin,rmax,isect,mint,hitted,depth+1);
							intersect_nodes(node->right(),ray,rmin,rmax,isect,mint,hitted,depth+1);
						} else {
							intersect_nodes(node->right(),ray,rmin,rmax,isect,mint,hitted,depth+1);
							intersect_nodes(node->left(),ray,rmin,rmax,isect,mint,hitted,depth+1);
						}
					}
				}
		} else return;
	}

	//for shadow rays
	void Kdtree::intersect_nodes(acc::KdtreeNode* node,scene::Ray ray,float* rmin,float* rmax,double& mint,bool& hitted,int depth) const {

		if (node != NULL)
		{
				if (node->box()->intersectp(ray,rmin,rmax))			
				{
					if (hitted == true) return;

					if(node->is_leaf() && !node->is_empty()) {

						float dist = 0;
						for(int j=0;j<node->facelist().size();j++)
						{
							const scene::Triangle* face = node->facelist()[j];

							if (face->intersectp(ray,&dist) == true)
							{
								if ( (dist > RAY_EPSILON) && (dist < ray.maxt()) ) {
									hitted = true;
									return;
								}
							}						
						}				
					} else if (node->is_parent()){
						int axis = depth % 3;
						if (ray.direction().v(axis) > 0) {
							intersect_nodes(node->left(),ray,rmin,rmax,mint,hitted,depth+1);
							intersect_nodes(node->right(),ray,rmin,rmax,mint,hitted,depth+1);
						} else {
							intersect_nodes(node->right(),ray,rmin,rmax,mint,hitted,depth+1);
							intersect_nodes(node->left(),ray,rmin,rmax,mint,hitted,depth+1);
						}
					}
				}
		}
	}

	bool Kdtree::examine_shadow(const scene::Ray& r) const 
	{
		bool ishitted = false;						
		double mint = 1e30;
		float t0 = 0 ,t1 = 0;
		intersect_nodes(m_root,r,&t0,&t1,mint,ishitted,0);
		return ishitted;
	}	 

	bool Kdtree::examine(const scene::Ray& r,scene::Intersection* isect) const
	{					
		bool ishitted = false;						
		double mint = 1e30;
		float t0 = 0 ,t1 = 0;

		intersect_nodes(m_root,r,&t0,&t1,isect,mint,ishitted,0);
		return ishitted;
	}

	void KdtreeNode::calculate_bounds(std::vector<scene::Triangle*>& list) const
	{
		double max_x,max_y,max_z;
		double min_x,min_y,min_z;
		
		max_x = 0;
		max_y = 0; 
		max_z = 0;
		min_x = 0;
		min_y = 0; 
		min_z = 0;				
			
		if (list.size()>0)
		{
			min_x = max_x = list[0]->a().x();
			min_y = max_y = list[0]->a().y();
			min_z = max_z = list[0]->a().z();
		}

		for(std::size_t i=0;i<list.size();i++)
		{
			for(std::size_t j=0;j<3;j++)
			{
				if (max_x < list[i]->v(j).x())
					max_x = list[i]->v(j).x();

				if (max_y < list[i]->v(j).y())
					max_y = list[i]->v(j).y();

				if (max_z < list[i]->v(j).z())
					max_z = list[i]->v(j).z();

				if (min_x > list[i]->v(j).x())
					min_x = list[i]->v(j).x();

				if (min_y > list[i]->v(j).y())
					min_y = list[i]->v(j).y();

				if (min_z > list[i]->v(j).z())
					min_z = list[i]->v(j).z();
			}
		}

		m_bounds[0] = space::Point3(min_x,min_y,min_z);
		m_bounds[1] = space::Point3(max_x,max_y,max_z);
		
		double midx = (m_bounds[1].x() - m_bounds[0].x())/2.0;
		double midy = (m_bounds[1].y() - m_bounds[0].y())/2.0;
		double midz = (m_bounds[1].z() - m_bounds[0].z())/2.0;
		
		m_center = space::Vector3(midx,midy,midz);
		m_box = new scene::BBox(m_bounds[0],m_bounds[1]);
	}
};