


#ifndef GFXOBJECT_H
#define GFXOBJECT_H

#include "shape.h"
#include "film.h"
#include "light.h"
#include "material.h"
#include "vector3.h"
#include "transformation.h"
#include "primitive.h"

#include <vector>
#include <string>


class GfxObject : public Primitive
{
	public:
		GfxObject(Shape* s,Material* m,Transformation* t,GfxObject* parent=NULL) {
			m_public_tranform = t;
			m_material  = m;
			m_shape = s;
			m_parent = parent;

			m_individual_transform = new Transformation();
			//m_child_tranform->rotation() = t->rotation();
			//m_child_tranform->translation() = t->translation();
			//m_child_tranform->scale() = t->scale();

			m_name = "new object";
			m_selected = false;

			m_child_index = -1;
		};

		void getCopy(GfxObject*&);


		bool isSelected(){ return m_selected; }
		void select(bool bl_){ m_selected = bl_ ; }

	

		Material* material() const {
			return m_material;
		}

		Shape* getShape(){ return m_shape; }
		Transformation* getPublicTranform(){ return m_public_tranform; }
		void setPublicTransform(Transformation* pbl_){ m_public_tranform = pbl_; }
		Transformation* getIndividualTranform(){ return m_individual_transform; }
		void setIndividualTransform(Transformation* pbl_){ m_individual_transform = pbl_; }
		Material* getMaterial(){ return m_material; }

		GfxObject* getParent() { return m_parent; }
		void setParent(GfxObject* obj_){ m_parent = obj_ ; }
		std::vector<GfxObject*>& getChildList(){ return m_child_list; }

		std::string getName()           { return m_name; };
		void        setName(std::string st_){ 
			m_name = st_;
			if (m_name == "") m_name = "unnamed object";
		}; 

		int getChildIndex(){ return m_child_index; };
		void setChildIndex(int ind_){ m_child_index = ind_; };

		void addChild(GfxObject* obj_)
		{
			obj_->setChildIndex(m_child_list.size());
			obj_->setParent(this);
			m_child_list.push_back(obj_);
		}
		void removeChildAt(int ind_)
		{
			for(int i= ind_+1 ; i<m_child_list.size() ; i++)
			{
				m_child_list[i]->setChildIndex( m_child_list[i]->getChildIndex()-1 );
			}

			m_child_list[ind_]->setChildIndex(-1);
			m_child_list[ind_]->setParent(NULL);
			m_child_list.erase(m_child_list.begin()+ind_);
		}
		void convertToMesh();


		virtual bool can_intersect() const {
			return m_shape->can_intersect();
		}
		virtual const std::vector<Triangle*>& refine() const {
			return m_shape->refine();		}

		virtual bool intersect(const Ray& r,Intersection* isect) const {				
			return false;		
		};

		virtual bool intersectp(const Ray& r) const {
			return false;
		};
		virtual BBox object_bound() const {
			return m_shape->object_bound();
		};

	private:
		std::string m_name;
		Shape* m_shape;
		Material* m_material;
		Transformation* m_individual_transform;
		Transformation* m_public_tranform;
		GfxObject* m_parent;
		std::vector<GfxObject*> m_child_list;
		bool m_selected;
		int m_child_index;
};


#endif