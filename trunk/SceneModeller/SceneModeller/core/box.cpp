#include "box.h"

BBox Box::object_bound() const 
{
	return BBox();
}
const std::vector<Triangle*>& Box::refine() const 
{
	std::vector<Triangle*> res_;
	return res_;
}

