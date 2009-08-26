


#ifndef MATRIX_H
#define MATRIX_H

#include "vector3.h"
#include "point3.h"


class SM_API_EXPORT Matrix
{
public:
	Matrix();
	Matrix(float matrix[4][4]);

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

		for(std::size_t i=0; i<4; i++)
			for(std::size_t j=0; j<4; j++)
				for(std::size_t k=0; k<4; k++)
					m_.setcell(i, j, m_.cell(i,j) + m_data[i][k]*rhs.cell(k,j));

		return m_;
	}

	Vector3 operator*(Vector3& vct_)
	{
		double res_[3] = {0, 0, 0};

        for(std::size_t i=0; i<3; i++)
		{
		    res_[i] += m_data[i][0]*vct_.x();
            res_[i] += m_data[i][1]*vct_.y();
            res_[i] += m_data[i][2]*vct_.z();
            res_[i] += m_data[i][3];
		}

		/// For homogeneous coordinates, divide the products by the last element,
		/// use inverse of last cell of the multiplication
		double invLast = 1.0 / ( m_data[3][0] * vct_.x() +
                                 m_data[3][1] * vct_.y() +
                                 m_data[3][2] * vct_.z() +
                                 m_data[3][3] );

		return Vector3(res_[0] * invLast, res_[1] * invLast, res_[2] * invLast);
	}

	Point3 operator*(Point3& pt_)
	{
        double res_[3] = {0, 0, 0};

        for(std::size_t i=0; i<3; i++)
		{
		    res_[i] += m_data[i][0]*pt_.x();
            res_[i] += m_data[i][1]*pt_.y();
            res_[i] += m_data[i][2]*pt_.z();
            res_[i] += m_data[i][3];
		}

		/// For homogeneous coordinates, divide the products by the last element,
		/// use inverse of last cell of the multiplication
		double invLast = 1.0 / ( m_data[3][0] * pt_.x() +
                                 m_data[3][1] * pt_.y() +
                                 m_data[3][2] * pt_.z() +
                                 m_data[3][3] );

		return Point3(res_[0] * invLast, res_[1] * invLast, res_[2] * invLast);
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


#endif
