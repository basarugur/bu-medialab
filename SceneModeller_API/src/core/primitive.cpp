#include "primitive.h"

#include <time.h>

Aggregate::Aggregate(){
	m_tree = new Kdtree();
}

bool Aggregate::intersect(const Ray& r,Intersection* isect) const {
	return m_tree->intersect(r,isect);
}

bool Aggregate::intersectp(const Ray& r) const {
	return m_tree->intersectp(r);
}

void Aggregate::add_primitive(Primitive* p) {
	m_primitives.push_back(p);
}

void Aggregate::post() {

	for(int i=0;i<m_primitives.size();i++) {

		if(m_primitives[i]->can_intersect() == false)
		{
			const std::vector<Triangle*> list = m_primitives[i]->refine();

			for(int j=0;j<list.size();j++)
			{
				list[j]->set_material(m_primitives[i]->material());
				list[j]->set_box(m_primitives[i]->object_bound());
				m_list.push_back(list[j]);
			}
		}

	}

	char* timeStr;
	// _strtime( timeStr );
    long t = time( (time_t*)0 );

	timeStr = ctime( &t );

	std::cout << "> " << timeStr << " : "<< "bounding volume hierarchy is creating..." << std::endl;

	m_tree->build(20,2,m_list);

	//_strtime( timeStr );
	t = time( (time_t*)0 );
    timeStr = ctime( &t );

	std::cout << "> " << timeStr << " : "<< "bounding volume hierarchy is created." << std::endl;
}
