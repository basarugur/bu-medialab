#include "trianglemesh.h"

#include<QHash>
#include <time.h>

void TriangleMesh::calculatebounds()
{
	max_x = 0;
	max_y = 0; 
	max_z = 0;
	min_x = 0;
	min_y = 0; 
	min_z = 0;				
		
	if (m_vertex_list.size()>0)
	{
		min_x = max_x = m_vertex_list[0]->x();
		min_y = max_y = m_vertex_list[0]->y();
		min_z = max_z = m_vertex_list[0]->z();
	}

	for(std::size_t i=0;i<m_vertex_list.size();i++)
	{
		if (max_x < m_vertex_list[i]->x())
			max_x = m_vertex_list[i]->x();

		if (max_y < m_vertex_list[i]->y())
			max_y = m_vertex_list[i]->y();

		if (max_z < m_vertex_list[i]->z())
			max_z = m_vertex_list[i]->z();

		if (min_x > m_vertex_list[i]->x())
			min_x = m_vertex_list[i]->x();

		if (min_y > m_vertex_list[i]->y())
			min_y = m_vertex_list[i]->y();

		if (min_z > m_vertex_list[i]->z())
			min_z = m_vertex_list[i]->z();
	}
}

BBox TriangleMesh::object_bound() const
{		
	return BBox(Point3(min_x,min_y,min_z),Point3(max_x,max_y,max_z));
}

std::vector<Triangle*> TriangleMesh::getSelectedFaceList()
{
	std::vector<Triangle*> tr_ ; 
	for (int i=0 ;i <m_facelist.size() ; i++)
	{
		if (m_facelist[i]->isSelected())
		{
			tr_.push_back(m_facelist[i]);
		}
	}
	return tr_;
}
std::vector<Vertex*> TriangleMesh::getSelectedVertexList()
{
	std::vector<Vertex*> tr_ ; 
	for (int i=0 ;i <m_vertex_list.size() ; i++)
	{
		if (m_vertex_list[i]->isSelected())
		{
			tr_.push_back(m_vertex_list[i]);
		}
	}
	return tr_;
}
void TriangleMesh::clearFaceSelections()
{
	for (int i=0 ;i <m_facelist.size() ; i++)
	{
		m_facelist[i]->select(false);
	}
}
void TriangleMesh::clearVertexSelections()
{
	for (int i=0 ;i <m_vertex_list.size() ; i++)
	{
		m_vertex_list[i]->select(false);
	}
}

void TriangleMesh::copyToMesh(TriangleMesh* msh_)
{
	QHash<QString,int> vertexHash_;
	QString tmpKey_;

	for (int i=0 ; i<m_facelist.size() ; i++ )
	{
		Vertex* v1_=m_facelist[i]->a();
		Vertex* v2_=m_facelist[i]->b();
		Vertex* v3_=m_facelist[i]->c();

		tmpKey_ = QString::number(v1_->x())+QString::number(v1_->y())+QString::number(v1_->z());
		if (vertexHash_.contains(tmpKey_))
		{
			v1_ = msh_->vertexList()[vertexHash_[tmpKey_]];
		}
		else
		{
			msh_->vertexList().push_back(new Vertex(v1_->x(),v1_->y(),v1_->z()));
			v1_ = msh_->vertexList()[msh_->vertexList().size()-1];
			vertexHash_.insert(tmpKey_,msh_->vertexList().size());
		}

		// v2
		tmpKey_ = QString::number(v2_->x())+QString::number(v2_->y())+QString::number(v2_->z());
		if (vertexHash_.contains(tmpKey_))
		{
			v2_ = msh_->vertexList()[vertexHash_[tmpKey_]];
		}
		else
		{
			msh_->vertexList().push_back(new Vertex(v2_->x(),v2_->y(),v2_->z()));
			v2_ = msh_->vertexList()[msh_->vertexList().size()-1];
			vertexHash_.insert(tmpKey_,msh_->vertexList().size());
		}

		// v3
		tmpKey_ = QString::number(v3_->x())+QString::number(v3_->y())+QString::number(v3_->z());
		if (vertexHash_.contains(tmpKey_))
		{
			v3_ = msh_->vertexList()[vertexHash_[tmpKey_]];
		}
		else
		{
			msh_->vertexList().push_back(new Vertex(v3_->x(),v3_->y(),v3_->z()));
			v3_ = msh_->vertexList()[msh_->vertexList().size()-1];
			vertexHash_.insert(tmpKey_,msh_->vertexList().size());
		}

		msh_->faceList().push_back(new Triangle(v1_,v2_,v3_));
	}
	msh_->calculatebounds();
}

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
