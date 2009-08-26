


#ifndef VECTEX_H
#define VECTEX_H

#include "vector3.h"

class SM_API_EXPORT Vertex : public Vector3
{
	public:
		Vertex(double _x=0, double _y=0, double _z=0) : Vector3(_x,_y,_z)
		{
			m_is_selected = false;
		};

		Vertex(const Vector3 vct_) : Vector3(vct_.x(),vct_.y(),vct_.z())
		{
			m_is_selected = false;
		};

		bool isSelected(){ return m_is_selected; };
		void select(bool bl_){ m_is_selected = bl_;};

		void setX(double x_){ m_v[0] = x_; };
		void setY(double y_){ m_v[1] = y_; };
		void setZ(double z_){ m_v[2] = z_; };

private:
	bool m_is_selected;

};


#endif
