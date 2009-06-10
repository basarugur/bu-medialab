


#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include "shape.h"

class TriangleMesh : public Shape
{
	public:
		TriangleMesh() 
		{
			m_type = TRIANGLE_MESH;
		};

		TriangleMesh(const std::string& str) 
		{
			m_filename = str;
			load();
			calculatebounds();
		};

		TriangleMesh(std::vector<Triangle*> m_list) 
		{
			m_facelist = m_list;
			calculatebounds();
		}

		void restoreTriangles()
		{
			for (int i=0 ; i<m_facelist.size() ; i++)
			{
				m_facelist[i]->restoreNormalAndMidPoint();
			}
		}

		virtual BBox object_bound() const;
		virtual bool can_intersect() const { return false; }
		virtual const std::vector<Triangle*>& refine() const { return m_facelist; }
		virtual bool intersect(const Ray& r,float *hit,DifferentialGeometry* d) const {
			//
			return false;
		};
		virtual bool intersectp(const Ray& r) const {
			//
			return false;
		};

		std::vector<Triangle*>& faceList(){ return m_facelist; }
		std::vector<Vertex*>& vertexList(){ return m_vertex_list; }

		void calculatebounds();

		void copyToMesh(TriangleMesh* msh_);

		std::vector<Triangle*> getSelectedFaceList();
		std::vector<Vertex*> getSelectedVertexList();
		void clearFaceSelections();
		void clearVertexSelections();

	private:
		mutable std::vector<Triangle*> m_facelist;
		mutable std::vector<Vertex*> m_vertex_list;
		double max_x,max_y,max_z;
		double min_x,min_y,min_z;	

		std::string m_filename;

		bool load();
};

#endif