#include "CanvasGrid.h"


void CanvasGrid::draw()
{
	if(m_is_on)
	{
		glDisable(GL_LIGHTING);
		if(m_grid_scale == SCALE_1X)
		{
			switch(m_oriantation)
			{
			case XY_GRID: //////////// XY
				glColor3f(0.55,0.55,0.55);	
				glLineWidth(1);
				glBegin(GL_LINES);
				for (int i=0 ; i<151 ; i++)
				{
					glVertex3f(75-i,-75,0 );
					glVertex3f(75-i, 75,0  );

					glVertex3f(-75,75-i,0 );
					glVertex3f(75 ,75-i,0 );
				}
				glEnd();

				glLineWidth(2);
				glBegin(GL_LINES);
				for (int i=0 ; i<31 ; i++)
				{
					glVertex3f(75-5*i,-75,0 );
					glVertex3f(75-5*i, 75,0  );

					glVertex3f(-75,75-5*i,0 );
					glVertex3f(75 ,75-5*i,0 );
				}
				glEnd();

			

				glLineWidth(3);		
				glBegin(GL_LINES);
				glColor3f(1,0.0,0.0);
				glVertex3f(0,0,0);
				glVertex3f(75,0,0);

				glColor3f(0.0,1,0.0);
				glVertex3f(0,0,0);
				glVertex3f(0,75,0);
				glEnd();

				glLineWidth(1);
				break;
			case XZ_GRID: ///////////////// XZ
				glColor3f(0.55,0.55,0.55);	

				glLineWidth(1);
				glBegin(GL_LINES);
				for (int i=0 ; i<151 ; i++)
				{
					glVertex3f(75-i,0,-75 );
					glVertex3f(75-i,0, 75  );

					glVertex3f(-75,0,75-i);
					glVertex3f(75 ,0,75-i );
				}
				glEnd();

				glLineWidth(2);
				glBegin(GL_LINES);
				for (int i=0 ; i<31 ; i++)
				{
					glVertex3f(75-5*i,0,-75 );
					glVertex3f(75-5*i,0, 75  );

					glVertex3f(-75,0,75-5*i);
					glVertex3f(75 ,0,75-5*i );
				}
				glEnd();


				glLineWidth(3);
				glBegin(GL_LINES);

				glColor3f(1,0.0,0.0);
				glVertex3f(0,0,0);
				glVertex3f(75,0,0);

				glColor3f(0.0,0.0,1);
				glVertex3f(0,0,0);
				glVertex3f(0,0,75);

				glEnd();
				glLineWidth(1);
				break;
			case YZ_GRID:
				glColor3f(0.55,0.55,0.55);		

				glLineWidth(1);
				glBegin(GL_LINES);
				for (int i=0 ; i<151 ; i++)
				{
					glVertex3f(0 , 75-i,-75);
					glVertex3f(0 , 75-i, 75  );

					glVertex3f(0 ,-75,75-i );
					glVertex3f(0 ,75 ,75-i );
				}
				glEnd();

				glLineWidth(2);
				glBegin(GL_LINES);
				for (int i=0 ; i<31 ; i++)
				{
					glVertex3f( 0 ,75-5*i,-75 );
					glVertex3f( 0 ,75-5*i, 75  );

					glVertex3f(0 ,-75,75-5*i );
					glVertex3f(0 ,75 ,75-5*i );
				}
				glEnd();

				glLineWidth(3);
				glBegin(GL_LINES);
				glColor3f(0.0,1,0.0);
				glVertex3f(0,0,0);
				glVertex3f(0,75,0);

				glColor3f(0.0,0.0,1);
				glVertex3f(0,0,0);
				glVertex3f(0,0,75);

				glEnd();
				glLineWidth(1);
				break;
			}
		}
		else if(m_grid_scale == SCALE_5X)
		{
			switch(m_oriantation)
			{
			case XY_GRID: //////////// XY
				glColor3f(0.55,0.55,0.55);	
				glLineWidth(1);

				glBegin(GL_LINES);
				for (int i=0 ; i<31 ; i++)
				{
					glVertex3f(75-5*i,-75,0 );
					glVertex3f(75-5*i, 75,0  );

					glVertex3f(-75,75-5*i,0 );
					glVertex3f(75 ,75-5*i,0 );
				}
				glEnd();

			

				glLineWidth(3);		
				glBegin(GL_LINES);
				glColor3f(1,0.0,0.0);
				glVertex3f(0,0,0);
				glVertex3f(75,0,0);

				glColor3f(0.0,1,0.0);
				glVertex3f(0,0,0);
				glVertex3f(0,75,0);
				glEnd();

				glLineWidth(1);
				break;
			case XZ_GRID: ///////////////// XZ
				glColor3f(0.55,0.55,0.55);	

				glLineWidth(1);
				glBegin(GL_LINES);
				for (int i=0 ; i<31 ; i++)
				{
					glVertex3f(75-5*i,0,-75 );
					glVertex3f(75-5*i,0, 75  );

					glVertex3f(-75,0,75-5*i);
					glVertex3f(75 ,0,75-5*i );
				}
				glEnd();


				glLineWidth(3);
				glBegin(GL_LINES);

				glColor3f(1,0.0,0.0);
				glVertex3f(0,0,0);
				glVertex3f(75,0,0);

				glColor3f(0.0,0.0,1);
				glVertex3f(0,0,0);
				glVertex3f(0,0,75);

				glEnd();
				glLineWidth(1);
				break;
			case YZ_GRID:
				glColor3f(0.55,0.55,0.55);		

				glLineWidth(1);
				glBegin(GL_LINES);
				for (int i=0 ; i<31 ; i++)
				{
					glVertex3f( 0 ,75-5*i,-75 );
					glVertex3f( 0 ,75-5*i, 75  );

					glVertex3f(0 ,-75,75-5*i );
					glVertex3f(0 ,75 ,75-5*i );
				}
				glEnd();

				glLineWidth(3);
				glBegin(GL_LINES);
				glColor3f(0.0,1,0.0);
				glVertex3f(0,0,0);
				glVertex3f(0,75,0);

				glColor3f(0.0,0.0,1);
				glVertex3f(0,0,0);
				glVertex3f(0,0,75);

				glEnd();
				glLineWidth(1);
				break;
			}
		}
		glEnable(GL_LIGHTING);
	}
}