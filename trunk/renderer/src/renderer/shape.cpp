#include "shape.h"
#include <time.h>

namespace scene
{
	bool TriangleMesh::load()
	{
			std::fstream stream;
			stream.open(m_filename.c_str(),std::ios::in);
			std::string temp_string;
			double x = 0,y = 0,z = 0;
			char timeStr [9];

			if (stream.is_open())
			{
				
				_strtime( timeStr );
				std::cout << "> " << timeStr << " : "<< "geometry is loading..." << std::endl;

				stream >> temp_string;
			
				while (!stream.eof() && temp_string!="")
				{
					if ( (temp_string.at(0)>='0' && temp_string.at(0)<='9') ||
						 (temp_string.at(0)=='-' || temp_string.at(0)=='+'))
					{					
						x = atof(temp_string.c_str());
						stream >> y >> z;					
						Vertex a(x,y,z);

						stream >> x >> y >> z;
						Vertex b(x,y,z);

						stream >> x >> y >> z;
						Vertex c(x,y,z);

						Triangle* t = new Triangle(a,b,c);	
						m_facelist.push_back(t);

					} else if (temp_string.at(0)!=' ')
					{
						//
					}

					stream >> temp_string;
				}				

				stream.close();
				
				_strtime( timeStr );
				std::cout << "> " << timeStr << " : "<< "geometry is loaded." << std::endl;
				
				return true;

			} else 
			{
				std::cout << "Error: geometry file does not exist" << std::endl;

				return false;
			}
	}

	void TriangleMesh::calculatebounds()
	{
		max_x = 0;
		max_y = 0; 
		max_z = 0;
		min_x = 0;
		min_y = 0; 
		min_z = 0;				
			
		if (m_facelist.size()>0)
		{
			min_x = max_x = m_facelist[0]->a().x();
			min_y = max_y = m_facelist[0]->a().y();
			min_z = max_z = m_facelist[0]->a().z();
		}

		for(std::size_t i=0;i<m_facelist.size();i++)
		{
			for(std::size_t j=0;j<3;j++)
			{
				if (max_x < m_facelist[i]->v(j).x())
					max_x = m_facelist[i]->v(j).x();

				if (max_y < m_facelist[i]->v(j).y())
					max_y = m_facelist[i]->v(j).y();

				if (max_z < m_facelist[i]->v(j).z())
					max_z = m_facelist[i]->v(j).z();

				if (min_x > m_facelist[i]->v(j).x())
					min_x = m_facelist[i]->v(j).x();

				if (min_y > m_facelist[i]->v(j).y())
					min_y = m_facelist[i]->v(j).y();

				if (min_z > m_facelist[i]->v(j).z())
					min_z = m_facelist[i]->v(j).z();
			}
		}
	}

	BBox TriangleMesh::object_bound() const
	{		
		return BBox(space::Point3(min_x,min_y,min_z),space::Point3(max_x,max_y,max_z));
	}
};