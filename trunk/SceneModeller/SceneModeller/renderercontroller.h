#ifndef RENDERERCONTROLLER_H
#define RENDERERCONTROLLER_H

#include <QDialog>
#include "ui_renderercontroller.h"

#include "core/scene.h"
#include "core/camera.h"

#include "formats/rawdevice.h"

class RendererController : public QDialog
{
	Q_OBJECT

public:
	RendererController(Scene* sc,RawDevice* rwdev_,QWidget *parent = 0);
	~RendererController();

	void showDialog(Camera*  crnt_);

private:
	Ui::RendererControllerClass ui;
	Scene* m_scene;
	Camera* m_current_camera;

	RawDevice* m_raw_device;

	void saveRawFiles();
	void saveXMLFile();

private slots:
	void on_pushButton_2_clicked();
	void on_pushButton_clicked();
};

#endif // RENDERERCONTROLLER_H
