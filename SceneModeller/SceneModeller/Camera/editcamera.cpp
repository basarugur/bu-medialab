#include "editcamera.h"

#include "../common.h"


EditCamera::EditCamera(Scene* sc_,QWidget *parent)
	: QDialog(parent),m_scene(sc_)
{
	ui.setupUi(this);

	m_previous_index = -1;

	connect(ui.lineEdit,SIGNAL(editingFinished()),this,SLOT(currentNameChanged()));
	connect(ui.lineEdit_2,SIGNAL(editingFinished()),this,SLOT(currentPositionChanged()));
	connect(ui.lineEdit_3,SIGNAL(editingFinished()),this,SLOT(currentTargetChanged()));
	connect(ui.lineEdit_4,SIGNAL(editingFinished()),this,SLOT(currentUpVectorChanged()));
}

EditCamera::~EditCamera()
{

}
void EditCamera::currentNameChanged()
{
	if(m_previous_index!=-1){
		m_scene->cameras()[m_previous_index]->setName(ui.lineEdit->text().toStdString());
		ui.listWidget->currentItem()->setText(QString::fromStdString(m_scene->cameras()[m_previous_index]->getName()));
	}
}
void EditCamera::currentPositionChanged()
{
	if(m_previous_index != -1)
	{
		QStringList lst_;
		double x_,y_,z_;
		m_scene->cameras()[m_previous_index]->setName(ui.lineEdit->text().toStdString());
		ui.listWidget->item(m_previous_index)->setText(ui.lineEdit->text());
		lst_ = ui.lineEdit_2->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();

			Camera* current_camera  = m_scene->cameras()[m_previous_index];

			if ( Point3(x_,y_,z_) != current_camera->position())
			{
				Vector3 dir1_ = (current_camera->position()-current_camera->atPoint()).normalize();

				current_camera->setPosition(Point3(x_,y_,z_));

				Vector3 dir2_ = (current_camera->position()-current_camera->atPoint()).normalize();

				if(!(dir1_ == dir2_))
				{
					double acos_ = acos(dir1_*dir2_);
					dir1_ = (dir1_^dir2_).normalize();

					Vector3 nwNorm_ = RotateVectorAroundVector(current_camera->upVector(),dir1_,acos_);
					current_camera->setUpVector(nwNorm_);

					updateGUI();
				}
			}
		}
	}
}
void EditCamera::currentTargetChanged()
{
	if(m_previous_index != -1)
	{
		QStringList lst_;
		double x_,y_,z_;
		m_scene->cameras()[m_previous_index]->setName(ui.lineEdit->text().toStdString());
		ui.listWidget->item(m_previous_index)->setText(ui.lineEdit->text());

		lst_ = ui.lineEdit_3->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();

			Camera* current_camera = m_scene->cameras()[m_previous_index];

			if ( Point3(x_,y_,z_) != current_camera->atPoint())
			{
				Vector3 dir1_ = (current_camera->atPoint()-current_camera->position()).normalize();

				current_camera->setAtPoint(Point3(x_,y_,z_));

				Vector3 dir2_ = (current_camera->atPoint()-current_camera->position()).normalize();

				if ( !(dir1_ == dir2_) )
				{
					double acos_ = acos(dir1_*dir2_);
					dir1_ = (dir1_^dir2_).normalize();

					Vector3 nwNorm_ = RotateVectorAroundVector(current_camera->upVector(),dir1_,acos_);
					current_camera->setUpVector(nwNorm_);
				}

				updateGUI();
			}
		}
	}
}
void EditCamera::currentUpVectorChanged()
{
	if(m_previous_index != -1)
	{
		QStringList lst_;
		double x_,y_,z_;
		m_scene->cameras()[m_previous_index]->setName(ui.lineEdit->text().toStdString());
		ui.listWidget->item(m_previous_index)->setText(ui.lineEdit->text());

		lst_ = ui.lineEdit_4->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();

			Camera* current_camera = m_scene->cameras()[m_previous_index];

			if (! (Vector3(x_,y_,z_) == current_camera->upVector()))
			{
				Vector3 dir1_ = current_camera->upVector();
				Vector3 dir2_ = Vector3(x_,y_,z_).normalize();
				if ( !(dir1_ == dir2_) )
				{
					current_camera->setUpVector(dir2_);

					double acos_ = acos(dir1_*dir2_);
					dir1_ = (dir1_^dir2_).normalize();

					Vector3 vct1_ = current_camera->atPoint()-current_camera->position();
					vct1_ = 	RotateVectorAroundVector(vct1_,dir1_,acos_);
					current_camera->setAtPoint(current_camera->position()+vct1_);
				}
			}
		}
	}
}
void EditCamera::clearGUI()
{
	ui.listWidget->clear();
	ui.lineEdit->setText("");
	ui.lineEdit_2->setText("");
	ui.lineEdit_3->setText("");
	ui.lineEdit_4->setText("");

	m_previous_index = -1;
}
void EditCamera::showDialog()
{
	clearGUI();
	for(int i=0 ; i<m_scene->cameras().size();i++)
	{
		ui.listWidget->addItem(QString::fromStdString(m_scene->cameras()[i]->getName()));
	}
	if(ui.listWidget->count()>0)
		ui.listWidget->setCurrentRow(0);

	this->exec();
}
void EditCamera::on_listWidget_currentRowChanged(int ind_)
{
	if(m_previous_index!=-1)
		saveCurrentGUI();
	if(ind_ != -1 && ind_ < m_scene->cameras().size())
	{
		m_previous_index = ind_;
		updateGUI();
	}
	else if(ind_ == -1) m_previous_index = -1;
}
void EditCamera::saveCurrentGUI()
{

}
void EditCamera::updateGUI()
{
	if(m_previous_index != -1)
	{
		QString txt_;
		Point3 pos_ = m_scene->cameras()[m_previous_index]->position();
		Vector3 upVec_ =  m_scene->cameras()[m_previous_index]->upVector();
		Point3 atDir_ = m_scene->cameras()[m_previous_index]->atPoint();
		ui.lineEdit->setText(QString::fromStdString(m_scene->cameras()[m_previous_index]->getName()));
		ui.lineEdit_2->setText(QString::number(pos_.x(),'f',3)+" , "+
			                QString::number(pos_.y(),'f',3)+" , "+
							QString::number(pos_.z(),'f',3));
		ui.lineEdit_4->setText(QString::number(upVec_.x(),'f',3)+" , "+
			                QString::number(upVec_.y(),'f',3)+" , "+
							QString::number(upVec_.z(),'f',3));
		ui.lineEdit_3->setText(QString::number(atDir_.x(),'f',3)+" , "+
			                QString::number(atDir_.y(),'f',3)+" , "+
							QString::number(atDir_.z(),'f',3));
	}
	else
	{
		ui.lineEdit->setText("");
		ui.lineEdit_2->setText("");
		ui.lineEdit_3->setText("");
		ui.lineEdit_4->setText("");
	}
}

void EditCamera::on_Add_clicked()
{
	Camera* nw_ = new Camera();
	m_scene->cameras().push_back(nw_);
	ui.listWidget->addItem(QString::fromStdString(nw_->getName()));
	ui.listWidget->setCurrentRow(ui.listWidget->count()-1);
}

void EditCamera::on_Close_clicked()
{
	saveCurrentGUI();
	this->close();
}

void EditCamera::on_pushButton_3_clicked()
{
	saveCurrentGUI();
	this->close();
}

void EditCamera::on_pushButton_2_clicked()
{
	if(m_previous_index != -1)
	{
		m_scene->cameras().erase(m_scene->cameras().begin()+m_previous_index);
		int tmp_ = m_previous_index ;
		m_previous_index = -1;
		ui.listWidget->takeItem(tmp_);
		if(ui.listWidget->count()>0) ui.listWidget->setCurrentRow(0);
	}
}