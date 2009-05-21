//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef SAMPLER_H
#define SAMPLER_H

#include "film.h"
#include "vector3.h"
#include "point3.h"

namespace output
{
	class Screen
	{
	public:
		Screen(double width = 400,double height = 400): m_w(width),m_h(height)
		{
			m_buffer = new output::TRadiance*[width];

			for(int i=0;i<width;i++)
				m_buffer[i] = new output::TRadiance[height];

		};

		double width() const { return m_w; };		
		double height() const { return m_h; };				

		const output::TRadiance& buffer(int i,int j) const { return m_buffer[i][j]; };
		void set_color(const output::TRadiance& c,int i,int j) const 
		{
			m_buffer[i][j].r = c.r;
			m_buffer[i][j].g = c.g;
			m_buffer[i][j].b = c.b;
		};

	private:
		double m_w;
		double m_h;
		mutable output::TRadiance **m_buffer;
	};

	class Sampler
	{
		public:	
			Sampler(double w,double h,double z,Screen* scr) : m_width(w),m_height(h),m_scr(scr),m_z(z)
			{
				m_inc_x = w / scr->width();
				m_inc_y = h / scr->height();				

				srand(1000);
			};

			const double width() const { return m_width; };
			const double height() const { return m_height; };
			void next(int x,int y)
			{
				//We add an epsilon to avoid direction vector (<0,0,c>). When we create a point on the viewing plane
				//for x=0,y=0 we get <0,0,c> vector which results in that the inverse direction vector would be 
				//undefined due to the zero-divison.
				m_y = (-m_height / 2.0) + ( y * m_inc_y ) + ZERO;
				m_x = (-m_width  / 2.0) + ( x * m_inc_x ) + ZERO;

				m_view = space::Point3(m_x,m_y,m_z);
			};

			const Screen* screen() const { return m_scr; };
			const space::Point3& view() const { return m_view; };
			
			//randomly generate sample (aa)
			const space::Point3 viewr() const {

					double yy =  m_y + (random()*m_inc_y);
					double xx =  m_x + (random()*m_inc_x);			

					return space::Point3(xx,yy,m_z);
			}
			



		private:	
			double m_width;
			double m_height;

			double m_x;
			double m_y;
			double m_z;

			double m_inc_x;
			double m_inc_y;			

			space::Point3 m_view;
			Screen* m_scr;			
	};
};

#endif