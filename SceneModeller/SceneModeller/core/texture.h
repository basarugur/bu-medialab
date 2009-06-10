//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef TEXTURE_H
#define TEXTURE_H

#include "film.h"
#include "vector3.h"
#include "point3.h"

class TextureBuffer 
{
	public:
		TextureBuffer(int size_x,int size_y) {

			m_width  = size_x;
			m_height = size_y;

			m_buffer = new TRadiance*[m_width];
			for(int i=0;i<m_width;i++)
				m_buffer[i] = new TRadiance[m_height];

		};

		void set_radiance(int x,int y,TRadiance r) {
			m_buffer[x][y] = r;
		}

		TRadiance radiance(int x,int y) {
			return m_buffer[x][y];
		}

		int width() { return m_width; }
		int height(){ return m_height; }

	private:
		TRadiance **m_buffer;
		int m_width;
		int m_height;
};

class Texture 
{
	public:
		Texture() {};	
		virtual TRadiance map(float u,float v,float w) const = 0;
};

class Texture2D : public Texture
{
	public:
		Texture2D(TextureBuffer* buff,Vector3 n,double scalex = 1,double scaley = 1):
			m_scalex(scalex),m_scaley(scaley)
		{
			m_normal = n;
			m_buffer = buff;				
		};
		//planar mapping
		virtual TRadiance map(float u,float v,float w) const {
				
			float uu = 0.0;
			float vv = 0.0;
			
			if (m_normal == Vector3(1,0,0)) {
				uu = w;
				vv = v;
			}
			if (m_normal == Vector3(0,1,0)) {
				uu = u;
				vv = w;
			}				
			if (m_normal == Vector3(0,0,1)) {
				uu = u;
				vv = v;
			}
			
			int xx = (int)(uu * m_scalex) % m_buffer->width();
			int yy = (int)(vv * m_scaley) % m_buffer->height();
			
			return m_buffer->radiance(xx,yy);
		};
	private:
		TextureBuffer* m_buffer;
		double m_scalex;
		double m_scaley;
		Vector3 m_normal;
};

#endif