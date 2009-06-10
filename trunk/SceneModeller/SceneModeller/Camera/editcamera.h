#ifndef EDITCAMERA_H
#define EDITCAMERA_H

#include <QDialog>
#include "ui_editcamera.h"

#include "../core/scene.h"

class EditCamera : public QDialog
{
	Q_OBJECT

public:
	EditCamera(Scene* sc_,QWidget *parent = 0);
	~EditCamera();


private:
	Ui::EditCameraClass ui;
	Scene* m_scene;

	int m_previous_index;

	void saveCurrentGUI();
	void updateGUI();
	void clearGUI();

protected:
	void keyPressEvent(QKeyEvent *)
	{

	};

public slots:
	void showDialog();
	void currentPositionChanged();
	void currentTargetChanged();
	void currentUpVectorChanged();
	void currentNameChanged();
private slots:
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_Close_clicked();
	void on_Add_clicked();
	void on_listWidget_currentRowChanged(int);
};

#endif // EDITCAMERA_H
