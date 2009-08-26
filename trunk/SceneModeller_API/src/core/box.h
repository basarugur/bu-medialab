


#ifndef BOX_H
#define BOX_H


#include "shape.h"

class Box : public Shape
{
	public:	
		Box(): Shape() {
		
			m_type = BOX;

		};						
		BBox object_bound() const ;
		const std::vector<Triangle*>& refine() const ;
};

#endif