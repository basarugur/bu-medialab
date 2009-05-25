#include "scenemodeller.h"
#include "centralwidget.h"

SceneModeller::SceneModeller(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	m_scene = new Scene();
	//m_scene->backgroundColor() = TRadiance(0,0,0);
	initializeGUI();
}


void SceneModeller::initializeGUI()
{
	m_central_widget = new CentralWidget(this);
	this->setCentralWidget(m_central_widget);

	m_top_canvas = new SMCanvasWindow(TOP_VIEW,m_scene,m_central_widget);
	m_front_canvas = new SMCanvasWindow(FRONT_VIEW,m_scene,m_central_widget);
	m_right_canvas = new SMCanvasWindow(RIGHT_VIEW,m_scene,m_central_widget);
	m_perspective_canvas = new SMCanvasWindow(PERSPECTIVE_VIEW,m_scene,m_central_widget);

	m_extendure_dialog = new ExtrudeDialog(this);
	connect(m_extendure_dialog,SIGNAL(sceneChanged()),this,SLOT(updateScene()));
	m_top_canvas->setExtendureDialog(m_extendure_dialog);
	m_front_canvas->setExtendureDialog(m_extendure_dialog);
	m_right_canvas->setExtendureDialog(m_extendure_dialog);
	m_perspective_canvas->setExtendureDialog(m_extendure_dialog);


	connect(m_top_canvas,SIGNAL(makeCurrent(CanvasType)),this,SLOT(changeCurrent(CanvasType)));
	connect(m_front_canvas,SIGNAL(makeCurrent(CanvasType)),this,SLOT(changeCurrent(CanvasType)));
	connect(m_right_canvas,SIGNAL(makeCurrent(CanvasType)),this,SLOT(changeCurrent(CanvasType)));
	connect(m_perspective_canvas,SIGNAL(makeCurrent(CanvasType)),this,SLOT(changeCurrent(CanvasType)));

	connect(m_top_canvas,SIGNAL(makeFullScreen(CanvasType,bool)),this,SLOT(changeFullScreen(CanvasType,bool)));
	connect(m_front_canvas,SIGNAL(makeFullScreen(CanvasType,bool)),this,SLOT(changeFullScreen(CanvasType,bool)));
	connect(m_right_canvas,SIGNAL(makeFullScreen(CanvasType,bool)),this,SLOT(changeFullScreen(CanvasType,bool)));
	connect(m_perspective_canvas,SIGNAL(makeFullScreen(CanvasType,bool)),this,SLOT(changeFullScreen(CanvasType,bool)));

	connect(m_top_canvas,SIGNAL(sceneChanged()),this,SLOT(updateScene()));
	connect(m_front_canvas,SIGNAL(sceneChanged()),this,SLOT(updateScene()));
	connect(m_right_canvas,SIGNAL(sceneChanged()),this,SLOT(updateScene()));
	connect(m_perspective_canvas,SIGNAL(sceneChanged()),this,SLOT(updateScene()));

	// create dock controllers
	m_object_tree_controller = new ObjectTreeController(ui.ObjectTreeDock);
	m_object_pro_controller = new ObjectPropertiesController(ui.ObjectPropertyDock);
	m_camera_controller = new CameraController(ui.cameraPropertyDock);

	connect(m_object_tree_controller,SIGNAL(sceneChanged()),this,SLOT(updateScene()));
	connect(m_object_pro_controller,SIGNAL(sceneChanged()),this,SLOT(updateScene()));
	connect(m_camera_controller,SIGNAL(sceneChanged()),this,SLOT(updateScene()));

	m_object_tree_controller->setScene(m_scene);
	m_object_pro_controller->setScene(m_scene);

	// creat menu
	m_menu_handler = new SMMenuHandler(this);
	m_menu_handler->setScene(m_scene);
	m_menu_handler->setCanvas(&m_current_canvas);
	m_menu_handler->serDialogParent(this);
	m_menu_handler->setWindowControllers(m_object_tree_controller,m_object_pro_controller,
		m_camera_controller);
	m_menu_handler->setWindowActions(ui.actionObject_Tree_Dock,
		ui.actionObject_Properties_Dock,
		ui.actionCamera_Property_Window);
	m_menu_handler->setPrimitiveActions(ui.actionCamera,ui.actionNew_Camera,
		ui.actionPoint_Light,ui.actionArea_Light);
	m_menu_handler->setNewObjectActions(ui.actionBox,
		ui.actionSphere,ui.actionCone,ui.actionCylinder,ui.actionTow_Sided_Cylinder,
		ui.actionTorus);
	m_menu_handler->setNew2DActions(ui.actionTriangle,ui.actionRectangle,
		ui.actionCircle,ui.actionDisk,ui.actionPartial_Disk);
	m_menu_handler->setEditingModeActions(ui.actionSingle_Object,
		ui.actionObject_Tree,ui.actionCamera_Editing,
		ui.actionLight_2,ui.actionFace,ui.actionPoint);
	m_menu_handler->setEditingTypeActions(ui.actionRotate,ui.actionTranslate,ui.actionScale,
		ui.actionDelete_2,ui.actionDuplicate,ui.actionAdd_Child,ui.actionRemove_Child,
		ui.actionConvert_to_Mesh);
	m_menu_handler->setRenderAction(ui.actionRender);
	m_menu_handler->setFileActions(ui.actionNew,ui.actionOpen,ui.actionSave,
		ui.actionSave_As,ui.actionMerge,ui.actionImport,ui.actionExport,ui.actionExit);
	m_menu_handler->setFaceActions(ui.actionSplit_Face,ui.actionExtrude_Face);
	m_menu_handler->setCameraActions(ui.actionMove_Target,ui.actionMove_Camera);
	m_menu_handler->setToolBars(ui.fileToolBar,ui.toolBar_2,ui.toolBar_3,ui.toolBar_4,
		ui.toolBar_5,ui.toolBar_6,ui.toolBar_8,ui.toolBar_7,ui.toolBar);
	m_menu_handler->setToolBarActions(ui.actionFile_Tool_Bar,ui.actionMode_Tool_Bar,
		ui.action3D_Objects_Toolbar,ui.action2D_Objects_Toolbar,ui.actionPrimitive_Toolbar,
		ui.actionMesh_Toolbar,ui.actionRender_Toolbar,ui.actionCamera_Toolbar,ui.actionEdit_Toolbar);

	connect(m_top_canvas,SIGNAL(cameraUpdated()),m_camera_controller,SLOT(updateCameraInfo()));
	connect(m_front_canvas,SIGNAL(cameraUpdated()),m_camera_controller,SLOT(updateCameraInfo()));
	connect(m_right_canvas,SIGNAL(cameraUpdated()),m_camera_controller,SLOT(updateCameraInfo()));
	connect(m_perspective_canvas,SIGNAL(cameraUpdated()),m_camera_controller,SLOT(updateCameraInfo()));

	connect(m_top_canvas,SIGNAL(canvasRepainted()),this,SLOT(repaintCanvases()));
	connect(m_front_canvas,SIGNAL(canvasRepainted()),this,SLOT(repaintCanvases()));
	connect(m_right_canvas,SIGNAL(canvasRepainted()),this,SLOT(repaintCanvases()));
	connect(m_perspective_canvas,SIGNAL(canvasRepainted()),this,SLOT(repaintCanvases()));

	connect(m_menu_handler,SIGNAL(sceneChanged()),this,SLOT(updateScene()));


	 changeCurrent(TOP_VIEW);
	 connect(m_central_widget,SIGNAL(sizeChanged()),this,SLOT(centralWidgetSizeChanged()));
	 changeFullScreen(TOP_VIEW,false);


	 ui.actionObject_Tree_Dock->setChecked(true);
	 ui.actionObject_Properties_Dock->setChecked(true);
	 ui.actionCamera_Property_Window->setChecked(true);
}
SceneModeller::~SceneModeller()
{

}

void SceneModeller::changeCurrent(CanvasType typ_)
{
	switch(typ_)
	{
	case PERSPECTIVE_VIEW:
		m_top_canvas->setCurrent(false);
		m_front_canvas->setCurrent(false);
		m_right_canvas->setCurrent(false);
		m_perspective_canvas->setCurrent(true);
		m_current_canvas = m_perspective_canvas;
		break;
	case TOP_VIEW:
		m_top_canvas->setCurrent(true);
		m_front_canvas->setCurrent(false);
		m_right_canvas->setCurrent(false);
		m_perspective_canvas->setCurrent(false);
		m_current_canvas = m_top_canvas;
		break;
	case RIGHT_VIEW:
		m_top_canvas->setCurrent(false);
		m_front_canvas->setCurrent(false);
		m_right_canvas->setCurrent(true);
		m_perspective_canvas->setCurrent(false);
		m_current_canvas = m_right_canvas;
		break;
	case FRONT_VIEW:
		m_top_canvas->setCurrent(false);
		m_front_canvas->setCurrent(true);
		m_right_canvas->setCurrent(false);
		m_perspective_canvas->setCurrent(false);
		m_current_canvas = m_front_canvas;
		break;
	}
	m_camera_controller->ShowCamera(m_current_canvas->getCanvasWidget()->getCamera());
}
void SceneModeller::changeFullScreen(CanvasType typ_,bool bl_)
{
	int x_ = (m_central_widget->width()-6)/2;
	int y_ = (m_central_widget->height()-6)/2;
	if(bl_)
	{
		switch(typ_)
		{
		case PERSPECTIVE_VIEW:
			m_perspective_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
			m_top_canvas->setGeometry(2,2,0,0);
			m_right_canvas->setGeometry(2,2,0,0);
			m_front_canvas->setGeometry(2,2,0,0);
			m_full_screen_index = 1;
			break;
		case TOP_VIEW:
			m_top_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
			m_perspective_canvas->setGeometry(2,2,0,0);
			m_right_canvas->setGeometry(2,2,0,0);
			m_front_canvas->setGeometry(2,2,0,0);
			m_full_screen_index = 2;
			break;
		case RIGHT_VIEW:
			m_right_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
			m_perspective_canvas->setGeometry(2,2,0,0);
			m_top_canvas->setGeometry(2,2,0,0);
			m_front_canvas->setGeometry(2,2,0,0);
			m_full_screen_index = 3;
			break;
		case FRONT_VIEW:
			m_front_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
			m_perspective_canvas->setGeometry(2,2,0,0);
			m_top_canvas->setGeometry(2,2,0,0);
			m_right_canvas->setGeometry(2,2,0,0);
			m_full_screen_index = 4;
			break;
		}
	}
	else
	{
		m_full_screen_index = -1;

	    m_top_canvas->setGeometry(2,2,x_,y_);
		m_perspective_canvas->setGeometry(4+x_,2,x_,y_);
		m_right_canvas->setGeometry(4+x_,4+y_,x_,y_);
		m_front_canvas->setGeometry(2,4+y_,x_,y_);
	}
}
void SceneModeller::resizeEvent(QResizeEvent* )
{
	centralWidgetSizeChanged();
}
void SceneModeller::repaintCanvases()
{
	//m_top_canvas->getCanvasWidget()->repaint();
	//m_perspective_canvas->getCanvasWidget()->repaint();
	//m_right_canvas->getCanvasWidget()->repaint();
	//m_front_canvas->getCanvasWidget()->repaint();
}
void SceneModeller::updateScene()
{
	m_top_canvas->getCanvasWidget()->repaint();
	m_front_canvas->getCanvasWidget()->repaint();
	m_right_canvas->getCanvasWidget()->repaint();
	m_perspective_canvas->getCanvasWidget()->repaint();

	m_object_pro_controller->checkScene();
	m_object_tree_controller->checkScene();
}
void SceneModeller::centralWidgetSizeChanged()
{
	int x_ = (m_central_widget->width()-6)/2;
	int y_ = (m_central_widget->height()-6)/2;
	switch(m_full_screen_index)
	{
	case -1:
		m_top_canvas->setGeometry(2,2,x_,y_);
		m_perspective_canvas->setGeometry(4+x_,2,x_,y_);
		m_right_canvas->setGeometry(4+x_,4+y_,x_,y_);
		m_front_canvas->setGeometry(2,4+y_,x_,y_);
		break;
	case 1:
		m_perspective_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
		m_top_canvas->setGeometry(2,2,0,0);
		m_right_canvas->setGeometry(2,2,0,0);
		m_front_canvas->setGeometry(2,2,0,0);
		break;
	case 2:
		m_top_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
		m_perspective_canvas->setGeometry(2,2,0,0);
		m_right_canvas->setGeometry(2,2,0,0);
		m_front_canvas->setGeometry(2,2,0,0);
		break;
	case 3:
		m_right_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
		m_perspective_canvas->setGeometry(2,2,0,0);
		m_top_canvas->setGeometry(2,2,0,0);
		m_front_canvas->setGeometry(2,2,0,0);
		break;
	case 4:
		m_front_canvas->setGeometry(2,2,2*x_+2,2*y_+2);
		m_perspective_canvas->setGeometry(2,2,0,0);
		m_top_canvas->setGeometry(2,2,0,0);
		m_right_canvas->setGeometry(2,2,0,0);
		break;
	default:
		break;
	}
}
