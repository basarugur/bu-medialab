#include "smcanvaswindow.h"


SMCanvasWindow::SMCanvasWindow(CanvasType typ_,Scene* sc_,QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
	setVisible(true);

	m_canvas_widget = new SMCanvasWidget(typ_,sc_,this);	
	m_tralation_tool = new SMTranslationTool(m_canvas_widget->getCamera()); 
	m_camera_tool = new SMCameraTool(m_canvas_widget->getCamera());
	m_scale_tool = new SMScaleTool(m_canvas_widget->getCamera());
	m_rotation_tool = new SMRotationTool(m_canvas_widget->getCamera());
	createMenu();

	TRadiance clr_ = sc_->backgroundColor();
	//this->setStyleSheet("background-color:rgb(" +QString::number(clr_.r*255)
	//	               +"," +
	//				   QString::number(clr_.g*255) +"," +
	//				   QString::number(clr_.b*255)+"); color:rgb(255,255,255);" );

	m_title_label = new QLabel(this);
	m_title_label->setStyleSheet("background-color: rgb(80 ,80 , 255 ); \n color : rgb(255 , 255 ,255 )");
	m_title_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

	m_title_label->setFocusPolicy(Qt::NoFocus);

	if( typ_ == PERSPECTIVE_VIEW)
	{
		m_title_label->setText("Perspective");
	}
	else if ( typ_ == TOP_VIEW )
	{
		m_title_label->setText("Top");
	}
	else if ( typ_ == FRONT_VIEW)
	{
		m_title_label->setText("Front");
	}
	else if( typ_ == RIGHT_VIEW )
	{
		m_title_label->setText("Right");
	}

	setFocusPolicy(Qt::StrongFocus);

	m_is_current = false;
}
SMCanvasWindow::~SMCanvasWindow()
{
}
void SMCanvasWindow::resizeEvent(QResizeEvent* event)
{
	m_title_label->setGeometry(0,0,60,20);
	m_menu_bar->setGeometry(60,0,event->size().width()-60,20);
	m_canvas_widget->setGeometry(0,21,event->size().width(),event->size().height()-21);
	m_tralation_tool->setViewport(event->size().width(),event->size().height()-21);
	m_camera_tool->setViewport(event->size().width(),event->size().height()-21);
	m_scale_tool->setViewport(event->size().width(),event->size().height()-21);
	m_rotation_tool->setViewport(event->size().width(),event->size().height()-21);
}
void SMCanvasWindow::createMenu()
{
	m_menu_bar = new QMenuBar(this);
	m_menu_bar->setFocusPolicy(Qt::NoFocus);
	QMenu* viewMenu = m_menu_bar->addMenu("View");
	

	m_grid_action = new QAction("Off",this);
	m_grid_action->setCheckable(true);
	m_grid_action->setChecked(false);
	connect(m_grid_action,SIGNAL(toggled(bool)),this,SLOT(showGrid(bool)));

	m_1xgrid_action = new QAction("1x",this);
	m_1xgrid_action->setCheckable(true);
	m_1xgrid_action->setChecked(false);
	connect(m_1xgrid_action,SIGNAL(toggled(bool)),this,SLOT(show1xGrid(bool)));

	m_5xgrid_action = new QAction("5x",this);
	m_5xgrid_action->setCheckable(true);
	m_5xgrid_action->setChecked(true);
	connect(m_5xgrid_action,SIGNAL(toggled(bool)),this,SLOT(show5xGrid(bool)));

	m_fullaction = new QAction("Full Screen",this);
	m_fullaction->setCheckable(true);
	m_fullaction->setChecked(false);
	connect(m_fullaction,SIGNAL(toggled(bool)),this,SLOT(showFullScreen(bool)));

	m_tree_path_action = new QAction(QIcon(QPixmap("icons/MACSITE.png")),"Tree Path",this);
	m_tree_path_action->setCheckable(true);
	m_tree_path_action->setChecked(true);
	connect(m_tree_path_action,SIGNAL(toggled(bool)),this,SLOT(showTreePath(bool)));


	m_show_lights_action = new QAction("Lights",this);
	m_show_lights_action->setCheckable(true);
	m_show_lights_action->setChecked(true);
	m_show_lights_action->setData(0);
	connect(m_show_lights_action,SIGNAL(toggled(bool)),this,SLOT(showItems(bool)));

	m_show_camera_action = new QAction("Cameras",this);
	m_show_camera_action->setCheckable(true);
	m_show_camera_action->setChecked(true);
	m_show_camera_action->setData(1);
	connect(m_show_camera_action,SIGNAL(toggled(bool)),this,SLOT(showItems(bool)));

	viewMenu->addAction(m_fullaction);
	viewMenu->addSeparator();
	QMenu* gridMenu = viewMenu->addMenu("Grid");
	gridMenu->addAction(m_1xgrid_action);
	gridMenu->addAction(m_5xgrid_action);
	gridMenu->addAction(m_grid_action);
	viewMenu->addSeparator();
	viewMenu->addAction(m_tree_path_action);
	viewMenu->addAction(m_show_lights_action);
	viewMenu->addAction(m_show_camera_action);



	// camera menu
	m_camera_menu = m_menu_bar->addMenu("Camera");
	connect(m_camera_menu,SIGNAL(aboutToShow()),this,SLOT(updateCameraList()));

	m_reset_camera = new QAction("Reset Camera",this);
	connect(m_reset_camera,SIGNAL(triggered()),this,SLOT(resetCamera()));
	
	m_camera_menu->addAction(m_reset_camera);

	m_camera_list_menu = m_camera_menu->addMenu("Shift to");
	for(int i=0 ; i<m_camera_list.size() ; i++)
	{
		disconnect(m_camera_list[i],SIGNAL(triggered()),this,SLOT(shiftCamera()));
		delete m_camera_list[i];
	}
	m_camera_list.clear();
	for(int i=0 ; i<m_canvas_widget->getScene()->cameras().size();i++)
	{
		QAction* act_ = new QAction(QString::fromStdString(m_canvas_widget->getScene()->cameras()[i]->getName()),this);
		act_->setData(QVariant(i));
		connect(act_,SIGNAL(triggered()),this,SLOT(shiftCamera()));
		m_camera_list_menu->addAction(act_);
		m_camera_list.push_back(act_);
	}

	m_camera_menu->addSeparator();
	QAction* zomCamera = new QAction(QIcon(QPixmap("icons/zoom.png")),"Zoom",this);
	zomCamera->setData(0);
	connect(zomCamera,SIGNAL(triggered()),this,SLOT(changeCameraTool()));
	QAction* panCamera = new QAction(QIcon(QPixmap("icons/pan.png")),"Pan",this);
	panCamera->setData(1);
	connect(panCamera,SIGNAL(triggered()),this,SLOT(changeCameraTool()));
	QAction* rotCamera = new QAction(QIcon(QPixmap("icons/rotate.png")),"Rotate",this);
	rotCamera->setData(2);
	connect(rotCamera,SIGNAL(triggered()),this,SLOT(changeCameraTool()));

	m_camera_menu->addAction(zomCamera);
	m_camera_menu->addAction(panCamera);
	m_camera_menu->addAction(rotCamera);


	//

	m_wired_action = new QAction(QIcon(QPixmap("icons/wired.png")),"Wired",this);
	m_wired_action->setCheckable(true);
	m_wired_action->setChecked(true);
	m_wired_action->setData(0);
	connect(m_wired_action,SIGNAL(toggled(bool)),this,SLOT(changeDrawingType(bool)));

	m_shaded_action = new QAction(QIcon(QPixmap("icons/shaded.png")),"Shaded",this);
	m_shaded_action->setCheckable(true);
	m_shaded_action->setChecked(false);
	m_shaded_action->setData(1);
	connect(m_shaded_action,SIGNAL(toggled(bool)),this,SLOT(changeDrawingType(bool)));

	m_wired_shaded_action = new QAction(QIcon(QPixmap("icons/shadedwired.png")),"Shaded + Wired",this);
	m_wired_shaded_action->setCheckable(true);
	m_wired_shaded_action->setChecked(false);
	m_wired_shaded_action->setData(2);
	connect(m_wired_shaded_action,SIGNAL(toggled(bool)),this,SLOT(changeDrawingType(bool)));

	QMenu* drwingMenu = m_menu_bar->addMenu("Drawing");
	drwingMenu->addAction(m_wired_action);
	drwingMenu->addAction(m_shaded_action);
	drwingMenu->addAction(m_wired_shaded_action);
}
void SMCanvasWindow::changeCameraTool()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if(action)
	{
		int ind_ = action->data().toInt();
		switch(ind_)
		{
		case 0:
			m_camera_tool->setType(ZOOM_TOOL);
			break;
		case 1:
			m_camera_tool->setType(PAN_TOOL);
			break;
		case 2:
			m_camera_tool->setType(ROTATE_TOOL);
			break;
		}
		changeCursor();
	}
}
void SMCanvasWindow::showItems(bool bl_)
{
	QAction *action = qobject_cast<QAction *>(sender());
	if(action)
	{
		int ind_ = action->data().toInt();
		switch(ind_)
		{
		case 0:
			m_canvas_widget->setShowLighst(bl_);
			break;
		case 1:
			m_canvas_widget->setShowCameras(bl_);
			break;
		}
	}
}

void SMCanvasWindow::updateCameraList()
{
	for(int i=0 ; i<m_camera_list.size() ; i++)
	{
		disconnect(m_camera_list[i],SIGNAL(triggered()),this,SLOT(shiftCamera()));
	}
	m_camera_list_menu->clear();
	m_camera_list.clear();
	for(int i=0 ; i<m_canvas_widget->getScene()->cameras().size();i++)
	{
		QAction* act_ = new QAction(QString::fromStdString(m_canvas_widget->getScene()->cameras()[i]->getName()),this);
		act_->setData(QVariant(i));
		connect(act_,SIGNAL(triggered()),this,SLOT(shiftCamera()));
		m_camera_list_menu->addAction(act_);
		m_camera_list.push_back(act_);
	}
}
void SMCanvasWindow::changeDrawingType(bool bl_)
{
	QAction *action = qobject_cast<QAction *>(sender());
     if (action)
	 {
		 int ind_ = action->data().toInt();
		 if(bl_)
		 {
			 switch(ind_)
			 {
			 case 0:
				 m_canvas_widget->setDrawingType(WIRED);
				 m_shaded_action->setChecked(false);
				 m_wired_shaded_action->setChecked(false);
				 break;
			 case 1:
				 m_canvas_widget->setDrawingType(SHADED);
				 m_wired_action->setChecked(false);
				 m_wired_shaded_action->setChecked(false);
				 break;
			 case 2:
				 m_canvas_widget->setDrawingType(SHADED_WIRED);
				 m_shaded_action->setChecked(false);
				 m_wired_action->setChecked(false);
				 break;
			 default:
				 break;
			 }
		 }
		 else
		 {
			  switch(ind_)
			 {
			 case 0:
				 if(m_canvas_widget->getDrawingType() == WIRED)
					 m_wired_action->setChecked(true);
				 break;
			 case 1:
				 if(m_canvas_widget->getDrawingType() == SHADED)
					 m_shaded_action->setChecked(true);
				 break;
			 case 2:
				 if(m_canvas_widget->getDrawingType() == SHADED_WIRED)
					 m_wired_shaded_action->setChecked(true);
				 break;
			 default:
				 break;
			 }
		 }
	 }
}
void SMCanvasWindow::resetCamera()
{
	switch(m_canvas_widget->getType())
	{
	case PERSPECTIVE_VIEW:
		// camera
		m_canvas_widget->getCamera()->setPosition(Point3(20,-20,40));
		m_canvas_widget->getCamera()->setAtPoint(Point3(0,0,0));
		m_canvas_widget->getCamera()->setUpVector(Vector3(-1,1,1).normalize());
		m_canvas_widget->getCamera()->setName("Perspective");
		break;
	case TOP_VIEW:
		// camera
		m_canvas_widget->getCamera()->setPosition(Point3(0,0,30));
		m_canvas_widget->getCamera()->setAtPoint(Point3(0,0,0));
		m_canvas_widget->getCamera()->setUpVector(Vector3(0,1,0));
		m_canvas_widget->getCamera()->setName("Top");
		break;
	case RIGHT_VIEW:
		// camera
		m_canvas_widget->getCamera()->setPosition(Point3(30,0,0));
		m_canvas_widget->getCamera()->setAtPoint(Point3(0,0,0));
		m_canvas_widget->getCamera()->setUpVector(Vector3(0,0,1));
		m_canvas_widget->getCamera()->setName("Right");
		break;
	case FRONT_VIEW:
		// camera
		m_canvas_widget->getCamera()->setPosition(Point3(0,-30,0));
		m_canvas_widget->getCamera()->setAtPoint(Point3(0,0,0));
		m_canvas_widget->getCamera()->setUpVector(Vector3(0,0,1));
		m_canvas_widget->getCamera()->setName("Front");
		break;
	default:
		break;
	}
	m_canvas_widget->update();
	emit cameraUpdated();
}
void SMCanvasWindow::shiftCamera()
{
	QAction *action = qobject_cast<QAction *>(sender());
     if (action)
	 {
		 int ind_ = action->data().toInt();
		 m_canvas_widget->getCamera()->setToCamera(m_canvas_widget->getScene()->cameras()[ind_]);
		 m_canvas_widget->update();
		 emit cameraUpdated();
	 }
}
void SMCanvasWindow::mousePressEvent(QMouseEvent* event)
{
	m_canvas_widget->update();
	// set Current 
	if(!m_is_current) emit makeCurrent(m_canvas_widget->getType());

	if(event->button() == Qt::LeftButton)
	{
		if(m_camera_tool->getType() != NO_TOOL)
		{
			m_camera_tool->startAction(event->x(),event->y()-21);
		}
		else
		{
			GfxObject* tmp_ = NULL; 
			Light* tmpLight_ = NULL;
			Camera* cmr_ = NULL;
			Vertex* vrtx_ = NULL;
			Triangle* fce_ = NULL;
			switch(SMGlobalSettings::getEditingMode())
			{
			case SINGLE_OBJECT_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject();
					if(tmp_ != NULL)
						m_tralation_tool->startTranslate(tmp_->getIndividualTranform()
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case ROTATE_TYPE:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject();
					if(tmp_ != NULL)
						m_rotation_tool->startRotate(tmp_->getIndividualTranform()
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case SCALE_TYPE:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject(); 
					if(tmp_ != NULL)
						m_scale_tool->startScale(tmp_->getIndividualTranform()
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case DELETE_TYPE:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->deleteSelectedObject();
					emit sceneChanged();
					break;
				case DUPLICATE_TYPE:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->duplicateSelectedObject();
					emit sceneChanged();
					break;
				case CONVERT_TO_MESH:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject(); 
					if(tmp_ != NULL)
						tmp_->convertToMesh();
					emit sceneChanged();
				}
				break;
			case OBJECT_TREE_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject(); 
					if( tmp_ != NULL){
						m_canvas_widget->getScene()->selectTree(tmp_);
						m_tralation_tool->startTranslate(tmp_->getPublicTranform()
						,event->x(),event->y()-21);
					}
					emit sceneChanged();
					break;
				case ROTATE_TYPE:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject();
					if(tmp_ != NULL){
						m_canvas_widget->getScene()->selectTree(tmp_);
						m_rotation_tool->startRotate(tmp_->getPublicTranform()
						,event->x(),event->y()-21);
					}
					emit sceneChanged();
					break;
				case SCALE_TYPE:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject();
					if( tmp_ != NULL)
						m_scale_tool->startScale(tmp_->getPublicTranform()
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case DELETE_TYPE:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject(); 
					if(tmp_ != NULL)
					{
						m_canvas_widget->getScene()->selectTree(tmp_);
						m_canvas_widget->getScene()->deleteSelectedTree();
					}
					emit sceneChanged();
					break;
				case DUPLICATE_TYPE:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject(); 
					if(tmp_ != NULL)
					{
						m_canvas_widget->getScene()->selectTree(tmp_);
						m_canvas_widget->getScene()->duplicateSelectedTree();
					}					
					emit sceneChanged();
					break;
				case CONVERT_TO_MESH:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject(); 
					if(tmp_ != NULL)
						tmp_->convertToMesh();
					emit sceneChanged();
				case REMOVE_CHILD_TYPE:
					m_canvas_widget->getScene()->clearTreeSelection();
					m_canvas_widget->removeChildAt(event->pos().x(),event->pos().y()-21);
					emit sceneChanged();
				case ADD_CHILD_TYPE:
					m_canvas_widget->getScene()->clearobjectSelections();
					m_canvas_widget->selectObject(event->pos().x(),event->pos().y()-21);
					tmp_ = m_canvas_widget->getScene()->getSelectedObject();
					if(tmp_ != NULL)
						m_canvas_widget->getScene()->addToChild(tmp_);
					else
						m_canvas_widget->getScene()->setTmpChild(NULL);
					emit sceneChanged();
				}
				break;
			case LIGHT_EDITING_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_canvas_widget->getScene()->clearLightSelection();
					m_canvas_widget->selectLight(event->pos().x(),event->pos().y()-21);
					tmpLight_ = m_canvas_widget->getScene()->getSelectedLight();
					if(tmpLight_ != NULL)
						m_tralation_tool->startTranslate(tmpLight_
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case DELETE_TYPE:
					m_canvas_widget->getScene()->clearLightSelection();
					m_canvas_widget->selectLight(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->deleteSelectedLight();
					emit sceneChanged();
					break;
				case DUPLICATE_TYPE:
					m_canvas_widget->getScene()->clearLightSelection();
					m_canvas_widget->selectLight(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->duplicateSelectedLight();
					emit sceneChanged();
					break;
				}
				break;
			case CAMERA_EDITING_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_canvas_widget->getScene()->clearCameraSelection();
					m_canvas_widget->selectCamera(event->pos().x(),event->pos().y()-21);
					cmr_ = m_canvas_widget->getScene()->getSelectedCamera();
					if(cmr_ != NULL)
						m_tralation_tool->startTranslate(cmr_
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case DELETE_TYPE:
					m_canvas_widget->getScene()->clearCameraSelection();
					m_canvas_widget->selectCamera(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->deleteSelectedCamera();
					emit sceneChanged();
					break;
				case DUPLICATE_TYPE:
					m_canvas_widget->getScene()->clearCameraSelection();
					m_canvas_widget->selectCamera(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->duplicateSelectedCamera();
					emit sceneChanged();
					break;
				case MOVE_TARGER:
					m_canvas_widget->getScene()->clearCameraSelection();
					m_canvas_widget->selectOnlyTarget(event->pos().x(),event->pos().y()-21);
					cmr_ = m_canvas_widget->getScene()->getSelectedCamera();
					if(cmr_ != NULL)
						m_tralation_tool->startMoveTarget(cmr_
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case MOVE_CAMERA:
					m_canvas_widget->getScene()->clearCameraSelection();
					m_canvas_widget->selectOnlyCamera(event->pos().x(),event->pos().y()-21);
					cmr_ = m_canvas_widget->getScene()->getSelectedCamera();
					if(cmr_ != NULL)
						m_tralation_tool->startMoveCamera(cmr_
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				}
				break;
			case FACE_EDITING_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_canvas_widget->getScene()->clearFaceSelections();
					m_canvas_widget->selectFace(event->pos().x(),event->pos().y()-21);
					fce_ = m_canvas_widget->getScene()->getSelectedFace();
					if(fce_ != NULL)
						m_tralation_tool->startTranslate(fce_
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case DELETE_TYPE:
					m_canvas_widget->getScene()->clearFaceSelections();
					m_canvas_widget->selectFace(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->deleteSelectedFace();
					emit sceneChanged;
					break;
				case SPLIT_FACE:
					m_canvas_widget->getScene()->clearFaceSelections();
					m_canvas_widget->selectFace(event->pos().x(),event->pos().y()-21);
					m_canvas_widget->getScene()->splitSelectedFace();
					break;
				case EXTRUDE_FACE:
					m_canvas_widget->getScene()->clearFaceSelections();
					m_canvas_widget->selectFace(event->pos().x(),event->pos().y()-21);
					fce_ = m_canvas_widget->getScene()->getExtrudingFace();
					if (fce_ != NULL)
					{
						m_extendure_dialog->showDialog(fce_);
					}
				}
				break;
			case VERTEX_EDITING_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_canvas_widget->getScene()->clearVertexSelections();
					m_canvas_widget->selectVertex(event->pos().x(),event->pos().y()-21);
					vrtx_ = m_canvas_widget->getScene()->getSelectedVertex();
					if(vrtx_ != NULL)
						m_tralation_tool->startTranslate(vrtx_
						,event->x(),event->y()-21);
					emit sceneChanged();
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	else if(event->button() == Qt::RightButton)
	{
		m_camera_tool->release();
		m_scale_tool->release();
		m_rotation_tool->release();
		SMGlobalSettings::setEditingType(TRANSLATE_TYPE);
	}


	//std::cout << "Mouse pressed at ("<<event->pos().x()<<","<<event->pos().y()<<")"<<std::endl;
}
void SMCanvasWindow::mouseMoveEvent(QMouseEvent* event)
{
	
	if(m_camera_tool->getType() != NO_TOOL)
	{
		 m_camera_tool->takeAction(event->x(),event->y()-21);
		 emit cameraUpdated();
	}
	else
	{
		switch(SMGlobalSettings::getEditingMode())
		{
		case SINGLE_OBJECT_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->translate(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case ROTATE_TYPE:
					m_rotation_tool->rotate(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case SCALE_TYPE:
					m_scale_tool->scale(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				default:
					break;
				}
			break;
		case OBJECT_TREE_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->translate(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case ROTATE_TYPE:
					m_rotation_tool->rotate(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case SCALE_TYPE:
					m_scale_tool->scale(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				default:
					break;
				}
			break;
		case LIGHT_EDITING_MODE:
				switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->translate(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				}
				break;
		case CAMERA_EDITING_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->translate(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case MOVE_TARGER:
					m_tralation_tool->moveTarget(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				case MOVE_CAMERA:
					m_tralation_tool->moveCamera(event->x(),event->y()-21);
					emit sceneChanged();
					break;
				default:
					break;
				}
			break;
		case FACE_EDITING_MODE:
			switch(SMGlobalSettings::getEditingType())
			{
			case TRANSLATE_TYPE:
				m_tralation_tool->translate(event->x(),event->y()-21);
				emit sceneChanged();
				break;
			}
			break;
		case VERTEX_EDITING_MODE:
			switch(SMGlobalSettings::getEditingType())
			{
			case TRANSLATE_TYPE:
				m_tralation_tool->translate(event->x(),event->y()-21);
				emit sceneChanged();
				break;
			}
			break;
		default:
			break;
		}
	}

	emit canvasRepainted();
	m_canvas_widget->update();
}
void SMCanvasWindow::mouseReleaseEvent(QMouseEvent* event)
{
	m_canvas_widget->update();
	if(m_camera_tool->getType() != NO_TOOL)
	{
		m_camera_tool->release();
		changeCursor();
	}
	else
	{
		switch(SMGlobalSettings::getEditingMode())
		{
		case SINGLE_OBJECT_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->release();
					break;
				case ROTATE_TYPE:
					m_rotation_tool->release();
					break;
				case SCALE_TYPE:
					m_scale_tool->release();
					break;
				default:
					break;
				}
			break;
		case OBJECT_TREE_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->release();
					break;
				case ROTATE_TYPE:
					m_rotation_tool->release();
					break;
				case SCALE_TYPE:
					m_scale_tool->release();
					break;
				default:
					break;
				}
			break;
		case LIGHT_EDITING_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->release();
					break;
				default:
					break;
				}
			break;
		case CAMERA_EDITING_MODE:
			switch(SMGlobalSettings::getEditingType())
				{
				case TRANSLATE_TYPE:
					m_tralation_tool->release();
					break;
				case MOVE_CAMERA:
					m_tralation_tool->release();
					break;
				case MOVE_TARGER:
					m_tralation_tool->release();
					break;
				default:
					break;
				}
			break;
		case FACE_EDITING_MODE:
			m_canvas_widget->getScene()->restoreTriangles();
			switch(SMGlobalSettings::getEditingType())
			{
			case TRANSLATE_TYPE:
				m_tralation_tool->release();
				emit sceneChanged();
				break;
			}
		case VERTEX_EDITING_MODE:
			m_canvas_widget->getScene()->restoreTriangles();
			switch(SMGlobalSettings::getEditingType())
			{
			case TRANSLATE_TYPE:
				m_tralation_tool->release();
				emit sceneChanged();
				break;
			}
			break;
		default:
			break;
		}
	}
}
void SMCanvasWindow::showGrid(bool isOn)
{
	if(isOn)
	{
		m_canvas_widget->getGrid()->setOn(false);		
		m_1xgrid_action->setChecked(false);
		m_5xgrid_action->setChecked(false);
		m_canvas_widget->update();
	}
	else
	{
		if(!m_canvas_widget->getGrid()->isOn())
			m_grid_action->setChecked(true);
	}
}
void SMCanvasWindow::show1xGrid(bool isOn)
{
	if(isOn)
	{
		m_canvas_widget->getGrid()->setOn(true);
		m_canvas_widget->getGrid()->setScale(SCALE_1X);
		m_grid_action->setChecked(false);
		m_5xgrid_action->setChecked(false);
		m_canvas_widget->update();
	}
	else
	{
		if(m_canvas_widget->getGrid()->isOn() && m_canvas_widget->getGrid()->getScale()==SCALE_1X)
			m_1xgrid_action->setChecked(true);
	}
}
void SMCanvasWindow::show5xGrid(bool isOn)
{
	if(isOn)
	{
		m_canvas_widget->getGrid()->setOn(true);
		m_canvas_widget->getGrid()->setScale(SCALE_5X);
		m_grid_action->setChecked(false);
		m_1xgrid_action->setChecked(false);
		m_canvas_widget->update();
	}
	else
	{
		if(m_canvas_widget->getGrid()->isOn() && m_canvas_widget->getGrid()->getScale()==SCALE_5X)
			m_5xgrid_action->setChecked(true);
	}
}
void SMCanvasWindow::setCurrent(bool crnt_)
{
	m_is_current = crnt_;
	if(m_is_current)
	{
		m_title_label->setStyleSheet("background-color: rgb(0 ,0 , 200 ); \n color : rgb(255 , 255 ,255 )");
	}
	else
	{
		if(m_camera_tool->getType() != NO_TOOL)
		{
			m_camera_tool->release();
			changeCursor();
		}
		m_title_label->setStyleSheet("background-color: rgb(100 ,100 , 255 ); \n color : rgb(255 , 255 ,255 )");
	}
}
void SMCanvasWindow::showFullScreen(bool fl_)
{
	emit makeFullScreen(m_canvas_widget->getType(),fl_);
}
void SMCanvasWindow::mouseDoubleClickEvent(QMouseEvent* )
{
	m_fullaction->setChecked(!m_fullaction->isChecked());
}
void SMCanvasWindow::wheelEvent(QWheelEvent *event)
{
	emit canvasRepainted();
	m_canvas_widget->update();
	// set Current 
	if(!m_is_current) emit makeCurrent(m_canvas_widget->getType());

	if (event->orientation() == Qt::Vertical)
	{
		m_canvas_widget->getCamera()->zoomIn(event->delta());
		m_canvas_widget->update();
		emit cameraUpdated();
	}
}
void SMCanvasWindow::changeCursor()
{
	if(m_camera_tool->getType() == NO_TOOL)
	{
		switch(SMGlobalSettings::getEditingType())
		{
		case TRANSLATE_TYPE:
			setCursor(Qt::ArrowCursor);
			break;
		case ROTATE_TYPE: // rotateObjCursor.png
			setCursor(QCursor(QPixmap("icons/rotateObjCursor.png")));
			break;
		case SCALE_TYPE: // scaleCursor.png
			setCursor(QCursor(QPixmap("icons/scaleCursor.png")));
			break;
		case DELETE_TYPE: // icon_eraser.gif
			setCursor(QCursor(QPixmap("icons/icon_eraser.png")));
			break;
		case DUPLICATE_TYPE: // duplicate.png
			setCursor(QCursor(QPixmap("icons/duplicate.png")));
			break;
		case ADD_CHILD_TYPE:
			setCursor(Qt::ArrowCursor);
			break;
		case REMOVE_CHILD_TYPE:
			setCursor(Qt::ArrowCursor);
			break;
		case CONVERT_TO_MESH:
			setCursor(Qt::ArrowCursor);
			break;
		case SPLIT_FACE:
			setCursor(Qt::ArrowCursor);
			break;
		case EXTRUDE_FACE:
			setCursor(Qt::ArrowCursor);
			break;
		}
	}
	else
	{
		switch(m_camera_tool->getType())
		{
		case PAN_TOOL:
			setCursor(QCursor(QPixmap("icons/pan.png")));
			break;
		case ROTATE_TOOL:
			setCursor(QCursor(QPixmap("icons/rotate.png")));
			break;
		case ZOOM_TOOL:
			setCursor(QCursor(QPixmap("icons/zoom.png")));
			break;
		}
	}
}
void SMCanvasWindow::enterEvent(QEvent* )
{
	changeCursor();
	m_canvas_widget->update();
}
void SMCanvasWindow::showTreePath(bool act_)
{
	m_canvas_widget->activateTreePath(act_);
}