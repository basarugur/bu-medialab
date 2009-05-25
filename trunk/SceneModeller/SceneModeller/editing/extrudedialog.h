#ifndef EXTRUDEDIALOG_H
#define EXTRUDEDIALOG_H

#include <QDialog>
#include "ui_extrudedialog.h"

#include "../core/triangle.h"

class ExtrudeDialog : public QDialog
{
	Q_OBJECT

public:
	ExtrudeDialog(QWidget *parent = 0);
	~ExtrudeDialog();

	void showDialog(Triangle* trng_);

signals:
	void sceneChanged();

private:
	Ui::ExtrudeDialogClass ui;
	Triangle* m_triangle;
	Vector3 m_init_x;
	Vector3 m_init_y;
	Vector3 m_init_z;

protected:
	void closeEvent(QCloseEvent *){ m_triangle->restoreNormalAndMidPoint(); };

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_horizontalSlider_valueChanged(int);
};

#endif // EXTRUDEDIALOG_H
