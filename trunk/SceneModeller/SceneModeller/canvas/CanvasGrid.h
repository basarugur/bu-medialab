#ifndef CANVAS_GRID_H
#define CANVAS_GRID_H



#include <QGLWidget>

enum GridOriantation
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

class CanvasGrid
{

public:
	CanvasGrid( GridOriantation or_)
	{
		m_oriantation = or_;
		m_is_on = true;
		m_grid_scale = SCALE_5X;
	};
	~CanvasGrid(){};

	void setScale(GridScale sc_){ m_grid_scale = sc_; }
	void setOn(bool isOn_){ m_is_on = isOn_; };
	bool isOn() { return m_is_on; }
	GridScale getScale(){ return m_grid_scale; }

	void draw();

private:
	GridScale m_grid_scale;
	bool m_is_on;
	GridOriantation m_oriantation;
};

#endif // SMCANVAS_H
