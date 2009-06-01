#include "smmenuhandler.h"


#include "../core/sphere.h"
#include "../core/cube.h"
#include "../core/cone.h"
#include "../core/cylinder.h"
#include "../core/twosidedcylinder.h"
#include "../core/torus.h"
#include "../core/gfxobject.h"

#include "../core/triangleshape.h"
#include "../core/rectangle.h"
#include "../core/circle.h"
#include "../core/disk.h"
#include "../core/partialdisk.h"

#include <math.h>

#include <QFileDialog>
#include <QMessageBox>


SMMenuHandler::SMMenuHandler(QObject *parent)
	: QObject(parent)
{
	srand(100);
	rand();
	rand();
	rand();

	m_vrml_device = new VrmlDevice();
	m_raw_device = new RawDevice();
	m_stl_device = new StlDevice();
}

SMMenuHandler::~SMMenuHandler()
{

}
void SMMenuHandler::setWindowActions(
		QAction* tree_wnd_action,
		QAction* obj_wnd_action,
		QAction* cmr_wnd_action
		)
{
	m_tree_wnd_action = tree_wnd_action;
	m_obj_wnd_action  = obj_wnd_action;
	m_cmr_wnd_action  = cmr_wnd_action;

	connect(m_tree_wnd_action,SIGNAL(toggled(bool)),m_object_tree_controller,SLOT(showDockWidget(bool)));
	connect(m_obj_wnd_action,SIGNAL(toggled(bool)),m_object_pro_controller,SLOT(showDockWidget(bool)));
	connect(m_cmr_wnd_action,SIGNAL(toggled(bool)),m_camera_controller,SLOT(showDockWidget(bool)));

	connect(m_object_tree_controller->m_dock_widget,SIGNAL(visibilityChanged(bool)),this,SLOT(updateWindowActions(bool)));
	connect(m_object_pro_controller->m_dock_widget,SIGNAL(visibilityChanged(bool)),this,SLOT(updateWindowActions(bool)));
	connect(m_camera_controller->m_dock_widget,SIGNAL(visibilityChanged(bool)),this,SLOT(updateWindowActions(bool)));

}
void SMMenuHandler::setWindowControllers(
	    ObjectTreeController* object_tree_controller,
	    ObjectPropertiesController* object_pro_controller,
	    CameraController* camera_controller
		)
{
	m_object_tree_controller = object_tree_controller;
	m_object_pro_controller = object_pro_controller;
	m_camera_controller = camera_controller;
}
void SMMenuHandler::updateWindowActions(bool)
{
	m_tree_wnd_action->setChecked(m_object_tree_controller->m_dock_widget->isVisible());
	m_obj_wnd_action->setChecked(m_object_pro_controller->m_dock_widget->isVisible());
	m_cmr_wnd_action->setChecked(m_camera_controller->m_dock_widget->isVisible());
}
void SMMenuHandler::setPrimitiveActions(
		QAction* edit_cameras_action,
		QAction* new_camera_action,
		QAction* point_light_action,
		QAction* area_light_action
		)
{
	m_edit_cameras_action = edit_cameras_action;
	m_new_camera_action = new_camera_action;
	m_point_light_action = point_light_action;
	m_area_light_action = area_light_action;

	m_new_camera_action->setData(0);
	m_point_light_action->setData(1);
	m_area_light_action->setData(2);

	connect(m_new_camera_action,SIGNAL(triggered()),this,SLOT(addNewItem()));
	connect(m_point_light_action,SIGNAL(triggered()),this,SLOT(addNewItem()));
	connect(m_area_light_action,SIGNAL(triggered()),this,SLOT(addNewItem()));

	connect(m_edit_cameras_action,SIGNAL(triggered()),m_edit_camera_dialog,SLOT(showDialog()));
}
void SMMenuHandler::addNewItem()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if(action)
	{
		int md_ = action->data().toInt();
		switch(md_)
		{
		case 0:
			*m_scene += new Camera();
			break;
		case 1:
			*m_scene += new PointLight();
			break;
		case 2:
			*m_scene += new AreaLight();
			break;
		default:
			break;
		}
		emit sceneChanged();
	}
}
void SMMenuHandler::setNewObjectActions(
		QAction* new_cube_action,
		QAction* new_sphere_action,
		QAction* new_cone_action,
		QAction* new_cylinder_action,
		QAction* new_2sidecylinder_action,
		QAction* new_torus_action
	)
{
	m_new_cube_action = new_cube_action;
	m_new_sphere_action = new_sphere_action;
	m_new_cone_action = new_cone_action;
	m_new_cylinder_action = new_cylinder_action;
	m_new_2sidecylinder_action = new_2sidecylinder_action;
	m_new_torus_action = new_torus_action;

	m_new_cube_action->setData(0);
	m_new_sphere_action->setData(1);
	m_new_cone_action->setData(2);
	m_new_cylinder_action->setData(3);
	m_new_2sidecylinder_action->setData(4);
	m_new_torus_action->setData(5);

	connect(m_new_cube_action,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_sphere_action,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_cone_action,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_cylinder_action,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_2sidecylinder_action,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_torus_action,SIGNAL(triggered()),this,SLOT(addNewObject()));
}
void SMMenuHandler::setNew2DActions(
		QAction* new_triangle,
		QAction* new_rectangle,
		QAction* new_circle,
		QAction* new_disk,
		QAction* new_partial_disk
		)
{
	m_new_triangle = new_triangle;
	m_new_rectangle = new_rectangle;
	m_new_circle = new_circle;
	m_new_disk = new_disk;
	m_new_partial_disk = new_partial_disk;

	m_new_triangle->setData(6);
	m_new_rectangle->setData(7);
	m_new_circle->setData(8);
	m_new_disk->setData(9);
	m_new_partial_disk->setData(10);

	connect(m_new_triangle,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_rectangle,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_circle,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_disk,SIGNAL(triggered()),this,SLOT(addNewObject()));
	connect(m_new_partial_disk,SIGNAL(triggered()),this,SLOT(addNewObject()));
}
void SMMenuHandler::addNewObject()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if(action)
	{
		int md_ = action->data().toInt();
		GfxObject* nwObj_ ; 
		switch (md_)
		{
		case 0:
			nwObj_ =new GfxObject(new Cube(),new Material(),new Transformation());
			nwObj_->setName("new cube");
			break;
		case 1:
			nwObj_ =new GfxObject(new Sphere(),new Material(),new Transformation());
			nwObj_->setName("new sphere");
			break;
		case 2:
			nwObj_ =new GfxObject(new Cone(),new Material(),new Transformation());
			nwObj_->setName("new cone");
			break;
		case 3:
			nwObj_ =new GfxObject(new Cylinder(),new Material(),new Transformation());
			nwObj_->setName("new cylinder");
			break;
		case 4:
			nwObj_ =new GfxObject(new TwoSidedCylinder(),new Material(),new Transformation());
			nwObj_->setName("new two sided cylinder");
			break;
		case 5:
			nwObj_ =new GfxObject(new Torus(),new Material(),new Transformation());
			nwObj_->setName("new torus");
			break;
		case 6:
			nwObj_ =new GfxObject(new TriangleShape(),new Material(),new Transformation());
			nwObj_->setName("new triangle");
			break;
		case 7:
			nwObj_ =new GfxObject(new RectangleShape(),new Material(),new Transformation());
			nwObj_->setName("new rectange");
			break;
		case 8:
			nwObj_ =new GfxObject(new Circle(),new Material(),new Transformation());
			nwObj_->setName("new circle");
			break;
		case 9:
			nwObj_ =new GfxObject(new Disk(),new Material(),new Transformation());
			nwObj_->setName("new disk");
			break;
		case 10:
			nwObj_ =new GfxObject(new PartialDisk(),new Material(),new Transformation());
			nwObj_->setName("new partial disk");
			break;
		default:
			break;
		};
		nwObj_->getMaterial()->setDiffColor(TRadiance(
				 ((double)rand())/((double)RAND_MAX) ,
				 ((double)rand())/((double)RAND_MAX) ,
				 ((double)rand())/((double)RAND_MAX) 
			));
		*m_scene += nwObj_;
		emit sceneChanged();
	}
}
void SMMenuHandler::setEditingModeActions(
		QAction* single_object_mode_action,
		QAction* object_tree_mode_action,
		QAction* camera_mode_action,
		QAction* light_mode_action,
		QAction* face_mode_action,
		QAction* point_mode_action
		)
{
	m_single_object_mode_action = single_object_mode_action;
	m_object_tree_mode_action = object_tree_mode_action ;
	m_camera_mode_action = camera_mode_action;
	m_light_mode_action = light_mode_action;
	m_face_mode_action = face_mode_action;
	m_point_mode_action = point_mode_action;

	m_single_object_mode_action->setData(QVariant(0));
	m_object_tree_mode_action->setData(QVariant(1));
	m_camera_mode_action->setData(QVariant(2));
	m_light_mode_action->setData(QVariant(3));
	m_face_mode_action->setData(QVariant(4));
	m_point_mode_action->setData(QVariant(5));

	connect(m_single_object_mode_action,SIGNAL(toggled(bool)),this,SLOT(changeEditingMode(bool)));
	connect(m_object_tree_mode_action,SIGNAL(toggled(bool)),this,SLOT(changeEditingMode(bool)));
	connect(m_camera_mode_action,SIGNAL(toggled(bool)),this,SLOT(changeEditingMode(bool)));
	connect(m_light_mode_action,SIGNAL(toggled(bool)),this,SLOT(changeEditingMode(bool)));
	connect(m_face_mode_action,SIGNAL(toggled(bool)),this,SLOT(changeEditingMode(bool)));
	connect(m_point_mode_action,SIGNAL(toggled(bool)),this,SLOT(changeEditingMode(bool)));
}
void SMMenuHandler::changeEditingMode(bool bl_)
{
	if(bl_)
	{
		QAction *action = qobject_cast<QAction *>(sender());
		if(action)
		{
			int md_ = action->data().toInt();
			switch(md_)
			{
			case 0:
				SMGlobalSettings::setEditingMode(SINGLE_OBJECT_MODE);

				m_object_tree_mode_action->setChecked(false);
				m_camera_mode_action->setChecked(false);
				m_light_mode_action->setChecked(false);
				m_face_mode_action->setChecked(false);
				m_point_mode_action->setChecked(false);

				// enable disable related actions
				m_addchild_type_action->setEnabled(false);
				m_removechild_type_action->setEnabled(false);
				m_split_face_action->setEnabled(false);
				m_extrude_face_action->setEnabled(false);
				m_move_camera_action->setEnabled(false);
				m_move_target_action->setEnabled(false);

				m_rotation_type_action->setEnabled(true);
				m_scale_type_action->setEnabled(true);
				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(true);
				m_duplicate_type_action->setEnabled(true);
				m_convert_mesh_action->setEnabled(true);


				// disable tree child move
				m_object_tree_controller->activateDragDropMode(false);
				m_object_pro_controller->setDockTitle("Selected Object");
				break;
			case 1:
				SMGlobalSettings::setEditingMode(OBJECT_TREE_MODE);
				m_single_object_mode_action->setChecked(false);
				m_camera_mode_action->setChecked(false);
				m_light_mode_action->setChecked(false);
				m_face_mode_action->setChecked(false);
				m_point_mode_action->setChecked(false);

				// enable disable related actions
				m_addchild_type_action->setEnabled(true);
				m_removechild_type_action->setEnabled(true);
				m_split_face_action->setEnabled(false);
				m_extrude_face_action->setEnabled(false);
				m_move_camera_action->setEnabled(false);
				m_move_target_action->setEnabled(false);

				m_rotation_type_action->setEnabled(true);
				m_scale_type_action->setEnabled(true);
				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(true);
				m_duplicate_type_action->setEnabled(true);
				m_convert_mesh_action->setEnabled(true);

				// activate tree child move
				m_object_tree_controller->activateDragDropMode(true);
				m_object_pro_controller->setDockTitle("Selected Object");
				break;
			case 2:
				SMGlobalSettings::setEditingMode(CAMERA_EDITING_MODE);
				m_single_object_mode_action->setChecked(false);
				m_object_tree_mode_action->setChecked(false);
				m_light_mode_action->setChecked(false);
				m_face_mode_action->setChecked(false);
				m_point_mode_action->setChecked(false);

				// enable disable related actions
				m_addchild_type_action->setEnabled(false);
				m_removechild_type_action->setEnabled(false);
				m_split_face_action->setEnabled(false);
				m_extrude_face_action->setEnabled(false);
				m_move_camera_action->setEnabled(true);
				m_move_target_action->setEnabled(true);

				m_rotation_type_action->setEnabled(false);
				m_scale_type_action->setEnabled(false);
				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(true);
				m_duplicate_type_action->setEnabled(true);
				m_convert_mesh_action->setEnabled(false);

				// disable tree child move
				m_object_tree_controller->activateDragDropMode(false);
				m_object_pro_controller->setDockTitle("Selected Camera");
				break;
			case 3:
				SMGlobalSettings::setEditingMode(LIGHT_EDITING_MODE);
				m_single_object_mode_action->setChecked(false);
				m_object_tree_mode_action->setChecked(false);
				m_camera_mode_action->setChecked(false);
				m_face_mode_action->setChecked(false);
				m_point_mode_action->setChecked(false);

				// enable disable related actions
				m_addchild_type_action->setEnabled(false);
				m_removechild_type_action->setEnabled(false);
				m_split_face_action->setEnabled(false);
				m_extrude_face_action->setEnabled(false);
				m_move_camera_action->setEnabled(false);
				m_move_target_action->setEnabled(false);

				m_rotation_type_action->setEnabled(false);
				m_scale_type_action->setEnabled(false);
				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(true);
				m_duplicate_type_action->setEnabled(true);
				m_convert_mesh_action->setEnabled(false);

				// disable tree child move
				m_object_tree_controller->activateDragDropMode(false);
				m_object_pro_controller->setDockTitle("Selected Light");

				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(true);
				m_duplicate_type_action->setEnabled(true);
				break;
			case 4:
				SMGlobalSettings::setEditingMode(FACE_EDITING_MODE);
				m_single_object_mode_action->setChecked(false);
				m_object_tree_mode_action->setChecked(false);
				m_camera_mode_action->setChecked(false);
				m_light_mode_action->setChecked(false);
				m_point_mode_action->setChecked(false);

				
				// enable disable related actions
				m_addchild_type_action->setEnabled(false);
				m_removechild_type_action->setEnabled(false);
				m_split_face_action->setEnabled(true);
				m_extrude_face_action->setEnabled(true);
				m_move_camera_action->setEnabled(false);
				m_move_target_action->setEnabled(false);

				m_rotation_type_action->setEnabled(false);
				m_scale_type_action->setEnabled(false);
				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(true);
				m_duplicate_type_action->setEnabled(false);
				m_convert_mesh_action->setEnabled(false);

				// disable tree child move
				m_object_tree_controller->activateDragDropMode(false);
				m_object_pro_controller->setDockTitle("Selected Face");

				break;
			case 5:
				SMGlobalSettings::setEditingMode(VERTEX_EDITING_MODE);
				m_single_object_mode_action->setChecked(false);
				m_object_tree_mode_action->setChecked(false);
				m_camera_mode_action->setChecked(false);
				m_light_mode_action->setChecked(false);
				m_face_mode_action->setChecked(false);

				// disable tree child move
				m_object_tree_controller->activateDragDropMode(false);
				m_object_pro_controller->setDockTitle("Selected Vertex");

				// enable disable related actions
				m_addchild_type_action->setEnabled(false);
				m_removechild_type_action->setEnabled(false);
				m_split_face_action->setEnabled(false);
				m_extrude_face_action->setEnabled(false);
				m_move_camera_action->setEnabled(false);
				m_move_target_action->setEnabled(false);

				m_rotation_type_action->setEnabled(false);
				m_scale_type_action->setEnabled(false);
				m_translation_type_action->setEnabled(true);
				m_delete_type_action->setEnabled(false);
				m_duplicate_type_action->setEnabled(false);
				m_convert_mesh_action->setEnabled(false);
				break;
		     default:
				break;
			};
		}

		SMGlobalSettings::setEditingType(TRANSLATE_TYPE);
		m_scene->clearAllSelections();
		emit sceneChanged();
	}
	else
	{
		QAction *action = qobject_cast<QAction *>(sender());
		if(action)
		{
			int md_ = action->data().toInt();
			switch(md_)
			{
			case 0:
				if(SMGlobalSettings::getEditingMode() == SINGLE_OBJECT_MODE)
					m_single_object_mode_action->setChecked(true);
				break;
			case 1:
				if(SMGlobalSettings::getEditingMode() == OBJECT_TREE_MODE)
					m_object_tree_mode_action->setChecked(true);
				break;
			case 2:
				if(SMGlobalSettings::getEditingMode() == CAMERA_EDITING_MODE)
					m_camera_mode_action->setChecked(true);
				break;
			case 3:
				if(SMGlobalSettings::getEditingMode() == LIGHT_EDITING_MODE)
					m_light_mode_action->setChecked(true);
				break;
			case 4:
				if(SMGlobalSettings::getEditingMode() == FACE_EDITING_MODE)
					m_face_mode_action->setChecked(true);
				break;
			case 5:
				if(SMGlobalSettings::getEditingMode() == VERTEX_EDITING_MODE)
					m_point_mode_action->setChecked(true);
				break;
		     default:
				break;
			};
		}
	}
}

void SMMenuHandler::setEditingTypeActions(
		QAction* rotation_type_action,
		QAction* translation_type_action,
		QAction* scale_type_action,
		QAction* delete_type_action,
		QAction* duplicate_type_action,
		QAction* addchild_type_action,
		QAction* removechild_type_action,
		QAction* convert_mesh_action
		)
{
	m_rotation_type_action = rotation_type_action;
	m_translation_type_action = translation_type_action;
	m_scale_type_action = scale_type_action;
	m_delete_type_action = delete_type_action;
	m_duplicate_type_action = duplicate_type_action;
	m_addchild_type_action = addchild_type_action;
	m_removechild_type_action = removechild_type_action;
	m_convert_mesh_action = convert_mesh_action;

	m_rotation_type_action->setData(0);
	m_translation_type_action->setData(1);
	m_scale_type_action->setData(2);
	m_delete_type_action->setData(3);
	m_duplicate_type_action->setData(4);
	m_addchild_type_action->setData(5);
	m_removechild_type_action->setData(6);
	m_convert_mesh_action->setData(7);

	connect(m_rotation_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_translation_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_scale_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_delete_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_duplicate_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_addchild_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_removechild_type_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
	connect(m_convert_mesh_action,SIGNAL(triggered()),this,SLOT(changeEditingType()));
}
void SMMenuHandler::changeEditingType()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if(action)
	{
		int md_ = action->data().toInt();
		switch(md_)
		{
		case 0:
			SMGlobalSettings::setEditingType(ROTATE_TYPE);
			break;
		case 1:
			SMGlobalSettings::setEditingType(TRANSLATE_TYPE);
			break;
		case 2:
			SMGlobalSettings::setEditingType(SCALE_TYPE);
			break;
		case 3:
			SMGlobalSettings::setEditingType(DELETE_TYPE);
			break;
		case 4:
			SMGlobalSettings::setEditingType(DUPLICATE_TYPE);
			break;
		case 5:
			SMGlobalSettings::setEditingType(ADD_CHILD_TYPE);
			break;
		case 6:
			SMGlobalSettings::setEditingType(REMOVE_CHILD_TYPE);
			m_scene->setTmpChild(NULL);
			break;
		case 7:
			SMGlobalSettings::setEditingType(CONVERT_TO_MESH);
			break;
	     default:
			break;
		};
	}
}
void SMMenuHandler::setRenderAction(
		QAction* render_action
		)
{
	m_render_action = render_action;
	connect(m_render_action,SIGNAL(triggered()),this,SLOT(renderScene()));

	m_render_controller = new RendererController(m_scene,m_raw_device,m_dialog_parent);
}
void SMMenuHandler::renderScene()
{
	m_render_controller->showDialog((*m_canvas)->getCanvasWidget()->getCamera());
}

void SMMenuHandler::setFileActions(
					QAction* new_scene_action,
					QAction* open_file_action,
					QAction* save_file_action,
					QAction* save_as_file_action,
					QAction* merge_file_action,
					QAction* import_file_action,
					QAction* export_file_action,
					QAction* exit_action
					)
{

	m_new_scene_action = new_scene_action;
	m_open_file_action = open_file_action;
	m_save_file_action = save_file_action;
	m_save_as_file_action = save_as_file_action;
	m_merge_file_action = merge_file_action;
	m_import_file_action = import_file_action;
	m_export_file_action = export_file_action;
	m_exit_action = exit_action;

	m_new_scene_action->setData(0);
	m_open_file_action->setData(1);
	m_save_file_action->setData(2);
	m_save_as_file_action->setData(3);
	m_merge_file_action->setData(4);
	m_import_file_action->setData(5);
	m_export_file_action->setData(6);
	m_exit_action->setData(7);

	connect(m_new_scene_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_open_file_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_save_file_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_save_as_file_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_merge_file_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_import_file_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_export_file_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));
	connect(m_exit_action,SIGNAL(triggered()),this,SLOT(fileActionClicked()));

}

void SMMenuHandler::fileActionClicked()
{
	QAction* sndr_ = qobject_cast<QAction*>(sender());
	if (sndr_)
	{
		QString flNme_;
		int ind_ = sndr_->data().toInt();
		switch (ind_)
		{
		case 0:
			if (QMessageBox::Yes==QMessageBox::question(m_dialog_parent,"Clear Scene","Are you sure to clear scene?",QMessageBox::Yes,QMessageBox::No))
			{
				m_scene->clearScene();
				emit sceneChanged();
			}
			break;
		case 1:
			m_scene->clearScene();
			flNme_ = QFileDialog::getOpenFileName(m_dialog_parent,"Open File",".",
				tr( " VRML Dos( *.wrl ) ;; RAW Dos ( *.raw ) ;; STL Dos( *.stl )"));
			if (flNme_.contains(".raw",Qt::CaseInsensitive))
			{
				m_raw_device->loadScene(flNme_.toStdString(),m_scene);
			}
			else if (flNme_.contains(".stl",Qt::CaseInsensitive))
			{
				m_stl_device->loadScene(flNme_.toStdString(),m_scene);
			}
			else if(flNme_.contains(".wrl",Qt::CaseInsensitive))
			{
				m_vrml_device->loadScene(flNme_.toStdString(),m_scene);
			}
			emit sceneChanged();
			break;
		case 2:
			flNme_ = QFileDialog::getSaveFileName(m_dialog_parent,"Save Scene",".",
				tr( " VRML Dos( *.wrl ) ;; RAW Dos ( *.raw ) ;; STL Dos( *.stl )"));
			if (flNme_.contains(".raw",Qt::CaseInsensitive))
			{
				m_raw_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			else if (flNme_.contains(".stl",Qt::CaseInsensitive))
			{
				m_stl_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			else if(flNme_.contains(".wrl",Qt::CaseInsensitive))
			{
				m_vrml_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			break;
		case 3:
			flNme_ = QFileDialog::getSaveFileName(m_dialog_parent,"Save As Scene",".",
				tr( " VRML Dos( *.wrl ) ;; RAW Dos ( *.raw ) ;; STL Dos( *.stl )"));
			if (flNme_.contains(".raw",Qt::CaseInsensitive))
			{
				m_raw_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			else if (flNme_.contains(".stl",Qt::CaseInsensitive))
			{
				m_stl_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			else if(flNme_.contains(".wrl",Qt::CaseInsensitive))
			{
				m_vrml_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			break;
		case 4:
			flNme_ = QFileDialog::getOpenFileName(m_dialog_parent,"Merge Scene",".",
				tr( " VRML Dos( *.wrl ) ;; RAW Dos ( *.raw ) ;; STL Dos( *.stl )"));
			if (flNme_.contains(".raw",Qt::CaseInsensitive))
			{
				m_raw_device->loadScene(flNme_.toStdString(),m_scene);
			}
			else if (flNme_.contains(".stl",Qt::CaseInsensitive))
			{
				m_stl_device->loadScene(flNme_.toStdString(),m_scene);
			}
			else if(flNme_.contains(".wrl",Qt::CaseInsensitive))
			{
				m_vrml_device->loadScene(flNme_.toStdString(),m_scene);
			}
			emit sceneChanged();
			break;
		case 5:
			flNme_ = QFileDialog::getOpenFileName(m_dialog_parent,"Import",".",
				tr( " VRML Dos( *.wrl ) ;; RAW Dos ( *.raw ) ;; STL Dos( *.stl )"));
			if (flNme_.contains(".raw",Qt::CaseInsensitive))
			{
				m_raw_device->loadScene(flNme_.toStdString(),m_scene);
			}
			else if (flNme_.contains(".stl",Qt::CaseInsensitive))
			{
				m_stl_device->loadScene(flNme_.toStdString(),m_scene);
			}
			else if(flNme_.contains(".wrl",Qt::CaseInsensitive))
			{
				m_vrml_device->loadScene(flNme_.toStdString(),m_scene);
			}
			emit sceneChanged();
			break;
		case 6:
			flNme_ = QFileDialog::getSaveFileName(m_dialog_parent,"Export Scene",".",
				tr( " VRML Dos( *.wrl ) ;; RAW Dos ( *.raw ) ;; STL Dos( *.stl )"));
			if (flNme_.contains(".raw",Qt::CaseInsensitive))
			{
				m_raw_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			else if (flNme_.contains(".stl",Qt::CaseInsensitive))
			{
				m_stl_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			else if(flNme_.contains(".wrl",Qt::CaseInsensitive))
			{
				m_vrml_device->saveToFile(flNme_.toStdString(),m_scene);
			}
			break;
		case 7:
			exit(0);
			break;
		default:
			break;
		}
	}
}

void SMMenuHandler::setFaceActions(
					QAction* split_face_action,
					QAction* extrude_face_action
					)
{
	m_split_face_action = split_face_action;
	m_extrude_face_action = extrude_face_action;

	m_split_face_action->setData(0);
	m_extrude_face_action->setData(1);

	connect(m_split_face_action,SIGNAL(triggered()),this,SLOT(editFaceActionEntered()));
	connect(m_extrude_face_action,SIGNAL(triggered()),this,SLOT(editFaceActionEntered()));
}
void SMMenuHandler::editFaceActionEntered()
{
	QAction* act_ = qobject_cast<QAction*>(sender());
	if (act_)
	{
		int ind_ = act_->data().toInt();
		switch(ind_)
		{
		case 0:
			SMGlobalSettings::setEditingType(SPLIT_FACE);
			break;
		case 1:
			SMGlobalSettings::setEditingType(EXTRUDE_FACE);
			break;
		default:
			break;

		}
	}
}

void SMMenuHandler::setCameraActions(
					  QAction* move_target_action,
					  QAction* move_camera_action
					  )
{
	m_move_target_action = move_target_action;
	m_move_camera_action = move_camera_action;

	m_move_target_action->setData(0);
	m_move_camera_action->setData(1);

	connect(m_move_camera_action,SIGNAL(triggered()),this,SLOT(cameraActionChanged()));
	connect(m_move_target_action,SIGNAL(triggered()),this,SLOT(cameraActionChanged()));

}
void SMMenuHandler::cameraActionChanged()
{
	QAction* act_ = qobject_cast<QAction*>(sender());
	if (act_)
	{
		int ind_ = act_->data().toInt();
		switch(ind_)
		{
		case 0:
			SMGlobalSettings::setEditingType(MOVE_TARGER);
			break;
		case 1:
			SMGlobalSettings::setEditingType(MOVE_CAMERA);
			break;
		}
	}
}
void SMMenuHandler::setToolBars(
				 QToolBar* file_toolbar,
				 QToolBar* mode_toolbar,
				 QToolBar* threedobjects_toolbar,
				 QToolBar* twodobjects_toolbar,
				 QToolBar* primitive_toolbar,
				 QToolBar* mesh_toolbar,
				 QToolBar* render_toolbar,
				 QToolBar* camera_toolbar,
				 QToolBar* edit_toolbar
				 )
{

	//toolbars 
	m_file_toolbar = file_toolbar;
	m_mode_toolbar = mode_toolbar;
	m_3dobjects_toolbar = threedobjects_toolbar;
	m_2dobjects_toolbar = twodobjects_toolbar;
	m_primitive_toolbar = primitive_toolbar;
	m_mesh_toolbar = mesh_toolbar;
	m_render_toolbar = render_toolbar;
	m_camera_toolbar = camera_toolbar;
	m_edit_toolbar = edit_toolbar;



}

void SMMenuHandler::setToolBarActions (
						QAction* file_toolbar_action,
						QAction* mode_toolbar_action,
						QAction* threedobjects_toolbar_action,
						QAction* twodobjects_toolbar_action,
						QAction* primitive_toolbar_action,
						QAction* mesh_toolbar_action,
						QAction* render_toolbar_action,
						QAction* camera_toolbar_action,
						QAction* edit_toolbar_action)
{
	//toolbar actions
	m_file_toolbar_action = file_toolbar_action;
	m_mode_toolbar_action = mode_toolbar_action;
	m_3dobjects_toolbar_action = threedobjects_toolbar_action;
	m_2dobjects_toolbar_action = twodobjects_toolbar_action;
	m_primitive_toolbar_action = primitive_toolbar_action;
	m_mesh_toolbar_action = mesh_toolbar_action;
	m_render_toolbar_action = render_toolbar_action;
	m_camera_toolbar_action = camera_toolbar_action;
	m_edit_toolbar_action = edit_toolbar_action;

	m_file_toolbar_action->setData(0);
	m_mode_toolbar_action->setData(1);
	m_3dobjects_toolbar_action->setData(2);
	m_2dobjects_toolbar_action->setData(3);
	m_primitive_toolbar_action->setData(4);
	m_mesh_toolbar_action->setData(5);
	m_render_toolbar_action->setData(6);
	m_camera_toolbar_action->setData(7);
	m_edit_toolbar_action->setData(8);

	connect(m_file_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_mode_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_3dobjects_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_2dobjects_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_primitive_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_mesh_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_render_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_camera_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));
	connect(m_edit_toolbar_action,SIGNAL(toggled(bool)),this,SLOT(showHideToolbars(bool)));

}

void SMMenuHandler::showHideToolbars(bool bl_)
{

	QAction* act_ = qobject_cast<QAction*>(sender());

	if (act_)
	{
		int ind_ = act_->data().toInt();
		switch(ind_)
		{
		case 0:
			m_file_toolbar->setVisible(bl_);
			break;
		case 1:
			m_mode_toolbar->setVisible(bl_);
			break;
		case 2:
			m_3dobjects_toolbar->setVisible(bl_);
			break;
		case 3:
			m_2dobjects_toolbar->setVisible(bl_);
			break;
		case 4:
			m_primitive_toolbar->setVisible(bl_);
			break;
		case 5:
			m_mesh_toolbar->setVisible(bl_);
			break;
		case 6:
			m_render_toolbar->setVisible(bl_);
			break;
		case 7:
			m_camera_toolbar->setVisible(bl_);
			break;
		case 8:
			m_edit_toolbar->setVisible(bl_);
			break;
		default:
			break;
		}
	}
}