#ifndef SMCANVAS_WINDOW_H
#define SMCANVAS_WINDOW_H

#include "../core/scene.h"
#include "../editing/EditingCamera.h"
#include "smcanvaswidget.h"

#include <QResizeEvent>
#include <QMenuBar>
#include <QLabel>
#include "../common.h"

#include "../tools/translationTool.h"
#include "../tools/CameraTool.h"
#include "../tools/scaleTool.h"
#include "../tools/rotationTool.h"

#include "../editing/extrudedialog.h"


class SMCanvasWindow : public QWidget
{
	Q_OBJECT

public:
	SMCanvasWindow(CanvasType typ_,Scene* sc_,QWidget *parent);
	~SMCanvasWindow();

	SMCanvasWidget* getCanvasWidget(){ return m_canvas_widget; };
    void setCurrent(bool);

	void setExtendureDialog(ExtrudeDialog* ext_ ) { m_extendure_dialog = ext_; }


protected:
	void resizeEvent(QResizeEvent* );
	void mousePressEvent(QMouseEvent* );
	void mouseReleaseEvent(QMouseEvent* );
	void mouseMoveEvent(QMouseEvent* );
	void mouseDoubleClickEvent(QMouseEvent* );
	void wheelEvent(QWheelEvent *);
	void enterEvent(QEvent* );


private:

	ExtrudeDialog* m_extendure_dialog;

	SMCanvasWidget *m_canvas_widget;
	QMenuBar* m_menu_bar;
	QLabel* m_title_label;

	QAction *m_grid_action;
	QAction *m_1xgrid_action;
	QAction *m_5xgrid_action;
	QAction *m_fullaction;

	QMenu *m_camera_menu;
	QMenu* m_camera_list_menu;
	QList<QAction*> m_camera_list;
	QAction* m_reset_camera;

	QAction* m_wired_action;
	QAction* m_shaded_action;
	QAction* m_wired_shaded_action;

	QAction* m_show_lights_action;
	QAction* m_show_camera_action;

	SMTranslationTool* m_tralation_tool; 
	SMCameraTool* m_camera_tool;
	SMScaleTool* m_scale_tool;
	SMRotationTool* m_rotation_tool;

	QAction* m_tree_path_action;

	void createMenu();
	bool m_is_current;
	void changeCursor();
	

signals:
	void makeCurrent(CanvasType);
	void makeFullScreen(CanvasType,bool);
	void cameraUpdated();
	void sceneChanged();
	void canvasRepainted();

private slots:
	void showGrid(bool);
	void show1xGrid(bool);
	void show5xGrid(bool);
	void showFullScreen(bool fl_);
	void updateCameraList();
    void resetCamera();
	void shiftCamera();
	void changeDrawingType(bool);
	void changeCameraTool();
	void showTreePath(bool);
	void showItems(bool);
};
#endif // SMCANVAS_H
