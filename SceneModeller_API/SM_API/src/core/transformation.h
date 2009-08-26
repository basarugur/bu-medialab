


#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


#include "matrix.h"
#include "shape.h"
#include "trianglemesh.h"
#include "vector3.h"
#include "diffgeometry.h"

struct Rotation4 // the concept of Quaternions
{
	// check normalizations in here
	Rotation4() 
	{
		m_x = 0 ; m_y= 0 ; m_z = 0 ; m_w = 1 ;

		m_ax = 0 ; m_ay = 0 ; m_az = 0 ;
		m_theta = 2.0 * acos(m_w);

		//angle= 2 * acos(w)
        //ax= x / scale
        //ay= y / scale
        //az= z / scale

	}
	Rotation4(double ax_,double ay_ , double az_ ,double theta_)
	{
		m_ax = ax_ ; m_ay = ay_ ; m_az = az_ ; m_theta = theta_ * 0.0174532925 ;

		double nrm_ = sqrt(m_ax*m_ax + m_ay*m_ay + m_az*m_az);
		if(nrm_ != 0)
		{
			m_ax = m_ax / nrm_ ;
			m_ay = m_ay / nrm_ ;
			m_az = m_az / nrm_ ;

			m_w = cos(m_theta/2.0);
			m_x = m_ax * sin( m_theta/2.0 );
			m_y = m_ay * sin(m_theta/2.0);
			m_z = m_az * sin(m_theta/2.0);
		}
		else
		{
			m_w =1;
			m_x =0;
			m_y =0;
			m_z =0;

			m_ax = 0 ; m_ay = 0 ; m_az = 0 ;
			m_theta = 2 * acos(m_w);
		}

		    //w   =   cos(theta/2)
			//x   =   ax * sin(theta/2)
			//y   =   ay * sin(theta/2)
			//z   =   az * sin(theta/2)

	}

	double x(){ return m_x; }
	double y(){ return m_y; }
	double z(){ return m_z; }
	double w(){ return m_w; }

	double ax(){ return m_ax; }
	double ay(){ return m_ay; }
	double az(){ return m_az; }
	double theta(){ return m_theta*57.2957795; }

	// Note that order matters with concatenating Quaternion rotations
	inline Rotation4 operator* (Rotation4 b) const
	{
        double w_,x_,y_,z_;

		w_ = m_w*b.w() - m_x*b.x() - m_y*b.y() - m_z*b.z();
		x_ = m_w*b.x() + m_x*b.w() + m_y*b.z() - m_z*b.y();
		y_ = m_w*b.y() + m_y*b.w() + m_z*b.x() - m_x*b.z();
		z_ = m_w*b.z() + m_z*b.w() + m_x*b.y() - m_y*b.x(); 


		Rotation4 res_;
		res_.setParams(x_,y_,z_,w_);


		return res_;


		//angle= 2 * acos(w)
        //ax= x / scale
        //ay= y / scale
        //az= z / scale

		//w=w1w2 - x1x2 - y1y2 - z1z2
		//x = w1x2 + x1w2 + y1z2 - z1y2
		//y = w1y2 + y1w2 + z1x2 - x1z2
		//z = w1z2 + z1w2 + x1y2 - y1x2 
	}

	void setParams(double x,double y,double z,double w)
	{
		m_x = x ; m_y = y ; m_z = z; m_w = w; 
		normalize();

		double scale_ = sqrt(m_x*m_x+m_y*m_y+m_z*m_z);

		m_theta = 2.0*acos(m_w);
		if(scale_ != 0)
		{
			m_ax = m_x / scale_;
			m_ay = m_y / scale_;
			m_az = m_z / scale_;
		}
		else
		{
			m_ax = 0;
			m_ay = 0;
			m_az = 0;
		}
	}
	Vector3 applyToVector(Vector3 vct_)
	{

			Matrix rotationMat = toMatrix();
			double res_[3]={ 0 , 0 , 0 };

			res_[0]+=rotationMat.cell(0,0)*vct_.x();
			res_[0]+=rotationMat.cell(0,1)*vct_.y();
			res_[0]+=rotationMat.cell(0,2)*vct_.z();

			res_[1]+=rotationMat.cell(1,0)*vct_.x();
			res_[1]+=rotationMat.cell(1,1)*vct_.y();
			res_[1]+=rotationMat.cell(1,2)*vct_.z();

			res_[2]+= rotationMat.cell(2,0)*vct_.x();
			res_[2]+= rotationMat.cell(2,1)*vct_.y();
			res_[2]+= rotationMat.cell(2,2)*vct_.z();

			return Vector3(res_[0],res_[1],res_[2]);
	}
	//public final void set(Matrix4f m1) {
	//	w = Math.sqrt(1.0 + m1.m00 + m1.m11 + m1.m22) / 2.0;
	//	double w4 = (4.0 * w);
	//	x = (m1.m21 - m1.m12) / w4 ;
	//	y = (m1.m02 - m1.m20) / w4 ;
	//	z = (m1.m10 - m1.m01) / w4 ;
	//}

	void setFromMatrix(Matrix mtrx_)
	{

		const double trace = 1.0f + mtrx_.cell(0,0)+ mtrx_.cell(1,1) + mtrx_.cell(2,2);

		if (trace > 0.00001f /*&& mtrx_.cell(0,0)!= 0 && mtrx_.cell(1,1)!= 0 && mtrx_.cell(2,2)!= 0*/)
		{
			const double s = sqrt(trace) * 2;

				m_x = (mtrx_.cell(2,1) - mtrx_.cell(1,2)) / s;
				m_y = (mtrx_.cell(0,2) - mtrx_.cell(2,0)) / s;
				m_z = (mtrx_.cell(1,0) - mtrx_.cell(0,1)) / s;
				m_w = 0.25 * s ;
		}
		else if (mtrx_.cell(0,0) > mtrx_.cell(1,1) && mtrx_.cell(0,0) > mtrx_.cell(2,2))
		{
			const double s = sqrt(1.0f + mtrx_.cell(0,0) - mtrx_.cell(1,1) - mtrx_.cell(2,2)) * 2;

				m_x = 0.25 * s;
				m_y = (mtrx_.cell(1,0) - mtrx_.cell(0,1)) / s;
				m_z = (mtrx_.cell(0,2) - mtrx_.cell(2,0)) / s;
				m_w = (mtrx_.cell(2,1) - mtrx_.cell(1,2)) / s;
		}
		else if (mtrx_.cell(1,1) > mtrx_.cell(2,2) && mtrx_.cell(1,1) > mtrx_.cell(0,0))
		{
			const double s = sqrt(1.0f + mtrx_.cell(1,1) - mtrx_.cell(0,0) - mtrx_.cell(2,2)) * 2;

				m_x = (mtrx_.cell(1,0) - mtrx_.cell(0,1)) / s;
				m_y = 0.25 * s ;
				m_z = (mtrx_.cell(2,1) - mtrx_.cell(1,2)) / s;
				m_w = (mtrx_.cell(0,2) - mtrx_.cell(2,0)) / s;
		}
		else if (mtrx_.cell(2,2) > mtrx_.cell(0,0) && mtrx_.cell(2,2) > mtrx_.cell(1,1))
		{
			const double s = sqrt(1.0f + mtrx_.cell(2,2) - mtrx_.cell(0,0) - mtrx_.cell(1,1)) * 2;

				m_x = (mtrx_.cell(0,2) - mtrx_.cell(2,0)) / s;
				m_y = (mtrx_.cell(2,1) - mtrx_.cell(1,2)) / s;
				m_z = 0.25 * s;
				m_w = (mtrx_.cell(1,0) - mtrx_.cell(0,1)) / s;
		}
		else
		{
			m_x = 0 ; m_y = 0; m_z = 0; m_w = 1;
		}

		normalize();

		double scale_ = sqrt(1-m_w*m_w);
		m_theta = 2*acos(m_w);
		/*if(m_w == 0 )m_theta = -acos(m_w);*/
		if(scale_ != 0)
		{
			m_ax = m_x / scale_;
			m_ay = m_y / scale_;
			m_az = m_z / scale_;
		}
		else
		{
			m_ax = 0;
			m_ay = 0;
			m_az = 0;
		}

	}



	Matrix toMatrix()
	{

		Matrix rotationMat;

		double sqw = m_w*m_w;   
		double sqx = m_x*m_x;   
		double sqy = m_y*m_y;   
		double sqz = m_z*m_z;

        // invs (inverse square length) is only required if quaternion is not already normalised
		double invs = 1 / (sqx + sqy + sqz + sqw) ;
		rotationMat.setcell(0,0,( sqx - sqy - sqz + sqw)*invs) ; // since sqw + sqx + sqy + sqz =1/invs*invs   
		rotationMat.setcell(1,1,(-sqx + sqy - sqz + sqw)*invs) ;    
		rotationMat.setcell(2,2,(-sqx - sqy + sqz + sqw)*invs) ;

		double tmp1 = m_x*m_y;   
		double tmp2 = m_z*m_w;   
		rotationMat.setcell(1,0,2.0 * (tmp1 + tmp2)*invs) ;  
		rotationMat.setcell(0,1,2.0 * (tmp1 - tmp2)*invs) ;

		tmp1 = m_x*m_z;    
		tmp2 = m_y*m_w;   
		rotationMat.setcell(2,0,2.0 * (tmp1 - tmp2)*invs) ; 
		rotationMat.setcell(0,2,2.0 * (tmp1 + tmp2)*invs) ;
		
		tmp1 = m_y*m_z;   
		tmp2 = m_x*m_w;  
		rotationMat.setcell(2,1,2.0 * (tmp1 + tmp2)*invs) ;  
		rotationMat.setcell(1,2,2.0 * (tmp1 - tmp2)*invs) ;

		return rotationMat;
	}

	void normalize()
	{
		double lngth_ = sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
		if (lngth_ != 0 && lngth_ != 1)
		{
			m_x = m_x / lngth_;
			m_y = m_y / lngth_;
			m_z = m_z / lngth_;
			m_w = m_w / lngth_;
		}
	}

private:
	double m_ax,m_ay,m_az,m_theta; // theta is in radians
	double m_x,m_y,m_z,m_w;
};

class SM_API_EXPORT Transformation 
{
	public:
		Transformation() {
			m_scale_vector = Vector3(1,1,1);
			m_rotation_vector = Rotation4();
			m_translation_vector=Vector3(0,0,0);
		};
		
		void rotate(double x,double y,double z,double angle) 
		{
			m_rotation_vector = Rotation4(x,y,z,angle);

			double c = cos(angle);
			double s = sin(angle);

			m_rotation.setcell(0,0,x*x*(1-c)+c);
			m_rotation.setcell(0,1,x*y*(1-c)-z*s);
			m_rotation.setcell(0,2,x*z*(1-c)+y*s);
			m_rotation.setcell(0,3,0);

			m_rotation.setcell(1,0,y*x*(1-c)+z*s);
			m_rotation.setcell(1,1,y*y*(1-c)+c);
			m_rotation.setcell(1,2,y*z*(1-c)-x*s);
			m_rotation.setcell(1,3,0);

			m_rotation.setcell(2,0,x*z*(1-c)-y*s);
			m_rotation.setcell(2,1,y*z*(1-c)+x*s);
			m_rotation.setcell(2,2,z*z*(1-c)+c);
			m_rotation.setcell(2,3,0);

			m_rotation.setcell(3,0,0);
			m_rotation.setcell(3,1,0);
			m_rotation.setcell(3,2,0);
			m_rotation.setcell(3,3,1);
		}

		void scale(double x,double y,double z) 
		{
			m_scale_vector = Vector3(x,y,z);
		}

		void translate(double x,double y,double z) 
		{
			m_translation_vector=Vector3(x,y,z);
		}

		Vector3& scale(){ return m_scale_vector; }
		Vector3& translation() { return m_translation_vector; }
		Rotation4& rotation() { return m_rotation_vector; }

		Transformation operator+(Transformation rhs)
		{
			Transformation res_ ; 
			res_.rotation() = m_rotation_vector*rhs.rotation();
			res_.scale()    = rhs.scale()+m_scale_vector-Vector3(1,1,1);
			res_.translation() = m_translation_vector+rhs.translation();

			
			return res_;
		}

		Transformation operator*(Transformation rhs)
		{
			Transformation res_ ; 
			res_.rotation() = m_rotation_vector*rhs.rotation();
			res_.scale()    = rhs.scale()+rhs.rotation().applyToVector(m_scale_vector-Vector3(1,1,1));
			res_.translation() = rhs.rotation().applyToVector(m_translation_vector.scale(rhs.scale()))+rhs.translation();
			
			return res_;
		}

		Point3 apply(Point3& p) {
			return m_transform*p;
		}

		Vertex applyToVertex(Vertex* vrt_)
		{
            Vertex res_ ; 
			res_.setX(vrt_->x()+m_translation_vector.x());
			res_.setY(vrt_->y()+m_translation_vector.y());
			res_.setZ(vrt_->z()+m_translation_vector.z());

			res_.setX(res_.x()*m_scale_vector.x());
			res_.setY(res_.y()*m_scale_vector.y());
			res_.setZ(res_.z()*m_scale_vector.z());

			Vector3 vct_(res_.x(),res_.y(),res_.z());
			vct_ = m_rotation_vector.applyToVector(vct_);

			return Vertex(vct_.x(),vct_.y(),vct_.z());
		}

		Shape* apply(Shape* s) {

			if (s->can_intersect() == false)
			{
				std::vector<Triangle*> list = s->refine();
				std::vector<Triangle*> list2;
				for(int i=0;i<list.size();i++)
				{
					Vector3 v1 = m_transform * static_cast<Vector3>(*list[i]->a());
					Vector3 v2 = m_transform * static_cast<Vector3>(*list[i]->b());
					Vector3 v3 = m_transform * static_cast<Vector3>(*list[i]->c());

					Triangle* t = new Triangle(Vertex(v1),Vertex(v2),Vertex(v3));
					list2.push_back(t);
				}		

				Shape* rets = new TriangleMesh(list2);

				return rets;

			} else {
				return NULL;
			}
		}

	private:

		Vector3 m_scale_vector;
		Vector3 m_translation_vector;
		Rotation4 m_rotation_vector;

		Matrix m_rotation;
		Matrix m_scale;
		Matrix m_translate;
		Matrix m_transform;
};

class SM_API_EXPORT Intersection 
{
public:
	Intersection() {
	};			

	DifferentialGeometry* dg() const { return &m_dg; };			
private:			
	mutable DifferentialGeometry m_dg;			
};

#endif