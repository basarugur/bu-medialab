#include "renderercontroller.h"

#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomText>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>
#include <QThread>


#include "core/sphere.h"
#include "core/cube.h"
#include "core/cone.h"
#include "core/trianglemesh.h"
#include "core/cylinder.h"
#include "core/twosidedcylinder.h"
#include "core/torus.h"
#include "core/triangleshape.h"
#include "core/rectangle.h"
#include "core/circle.h"
#include "core/disk.h"
#include "core/partialdisk.h"

//
class RenderThread : public QThread
{
public:
	RenderThread(QObject* obj_):QThread(obj_)
	{

	}
	~RenderThread(){ };

	void run()
	{
		QStringList arg_ ;
		arg_ << "data/scene.xml";
		QProcess::execute("renderer.exe",arg_);
	}
};
//



RendererController::RendererController(Scene* sc,RawDevice* rwdev_,QWidget *parent)
	: QDialog(parent), m_scene(sc) , m_raw_device(rwdev_)
{
	ui.setupUi(this);

	m_scene = sc;
}

RendererController::~RendererController()
{

}
void RendererController::on_pushButton_clicked()
{
	this->reject();
}

void RendererController::on_pushButton_2_clicked()
{

	int w_ = ui.lineEdit->text().toInt();
	int h_ = ui.lineEdit_2->text().toInt();

	if ( w_ > 0 && h_ > 0 )
	{
		QDir dir(".");
		if(!dir.entryList().contains("data")) dir.mkdir("data");

		saveRawFiles();
		saveXMLFile();

		RenderThread rnd_(this);
		rnd_.start();

		this->accept();
		this->close();
	}
	else if( w_ <= 0)
	{
		QMessageBox::warning(this,"Size Error","Widht must be greater than 0.");
	}
	else
	{
		QMessageBox::warning(this,"Size Error","Height must be greater than 0.");
	}
}
void RendererController::showDialog(Camera*  crnt_)
{
	m_current_camera  = crnt_ ; 
	ui.checkBox->setChecked(false);
	ui.checkBox_2->setChecked(false);
	ui.lineEdit->setText("600");
	ui.lineEdit_2->setText("600");

	this->exec();
}
void RendererController::saveRawFiles()
{
	for(int i=0 ; i<m_scene->objects().size() ; i++)
	{
		if(m_scene->objects()[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* meshShape_ = static_cast<TriangleMesh*>(m_scene->objects()[i]->getShape());
			m_raw_device->saveMesh("data/obj"+QString::number(i).toStdString()+".raw",meshShape_);
		}
		else
		{
			Cube* cp_;
			Sphere* sph_;
			Cone* cne_;
			Cylinder* cyld_;
			TwoSidedCylinder* twcyl_;
			Torus* trs_; 
			TriangleShape* trngshp_;
			RectangleShape* rect_;
			Circle* circle_;
			Disk* disk_;
			PartialDisk* pdisk_;
			TriangleMesh* meshShape_ = new TriangleMesh();
			switch(m_scene->objects()[i]->getShape()->type())
			{
			case CUBE:
				cp_ = static_cast<Cube*>(m_scene->objects()[i]->getShape());
				cp_->copyToMesh(meshShape_);
				break;
			case SPHERE:
				sph_ = static_cast<Sphere*>(m_scene->objects()[i]->getShape());
				sph_->copyToMesh(meshShape_);
				break;
			case CONE:
				cne_ = static_cast<Cone*>(m_scene->objects()[i]->getShape());
				cne_->copyToMesh(meshShape_);
				break;
			case CYLINDER:
				cyld_ = static_cast<Cylinder*>(m_scene->objects()[i]->getShape());
				cyld_->copyToMesh(meshShape_);
				break;
			case TWO_SIDED_CYLINDER:
				twcyl_ = static_cast<TwoSidedCylinder*>(m_scene->objects()[i]->getShape());
				twcyl_->copyToMesh(meshShape_);
				break;
			case TORUS:
				trs_ = static_cast<Torus*>(m_scene->objects()[i]->getShape());
				trs_->copyToMesh(meshShape_);
				break;
			case TRIANGLE_SHAPE:
				trngshp_ = static_cast<TriangleShape*>(m_scene->objects()[i]->getShape());
				trngshp_->copyToMesh(meshShape_);
				break;
			case RECTANGLE:
				rect_ = static_cast<RectangleShape*>(m_scene->objects()[i]->getShape());
				rect_->copyToMesh(meshShape_);
				break;
			case CIRCLE:
				circle_ = static_cast<Circle*>(m_scene->objects()[i]->getShape());
				circle_->copyToMesh(meshShape_);
				break;
			case DISK:
				disk_ = static_cast<Disk*>(m_scene->objects()[i]->getShape());
				disk_->copyToMesh(meshShape_);
				break;
			case PARTIAL_DISK:
				pdisk_ = static_cast<PartialDisk*>(m_scene->objects()[i]->getShape());
				pdisk_->copyToMesh(meshShape_);
				break;
			default:
				break;
			}

			m_raw_device->saveMesh("data/obj"+QString::number(i).toStdString()+".raw",meshShape_);
			delete meshShape_;
		}
	}
}
void RendererController::saveXMLFile()
{
	QDomDocument doc_("Scene");	
	QDomElement root_ = doc_.createElement("Scene");
	doc_.appendChild(root_);
	QDomElement trns_ = doc_.createElement("Transformations");
	root_.appendChild(trns_);
	QDomElement txts_ = doc_.createElement("Textures");
	root_.appendChild(txts_);
	QDomElement mats_ = doc_.createElement("Materials");
	root_.appendChild(mats_);
	QDomElement lgts_ = doc_.createElement("Lights");
	root_.appendChild(lgts_);
	QDomElement cmr_ = doc_.createElement("Camera");
	root_.appendChild(cmr_);
	QDomElement scrn_ = doc_.createElement("Screen");
	root_.appendChild(scrn_);
	QDomElement shps_ = doc_.createElement("Shapes");
	root_.appendChild(shps_);
	QDomElement prms_ = doc_.createElement("Primitives");
	root_.appendChild(prms_);
	QDomElement props_ = doc_.createElement("Properties");
	root_.appendChild(props_);

	for(int i=0 ; i<m_scene->objects().size() ; i++)
	{
		GfxObject* obj_ = m_scene->objects()[i];
		Transformation globalTrns_ =  *obj_->getIndividualTranform()+*obj_->getPublicTranform();
		GfxObject* tmp_ = obj_->getParent();
		while(tmp_ != NULL)
		{
			globalTrns_ = globalTrns_*(*tmp_->getPublicTranform());
			tmp_ = tmp_->getParent();
		}

		// transformation
		QDomElement tr_ = doc_.createElement("Transformation");
		trns_.appendChild(tr_);
		tr_.setAttribute("id",QString::number(i));
		//QDomAttr at1_ = doc_.createAttribute("id"); 
		//at1_.setNodeValue(QString::number(i));
		//tr_.appendChild(at1_);

		QDomElement rot_ = doc_.createElement("Rotation");
		tr_.appendChild(rot_);
		rot_.setAttribute("x",QString::number(globalTrns_.rotation().ax(),'f',3));
		rot_.setAttribute("y",QString::number(globalTrns_.rotation().ay(),'f',3));
		rot_.setAttribute("z",QString::number(globalTrns_.rotation().az(),'f',3));
		rot_.setAttribute("r",QString::number(globalTrns_.rotation().theta(),'f',3));
		//QDomAttr rx_ = doc_.createAttribute("x"); 
		//rx_.setNodeValue(QString::number(globalTrns_.rotation().ax(),'f',3));
		//rot_.appendChild(rx_);
		//QDomAttr ry_ = doc_.createAttribute("y"); 
		//ry_.setNodeValue(QString::number(globalTrns_.rotation().ay(),'f',3));
		//rot_.appendChild(ry_);
		//QDomAttr rz_ = doc_.createAttribute("z"); 
		//rz_.setNodeValue(QString::number(globalTrns_.rotation().az(),'f',3));
		//rot_.appendChild(rz_);
		//QDomAttr rr_ = doc_.createAttribute("r"); 
		//rr_.setNodeValue(QString::number(globalTrns_.rotation().theta(),'f',3));
		//rot_.appendChild(rr_);

		QDomElement sc_ = doc_.createElement("Scale");
		tr_.appendChild(sc_);
		sc_.setAttribute("x",QString::number(globalTrns_.scale().x(),'f',3));
		sc_.setAttribute("y",QString::number(globalTrns_.scale().y(),'f',3));
		sc_.setAttribute("z",QString::number(globalTrns_.scale().z(),'f',3));
		//QDomAttr sx_ = doc_.createAttribute("x"); 
		//sx_.setNodeValue(QString::number(globalTrns_.scale().x(),'f',3));
		//sc_.appendChild(sx_);
		//QDomAttr sy_ = doc_.createAttribute("y"); 
		//sy_.setNodeValue(QString::number(globalTrns_.scale().y(),'f',3));
		//sc_.appendChild(sy_);
		//QDomAttr sz_ = doc_.createAttribute("z"); 
		//sz_.setNodeValue(QString::number(globalTrns_.scale().z(),'f',3));
		//sc_.appendChild(sz_);

		QDomElement translation_ = doc_.createElement("Translation");
		tr_.appendChild(translation_);
		translation_.setAttribute("x",QString::number(globalTrns_.translation().x(),'f',3));
		translation_.setAttribute("y",QString::number(globalTrns_.translation().y(),'f',3));
		translation_.setAttribute("z",QString::number(globalTrns_.translation().z(),'f',3));
		//QDomAttr trnsx_ = doc_.createAttribute("x"); 
		//trnsx_.setNodeValue(QString::number(globalTrns_.translation().x(),'f',3));
		//translation_.appendChild(trnsx_);
		//QDomAttr trnsy_ = doc_.createAttribute("y"); 
		//trnsy_.setNodeValue(QString::number(globalTrns_.translation().y(),'f',3));
		//translation_.appendChild(trnsy_);
		//QDomAttr trnsz_ = doc_.createAttribute("z"); 
		//trnsz_.setNodeValue(QString::number(globalTrns_.translation().z(),'f',3));
		//translation_.appendChild(trnsz_);

		// texture
		QDomElement texture_ = doc_.createElement("Texture");
		txts_.appendChild(texture_);
		texture_.setAttribute("id",QString::number(i));
		//QDomAttr at2_ = doc_.createAttribute("id"); 
		//at2_.setNodeValue(QString::number(i));
		//texture_.appendChild(at2_);

		QDomElement fle_ = doc_.createElement("File");
		texture_.appendChild(fle_);
		fle_.setAttribute("path",QString::fromStdString(obj_->getMaterial()->getTexture().m_path));
		//QDomAttr pth_ = doc_.createAttribute("path");
		//pth_.setNodeValue(QString::fromStdString(obj_->getMaterial()->getTexture().m_path));
		//fle_.appendChild(pth_);

		QDomElement normal_ = doc_.createElement("Normal");
		texture_.appendChild(normal_);
		normal_.setAttribute("x",QString::number(obj_->getMaterial()->getTexture().m_n.x()));
		normal_.setAttribute("y",QString::number(obj_->getMaterial()->getTexture().m_n.y()));
		normal_.setAttribute("z",QString::number(obj_->getMaterial()->getTexture().m_n.z()));
		//QDomAttr nx_ = doc_.createAttribute("x"); 
		//nx_.setNodeValue(QString::number(obj_->getMaterial()->getTexture().m_n.x(),'f',3));
		//normal_.appendChild(nx_);
		//QDomAttr ny_ = doc_.createAttribute("y"); 
		//ny_.setNodeValue(QString::number(obj_->getMaterial()->getTexture().m_n.y(),'f',3));
		//normal_.appendChild(ny_);
		//QDomAttr nz_ = doc_.createAttribute("z"); 
		//nz_.setNodeValue(QString::number(obj_->getMaterial()->getTexture().m_n.z(),'f',3));
		//normal_.appendChild(nz_);

		QDomElement txtScale_ = doc_.createElement("Scale");
		texture_.appendChild(txtScale_);
		txtScale_.setAttribute("x",QString::number(obj_->getMaterial()->getTexture().m_scale_x,'f',3));
		txtScale_.setAttribute("y",QString::number(obj_->getMaterial()->getTexture().m_scale_y,'f',3));
		//QDomAttr tsx_ = doc_.createAttribute("x"); 
		//tsx_.setNodeValue(QString::number(obj_->getMaterial()->getTexture().m_scale_x,'f',3));
		//txtScale_.appendChild(tsx_);
		//QDomAttr tsy_ = doc_.createAttribute("y"); 
		//tsy_.setNodeValue(QString::number(obj_->getMaterial()->getTexture().m_scale_y,'f',3));
		//txtScale_.appendChild(tsy_);

		// material
		QDomElement material_ = doc_.createElement("Material");
		mats_.appendChild(material_);
		material_.setAttribute("id",QString::number(i));
		//QDomAttr at3_ = doc_.createAttribute("id"); 
		//at3_.setNodeValue(QString::number(i));
		//material_.appendChild(at3_);

		if(obj_->getMaterial()->isTextureEnabled())	material_.setAttribute("texture_id",QString::number(i));
		else material_.setAttribute("texture_id","-1");

		//QDomAttr txtID_ = doc_.createAttribute("texture_id"); 
		//if(obj_->getMaterial()->isTextureEnabled())	txtID_.setNodeValue(QString::number(i));
		//else txtID_.setNodeValue("-1");
		//material_.appendChild(txtID_);

		QDomElement dfCl_ = doc_.createElement("Diffusecolor");
		material_.appendChild(dfCl_);
		dfCl_.setAttribute("r",QString::number(obj_->getMaterial()->diffcolor().r,'f',3));
		dfCl_.setAttribute("g",QString::number(obj_->getMaterial()->diffcolor().g,'f',3));
		dfCl_.setAttribute("b",QString::number(obj_->getMaterial()->diffcolor().b,'f',3));
		//QDomAttr dr_ = doc_.createAttribute("r"); 
		//dr_.setNodeValue(QString::number(obj_->getMaterial()->diffcolor().r,'f',3));
		//dfCl_.appendChild(dr_);
		//QDomAttr dg_ = doc_.createAttribute("g"); 
		//dg_.setNodeValue(QString::number(obj_->getMaterial()->diffcolor().g,'f',3));
		//dfCl_.appendChild(dg_);
		//QDomAttr db_ = doc_.createAttribute("b"); 
		//db_.setNodeValue(QString::number(obj_->getMaterial()->diffcolor().b,'f',3));
		//dfCl_.appendChild(db_);

		QDomElement spCl_ = doc_.createElement("Specularcolor");
		material_.appendChild(spCl_);
		spCl_.setAttribute("r",QString::number(obj_->getMaterial()->speccolor().r,'f',3));
		spCl_.setAttribute("g",QString::number(obj_->getMaterial()->speccolor().g,'f',3));
		spCl_.setAttribute("b",QString::number(obj_->getMaterial()->speccolor().b,'f',3));
		//QDomAttr sr_ = doc_.createAttribute("r"); 
		//sr_.setNodeValue(QString::number(obj_->getMaterial()->speccolor().r,'f',3));
		//spCl_.appendChild(sr_);
		//QDomAttr sg_ = doc_.createAttribute("g"); 
		//sg_.setNodeValue(QString::number(obj_->getMaterial()->speccolor().g,'f',3));
		//spCl_.appendChild(sg_);
		//QDomAttr sb_ = doc_.createAttribute("b"); 
		//sb_.setNodeValue(QString::number(obj_->getMaterial()->speccolor().b,'f',3));
		//spCl_.appendChild(sb_);

		QDomElement ambCl_ = doc_.createElement("Ambientcolor");
		material_.appendChild(ambCl_);
		ambCl_.setAttribute("r",QString::number(obj_->getMaterial()->ambientcolor().r,'f',3));
		ambCl_.setAttribute("g",QString::number(obj_->getMaterial()->ambientcolor().g,'f',3));
		ambCl_.setAttribute("b",QString::number(obj_->getMaterial()->ambientcolor().b,'f',3));
		//QDomAttr ar_ = doc_.createAttribute("r"); 
		//ar_.setNodeValue(QString::number(obj_->getMaterial()->ambientcolor().r,'f',3));
		//ambCl_.appendChild(ar_);
		//QDomAttr ag_ = doc_.createAttribute("g"); 
		//ag_.setNodeValue(QString::number(obj_->getMaterial()->ambientcolor().g,'f',3));
		//ambCl_.appendChild(ag_);
		//QDomAttr ab_ = doc_.createAttribute("b"); 
		//ab_.setNodeValue(QString::number(obj_->getMaterial()->ambientcolor().b,'f',3));
		//ambCl_.appendChild(ab_);

		QDomElement sld_ = doc_.createElement("solid");
		QDomText sld_txt_ = doc_.createTextNode(QString::number(obj_->material()->solid(),'f',3)); 
		sld_.appendChild(sld_txt_);
		material_.appendChild(sld_);

		QDomElement reflection_ = doc_.createElement("reflection");
		QDomText reflect_text_ = doc_.createTextNode(QString::number(obj_->material()->reflection(),'f',3));
		reflection_.appendChild(reflect_text_);
		material_.appendChild(reflection_);

		QDomElement refract_ = doc_.createElement("refraction_index");
		QDomText refract_text_ = doc_.createTextNode(QString::number(obj_->material()->refraction_index(),'f',3));
		refract_.appendChild(refract_text_);
		material_.appendChild(refract_);

		QDomElement lcl_ = doc_.createElement("luculent");
		QDomText lcl_txt_ = doc_.createTextNode(QString::number(obj_->material()->luculent(),'f',3));
		lcl_.appendChild(lcl_txt_);
		material_.appendChild(lcl_);

		// shape
		QDomElement shape_ = doc_.createElement("Shape");
		shps_.appendChild(shape_);
		shape_.setAttribute("id",QString::number(i));
		//QDomAttr at4_ = doc_.createAttribute("id"); 
		//at4_.setNodeValue(QString::number(i));
		//shape_.appendChild(at4_);

		shape_.setAttribute("type","triangle_mesh");
		//QDomAttr type_ = doc_.createAttribute("type"); 
		//type_.setNodeValue("triangle_mesh");
		//shape_.appendChild(type_);

		QDomElement shpfle_ = doc_.createElement("File");
		shape_.appendChild(shpfle_);
		shpfle_.setAttribute("path","data/obj"+QString::number(i)+".raw");
		//QDomAttr shp_pth_ = doc_.createAttribute("path");
		//shp_pth_.setNodeValue("data/obj"+QString::number(i)+".raw");
		//shpfle_.appendChild(shp_pth_);

		// primitive 
		QDomElement primitive_ = doc_.createElement("Primitive");
		prms_.appendChild(primitive_);
		primitive_.setAttribute("id",QString::number(i));
		//QDomAttr at5_ = doc_.createAttribute("id"); 
		//at5_.setNodeValue(QString::number(i));
		//primitive_.appendChild(at5_);

		QDomElement pSha_ = doc_.createElement("Shape");
		QDomText pSha_txt_ = doc_.createTextNode(QString::number(i));
		pSha_.appendChild(pSha_txt_);
		primitive_.appendChild(pSha_);

		QDomElement pMat_ = doc_.createElement("Material");
		QDomText pMat_txt = doc_.createTextNode(QString::number(i));
		pMat_.appendChild(pMat_txt);
		primitive_.appendChild(pMat_);

		QDomElement pTrns_ = doc_.createElement("Transformation");
		QDomText pTrns_txt = doc_.createTextNode(QString::number(i));
		pTrns_.appendChild(pTrns_txt);
		primitive_.appendChild(pTrns_);

	}

	if(ui.checkBox_2->isChecked())
	{
		QDomElement lghtElm_ = doc_.createElement("Light");
		lgts_.appendChild(lghtElm_);
		lghtElm_.setAttribute("id","0");
		//QDomAttr at5_ = doc_.createAttribute("id"); 
		//at5_.setNodeValue("0");
		//lghtElm_.appendChild(at5_);

		lghtElm_.setAttribute("type","sky");
		//QDomAttr txtID_ = doc_.createAttribute("type"); 
		//txtID_.setNodeValue("sky");
		//lghtElm_.appendChild(txtID_);

		QDomElement normal_ = doc_.createElement("Position");
		lghtElm_.appendChild(normal_);
		normal_.setAttribute("x","0");
		normal_.setAttribute("y","7");
		normal_.setAttribute("z","-5");

		//QDomAttr nx_ = doc_.createAttribute("x"); 
		//nx_.setNodeValue("0");
		//normal_.appendChild(nx_);
		//QDomAttr ny_ = doc_.createAttribute("y"); 
		//ny_.setNodeValue("7");
		//normal_.appendChild(ny_);
		//QDomAttr nz_ = doc_.createAttribute("z"); 
		//nz_.setNodeValue("-5");
		//normal_.appendChild(nz_);

		QDomElement translation_ = doc_.createElement("Direction");
		lghtElm_.appendChild(translation_);
		translation_.setAttribute("x","0");
		translation_.setAttribute("y","1");
		translation_.setAttribute("z","0");

		//QDomAttr trnsx_ = doc_.createAttribute("x"); 
		//trnsx_.setNodeValue("0");
		//translation_.appendChild(trnsx_);
		//QDomAttr trnsy_ = doc_.createAttribute("y"); 
		//trnsy_.setNodeValue("1");
		//translation_.appendChild(trnsy_);
		//QDomAttr trnsz_ = doc_.createAttribute("z"); 
		//trnsz_.setNodeValue("0");
		//translation_.appendChild(trnsz_);

		QDomElement pTrns_ = doc_.createElement("Coefficient");
		QDomText pTrns_txt = doc_.createTextNode("1");
		pTrns_.appendChild(pTrns_txt);
		lghtElm_.appendChild(pTrns_);
	}

	for(int i=0 ; i<m_scene->lights().size() ; i++)
	{
		QDomElement lghtElm_ = doc_.createElement("Light");
		lgts_.appendChild(lghtElm_);
		if(ui.checkBox_2->isChecked())lghtElm_.setAttribute("id",QString::number(i+1));
		else lghtElm_.setAttribute("id",QString::number(i));
		//QDomAttr at5_ = doc_.createAttribute("id"); 
		//if(ui.checkBox_2->isChecked()) at5_.setNodeValue(QString::number(i+1));
		//else at5_.setNodeValue(QString::number(i));
		//lghtElm_.appendChild(at5_);

		//QDomAttr txtID_ = doc_.createAttribute("type"); 
		if(m_scene->lights()[i]->type() == POINT_LIGHT) lghtElm_.setAttribute("type","point");
		else lghtElm_.setAttribute("type","area");
		//lghtElm_.appendChild(txtID_);

		QDomElement normal_ = doc_.createElement("Position");
		lghtElm_.appendChild(normal_);
		normal_.setAttribute("x",QString::number(m_scene->lights()[i]->p().x(),'f',3));
		normal_.setAttribute("y",QString::number(m_scene->lights()[i]->p().y(),'f',3));
		normal_.setAttribute("z",QString::number(m_scene->lights()[i]->p().z(),'f',3));

		//QDomAttr nx_ = doc_.createAttribute("x"); 
		//nx_.setNodeValue(QString::number(m_scene->lights()[i]->p().x(),'f',3));
		//normal_.appendChild(nx_);
		//QDomAttr ny_ = doc_.createAttribute("y"); 
		//ny_.setNodeValue(QString::number(m_scene->lights()[i]->p().y(),'f',3));
		//normal_.appendChild(ny_);
		//QDomAttr nz_ = doc_.createAttribute("z"); 
		//nz_.setNodeValue(QString::number(m_scene->lights()[i]->p().z(),'f',3));
		//normal_.appendChild(nz_);

		QDomElement translation_ = doc_.createElement("Direction");
		lghtElm_.appendChild(translation_);
		translation_.setAttribute("x","0");
		translation_.setAttribute("y","1");
		translation_.setAttribute("z","0");
		//QDomAttr trnsx_ = doc_.createAttribute("x"); 
		//trnsx_.setNodeValue("0");
		//translation_.appendChild(trnsx_);
		//QDomAttr trnsy_ = doc_.createAttribute("y"); 
		//trnsy_.setNodeValue("1");
		//translation_.appendChild(trnsy_);
		//QDomAttr trnsz_ = doc_.createAttribute("z"); 
		//trnsz_.setNodeValue("0");
		//translation_.appendChild(trnsz_);

		QDomElement pTrns_ = doc_.createElement("Coefficient");
		QDomText pTrns_txt = doc_.createTextNode("1");
		pTrns_.appendChild(pTrns_txt);
		lghtElm_.appendChild(pTrns_);
	}

	// camera
		cmr_.setAttribute("type","perspective");
		//QDomAttr at1_ = doc_.createAttribute("type"); 
		//at1_.setNodeValue("perspective");
		//cmr_.appendChild(at1_);

		QDomElement rot_ = doc_.createElement("Position");
		cmr_.appendChild(rot_);
		rot_.setAttribute("x",QString::number(m_current_camera->position().x(),'f',3));
		rot_.setAttribute("y",QString::number(m_current_camera->position().y(),'f',3));
		rot_.setAttribute("z",QString::number(m_current_camera->position().z(),'f',3));

		//QDomAttr rx_ = doc_.createAttribute("x"); 
		//rx_.setNodeValue(QString::number(m_current_camera->position().x(),'f',3));
		//rot_.appendChild(rx_);
		//QDomAttr ry_ = doc_.createAttribute("y"); 
		//ry_.setNodeValue(QString::number(m_current_camera->position().y(),'f',3));
		//rot_.appendChild(ry_);
		//QDomAttr rz_ = doc_.createAttribute("z"); 
		//rz_.setNodeValue(QString::number(m_current_camera->position().z(),'f',3));
		//rot_.appendChild(rz_);

		QDomElement sc_ = doc_.createElement("Up");
		cmr_.appendChild(sc_);
		sc_.setAttribute("x",QString::number(m_current_camera->upVector().x(),'f',3));
		sc_.setAttribute("y",QString::number(m_current_camera->upVector().y(),'f',3));
		sc_.setAttribute("z",QString::number(m_current_camera->upVector().z(),'f',3));

		//QDomAttr sx_ = doc_.createAttribute("x"); 
		//sx_.setNodeValue(QString::number(m_current_camera->upVector().x(),'f',3));
		//sc_.appendChild(sx_);
		//QDomAttr sy_ = doc_.createAttribute("y"); 
		//sy_.setNodeValue(QString::number(m_current_camera->upVector().y(),'f',3));
		//sc_.appendChild(sy_);
		//QDomAttr sz_ = doc_.createAttribute("z"); 
		//sz_.setNodeValue(QString::number(m_current_camera->upVector().z(),'f',3));
		//sc_.appendChild(sz_);

		QDomElement translation_ = doc_.createElement("Target");
		cmr_.appendChild(translation_);
		translation_.setAttribute("x",QString::number(m_current_camera->atPoint().x(),'f',3));
		translation_.setAttribute("y",QString::number(m_current_camera->atPoint().y(),'f',3));
		translation_.setAttribute("z",QString::number(m_current_camera->atPoint().z(),'f',3));

		//QDomAttr trnsx_ = doc_.createAttribute("x"); 
		//trnsx_.setNodeValue(QString::number(m_current_camera->atPoint().x(),'f',3));
		//translation_.appendChild(trnsx_);
		//QDomAttr trnsy_ = doc_.createAttribute("y"); 
		//trnsy_.setNodeValue(QString::number(m_current_camera->atPoint().y(),'f',3));
		//translation_.appendChild(trnsy_);
		//QDomAttr trnsz_ = doc_.createAttribute("z"); 
		//trnsz_.setNodeValue(QString::number(m_current_camera->atPoint().z(),'f',3));
		//translation_.appendChild(trnsz_);
	//


    // screen
	QDomElement pSha_ = doc_.createElement("Width");
	QDomText pSha_txt_ = doc_.createTextNode(ui.lineEdit->text());
	pSha_.appendChild(pSha_txt_);
	scrn_.appendChild(pSha_);

	QDomElement pMat_ = doc_.createElement("Height");
	QDomText pMat_txt = doc_.createTextNode(ui.lineEdit_2->text());
	pMat_.appendChild(pMat_txt);
	scrn_.appendChild(pMat_);

	//QDomElement props_ 
	QString isAnt_ = "false";
	if(ui.checkBox->isChecked())isAnt_ = "true";

	QDomElement primitive_ = doc_.createElement("AntiAlias");
	props_.appendChild(primitive_);
	QDomText pSha1_txt_ = doc_.createTextNode(isAnt_);
	primitive_.appendChild(pSha1_txt_);

	std::ofstream stream;
	stream.open("data/scene.xml",std::ios::out);
	if(stream.is_open())
		stream << doc_.toString().toStdString() ;
	stream.close();
}