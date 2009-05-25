


#ifndef FACE_H
#define FACE_H

#include "vertex.h"
#include "triangle.h"

#include<vector>

class Face 
{
	public:
		Face(Vertex a,Vertex b,Vertex c)
		{
			m_material = NULL;
			m_triangulated = false;

			m_v.push_back(a);
			m_v.push_back(b);
			m_v.push_back(c);
			
			Vector3 v = ((m_v[2] - m_v[0]) ^ (m_v[1] - m_v[0])).normalize();
			m_n = Normal3(v.x(),v.y(),v.z());
		};

			
		const Vertex& v(int i) const { return m_v[i]; };
		const Triangle& t(int i) const { return m_t[i]; };
		const Normal3& n() const { return m_n; };
		
		void set_material(Material* m) { m_material = m;};
		const Material* material() const { return m_material; };

		bool isTriangulated(){ return m_triangulated; };
		void addVertex(Vertex v_) { m_v.push_back(v_); };
		void triangulate();

		int vertexCount(){ return m_v.size(); };
		int triangleCount(){ return m_t.size(); };

	private:
		std::vector<Vertex> m_v;
		std::vector<Triangle> m_t;

		Normal3 m_n;		
		Material* m_material;
		bool m_triangulated;	
};


#endif