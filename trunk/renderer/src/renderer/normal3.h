//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef NORMAL_H
#define NORMAL_H

#include "vector3.h"

namespace space
{
	//Although normals are superficially similar to vectors, it is important to distinguish 
	//between the two of them: because normals are defined in terms of their relationship to 
	//a particular surface, they behave differently than vectors in some situations, particularly 
	//when applying transformations.
	//Note : It will be defined later.
	class Normal3 : public Vector3
	{
		public:	
			Normal3(double _x=0,double _y=0,double _z=0) : Vector3(_x,_y,_z)			 
			{};			
			
	};
};

#endif