#include "objectpropertiescontroller.h"

#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>
#include <QGroupBox>
#include <QComboBox>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>

#include "../common.h"

#include "../core/sphere.h"
#include "../core/cube.h"
#include "../core/cone.h"
#include "../core/trianglemesh.h"
#include "../core/cylinder.h"
#include "../core/twosidedcylinder.h"
#include "../core/torus.h"

#include "../core/triangleshape.h"
#include "../core/rectangle.h"
#include "../core/circle.h"
#include "../core/disk.h"
#include "../core/partialdisk.h"

//class 
class SMPushButton : public QPushButton
{
public:
	SMPushButton(QWidget* prnt = NULL) : QPushButton(prnt) {
		//setFlat(true);
	} 
	~SMPushButton() {}

	std::string m_icon_path;
	void setIconPath(std::string str)
	{
		m_pixmap = QImage(QString::fromStdString(str));
		m_icon_path = str;
		update();
	}
    QImage m_pixmap;
protected:
	void paintEvent(QPaintEvent* )
	{
		QPainter painter(this);
		painter.drawImage(rect(),m_pixmap);
	}
};

ObjectPropertiesController::ObjectPropertiesController(QDockWidget* m_): m_dock_widget(m_)
{
	//m_dock_widget->setVisible(true);

	m_current_object = NULL;
	m_layout = new QGridLayout(m_dock_widget->widget());
	m_layout->setSpacing(2);
	m_layout->setMargin(2);

	m_current_camera = NULL;

	m_block_signal = false;
}
ObjectPropertiesController::~ObjectPropertiesController()
{

}
void ObjectPropertiesController::clearAll()
{
	int cl_ = m_layout->columnCount();
	int rw_ = m_layout->rowCount();

	for(int i=rw_-1 ; i>=0 ; i--)
		for(int j=cl_-1 ; j>=0 ; j--)
		{
			QLayoutItem* itm_ = m_layout->itemAtPosition(i,j); 
			if(itm_)
			{
				QWidget* wdg_ = itm_->widget();
				m_layout->removeWidget(wdg_);
				delete (wdg_);
			}
		}
}
void ObjectPropertiesController::setMinimumSizes()
{
		int cl_ = m_layout->columnCount();
		int rw_ = m_layout->rowCount();

		for(int i=rw_-1 ; i>=0 ; i--)
			for(int j=cl_-1 ; j>=0 ; j--)
			{
				QLayoutItem* itm_ = m_layout->itemAtPosition(i,j); 
				if(itm_)
				{
					QWidget* wdg_ = itm_->widget();
					wdg_->setMinimumSize(QSize(0,0));
				}
			}
}
void ObjectPropertiesController::showCamera()
{
	Camera* cmr_ = m_current_camera;
	if(cmr_ != NULL)
	{
		QLabel* lb_ = new QLabel(m_dock_widget);
		lb_->setText("Name");
		QLineEdit* nm_ = new QLineEdit(m_dock_widget);
		nm_->setText(QString::fromStdString(cmr_->getName()));
		m_layout->addWidget(lb_,0,0,1,1);
		m_layout->addWidget(nm_,0,1,1,1);

		QLabel* sc_ = new QLabel(m_dock_widget);
		sc_->setText("Position");
		QLineEdit* sce_ = new QLineEdit(m_dock_widget);
		sce_->setText(QString::number(cmr_->position().x(),'f',3)+" , "+
					  QString::number(cmr_->position().y(),'f',3)+" , "+
					  QString::number(cmr_->position().z(),'f',3));
		m_layout->addWidget(sc_,1,0,1,1);
		m_layout->addWidget(sce_,1,1,1,1);
		connect(sce_,SIGNAL(editingFinished()),this,SLOT(cameraPosChanged()));

		QLabel* rt_ = new QLabel(m_dock_widget);
		rt_->setText("Target");
		QLineEdit* rte_ = new QLineEdit(m_dock_widget);
		rte_->setText(QString::number(cmr_->atPoint().x(),'f',3)+" , "+
			          QString::number(cmr_->atPoint().y(),'f',3)+" , "+
					  QString::number(cmr_->atPoint().z(),'f',3));
		m_layout->addWidget(rt_,2,0,1,1);
		m_layout->addWidget(rte_,2,1,1,1);
		connect(rte_,SIGNAL(editingFinished()),this,SLOT(cameraTargetChanged()));

		QLabel* tr_ = new QLabel(m_dock_widget);
		tr_->setText("Up Vector");
		QLineEdit* tre_ = new QLineEdit(m_dock_widget);
		tre_->setText(QString::number(cmr_->upVector().x(),'f',3)+" , "+
			          QString::number(cmr_->upVector().y(),'f',3)+" , "+
					  QString::number(cmr_->upVector().z(),'f',3));
		m_layout->addWidget(tr_,3,0,1,1);
		m_layout->addWidget(tre_,3,1,1,1);
		connect(tre_,SIGNAL(editingFinished()),this,SLOT(cameraUpChanged()));
	}
}
void ObjectPropertiesController::showLight()
{
	Light* lg_ = m_current_light;
	if( lg_ != NULL)
	{
		AreaLight* arLg_ ; 
		if(lg_->type() == POINT_LIGHT)
		{
			QLabel* lb_ = new QLabel(m_dock_widget);
			lb_->setText("Type");
			QLineEdit* nm_ = new QLineEdit(m_dock_widget);
			nm_->setText("Point Light");
			nm_->setReadOnly(true);
			m_layout->addWidget(lb_,0,0,1,1);
			m_layout->addWidget(nm_,0,1,1,1);

			QLabel* sc_ = new QLabel(m_dock_widget);
			sc_->setText("Position");
			QLineEdit* sce_ = new QLineEdit(m_dock_widget);
			sce_->setText(QString::number(lg_->p().x(),'f',3)+" , "+
						  QString::number(lg_->p().y(),'f',3)+" , "+
						  QString::number(lg_->p().z(),'f',3));
			m_layout->addWidget(sc_,1,0,1,1);
			m_layout->addWidget(sce_,1,1,1,1);
			connect(sce_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* refCo_ = new QLabel(m_dock_widget);
			refCo_->setText("Coefficient ");
			QLineEdit* refCoe_ = new QLineEdit(m_dock_widget);
			refCoe_->setText(QString::number(lg_->coeff(),'f',3));
			m_layout->addWidget(refCo_,2,0,1,1);
			m_layout->addWidget(refCoe_,2,1,1,1);
			connect(refCoe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else
		{
			arLg_ = static_cast<AreaLight*>(lg_);

			QLabel* lb_ = new QLabel(m_dock_widget);
			lb_->setText("Type");
			QLineEdit* nm_ = new QLineEdit(m_dock_widget);
			nm_->setText("Area Light");
			nm_->setReadOnly(true);
			m_layout->addWidget(lb_,0,0,1,1);
			m_layout->addWidget(nm_,0,1,1,1);

			QLabel* sc_ = new QLabel(m_dock_widget);
			sc_->setText("Position");
			QLineEdit* sce_ = new QLineEdit(m_dock_widget);
			sce_->setText(QString::number(arLg_->p().x(),'f',3)+" , "+
						  QString::number(arLg_->p().y(),'f',3)+" , "+
						  QString::number(arLg_->p().z(),'f',3));
			m_layout->addWidget(sc_,1,0,1,1);
			m_layout->addWidget(sce_,1,1,1,1);
			connect(sce_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* refCo_ = new QLabel(m_dock_widget);
			refCo_->setText("Width ");
			QLineEdit* refCoe_ = new QLineEdit(m_dock_widget);
			refCoe_->setText(QString::number(arLg_->h(),'f',3));
			m_layout->addWidget(refCo_,2,0,1,1);
			m_layout->addWidget(refCoe_,2,1,1,1);
			connect(refCoe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* luCo_ = new QLabel(m_dock_widget);
			luCo_->setText("Height ");
			QLineEdit* luCoe_ = new QLineEdit(m_dock_widget);
			luCoe_->setText(QString::number(arLg_->w(),'f',3));
			m_layout->addWidget(luCo_,3,0,1,1);
			m_layout->addWidget(luCoe_,3,1,1,1);
			connect(luCoe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* ref1Co_ = new QLabel(m_dock_widget);
			ref1Co_->setText("Coefficient ");
			QLineEdit* ref1Coe_ = new QLineEdit(m_dock_widget);
			ref1Coe_->setText(QString::number(lg_->coeff(),'f',3));
			m_layout->addWidget(ref1Co_,4,0,1,1);
			m_layout->addWidget(ref1Coe_,4,1,1,1);
			connect(ref1Coe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
	}
}

void ObjectPropertiesController::showVertex()
{
	Vertex* vrt_ = m_current_vertex;
	if (vrt_ != NULL)
	{
		QLabel* sc_ = new QLabel(m_dock_widget);
		sc_->setText("Vertex ");
		QLineEdit* sce_ = new QLineEdit(m_dock_widget);
		sce_->setText(QString::number(vrt_->x(),'f',3)+" , "+
			QString::number(vrt_->y(),'f',3)+" , "+
			QString::number(vrt_->z(),'f',3));
		m_layout->addWidget(sc_,0,0,1,1);
		m_layout->addWidget(sce_,0,1,1,1);
		connect(sce_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
	}
}
void ObjectPropertiesController::showTriangle()
{
	Triangle* trng_ = m_current_face;
	if (trng_ != NULL)
	{
		QLabel* sc_ = new QLabel(m_dock_widget);
		sc_->setText("Normal : ");
		QLineEdit* sce_ = new QLineEdit(m_dock_widget);
		sce_->setText(QString::number(trng_->n().x(),'f',3)+" , "+
			QString::number(trng_->n().y(),'f',3)+" , "+
			QString::number(trng_->n().z(),'f',3));
		m_layout->addWidget(sc_,0,0,1,1);
		m_layout->addWidget(sce_,0,1,1,1);
		sce_->setReadOnly(true);

		QLabel* rt_ = new QLabel(m_dock_widget);
		rt_->setText("Vertex A ");
		QLineEdit* rte_ = new QLineEdit(m_dock_widget);
		rte_->setText(QString::number(trng_->a()->x(),'f',3)+" , "+
			QString::number(trng_->a()->y(),'f',3)+" , "+
			QString::number(trng_->a()->z(),'f',3));
		m_layout->addWidget(rt_,1,0,1,1);
		m_layout->addWidget(rte_,1,1,1,1);
		connect(rte_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* tr_ = new QLabel(m_dock_widget);
		tr_->setText("Vertex B ");
		QLineEdit* tre_ = new QLineEdit(m_dock_widget);
		tre_->setText(QString::number(trng_->b()->x(),'f',3)+" , "+
			QString::number(trng_->b()->y(),'f',3)+" , "+
			QString::number(trng_->b()->z(),'f',3));
		m_layout->addWidget(tr_,2,0,1,1);
		m_layout->addWidget(tre_,2,1,1,1);
		connect(tre_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		// tree transformmation

		QLabel* sc1_ = new QLabel(m_dock_widget);
		sc1_->setText("Vertex C ");
		QLineEdit* sce1_ = new QLineEdit(m_dock_widget);
		sce1_->setText(QString::number(trng_->c()->x(),'f',3)+" , "+
			QString::number(trng_->c()->y(),'f',3)+" , "+
			QString::number(trng_->c()->z(),'f',3));
		m_layout->addWidget(sc1_,3,0,1,1);
		m_layout->addWidget(sce1_,3,1,1,1);
		connect(sce1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
	}
}



void ObjectPropertiesController::showObject()
{
	GfxObject* obj_ = m_current_object;
	if(obj_ != NULL)
	{
		Transformation* trns_  = obj_->getIndividualTranform();
		Material* material_ = obj_->material();
		Shape* shape_  = obj_->getShape();

		QLabel* lb_ = new QLabel(m_dock_widget);
		lb_->setText("Name");
		QLineEdit* nm_ = new QLineEdit(m_dock_widget);
		nm_->setText(QString::fromStdString(obj_->getName()));
		m_layout->addWidget(lb_,0,0,1,1);
		m_layout->addWidget(nm_,0,1,1,1);
		connect(nm_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		// ind transform
		QLabel* trnsTitle_ = new QLabel(m_dock_widget);
		QFont fnt_;
		fnt_.setBold(true);
		trnsTitle_->setFont(fnt_);
		trnsTitle_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		trnsTitle_->setText("Individual Transformation");
		trnsTitle_->setFixedHeight(20);
		trnsTitle_->setStyleSheet("color : rgb(255,255,255); background-color : rgb(0,0,100)");
		m_layout->addWidget(trnsTitle_,1,0,1,2);

		QLabel* sc_ = new QLabel(m_dock_widget);
		sc_->setText("Scale");
		QLineEdit* sce_ = new QLineEdit(m_dock_widget);
		sce_->setText(QString::number(trns_->scale().x(),'f',3)+" , "+
			          QString::number(trns_->scale().y(),'f',3)+" , "+
					  QString::number(trns_->scale().z(),'f',3));
		m_layout->addWidget(sc_,2,0,1,1);
		m_layout->addWidget(sce_,2,1,1,1);
		connect(sce_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* rt_ = new QLabel(m_dock_widget);
		rt_->setText("Rotation");
		QLineEdit* rte_ = new QLineEdit(m_dock_widget);
		rte_->setText(QString::number(trns_->rotation().ax(),'f',3)+" , "+
			          QString::number(trns_->rotation().ay(),'f',3)+" , "+
					  QString::number(trns_->rotation().az(),'f',3)+" , "+
					  QString::number(trns_->rotation().theta(),'f',3));
		m_layout->addWidget(rt_,3,0,1,1);
		m_layout->addWidget(rte_,3,1,1,1);
		connect(rte_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* tr_ = new QLabel(m_dock_widget);
		tr_->setText("Translation");
		QLineEdit* tre_ = new QLineEdit(m_dock_widget);
		tre_->setText(QString::number(trns_->translation().x(),'f',3)+" , "+
			          QString::number(trns_->translation().y(),'f',3)+" , "+
					  QString::number(trns_->translation().z(),'f',3));
		m_layout->addWidget(tr_,4,0,1,1);
		m_layout->addWidget(tre_,4,1,1,1);
		connect(tre_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		// tree transformmation
		trns_  = obj_->getPublicTranform();
		QLabel* trnsTitle1_ = new QLabel(m_dock_widget);
		trnsTitle1_->setFont(fnt_);
		trnsTitle1_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		trnsTitle1_->setText("Tree Transformation");
		trnsTitle1_->setStyleSheet("color : rgb(255,255,255); background-color : rgb(0,0,100)");
		trnsTitle1_->setFixedHeight(20);
		m_layout->addWidget(trnsTitle1_,5,0,1,2);

		QLabel* sc1_ = new QLabel(m_dock_widget);
		sc1_->setText("Scale");
		QLineEdit* sce1_ = new QLineEdit(m_dock_widget);
		sce1_->setText(QString::number(trns_->scale().x(),'f',3)+" , "+
			          QString::number(trns_->scale().y(),'f',3)+" , "+
					  QString::number(trns_->scale().z(),'f',3));
		m_layout->addWidget(sc1_,6,0,1,1);
		m_layout->addWidget(sce1_,6,1,1,1);
		connect(sce1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* rt1_ = new QLabel(m_dock_widget);
		rt1_->setText("Rotation");
		QLineEdit* rte1_ = new QLineEdit(m_dock_widget);
		rte1_->setText(QString::number(trns_->rotation().ax(),'f',3)+" , "+
			          QString::number(trns_->rotation().ay(),'f',3)+" , "+
					  QString::number(trns_->rotation().az(),'f',3)+" , "+
					  QString::number(trns_->rotation().theta(),'f',3));
		m_layout->addWidget(rt1_,7,0,1,1);
		m_layout->addWidget(rte1_,7,1,1,1);
		connect(rte1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* tr1_ = new QLabel(m_dock_widget);
		tr1_->setText("Translation");
		QLineEdit* tre1_ = new QLineEdit(m_dock_widget);
		tre1_->setText(QString::number(trns_->translation().x(),'f',3)+" , "+
			          QString::number(trns_->translation().y(),'f',3)+" , "+
					  QString::number(trns_->translation().z(),'f',3));
		m_layout->addWidget(tr1_,8,0,1,1);
		m_layout->addWidget(tre1_,8,1,1,1);
		connect(tre1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		// material 
		QLabel* mat_ = new QLabel(m_dock_widget);
		mat_->setFont(fnt_);
		mat_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		mat_->setText("Material");
		mat_->setStyleSheet("color : rgb(255,255,255); background-color : rgb(0,0,100)");
		mat_->setFixedHeight(20);
		m_layout->addWidget(mat_,9,0,1,2);

		QLabel* dfcl_ = new QLabel(m_dock_widget);
		dfcl_->setText("Diffuse Color");
		QPushButton* dfclp_ = new QPushButton(m_dock_widget);
		dfclp_->setStyleSheet("background-color : rgb("+
			          QString::number(material_->diffcolor().r*255)+","+
			          QString::number(material_->diffcolor().g*255)+","+
					  QString::number(material_->diffcolor().b*255)+");");
		m_layout->addWidget(dfcl_,10,0,1,1);
		m_layout->addWidget(dfclp_,10,1,1,1);
		dfclp_->setWhatsThis("diff"); // diffuse color
		connect(dfclp_,SIGNAL(clicked()),this,SLOT(changeColor()));

		QLabel* spc_ = new QLabel(m_dock_widget);
		spc_->setText("Specular Color");
		QPushButton* spcp_ = new QPushButton(m_dock_widget);
		spcp_->setStyleSheet("background-color : rgb("+
			          QString::number(material_->speccolor().r*255)+","+
			          QString::number(material_->speccolor().g*255)+","+
					  QString::number(material_->speccolor().b*255)+");");
		m_layout->addWidget(spc_,11,0,1,1);
		m_layout->addWidget(spcp_,11,1,1,1);
		spcp_->setWhatsThis("spec"); // specular color
		connect(spcp_,SIGNAL(clicked()),this,SLOT(changeColor()));

		QLabel* amb_ = new QLabel(m_dock_widget);
		amb_->setText("Ambient Color");
		QPushButton* ambp_ = new QPushButton(m_dock_widget);
		ambp_->setStyleSheet("background-color : rgb("+
			          QString::number(material_->ambientcolor().r*255)+","+
			          QString::number(material_->ambientcolor().g*255)+","+
					  QString::number(material_->ambientcolor().b*255)+");");
		m_layout->addWidget(amb_,12,0,1,1);
		m_layout->addWidget(ambp_,12,1,1,1);
		ambp_->setWhatsThis("amb"); // ambient color
		connect(ambp_,SIGNAL(clicked()),this,SLOT(changeColor()));

		// put texture here
		QGroupBox* bx_ = new QGroupBox(m_dock_widget);
		bx_->setTitle("Texture");
		bx_->setCheckable(true);
		m_layout->addWidget(bx_,13,0,1,2);
		bx_->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
		connect(bx_,SIGNAL(toggled(bool)),this,SLOT(textureOnOff(bool)));

		QGridLayout* lyt_ = new QGridLayout(bx_);
		lyt_->setSpacing(2);
		lyt_->setMargin(2);

		QLabel* lbl1_ = new QLabel(bx_);
		lbl1_->setText("Plane ");
		lyt_->addWidget(lbl1_,0,0,1,1);
		QLabel* lbl2_ = new QLabel(bx_);
		lbl2_->setText("Scale X ");
		lyt_->addWidget(lbl2_,1,0,1,1);
		QLabel* lbl3_ = new QLabel(bx_);
		lbl3_->setText("Scale Y ");
		lyt_->addWidget(lbl3_,2,0,1,1);

		QComboBox* cmb_ = new QComboBox(bx_);
		cmb_->addItem("XY");cmb_->addItem("YZ");cmb_->addItem("XZ");
		lyt_->addWidget(cmb_,0,1,1,1);
		cmb_->setMaximumWidth(40);
		if(material_->getTexture().m_n == Vector3(0,0,1))
			cmb_->setCurrentIndex(0);
		else if(material_->getTexture().m_n == Vector3(1,0,0))
			cmb_->setCurrentIndex(1);
		else if(material_->getTexture().m_n == Vector3(0,1,0))
			cmb_->setCurrentIndex(2);
		connect(cmb_,SIGNAL(currentIndexChanged(int)),this,SLOT(changeTexturePlane(int)));
		QLineEdit* lned1_ = new QLineEdit(bx_);
		lned1_->setMaximumWidth(40);
		lned1_->setText(QString::number(material_->getTexture().m_scale_x,'f',3));
		connect(lned1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		lyt_->addWidget(lned1_,1,1,1,1);		
		QLineEdit* lned2_ = new QLineEdit(bx_);
		lned2_->setMaximumWidth(40);
		lned2_->setText(QString::number(material_->getTexture().m_scale_y,'f',3));
		connect(lned2_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		lyt_->addWidget(lned2_,2,1,1,1);
		SMPushButton* txtBtn_ = new SMPushButton(bx_);
		txtBtn_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		txtBtn_->setCursor(Qt::PointingHandCursor);
		lyt_->addWidget(txtBtn_,0,2,3,3);
		txtBtn_->setIconPath(material_->getTexture().m_path);
		connect(txtBtn_,SIGNAL(clicked()),this,SLOT(changeTexture()));

		bx_->setChecked(material_->isTextureEnabled());

		// texture finished here

		QLabel* refCo_ = new QLabel(m_dock_widget);
		refCo_->setText("Reflection Coeff");
		QLineEdit* refCoe_ = new QLineEdit(m_dock_widget);
		refCoe_->setText(QString::number(material_->reflection(),'f',3));
		m_layout->addWidget(refCo_,14,0,1,1);
		m_layout->addWidget(refCoe_,14,1,1,1);
		connect(refCoe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* luCo_ = new QLabel(m_dock_widget);
		luCo_->setText("Luculent Coeff");
		QLineEdit* luCoe_ = new QLineEdit(m_dock_widget);
		luCoe_->setText(QString::number(material_->luculent(),'f',3));
		m_layout->addWidget(luCo_,15,0,1,1);
		m_layout->addWidget(luCoe_,15,1,1,1);
		connect(luCoe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* soCo_ = new QLabel(m_dock_widget);
		soCo_->setText("Solid Coeff");
		QLineEdit* soCoe_ = new QLineEdit(m_dock_widget);
		soCoe_->setText(QString::number(material_->solid(),'f',3));
		m_layout->addWidget(soCo_,16,0,1,1);
		m_layout->addWidget(soCoe_,16,1,1,1);
		connect(soCoe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

		QLabel* refInd_ = new QLabel(m_dock_widget);
		refInd_->setText("Refraction Index");
		QLineEdit* refInde_ = new QLineEdit(m_dock_widget);
		refInde_->setText(QString::number(material_->refraction_index(),'f',3));
		m_layout->addWidget(refInd_,17,0,1,1);
		m_layout->addWidget(refInde_,17,1,1,1);
		connect(refInde_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		//end of material

		//shape
		QLabel* shp_ = new QLabel(m_dock_widget);
		shp_->setFont(fnt_);
		shp_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		shp_->setText("Shape");
		shp_->setFixedHeight(20);
		shp_->setStyleSheet("color : rgb(255,255,255); background-color : rgb(0,0,100)");
		m_layout->addWidget(shp_,18,0,1,2);

		QLabel* typ_ = new QLabel(m_dock_widget);
		typ_->setText("Type");
		QLineEdit* type_ = new QLineEdit(m_dock_widget);
		type_->setReadOnly(true);
		m_layout->addWidget(typ_,19,0,1,1);
		m_layout->addWidget(type_,19,1,1,1);

		if(shape_->type()==CUBE)
		{
			type_->setText("Cube");
			Cube* cube_ = static_cast<Cube*>(shape_);

			QLabel* dim_ = new QLabel(m_dock_widget);
			dim_->setText("Dimension");
			QLineEdit* dime_ = new QLineEdit(m_dock_widget);
			dime_->setText(QString::number(cube_->Dim(),'f',3));
			m_layout->addWidget(dim_,20,0,1,1);
			m_layout->addWidget(dime_,20,1,1,1);
			connect(dime_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type()==SPHERE)
		{
			type_->setText("Sphere");
			Sphere* sphere_ = static_cast<Sphere*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(sphere_->m_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(sphere_->m_slices));
			m_layout->addWidget(slcs_,21,0,1,1);
			m_layout->addWidget(slcse_,21,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Stacks");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(sphere_->m_stacks));
			m_layout->addWidget(stck_,22,0,1,1);
			m_layout->addWidget(stcke_,22,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type()==CONE)
		{
			type_->setText("Cone");
			Cone* cone_ = static_cast<Cone*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(cone_->m_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* hght_ = new QLabel(m_dock_widget);
			hght_->setText("Height");
			QLineEdit* hghte_ = new QLineEdit(m_dock_widget);
			hghte_->setText(QString::number(cone_->m_h,'f',3));
			m_layout->addWidget(hght_,21,0,1,1);
			m_layout->addWidget(hghte_,21,1,1,1);
			connect(hghte_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(cone_->m_slices));
			m_layout->addWidget(slcs_,22,0,1,1);
			m_layout->addWidget(slcse_,22,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Stacks");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(cone_->m_stacks));
			m_layout->addWidget(stck_,23,0,1,1);
			m_layout->addWidget(stcke_,23,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type()==CYLINDER)
		{
			type_->setText("Clinder");
			Cylinder* cylinder_ = static_cast<Cylinder*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(cylinder_->m_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* hght_ = new QLabel(m_dock_widget);
			hght_->setText("Height");
			QLineEdit* hghte_ = new QLineEdit(m_dock_widget);
			hghte_->setText(QString::number(cylinder_->m_h,'f',3));
			m_layout->addWidget(hght_,21,0,1,1);
			m_layout->addWidget(hghte_,21,1,1,1);
			connect(hghte_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(cylinder_->m_slices));
			m_layout->addWidget(slcs_,22,0,1,1);
			m_layout->addWidget(slcse_,22,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Stacks");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(cylinder_->m_stacks));
			m_layout->addWidget(stck_,23,0,1,1);
			m_layout->addWidget(stcke_,23,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type()==TWO_SIDED_CYLINDER)
		{
			type_->setText("Two Sided Cylinder");
			TwoSidedCylinder* two_sided_cylinder_ = static_cast<TwoSidedCylinder*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Base Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(two_sided_cylinder_->m_base_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* rad1_ = new QLabel(m_dock_widget);
			rad1_->setText("Top Radius");
			QLineEdit* rade1_ = new QLineEdit(m_dock_widget);
			rade1_->setText(QString::number(two_sided_cylinder_->m_top_r,'f',3));
			m_layout->addWidget(rad1_,21,0,1,1);
			m_layout->addWidget(rade1_,21,1,1,1);
			connect(rade1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* hght_ = new QLabel(m_dock_widget);
			hght_->setText("Height");
			QLineEdit* hghte_ = new QLineEdit(m_dock_widget);
			hghte_->setText(QString::number(two_sided_cylinder_->m_h,'f',3));
			m_layout->addWidget(hght_,22,0,1,1);
			m_layout->addWidget(hghte_,22,1,1,1);
			connect(hghte_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(two_sided_cylinder_->m_slices));
			m_layout->addWidget(slcs_,23,0,1,1);
			m_layout->addWidget(slcse_,23,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Stacks");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(two_sided_cylinder_->m_stacks));
			m_layout->addWidget(stck_,24,0,1,1);
			m_layout->addWidget(stcke_,24,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type()==TORUS)
		{
			type_->setText("Torus");
			Torus* torus_ = static_cast<Torus*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Inner Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(torus_->m_in_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* rad1_ = new QLabel(m_dock_widget);
			rad1_->setText("Outer Radius");
			QLineEdit* rade1_ = new QLineEdit(m_dock_widget);
			rade1_->setText(QString::number(torus_->m_out_r,'f',3));
			m_layout->addWidget(rad1_,21,0,1,1);
			m_layout->addWidget(rade1_,21,1,1,1);
			connect(rade1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Sides");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(torus_->m_sides));
			m_layout->addWidget(slcs_,22,0,1,1);
			m_layout->addWidget(slcse_,22,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Rings");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(torus_->m_rings));
			m_layout->addWidget(stck_,23,0,1,1);
			m_layout->addWidget(stcke_,23,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type()==TRIANGLE_MESH)
		{
			type_->setText("Triangle Mesh");
			TriangleMesh* triangle_mesh_ = static_cast<TriangleMesh*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Triange Count");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(triangle_mesh_->faceList().size()));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			rade_->setReadOnly(true);
		}
		else if(shape_->type() == TRIANGLE_SHAPE)
		{
			type_->setText("Triangle");
			TriangleShape* triangle_shape_ = static_cast<TriangleShape*>(shape_);

			QLabel* p1_ = new QLabel(m_dock_widget);
			p1_->setText("Vertex 1");
			QLineEdit* p1e_ = new QLineEdit(m_dock_widget);
			p1e_->setText(QString::number(triangle_shape_->m_p1.x(),'f',3)+" , "+
			          QString::number(triangle_shape_->m_p1.y(),'f',3)+" , "+
					  QString::number(triangle_shape_->m_p1.z(),'f',3));
			m_layout->addWidget(p1_,20,0,1,1);
			m_layout->addWidget(p1e_,20,1,1,1);
			connect(p1e_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* p2_ = new QLabel(m_dock_widget);
			p2_->setText("Vertex 2");
			QLineEdit* p2e_ = new QLineEdit(m_dock_widget);
			p2e_->setText(QString::number(triangle_shape_->m_p2.x(),'f',3)+" , "+
			          QString::number(triangle_shape_->m_p2.y(),'f',3)+" , "+
					  QString::number(triangle_shape_->m_p2.z(),'f',3));
			m_layout->addWidget(p2_,21,0,1,1);
			m_layout->addWidget(p2e_,21,1,1,1);
			connect(p2e_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* p3_ = new QLabel(m_dock_widget);
			p3_->setText("Vertex 3");
			QLineEdit* p3e_ = new QLineEdit(m_dock_widget);
			p3e_->setText(QString::number(triangle_shape_->m_p3.x(),'f',3)+" , "+
			          QString::number(triangle_shape_->m_p3.y(),'f',3)+" , "+
					  QString::number(triangle_shape_->m_p3.z(),'f',3));
			m_layout->addWidget(p3_,22,0,1,1);
			m_layout->addWidget(p3e_,22,1,1,1);
			connect(p3e_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type() == RECTANGLE)
		{
			type_->setText("Rectangle");
			RectangleShape*  rectangle_= static_cast<RectangleShape*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Size x ");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(rectangle_->m_x,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* rad1_ = new QLabel(m_dock_widget);
			rad1_->setText("Size y ");
			QLineEdit* rade1_ = new QLineEdit(m_dock_widget);
			rade1_->setText(QString::number(rectangle_->m_y,'f',3));
			m_layout->addWidget(rad1_,21,0,1,1);
			m_layout->addWidget(rade1_,21,1,1,1);
			connect(rade1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type() == CIRCLE)
		{
			type_->setText("Circle");
			Circle* circle_ = static_cast<Circle*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(circle_->m_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(circle_->m_slices));
			m_layout->addWidget(slcs_,21,0,1,1);
			m_layout->addWidget(slcse_,21,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Loops");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(circle_->m_loops));
			m_layout->addWidget(stck_,22,0,1,1);
			m_layout->addWidget(stcke_,22,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type() == DISK)
		{
			type_->setText("Disk");
			Disk* disk_ = static_cast<Disk*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Inner Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(disk_->m_in_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* rad1_ = new QLabel(m_dock_widget);
			rad1_->setText("Outer Radius");
			QLineEdit* rade1_ = new QLineEdit(m_dock_widget);
			rade1_->setText(QString::number(disk_->m_out_r,'f',3));
			m_layout->addWidget(rad1_,21,0,1,1);
			m_layout->addWidget(rade1_,21,1,1,1);
			connect(rade1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(disk_->m_slices));
			m_layout->addWidget(slcs_,22,0,1,1);
			m_layout->addWidget(slcse_,22,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Loops");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(disk_->m_loops));
			m_layout->addWidget(stck_,23,0,1,1);
			m_layout->addWidget(stcke_,23,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}
		else if(shape_->type() == PARTIAL_DISK)
		{
			type_->setText("Partial Disk");
			PartialDisk* partial_disk_ = static_cast<PartialDisk*>(shape_);

			QLabel* rad_ = new QLabel(m_dock_widget);
			rad_->setText("Inner Radius");
			QLineEdit* rade_ = new QLineEdit(m_dock_widget);
			rade_->setText(QString::number(partial_disk_->m_in_r,'f',3));
			m_layout->addWidget(rad_,20,0,1,1);
			m_layout->addWidget(rade_,20,1,1,1);
			connect(rade_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* rad1_ = new QLabel(m_dock_widget);
			rad1_->setText("Outer Radius");
			QLineEdit* rade1_ = new QLineEdit(m_dock_widget);
			rade1_->setText(QString::number(partial_disk_->m_out_r,'f',3));
			m_layout->addWidget(rad1_,21,0,1,1);
			m_layout->addWidget(rade1_,21,1,1,1);
			connect(rade1_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* strt_ = new QLabel(m_dock_widget);
			strt_->setText("Start Angle");
			QLineEdit* strte_ = new QLineEdit(m_dock_widget);
			strte_->setText(QString::number(partial_disk_->start_ang,'f',3));
			m_layout->addWidget(strt_,22,0,1,1);
			m_layout->addWidget(strte_,22,1,1,1);
			connect(strte_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* swp_ = new QLabel(m_dock_widget);
			swp_->setText("Sweep Angle");
			QLineEdit* swpe_ = new QLineEdit(m_dock_widget);
			swpe_->setText(QString::number(partial_disk_->sweep_ang,'f',3));
			m_layout->addWidget(swp_,23,0,1,1);
			m_layout->addWidget(swpe_,23,1,1,1);
			connect(swpe_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* slcs_ = new QLabel(m_dock_widget);
			slcs_->setText("Slices");
			QLineEdit* slcse_ = new QLineEdit(m_dock_widget);
			slcse_->setText(QString::number(partial_disk_->m_slices));
			m_layout->addWidget(slcs_,24,0,1,1);
			m_layout->addWidget(slcse_,24,1,1,1);
			connect(slcse_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));

			QLabel* stck_ = new QLabel(m_dock_widget);
			stck_->setText("Loops");
			QLineEdit* stcke_ = new QLineEdit(m_dock_widget);
			stcke_->setText(QString::number(partial_disk_->m_loops));
			m_layout->addWidget(stck_,25,0,1,1);
			m_layout->addWidget(stcke_,25,1,1,1);
			connect(stcke_,SIGNAL(editingFinished()),this,SLOT(lineEditsChanged()));
		}


		// en of shape

		setMinimumSizes();
	}
}
void ObjectPropertiesController::showDockWidget(bool sh_)
{
	m_dock_widget->setVisible(sh_);
}
void ObjectPropertiesController::checkScene()
{
	if(!m_block_signal)
	{
		clearAll();
		
		switch(SMGlobalSettings::getEditingMode())
		{
		case OBJECT_TREE_MODE:
			m_current_object = m_scene->getSelectedTreeRoot();
			showObject();
			break;
		case SINGLE_OBJECT_MODE:
			m_current_object = m_scene->getSelectedObject();
			showObject();
			break;
		case LIGHT_EDITING_MODE:
			m_current_light = m_scene->getSelectedLight();
			showLight();
			break;
		case CAMERA_EDITING_MODE:
			m_current_camera = m_scene->getSelectedCamera();
			showCamera();
			break;
		case FACE_EDITING_MODE:
			m_current_face = m_scene->getSelectedFace();
			showTriangle();
			break;
		case VERTEX_EDITING_MODE:
			m_current_vertex = m_scene->getSelectedVertex();
			showVertex();
			break;
		default:
			break;
		}		
	}
}
void ObjectPropertiesController::changeColor()
{
	QPushButton *pshBtn = qobject_cast<QPushButton *>(sender());
	if(pshBtn)
	{
		QString def_ = pshBtn->whatsThis();
		if(def_ == "diff")
		{
			//QColor clr_ = QColorDialog::getColor(QColor(m_current_object->material()->diffcolor().r*255,
			//	                                        m_current_object->material()->diffcolor().g*255,
			//											m_current_object->material()->diffcolor().b*255)
			//											,m_dock_widget,"Change Diffuse Color");

			QColor clr_ = QColorDialog::getColor(QColor(m_current_object->material()->diffcolor().r*255,
					                                        m_current_object->material()->diffcolor().g*255,
															m_current_object->material()->diffcolor().b*255)
															,m_dock_widget);


			if(clr_.isValid())
			{
				m_current_object->material()->setDiffColor(TRadiance(clr_.redF(),
					                                                  clr_.greenF(),
																	  clr_.blueF()));

				pshBtn->setStyleSheet("background-color : rgb("+
			          QString::number(clr_.red())+","+
			          QString::number(clr_.green())+","+
					  QString::number(clr_.blue())+");");
				m_block_signal = true;
				emit sceneChanged();
				m_block_signal = false;
			}
		}
		else if(def_ == "spec")
		{
			//QColor clr_ = QColorDialog::getColor(QColor(m_current_object->material()->speccolor().r*255,
			//	                                        m_current_object->material()->speccolor().g*255,
			//											m_current_object->material()->speccolor().b*255)
			//											,m_dock_widget,"Change Specular Color");
			QColor clr_ = QColorDialog::getColor(QColor(m_current_object->material()->diffcolor().r*255,
				m_current_object->material()->diffcolor().g*255,
				m_current_object->material()->diffcolor().b*255)
				,m_dock_widget);
			if(clr_.isValid())
			{
				m_current_object->material()->setSpecColor(TRadiance(clr_.redF(),
					                                                  clr_.greenF(),
																	  clr_.blueF()));
				pshBtn->setStyleSheet("background-color : rgb("+
			          QString::number(clr_.red())+","+
			          QString::number(clr_.green())+","+
					  QString::number(clr_.blue())+");");
				m_block_signal = true;
				emit sceneChanged();
				m_block_signal = false;
			}
		}
		else if(def_ == "amb")
		{
			//QColor clr_ = QColorDialog::getColor(QColor(m_current_object->material()->ambientcolor().r*255,
			//	                                        m_current_object->material()->ambientcolor().g*255,
			//											m_current_object->material()->ambientcolor().b*255)
			//											,m_dock_widget,"Ambient Diffuse Color");

			QColor clr_ = QColorDialog::getColor(QColor(m_current_object->material()->diffcolor().r*255,
				m_current_object->material()->diffcolor().g*255,
				m_current_object->material()->diffcolor().b*255)
				,m_dock_widget);
			if(clr_.isValid())
			{
				m_current_object->material()->setAmbienColor(TRadiance(clr_.redF(),
					                                                  clr_.greenF(),
																	  clr_.blueF()));
				pshBtn->setStyleSheet("background-color : rgb("+
			          QString::number(clr_.red())+","+
			          QString::number(clr_.green())+","+
					  QString::number(clr_.blue())+");");
				m_block_signal = true;
				emit sceneChanged();
				m_block_signal = false;
			}
		}
	}
}
void ObjectPropertiesController::lineEditsChanged()
{

	switch(SMGlobalSettings::getEditingMode())
	{
	case SINGLE_OBJECT_MODE:
	case OBJECT_TREE_MODE:
		saveGUIToObject();
		break;
	case LIGHT_EDITING_MODE:
		saveGUIToLight();
		break;
	//case CAMERA_EDITING_MODE:
	//	saveGUIToCamera();
	//	break;
	case FACE_EDITING_MODE:
		saveGUIToTriangle();
		break;
	case VERTEX_EDITING_MODE:
		saveGUIToVertex();
		break;
	}

	m_block_signal = true;
	emit sceneChanged();
	m_block_signal = false;
}

void ObjectPropertiesController::saveGUIToTriangle()
{
	double x_,y_,z_;
	QStringList lst_;
	QLineEdit* tmp_ ;

	// pos 
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(1,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_face->a()->setX(x_);
			m_current_face->a()->setY(y_);
			m_current_face->a()->setZ(z_);
		}
	}
	// target 
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(2,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_face->b()->setX(x_);
			m_current_face->b()->setY(y_);
			m_current_face->b()->setZ(z_);
		}
	}
	// up vector
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(3,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_face->c()->setX(x_);
			m_current_face->c()->setY(y_);
			m_current_face->c()->setZ(z_);
		}
	}

	m_current_face->restoreNormalAndMidPoint();
}
void ObjectPropertiesController::saveGUIToVertex()
{
	double x_,y_,z_;
	QStringList lst_;
	QLineEdit* tmp_ ;

	// pos 
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(0,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_vertex->setX(x_);
			m_current_vertex->setY(y_);
			m_current_vertex->setZ(z_);
		}
	}
}

void ObjectPropertiesController::cameraPosChanged()
{
	double x_,y_,z_;
	QStringList lst_;
	QLineEdit* tmp_  = qobject_cast<QLineEdit*>(sender());

	// pos 
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(1,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			if ( Point3(x_,y_,z_) != m_current_camera->position())
			{
				Vector3 dir1_ = (m_current_camera->position()-m_current_camera->atPoint()).normalize();

				m_current_camera->setPosition(Point3(x_,y_,z_));

				Vector3 dir2_ = (m_current_camera->position()-m_current_camera->atPoint()).normalize();

				if(!(dir1_ == dir2_))
				{
					double acos_ = acos(dir1_*dir2_);
					dir1_ = (dir1_^dir2_).normalize();

					Vector3 nwNorm_ = RotateVectorAroundVector(m_current_camera->upVector(),dir1_,acos_);
					m_current_camera->setUpVector(nwNorm_);
				}
			}
		}
	}

	m_block_signal = true;
	emit sceneChanged();
	m_block_signal = false;
}
void ObjectPropertiesController::cameraTargetChanged()
{
	double x_,y_,z_;
	QStringList lst_;
	QLineEdit* tmp_  = qobject_cast<QLineEdit*>(sender());

	lst_ = tmp_->text().split(",");
	if(lst_.size()>2)
	{
		x_ = lst_[0].toDouble();
		y_ = lst_[1].toDouble();
		z_ = lst_[2].toDouble();
		if ( Point3(x_,y_,z_) != m_current_camera->atPoint())
		{
			Vector3 dir1_ = (m_current_camera->atPoint()-m_current_camera->position()).normalize();

			m_current_camera->setAtPoint(Point3(x_,y_,z_));

			Vector3 dir2_ = (m_current_camera->atPoint()-m_current_camera->position()).normalize();

			if ( !(dir1_ == dir2_) )
			{
				double acos_ = acos(dir1_*dir2_);
				dir1_ = (dir1_^dir2_).normalize();

				Vector3 nwNorm_ = RotateVectorAroundVector(m_current_camera->upVector(),dir1_,acos_);
				m_current_camera->setUpVector(nwNorm_);
			}
		}
	}
	m_block_signal = true;
	emit sceneChanged();
	m_block_signal = false;
}
void ObjectPropertiesController::cameraUpChanged()
{
	double x_,y_,z_;
	QStringList lst_;
	QLineEdit* tmp_  = qobject_cast<QLineEdit*>(sender());

	// up vector
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			if (! (Vector3(x_,y_,z_) == m_current_camera->upVector()))
			{
				Vector3 dir1_ = m_current_camera->upVector();
				Vector3 dir2_ = Vector3(x_,y_,z_).normalize();
				if ( !(dir1_ == dir2_) )
				{
					m_current_camera->setUpVector(dir2_);

					double acos_ = acos(dir1_*dir2_);
					dir1_ = (dir1_^dir2_).normalize();

					Vector3 vct1_ = m_current_camera->atPoint()-m_current_camera->position();
					vct1_ = 	RotateVectorAroundVector(vct1_,dir1_,acos_);
					m_current_camera->setAtPoint(m_current_camera->position()+vct1_);
				}
			}
		}
	}
	m_block_signal = true;
	emit sceneChanged();
	m_block_signal = false;
}
void ObjectPropertiesController::saveGUIToLight()
{
	double x_,y_,z_,ang_;
	QStringList lst_;
	QLineEdit* tmp_ ;

	// pos scale
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(1,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_light->setPos(Point3(x_,y_,z_));
		}
	}

	if (m_current_light->type() == POINT_LIGHT)
	{
		// pos scale
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(2,1)->widget());
		if(tmp_)
		{
			m_current_light->set_coeff(tmp_->text().toDouble());
		}
	}
	else if(m_current_light->type() == AREA_LIGHT)
	{
		AreaLight* areLig_ = static_cast<AreaLight*>(m_current_light);

		// pos scale
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(2,1)->widget());
		if(tmp_)
		{
			areLig_->setW(tmp_->text().toDouble());
		}

		// pos scale
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(3,1)->widget());
		if(tmp_)
		{
			areLig_->setH(tmp_->text().toDouble());
		}

		// pos scale
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(4,1)->widget());
		if(tmp_)
		{
			areLig_->set_coeff(tmp_->text().toDouble());
		}
	}

}
void ObjectPropertiesController::saveGUIToObject()
{
		double x_,y_,z_,ang_;
	QStringList lst_;
	QLineEdit* tmp_ ;

	// name
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(0,1)->widget());
	if(tmp_)
	{
		m_current_object->setName(tmp_->text().toStdString());
	}

	// ind scale
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(2,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_object->getIndividualTranform()->scale(x_,y_,z_);
		}
	}
	// ind rot
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(3,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>3)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			ang_ = lst_[3].toDouble();
			m_current_object->getIndividualTranform()->rotate(x_,y_,z_,ang_);
		}
	}
	// ind trans
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(4,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_object->getIndividualTranform()->translate(x_,y_,z_);
		}
	}

	// tree scale
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(6,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_object->getPublicTranform()->scale(x_,y_,z_);
		}
	}
	// tree rot
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(7,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>3)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			ang_ = lst_[3].toDouble();
			m_current_object->getPublicTranform()->rotate(x_,y_,z_,ang_);
		}
	}
	// tree trans
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(8,1)->widget());
	if(tmp_)
	{
		lst_ = tmp_->text().split(",");
		if(lst_.size()>2)
		{
			x_ = lst_[0].toDouble();
			y_ = lst_[1].toDouble();
			z_ = lst_[2].toDouble();
			m_current_object->getPublicTranform()->translate(x_,y_,z_);
		}
	}

	// texture parameters
	QGroupBox* bx_ = static_cast<QGroupBox*>(m_layout->itemAtPosition(13,0)->widget());
	QGridLayout* lyt_ = static_cast<QGridLayout*>(bx_->layout());
	tmp_ = static_cast<QLineEdit*>(lyt_->itemAtPosition(1,1)->widget());
	if(tmp_)
	{
		m_current_object->getMaterial()->getTexture().m_scale_x = tmp_->text().toDouble();
	}
	tmp_ = static_cast<QLineEdit*>(lyt_->itemAtPosition(2,1)->widget());
	if(tmp_)
	{
		m_current_object->getMaterial()->getTexture().m_scale_y = tmp_->text().toDouble();
	}

	//rec coeff
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(14,1)->widget());
	if(tmp_)
	{
		m_current_object->getMaterial()->set_reflective(tmp_->text().toDouble());
	}

	//laculent coeff
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(15,1)->widget());
	if(tmp_)
	{
		m_current_object->getMaterial()->set_luculent(tmp_->text().toDouble());
	}

	//solid coeff
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(16,1)->widget());
	if(tmp_)
	{
		m_current_object->getMaterial()->set_solid(tmp_->text().toDouble());
	}

	//refraction index
	tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(17,1)->widget());
	if(tmp_)
	{
		m_current_object->getMaterial()->set_refraction_index(tmp_->text().toDouble());
	}

	Cube* cp_;
	Sphere* sph_;
	Cone* cne_;
	Cylinder* cyld_;
	TwoSidedCylinder* twcyl_;
	Torus* trs_ ; 
	TriangleShape* trngshp_;
	RectangleShape* rect_;
	Circle* circle_;
	Disk* disk_;
	PartialDisk* pdisk_;	
	switch(m_current_object->getShape()->type())
	{
	case CUBE:
		cp_ = static_cast<Cube*>(m_current_object->getShape());
		//cube dim
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			cp_->m_d = tmp_->text().toDouble();
		}
		break;
	case SPHERE:
		sph_ = static_cast<Sphere*>(m_current_object->getShape());
		//shape r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			sph_->m_r = tmp_->text().toDouble();
		}
		//shape slices
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			sph_->m_slices = tmp_->text().toInt();
		}
		//shape stacks
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			sph_->m_stacks = tmp_->text().toInt();
		}
		break;
	case CONE:
		cne_ = static_cast<Cone*>(m_current_object->getShape());
		//cone r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			cne_->m_r = tmp_->text().toDouble();
		}
		//cone h
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			cne_->m_h = tmp_->text().toDouble();
		}
		//cone slices
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			cne_->m_slices = tmp_->text().toInt();
		}
		//cone stacks
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(23,1)->widget());
		if(tmp_)
		{
			cne_->m_stacks = tmp_->text().toInt();
		}
		break;
	case CYLINDER:
		cyld_ = static_cast<Cylinder*>(m_current_object->getShape());

		cne_ = static_cast<Cone*>(m_current_object->getShape());
		//cylinder r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			cyld_->m_r = tmp_->text().toDouble();
		}
		//cylinder h
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			cyld_->m_h = tmp_->text().toDouble();
		}
		//cylinder slices
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			cyld_->m_slices = tmp_->text().toInt();
		}
		//cylinder stacks
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(23,1)->widget());
		if(tmp_)
		{
			cyld_->m_stacks = tmp_->text().toInt();
		}

		break;
	case TWO_SIDED_CYLINDER:
		twcyl_ = static_cast<TwoSidedCylinder*>(m_current_object->getShape());

		//two sided cylinder base r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			twcyl_->m_base_r = tmp_->text().toDouble();
		}
		//two sided cylinder top r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			twcyl_->m_top_r = tmp_->text().toDouble();
		}
		//two sided cylinder h
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			twcyl_->m_h = tmp_->text().toDouble();
		}
		//two sided cylinder slices
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(23,1)->widget());
		if(tmp_)
		{
			twcyl_->m_slices = tmp_->text().toInt();
		}
		//two sided cylinder stacks
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(24,1)->widget());
		if(tmp_)
		{
			twcyl_->m_stacks = tmp_->text().toInt();
		}

		break;
	case TORUS:
		trs_ = static_cast<Torus*>(m_current_object->getShape());

		//torus  inner r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			trs_->m_in_r = tmp_->text().toDouble();
		}
		//torus outer r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			trs_->m_out_r = tmp_->text().toDouble();
		}
		//torus sides
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			trs_->m_sides = tmp_->text().toInt();
		}
		//torus rings
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(23,1)->widget());
		if(tmp_)
		{
			trs_->m_rings = tmp_->text().toInt();
		}

		break;
	case TRIANGLE_SHAPE:
		trngshp_ = static_cast<TriangleShape*>(m_current_object->getShape());
		// vertex 1
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			lst_ = tmp_->text().split(",");
			if(lst_.size()>2)
			{
				x_ = lst_[0].toDouble();
				y_ = lst_[1].toDouble();
				z_ = lst_[2].toDouble();
				trngshp_->m_p1 = Vertex(x_,y_,z_);
			}
		}

		// vertex 2
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			lst_ = tmp_->text().split(",");
			if(lst_.size()>2)
			{
				x_ = lst_[0].toDouble();
				y_ = lst_[1].toDouble();
				z_ = lst_[2].toDouble();
				trngshp_->m_p2 = Vertex(x_,y_,z_);
			}
		}

		// vertex 3
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			lst_ = tmp_->text().split(",");
			if(lst_.size()>2)
			{
				x_ = lst_[0].toDouble();
				y_ = lst_[1].toDouble();
				z_ = lst_[2].toDouble();
				trngshp_->m_p3 = Vertex(x_,y_,z_);
			}
		}
		break;
	case RECTANGLE:
		rect_ = static_cast<RectangleShape*>(m_current_object->getShape());

		//rectange size x
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			rect_->m_x = tmp_->text().toDouble();
		}
		//rectange size y
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			rect_->m_y = tmp_->text().toDouble();
		}

		break;
	case CIRCLE:
		circle_ = static_cast<Circle*>(m_current_object->getShape());

		//circle r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			circle_->m_r = tmp_->text().toDouble();
		}
		//circle slices
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			circle_->m_slices = tmp_->text().toInt();
		}
		//circle loops
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			circle_->m_loops = tmp_->text().toInt();
		}

		break;
	case DISK:
		disk_ = static_cast<Disk*>(m_current_object->getShape());

		//disk  inner r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			disk_->m_in_r = tmp_->text().toDouble();
		}
		//disk outer r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			disk_->m_out_r = tmp_->text().toDouble();
		}
		//disk siices
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			disk_->m_slices = tmp_->text().toInt();
		}
		//disk loops
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(23,1)->widget());
		if(tmp_)
		{
			disk_->m_loops = tmp_->text().toInt();
		}

		break;
	case PARTIAL_DISK:
		pdisk_ = static_cast<PartialDisk*>(m_current_object->getShape());

		//partial disk  inner r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(20,1)->widget());
		if(tmp_)
		{
			pdisk_->m_in_r = tmp_->text().toDouble();
		}
		//partial disk  outer r
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(21,1)->widget());
		if(tmp_)
		{
			pdisk_->m_out_r = tmp_->text().toDouble();
		}

		//partial disk  start ang
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(22,1)->widget());
		if(tmp_)
		{
			pdisk_->start_ang = tmp_->text().toDouble();
		}
		//partial disk  sweep ang
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(23,1)->widget());
		if(tmp_)
		{
			pdisk_->sweep_ang = tmp_->text().toDouble();
		}

		//partial disk  sides
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(24,1)->widget());
		if(tmp_)
		{
			pdisk_->m_slices = tmp_->text().toInt();
		}
		//partial disk  loops
		tmp_ = static_cast<QLineEdit*>(m_layout->itemAtPosition(25,1)->widget());
		if(tmp_)
		{
			pdisk_->m_loops = tmp_->text().toInt();
		}

		break;
	default:
		break;
	}
}
void ObjectPropertiesController::textureOnOff(bool bl_)
{
	m_current_object->getMaterial()->enableTexture(bl_);
}
void ObjectPropertiesController::changeTexturePlane(int ind_)
{
	//if(material_->getTexture().m_n == Vector3(0,0,1))
	//		cmb_->setCurrentIndex(0);
	//else if(material_->getTexture().m_n == Vector3(1,0,0))
	//		cmb_->setCurrentIndex(1);
	//else if(material_->getTexture().m_n == Vector3(0,1,0))
	//		cmb_->setCurrentIndex(2);
	switch(ind_)
	{
	case 0:
		m_current_object->getMaterial()->getTexture().m_n = Vector3(0,0,1);
		break;
	case 1:
		m_current_object->getMaterial()->getTexture().m_n = Vector3(1,0,0);
		break;
	case 2:
		m_current_object->getMaterial()->getTexture().m_n = Vector3(0,1,0);
		break;
	}
}
void ObjectPropertiesController::changeTexture()
{
	QGroupBox* bx_ = static_cast<QGroupBox*>(m_layout->itemAtPosition(13,0)->widget());
	QGridLayout* lyt_ = static_cast<QGridLayout*>(bx_->layout());
	SMPushButton* pbtn_ = static_cast<SMPushButton*>(lyt_->itemAtPosition(0,2)->widget());

	QString nwTxt_ = QFileDialog::getOpenFileName(m_dock_widget,"Select New Texture","texture",tr("BMP Image(*.bmp)"));
	if(!nwTxt_.isEmpty())
	{
		QFileInfo fi(nwTxt_);
		QDir dr_("texture");
		if(fi.absolutePath().toUpper() != dr_.absolutePath().toUpper())
		{
			if(!dr_.entryList().contains(fi.fileName()))
			{
				QFile::copy(nwTxt_,"texture/"+fi.fileName());
				pbtn_->setIconPath("texture/"+fi.fileName().toStdString());
			}
			else
			{
				bool isOk_ = false ; int cntr_ = 1 ; 
				QString bse_ = fi.fileName();
				bse_.remove(".bmp",Qt::CaseInsensitive);
				while(!isOk_)
				{
					if(!dr_.entryList().contains(fi.fileName()+"_"+QString::number(cntr_)))
					{
						QFile::copy(nwTxt_,"texture/"+bse_+"_"+QString::number(cntr_)+".bmp");
						pbtn_->setIconPath("texture/"+bse_.toStdString()+"_"+
							QString::number(cntr_).toStdString()+".bmp");
						isOk_ = true;
					}
					else cntr_++;
				}
			}
		}
		else
		{
			pbtn_->setIconPath("texture/"+fi.fileName().toStdString());
		}
	}
	m_current_object->getMaterial()->getTexture().m_path = pbtn_->m_icon_path;
}