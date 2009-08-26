#ifndef CANVAS_GRID_H
#define CANVAS_GRID_H

#include "GL/glut.h"
#include "common.h"

enum  GridOrientation
{
	XY_GRID = 0,
	XZ_GRID = 1,
	YZ_GRID = 2
};
enum GridScale
{
	SCALE_1X = 0,
	SCALE_5X = 1
};

class SM_API_EXPORT CanvasGrid
{

public:
	CanvasGrid( GridOrientation or_)
	{
		m_orientation = or_;
		m_is_on = true;
		m_draw_axes = true;
		m_grid_scale = SCALE_5X;
	};
	~CanvasGrid(){};

	void setScale(GridScale sc_){ m_grid_scale = sc_; }

	void setOn(bool isOn_){ m_is_on = isOn_; };
	bool isOn() { return m_is_on; }

	void setAxesDrawn(bool draw_axes) { m_draw_axes = draw_axes; };
	bool areAxesDrawn() { return m_draw_axes; }

	GridScale getScale(){ return m_grid_scale; }

	void draw();

private:
	GridScale m_grid_scale;
	bool m_is_on;
	bool m_draw_axes;
	GridOrientation m_orientation;
};

#endif // SMCANVAS_H
