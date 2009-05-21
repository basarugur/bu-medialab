//Author : Ufuk Tiryaki @ 2009
//Desc   : 

#ifndef MATRIX_H
#define MATRIX_H

#include "vector3.h"
#include "point3.h"

namespace space
{
	//row x column
	class Matrix
	{
	public:
		Matrix(); 

		const double &cell(const std::size_t&,const std::size_t&);
		const double &cell(const std::size_t&,const std::size_t&) const;
		void  setcell(const std::size_t&,const std::size_t&,const double&);
		void  setrow(const std::size_t&,Vector3&);
		void  setcol(const std::size_t&,Vector3&);
		Vector3 row(const std::size_t& i);
		Vector3 col(const std::size_t& i);
		void  identity(); //convert current matrix to an identity matrix.
		void  zeros();    //convert current matrix to a zero matrix. 
		Matrix inv();
		void print(); //It prints out current matrix data to console.
		void read(const std::string&); //It reads 4x4 matrix from ordinary text file.

		Matrix& operator=(const Matrix& rhs)
		{
			for(std::size_t i=0;i<4;i++)
				for(std::size_t j=0;j<4;j++)
					m_data[i][j] = rhs.cell(i,j);
					
			return *this;
		}

		Matrix operator*(Matrix& rhs)
		{
			Matrix m_;

			for(std::size_t i=0;i<4;i++)
				for(std::size_t j=0;j<4;j++)
					for(std::size_t k=0;k<4;k++)
						m_.setcell(i,j,m_.cell(i,j) + m_data[i][k]*rhs.cell(k,j));

			return m_;
		}



		Vector3 operator*(Vector3& rhs)
		{
			double d[4] = {0,0,0,0};
			double v[4] = {rhs.x(),rhs.y(),rhs.z(),1.0};

			for(std::size_t i=0;i<4;i++)		
				for(std::size_t j=0;j<4;j++)				
						d[i] = d[i] + m_data[i][j]*v[j];		
			
			return Vector3(d[0],d[1],d[2]);
		}

		Point3 operator*(Point3& rhs)
		{
			double d[4] = {0,0,0,0};
			double v[4] = {rhs.x(),rhs.y(),rhs.z(),1.0};

			for(std::size_t i=0;i<4;i++)		
				for(std::size_t j=0;j<4;j++)				
						d[i] = d[i] + m_data[i][j]*v[j];		
			
			return Point3(d[0],d[1],d[2]);
		}

	private:
		double m_data[4][4];

		void swap(double *a, double *b)
		{
			double temp = *a;
			*a = *b;
			*b = temp;
		}
	};
};

#endif