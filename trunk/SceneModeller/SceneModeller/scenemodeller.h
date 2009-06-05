#ifndef SCENEMODELLER_H
#define SCENEMODELLER_H

#include <QtGui/QMainWindow>
#include "ui_scenemodeller.h"

#include "Canvas/smcanvaswindow.h"
#include "core/scene.h"

#include "editing/smmenuhandler.h"



#include "windows/camerapropertiescontroller.h"
#include "windows/objectpropertiescontroller.h"
#include "windows/objecttreecontroller.h"

#include "centralwidget.h"

#include "editing/extrudedialog.h"



class SceneModeller : public QMainWindow
{
	Q_OBJECT
public:
	SceneModeller(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SceneModeller();

	void showDockWindows()
	{
		ui.ObjectPropertyDock->setVisible(true);
		ui.ObjectTreeDock->setVisible(true);
		ui.cameraPropertyDock->setVisible(true);
	}

private:
	Ui::SceneModellerClass ui;


	void initializeGUI();
	//  central widget
	CentralWidget* m_central_widget;

	/// Canvas
	SMCanvasWindow* m_top_canvas;
	SMCanvasWindow* m_front_canvas;
	SMCanvasWindow* m_right_canvas;
	SMCanvasWindow* m_perspective_canvas;
	SMCanvasWindow* m_current_canvas;
	Scene* m_scene;

	ExtrudeDialog* m_extendure_dialog;


	//dock window controllers
	ObjectTreeController* m_object_tree_controller;
	ObjectPropertiesController* m_object_pro_controller;
	CameraController* m_camera_controller;


	SMMenuHandler* m_menu_handler;

	int m_full_screen_index; // -1 for none
                             // 1 for perspective
                             // 2 for top
                             // 3 for right
                             // 4 for front
private slots:
	void changeCurrent(CanvasType);
	void changeFullScreen(CanvasType,bool);
	void updateScene();
	void centralWidgetSizeChanged();
	void repaintCanvases();

protected:
	void resizeEvent(QResizeEvent* );
};

#endif // SCENEMODELLER_H
