#ifndef SMCANVAS_WIDGET_H
#define SMCANVAS_WIDGET_H

#include "../core/scene.h"
#include "../editing/EditingCamera.h"

#include "CanvasGrid.h"
#include "../common.h"

#include <QGLWidget>

enum CanvasType
{
	PERSPECTIVE_VIEW = 0,
	TOP_VIEW = 1,
	RIGHT_VIEW = 3,
	FRONT_VIEW =4
};

enum DrawingType
{
	SHADED = 0,
	WIRED = 1,
	SHADED_WIRED = 2
};

class SMCanvasWidget : public QGLWidget 
{
	Q_OBJECT

public:
	SMCanvasWidget(CanvasType typ_,Scene* sc_,QWidget *parent);
	~SMCanvasWidget();

	Scene* getScene(){ return m_scene; };
	CanvasGrid* getGrid() { return m_grid; }
	CanvasType getType(){ return m_canvas_type; }
	DrawingType getDrawingType() { return m_drawing_type; }
	EditingCamera* getCamera(){ return m_camera; }

	void setDrawingType(DrawingType typ_)
	{
		m_drawing_type = typ_;
		update();
	}
	void setShowCameras(bool bl_)
	{
		m_draw_cameras = bl_;
		update();
	}
	void setShowLighst(bool bl_)
	{
		m_draw_lights = bl_ ;
		update();
	}


	bool selectObject(int x_,int y_,int w_ = 1 , int h_ = 1);
	bool getPickedObjectsInfo(GLint hits_,GLuint* buff_);

	void activateTreePath(bool act_){ m_draw_tree_path = act_; update(); };
	void removeChildAt(int x_,int y_,int w_ = 3 , int h_ = 3);

	void selectLight(int x_ , int y_ , int w_ = 2 , int h_ = 2);
	void selectCamera(int x_ , int y_ , int w_ = 2 , int h_ = 2);

	void selectOnlyTarget(int x_ , int y_ , int w_ = 2 , int h_ = 2);
	void selectOnlyCamera(int x_ , int y_ , int w_ = 2 , int h_ = 2);

	void selectFace(int x_ , int y_ , int w_ = 1 , int h_ = 1);
	void selectVertex(int x_ , int y_ , int w_ = 1 , int h_ = 1);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);


private:
	Scene* m_scene;
	EditingCamera* m_camera;
	CanvasGrid* m_grid;
	CanvasType m_canvas_type;	
	DrawingType m_drawing_type;
	bool m_draw_tree_path;
	bool m_draw_cameras;
	bool m_draw_lights;

	

	void paintForObjectSelection();
	void paintForPathSelection();
	void paintForLightSelection();
	void paintForCameraSelection();
	void paintForVertexSelection();
	void paintForFaceSelection();

	void setUpTypeSettings();
	void glPutLetter(double x,double y,double z,char w);

	void drawShadedObject(GfxObject* obj_);
	void drawWiredObject(GfxObject* obj_);
	void drawShadedWiredObject(GfxObject* obj_);
	void drawObjectPath(GfxObject* obj_);

	void drawLight(Light* lg_);
	void drawCamera(Camera* cm_);

	void drawPoints(GfxObject* obj);


	//GLuint m_obj_sel_counter; 
	//void traverseSelectedObjectList(std::vector<int> sel_,GfxObject* obj_);
	//void drawGfxObjectSelections(GfxObject* obj_,Transformation tr_);
	//void drawGfxObjectTree(GfxObject* obj_,Transformation tr_);
	//void drawSingleObjectWired(GfxObject* obj_,Transformation tr_);
	//void drawSingleObjectShaded(GfxObject* obj_,Transformation tr_);
	//void drawSingleObjectShadedWired(GfxObject* obj_,Transformation tr_);

	//void drawObjectTreePath(GfxObject* obj_,Transformation tr_);
	//void drawSingleObjectPath(GfxObject* obj_,Transformation tr_);


	
};

#endif // SMCANVAS_H
