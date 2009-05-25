#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <Qt>
#include <QObject>
#include <QDockWidget>
#include <QLineEdit>

#include "../core/camera.h"

class CameraController : public QObject
{
	Q_OBJECT
public:
	CameraController(QDockWidget* m_);
	~CameraController();

	QDockWidget* m_dock_widget;

    void ShowCamera(Camera* cmr_);

signals:
	void sceneChanged();

public slots:
	void showDockWidget(bool sh_);
	void updateCameraInfo();
	void lineEditsChanged();

private:
	QLineEdit* m_name_edit;
	QLineEdit* m_pos_edit;
	QLineEdit* m_tar_edit;
	QLineEdit* m_up_edit;

	Camera* m_current_camera;
};

#endif // SMMENUHANDLER_H
