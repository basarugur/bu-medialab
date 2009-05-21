#include "matrix.h"
#include <fstream>

namespace space
{

	Matrix::Matrix()
	{	
		zeros();
	}

	void  Matrix::setrow(const std::size_t& i,Vector3& v)
	{
		for(std::size_t k=0;k<4;k++)
				m_data[i][k] = v.v(k);
	}

	void  Matrix::setcol(const std::size_t& i,Vector3& v)
	{
		for(std::size_t k=0;k<4;k++)
				m_data[k][i] = v.v(k);
	}

	Vector3 Matrix::row(const std::size_t& i)
	{
		double d[4] = {0,0,0,0};
		
		for(std::size_t k=0;k<4;k++)
				d[k] = m_data[i][k];

		return Vector3(d[0],d[1],d[2]);
	}

	Vector3 Matrix::col(const std::size_t& i)
	{
		double d[4] = {0,0,0,0};
		
		for(std::size_t k=0;k<4;k++)
				d[k] = m_data[k][i];

		return Vector3(d[0],d[1],d[2]);
	}

	const double &Matrix::cell(const std::size_t& x,const std::size_t& y)
	{
		if ((x >= 0) && (x < 4) && (y >= 0) && (y < 4))
		{
			return m_data[x][y];
		} else
		{
			return m_data[0][0];
		}
	}

	const double &Matrix::cell(const std::size_t& x,const std::size_t& y) const
	{
		if ((x >= 0) && (x < 4) && (y >= 0) && (y < 4))
		{
			return m_data[x][y];
		} else
		{
			return m_data[0][0];
		}
	}

	void  Matrix::setcell(const std::size_t& x,const std::size_t& y,const double& d)
	{
		if ((x >= 0) && (x < 4) && (y >= 0) && (y < 4))
		{
			m_data[x][y] = d;
		}
	}

	void Matrix::identity()
	{
		zeros();

		for(std::size_t i=0;i<4;i++)
			m_data[i][i] = 1.0;
	}

	void Matrix::zeros()
	{
		for(std::size_t i=0;i<4;i++)
			for(std::size_t j=0;j<4;j++)
				m_data[i][j] = 0.0;
	}

	void Matrix::print()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)			
				std::cout << m_data[i][j] << " ";			

			std::cout << std::endl;
		}
	}

	void Matrix::read(const std::string& filename)
	{
		std::fstream stream;
		stream.open(filename.c_str(),std::ios::in);

		if (stream.is_open())
		{
				for(int i=0;i<4;i++)
					for(int j=0;j<4;j++)
					{	
						double d;
						stream >> d;

						setcell(i,j,d);
					}
				
				stream.close();
		} else 
		{
			std::cout << "Error: file does not exist" << std::endl;
		} 
	}


	Matrix Matrix::inv()
	{
		int indxc [4], indxr [4], ipiv [4];
		int i, j, k, row=0, col=0, l, ll;
		double big, dummy, pivinv;
		double mass_copy[4][4];
		double mass_inverse[4][4];
		Matrix return_matrix;

		for (i = 0; i <= 3; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				mass_copy [i][j] = m_data [i][j];
				if (i == j) mass_inverse [i][j] = 1.0;
				else mass_inverse [i][j] = 0.0;
			}
		}
		// int arrays ipiv, indxr and indxc are used for bookkeeping on the pivoting
		for (j = 0; j <= 3; j++) ipiv [j] = 0; // initialize loop
		for (i = 0; i <= 3; i++) // main loop over columns reduced
		{
			big = 0.0;
			for (j = 0; j <= 3; j++) // outer loop of pivot search
			{

				if (ipiv [j] != 1)
				{
					for (k = 0; k <= 3; k++)
					{
						if (ipiv [k] == 0)
						{
							if (fabs (mass_copy [j][k]) >= big)
							{
								big = fabs (mass_copy [j][k]);
								row = j;
								col = k;
							}
						}
						else if (ipiv [k] > 1)
						{
							std::cout << "Error: singular mass matrix" << std::endl;
							return return_matrix;
						}
					}
				}
			}
			++ (ipiv [col]);
			// see detailed comments in reference code for pivot bookkeeping scheme
			if (row != col)
			{
				for (l = 0; l <= 3; l++) swap (& mass_copy [row][l],
					& mass_copy [col][l]);
					for (l = 0; l <= 3; l++) swap (& mass_inverse [row][l],
						& mass_inverse [col][l]);
			}
			indxr [i] = row; // we are now ready to divide pivot row by pivot element
			indxc [i] = col; // which is located at [row, col]
			if (mass_copy [col][col] == 0.0)
			{
				std::cout << "invert error, singular matrix" << std::endl;
				return return_matrix;
			}
			pivinv = 1.0 / mass_copy [col][col];
			mass_copy [col][col] = 1.0;
			for (l = 0; l <= 3; l++) mass_copy [col][l] *= pivinv;
			for (l = 0; l <= 3; l++) mass_inverse [col][l] *= pivinv;
			for (ll = 0; ll <= 3; ll++) // next we reduce the rows
			{
				if (ll != col) // except for the pivot row, of course
				{
					dummy = mass_copy [ll][col];
					mass_copy [ll][col] = 0.0;
					for (l = 0; l <= 3; l++)
						mass_copy [ll][l] -= mass_copy [col][l] * dummy;
					for (l = 0; l <= 3; l++)
						mass_inverse [ll][l] -= mass_inverse [col][l] * dummy;
				}
			}
		}
		// we now unscramble the columns by interchanging in reverse order
		for (l = 3; l >= 0; l--)
		{
			if (indxr [l] != indxc [l])
			{
				for (k = 0; k <= 3; k++)
				{
					swap (& mass_copy [k][indxr [l]], & mass_copy [k][indxc [l]]);
				}
			}
		}

		for(std::size_t i=0;i<4;i++)
			for(std::size_t j=0;j<4;j++)
				return_matrix.setcell(i,j,mass_inverse[i][j]);

		return return_matrix;
	}
}