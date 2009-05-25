#ifndef SMMENU_HANDLER_H
#define SMMENU_HANDLER_H

#include <QObject>
#include <QToolBar>

#include "../formats/SMIODevice.h"
#include "../formats/vrmldevice.h"
#include "../formats/rawdevice.h"
#include "../formats/stldevice.h"


#include "../core/scene.h"
#include "../canvas/smcanvaswindow.h"

#include "../camera/editcamera.h"


#include "../windows/camerapropertiescontroller.h"
#include "../windows/objectpropertiescontroller.h"
#include "../windows/objecttreecontroller.h"

#include "../common.h"

#include "../renderercontroller.h"




class SMMenuHandler : public QObject
{
	Q_OBJECT
public:
	SMMenuHandler(QObject *parent);
	~SMMenuHandler();

	void serDialogParent(QWidget* dl_)
	{ 
		m_dialog_parent=dl_; 
		m_edit_camera_dialog = new EditCamera(m_scene,dl_);
	}
	void setScene(Scene* sc_) { m_scene = sc_ ;};
	void setCanvas(SMCanvasWindow** cn_) { m_canvas = cn_; };

	void setWindowActions(
		QAction* tree_wnd_action,
		QAction* obj_wnd_action,
		QAction* cmr_wnd_action
		);
	void setWindowControllers(
	    ObjectTreeController* object_tree_controller,
	    ObjectPropertiesController* object_pro_controller,
	    CameraController* camera_controller
		);
	void setPrimitiveActions(
		QAction* edit_cameras_action,
		QAction* new_camera_action,
		QAction* point_light_action,
		QAction* area_light_action
		);
	void setNewObjectActions(
		QAction* new_cube_action,
		QAction* new_sphere_action,
		QAction* new_cone_action,
		QAction* new_cylinder_action,
		QAction* new_2sidecylinder_action,
		QAction* new_torus_action
		);

	void setNew2DActions(
		QAction* new_triangle,
		QAction* new_rectangle,
		QAction* new_circle,
		QAction* new_disk,
		QAction* new_partial_disk
		);

	void setEditingModeActions(
		QAction* single_object_mode_action,
		QAction* object_tree_mode_action,
		QAction* camera_mode_action,
		QAction* light_mode_action,
		QAction* face_mode_action,
		QAction* point_mode_action
		);

	void setEditingTypeActions(
		QAction* rotation_type_action,
		QAction* translation_type_action,
		QAction* scale_type_action,
		QAction* delete_type_action,
		QAction* duplicate_type_action,
		QAction* addchild_type_action,
		QAction* removechild_type_action,
		QAction* convert_mesh_action
		);

	void setRenderAction(
		QAction* render_action
		);

	void setFileActions(
	QAction* new_scene_action,
	QAction* open_file_action,
	QAction* save_file_action,
	QAction* save_as_file_action,
	QAction* merge_file_action,
	QAction* import_file_action,
	QAction* export_file_action,
	QAction* exit_action
		);
	void setFaceActions(
	QAction* split_face_action,
	QAction* extrude_face_action
	);

	void setCameraActions(
		QAction* move_target_action,
	    QAction* move_camera_action
		);

	void setToolBars(
		QToolBar* file_toolbar,
		QToolBar* mode_toolbar,
		QToolBar* threedobjects_toolbar,
		QToolBar* twodobjects_toolbar,
		QToolBar* primitive_toolbar,
		QToolBar* mesh_toolbar,
		QToolBar* render_toolbar,
		QToolBar* camera_toolbar,
		QToolBar* edit_toolbar
	);

	void setToolBarActions (
		QAction* file_toolbar_action,
		QAction* mode_toolbar_action,
		QAction* threedobjects_toolbar_action,
		QAction* twodobjects_toolbar_action,
		QAction* primitive_toolbar_action,
		QAction* mesh_toolbar_action,
		QAction* render_toolbar_action,
		QAction* camera_toolbar_action,
		QAction* edit_toolbar_action
	);

signals:
	void sceneChanged();

private:

	VrmlDevice* m_vrml_device;
	RawDevice* m_raw_device;
	StlDevice* m_stl_device;

	RendererController* m_render_controller;

	QWidget* m_dialog_parent;

	Scene* m_scene;
	SMCanvasWindow** m_canvas;

	EditCamera* m_edit_camera_dialog;

	// window menu
	QAction* m_tree_wnd_action;
	QAction* m_obj_wnd_action;
	QAction* m_cmr_wnd_action;
	//

	//dock window controllers
	ObjectTreeController* m_object_tree_controller;
	ObjectPropertiesController* m_object_pro_controller;
	CameraController* m_camera_controller;
	//

	// primitive Actions
	QAction* m_edit_cameras_action;
	QAction* m_new_camera_action;
	QAction* m_point_light_action;
	QAction* m_area_light_action;

	// new 3D object actions
	QAction* m_new_cube_action;
	QAction* m_new_sphere_action;
	QAction* m_new_cone_action;
	QAction* m_new_cylinder_action;
	QAction* m_new_2sidecylinder_action;
	QAction* m_new_torus_action;

	// new 2D object actions
	QAction* m_new_triangle;
	QAction* m_new_rectangle;
	QAction* m_new_circle;
	QAction* m_new_disk;
	QAction* m_new_partial_disk;

	//Editing Mode Actions
	QAction* m_single_object_mode_action;
	QAction* m_object_tree_mode_action;
	QAction* m_camera_mode_action;
	QAction* m_light_mode_action;
	QAction* m_face_mode_action;
	QAction* m_point_mode_action;

	//editing type actions
	QAction* m_rotation_type_action;
	QAction* m_translation_type_action;
	QAction* m_scale_type_action;
	QAction* m_delete_type_action;
	QAction* m_duplicate_type_action;
	QAction* m_addchild_type_action;
	QAction* m_removechild_type_action;
	QAction* m_convert_mesh_action;

	// render action
	QAction* m_render_action;

	//file actions 
	QAction* m_new_scene_action;
	QAction* m_open_file_action;
	QAction* m_save_file_action;
	QAction* m_save_as_file_action;
	QAction* m_merge_file_action;
	QAction* m_import_file_action;
	QAction* m_export_file_action;
	QAction* m_exit_action;

	// face actions
	QAction* m_split_face_action;
	QAction* m_extrude_face_action;

	// camera actions
	QAction* m_move_target_action;
	QAction* m_move_camera_action;

	//toolbars 
	QToolBar* m_file_toolbar;
	QToolBar* m_mode_toolbar;
	QToolBar* m_3dobjects_toolbar;
	QToolBar* m_2dobjects_toolbar;
	QToolBar* m_primitive_toolbar;
	QToolBar* m_mesh_toolbar;
	QToolBar* m_render_toolbar;
	QToolBar* m_camera_toolbar;
	QToolBar* m_edit_toolbar;

	//toolbar actions
	QAction* m_file_toolbar_action;
	QAction* m_mode_toolbar_action;
	QAction* m_3dobjects_toolbar_action;
	QAction* m_2dobjects_toolbar_action;
	QAction* m_primitive_toolbar_action;
	QAction* m_mesh_toolbar_action;
	QAction* m_render_toolbar_action;
	QAction* m_camera_toolbar_action;
	QAction* m_edit_toolbar_action;




private slots:
	void updateWindowActions(bool);
	void changeEditingMode(bool);
	void addNewObject();
	void changeEditingType();
	void addNewItem();
	void renderScene();
	void fileActionClicked();
	void editFaceActionEntered();
	void cameraActionChanged();
	void showHideToolbars(bool);
};

#endif // SMMENUHANDLER_H
