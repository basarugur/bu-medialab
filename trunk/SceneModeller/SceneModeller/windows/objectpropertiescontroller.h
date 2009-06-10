#ifndef OBJECT_PROPERTIES_H
#define OBJECT_PROPERTIES_H

#include <Qt>
#include <QObject>
#include <QDockWidget>
#include <QGridLayout>

#include "../core/scene.h"

class ObjectPropertiesController : public QObject
{
	Q_OBJECT
public:
	ObjectPropertiesController(QDockWidget* m_);
	~ObjectPropertiesController();

	QDockWidget* m_dock_widget;

	void setScene(Scene* sc_ ) { m_scene = sc_; };

	void checkScene();

	void setDockTitle(QString title_)
	{
		m_dock_widget->setWindowTitle(title_);
	}

signals:
	void sceneChanged();

private:
	void clearAll();
	void setMinimumSizes();
	void showObject();
	void showLight();
	void showCamera();

	void showVertex();
	void showTriangle();

	Triangle* m_current_face;
	Vertex* m_current_vertex;
	GfxObject* m_current_object;
	Light* m_current_light;
	Camera* m_current_camera;
	QGridLayout* m_layout;
	Scene* m_scene;

	bool m_block_signal;

	void saveGUIToObject();
	void saveGUIToLight();
	void saveGUIToCamera();

	void saveGUIToTriangle();
	void saveGUIToVertex();

public slots:
	void showDockWidget(bool sh_);
	void lineEditsChanged();
	void changeColor();
	void changeTexture();

	void cameraPosChanged();
	void cameraTargetChanged();
	void cameraUpChanged();

	void textureOnOff(bool);
    void changeTexturePlane(int);
};

#endif // SMMENUHANDLER_H
