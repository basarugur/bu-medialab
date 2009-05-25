#include "camerapropertiescontroller.h"

#include <QGridLayout>

#include "../common.h"

CameraController::CameraController(QDockWidget* m_): m_dock_widget(m_)
{
	//m_dock_widget->setVisible(true);

	QGridLayout* lyt_ = static_cast<QGridLayout*>(m_->widget()->layout());

	m_name_edit = static_cast<QLineEdit*>(lyt_->itemAtPosition(0,1)->widget());
	m_pos_edit  = static_cast<QLineEdit*>(lyt_->itemAtPosition(1,1)->widget());
	m_tar_edit  = static_cast<QLineEdit*>(lyt_->itemAtPosition(2,1)->widget());
	m_up_edit   = static_cast<QLineEdit*>(lyt_->itemAtPosition(3,1)->widget());

	connect(m_name_edit,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
	connect(m_pos_edit,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
	connect(m_tar_edit,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
	connect(m_up_edit,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

	m_current_camera = NULL;
}

CameraController::~CameraController()
{

}
void CameraController::showDockWidget(bool sh_)
{
	m_dock_widget->setVisible(sh_);
}
void CameraController::ShowCamera(Camera* cmr_)
{
	m_current_camera = cmr_;
	updateCameraInfo();

}
void CameraController::updateCameraInfo()
{
	if(m_current_camera == NULL)
	{
		m_name_edit->setText("");
		m_pos_edit->setText("");
		m_tar_edit->setText("");
		m_up_edit->setText("");
	}
	else
	{
		m_name_edit->setText(QString::fromStdString(m_current_camera->getName()));
		m_pos_edit->setText(QString::number(m_current_camera->position().x(),'f',3)+" , "+
			                QString::number(m_current_camera->position().y(),'f',3)+" , "+
							QString::number(m_current_camera->position().z(),'f',3));
		m_tar_edit->setText(QString::number(m_current_camera->atPoint().x(),'f',3)+" , "+
			                QString::number(m_current_camera->atPoint().y(),'f',3)+" , "+
							QString::number(m_current_camera->atPoint().z(),'f',3));
		m_up_edit->setText(QString::number(m_current_camera->upVector().x(),'f',3)+" , "+
			                QString::number(m_current_camera->upVector().y(),'f',3)+" , "+
							QString::number(m_current_camera->upVector().z(),'f',3));
	}
}
void CameraController::lineEditsChanged()
{
	if(m_current_camera != NULL)
	{
		double x_,y_,z_;
		QStringList lst_;

		// name
		m_current_camera->setName(m_name_edit->text().toStdString());


		lst_ = m_pos_edit->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_camera->setPosition(Point3(x_,y_,z_));
		}
		lst_ = m_tar_edit->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_camera->setAtPoint(Point3(x_,y_,z_));
		}
		lst_ = m_up_edit->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_camera->setUpVector(Vector3(x_,y_,z_).normalize());
		}

		emit sceneChanged();
	}
}
