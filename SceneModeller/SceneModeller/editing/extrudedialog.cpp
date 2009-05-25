#include "extrudedialog.h"

ExtrudeDialog::ExtrudeDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_triangle = NULL;
}

ExtrudeDialog::~ExtrudeDialog()
{

}

void ExtrudeDialog::showDialog(Triangle* trng_)
{
	m_triangle = trng_;

	m_init_x = *m_triangle->a();
	m_init_y = *m_triangle->b();
	m_init_z = *m_triangle->c();

	ui.horizontalSlider->setValue(0);

	this->exec();
}

void ExtrudeDialog::on_horizontalSlider_valueChanged(int vle_)
{
	Vector3 delta_ = 0.4*vle_*m_triangle->n();
	Vector3 newX_ = delta_+m_init_x;
	Vector3 newY_ = delta_+m_init_y;
	Vector3 newZ_ = delta_+m_init_z;

	m_triangle->a()->setX(newX_.x());
	m_triangle->a()->setY(newX_.y());
	m_triangle->a()->setZ(newX_.z());

	m_triangle->b()->setX(newY_.x());
	m_triangle->b()->setY(newY_.y());
	m_triangle->b()->setZ(newY_.z());

	m_triangle->c()->setX(newZ_.x());
	m_triangle->c()->setY(newZ_.y());
	m_triangle->c()->setZ(newZ_.z());

	emit sceneChanged();
}

void ExtrudeDialog::on_pushButton_2_clicked()
{
	this->close();
}

void ExtrudeDialog::on_pushButton_clicked()
{
	this->close();
}