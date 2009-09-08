#include "RenderController.h"

#include "formats/rawdevice.h"
#include <sstream>

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

#include "tinyXML/tinyxml.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>


RenderController::RenderController(void)
{
}

RenderController::~RenderController(void)
{
}

void RenderController::render(Scene* sc_, Camera* cm_,
                              bool skyLight, double skyCoeff, bool antiAlisng,
                              int width, int height)
{
	saveRawFiles(sc_);
	saveXML( sc_, cm_,skyLight ,skyCoeff , antiAlisng,
		width , height);

	#ifdef WIN32
        system("renderer.exe scene.xml");
	#elif defined(UNIX)
        system("./renderer scene.xml");
	#else
        execl("renderer", " scene.xml");
	#endif
}

void RenderController::saveXML(Scene* scene_, Camera* cm_,
                               bool skyLight, double skyCoeff, bool antiAlisng,
                               int width, int height)
{
	TiXmlDocument doc;
	TiXmlElement* root_ = new TiXmlElement("Scene");
	doc.LinkEndChild(root_);
	TiXmlElement* trns_ = new TiXmlElement("Transformations");
	root_->LinkEndChild(trns_);
	TiXmlElement* txts_ = new TiXmlElement("Textures");
	root_->LinkEndChild(txts_);
	TiXmlElement* mats_ = new TiXmlElement("Materials");
	root_->LinkEndChild(mats_);
	TiXmlElement* lgts_ = new TiXmlElement("Lights");
	root_->LinkEndChild(lgts_);
	TiXmlElement* cmr_ = new TiXmlElement("Camera");
	root_->LinkEndChild(cmr_);
	TiXmlElement* scrn_ = new TiXmlElement("Screen");
	root_->LinkEndChild(scrn_);
	TiXmlElement* shps_ = new TiXmlElement("Shapes");
	root_->LinkEndChild(shps_);
	TiXmlElement* prms_ = new TiXmlElement("Primitives");
	root_->LinkEndChild(prms_);
	TiXmlElement* props_ = new TiXmlElement("Properties");
	root_->LinkEndChild(props_);

	for (int i=0 ; i<scene_->objects().size() ; i++)
	{
		GfxObject* obj_ = scene_->objects()[i];
		Transformation globalTrns_ =  *obj_->getLocalTransform()+*obj_->getGlobalTransform();
		GfxObject* tmp_ = obj_->getParent();
		while(tmp_ != NULL)
		{
			globalTrns_ = globalTrns_ * (*tmp_->getGlobalTransform());
			tmp_ = tmp_->getParent();
		}

		std::ostringstream ss1; ss1<<i;
		TiXmlElement* tr_ = new TiXmlElement("Transformation");
		trns_->LinkEndChild(tr_);
		tr_->SetAttribute("id",(char*)ss1.str().c_str());

		TiXmlElement* rot_ = new TiXmlElement("Rotation");
		tr_->LinkEndChild(rot_);
		std::ostringstream ss2; ss2<<globalTrns_.rotation().ax();
		std::ostringstream ss3; ss3<<globalTrns_.rotation().ay();
		std::ostringstream ss4; ss4<<globalTrns_.rotation().az();
		std::ostringstream ss5; ss5<<globalTrns_.rotation().theta();
		rot_->SetAttribute("x",(char*)ss2.str().c_str());
		rot_->SetAttribute("y",(char*)ss3.str().c_str());
		rot_->SetAttribute("z",(char*)ss4.str().c_str());
		rot_->SetAttribute("r",(char*)ss5.str().c_str());

		TiXmlElement* sc_ = new TiXmlElement("Scale");
		tr_->LinkEndChild(sc_);
		std::ostringstream ss6; ss6<<globalTrns_.scale().x();
		std::ostringstream ss7; ss7<<globalTrns_.scale().y();
		std::ostringstream ss8; ss8<<globalTrns_.scale().z();
		sc_->SetAttribute("x",(char*)ss6.str().c_str());
		sc_->SetAttribute("y",(char*)ss7.str().c_str());
		sc_->SetAttribute("z",(char*)ss8.str().c_str());

		TiXmlElement* translation_ = new TiXmlElement("Translation");
		tr_->LinkEndChild(translation_);
		std::ostringstream ss9; ss9<<globalTrns_.translation().x();
		std::ostringstream ss10; ss10<<globalTrns_.translation().y();
		std::ostringstream ss11; ss11<<globalTrns_.translation().z();
		translation_->SetAttribute("x",(char*)ss9.str().c_str());
		translation_->SetAttribute("y",(char*)ss10.str().c_str());
		translation_->SetAttribute("z",(char*)ss11.str().c_str());

		TiXmlElement* texture_ = new TiXmlElement("Texture");
		txts_->LinkEndChild(texture_);
		texture_->SetAttribute("id",(char*)ss1.str().c_str());

		TiXmlElement* fle_ = new TiXmlElement("File");
		texture_->LinkEndChild(fle_);
		fle_->SetAttribute("path",(char*)obj_->getMaterial()->getTexture().m_path.c_str());

		TiXmlElement* normal_ = new TiXmlElement("Normal");
		texture_->LinkEndChild(normal_);
		std::ostringstream ss12; ss12<<obj_->getMaterial()->getTexture().m_n.x();
		std::ostringstream ss13; ss13<<obj_->getMaterial()->getTexture().m_n.y();
		std::ostringstream ss14; ss14<<obj_->getMaterial()->getTexture().m_n.z();
		normal_->SetAttribute("x",(char*)ss12.str().c_str());
		normal_->SetAttribute("y",(char*)ss13.str().c_str());
		normal_->SetAttribute("z",(char*)ss14.str().c_str());

		TiXmlElement* txtScale_ = new TiXmlElement("Scale");
		texture_->LinkEndChild(txtScale_);
		std::ostringstream ss15; ss15<<obj_->getMaterial()->getTexture().m_scale_x;
		std::ostringstream ss16; ss16<<obj_->getMaterial()->getTexture().m_scale_y;
		txtScale_->SetAttribute("x",(char*)ss15.str().c_str());
		txtScale_->SetAttribute("y",(char*)ss16.str().c_str());

		TiXmlElement* material_ = new TiXmlElement("Material");
		mats_->LinkEndChild(material_);
		material_->SetAttribute("id",(char*)ss1.str().c_str());

		if(obj_->getMaterial()->isTextureEnabled())
			material_->SetAttribute("texture_id",(char*)ss1.str().c_str());
		else material_->SetAttribute("texture_id","-1");

		TiXmlElement* dfCl_ = new TiXmlElement("Diffusecolor");
		material_->LinkEndChild(dfCl_);
		std::ostringstream ss17; ss17<<obj_->getMaterial()->diffcolor().r;
		std::ostringstream ss18; ss18<<obj_->getMaterial()->diffcolor().g;
		std::ostringstream ss19; ss19<<obj_->getMaterial()->diffcolor().b;
		dfCl_->SetAttribute("r",(char*)ss17.str().c_str());
		dfCl_->SetAttribute("g",(char*)ss18.str().c_str());
		dfCl_->SetAttribute("b",(char*)ss19.str().c_str());

		TiXmlElement* spCl_ = new TiXmlElement("Specularcolor");
		material_->LinkEndChild(spCl_);
		std::ostringstream ss20; ss20<<obj_->getMaterial()->speccolor().r;
		std::ostringstream ss21; ss21<<obj_->getMaterial()->speccolor().g;
		std::ostringstream ss22; ss22<<obj_->getMaterial()->speccolor().b;
		spCl_->SetAttribute("r",(char*)ss20.str().c_str());
		spCl_->SetAttribute("g",(char*)ss21.str().c_str());
		spCl_->SetAttribute("b",(char*)ss22.str().c_str());

		TiXmlElement* ambCl_ = new TiXmlElement("Ambientcolor");
		material_->LinkEndChild(ambCl_);
		std::ostringstream ss23; ss23<<obj_->getMaterial()->ambientcolor().r;
		std::ostringstream ss24; ss24<<obj_->getMaterial()->ambientcolor().g;
		std::ostringstream ss25; ss25<<obj_->getMaterial()->ambientcolor().b;
		ambCl_->SetAttribute("r",(char*)ss23.str().c_str());
		ambCl_->SetAttribute("g",(char*)ss24.str().c_str());
		ambCl_->SetAttribute("b",(char*)ss25.str().c_str());

		TiXmlElement* sld_ = new TiXmlElement("solid");
		std::ostringstream ss26; ss26<<obj_->material()->solid();
		sld_->LinkEndChild(new TiXmlText((char*)ss26.str().c_str()));
		material_->LinkEndChild(sld_);

		TiXmlElement* reflection_ = new TiXmlElement("reflection");
		std::ostringstream ss27; ss27<<obj_->material()->reflection();
		reflection_->LinkEndChild(new TiXmlText((char*)ss27.str().c_str()));
		material_->LinkEndChild(reflection_);

		TiXmlElement* refract_ = new TiXmlElement("refraction_index");
		std::ostringstream ss28; ss28<<obj_->material()->refraction_index();
		refract_->LinkEndChild(new TiXmlText((char*)ss28.str().c_str()));
		material_->LinkEndChild(refract_);

		TiXmlElement* lcl_ = new TiXmlElement("luculent");
		std::ostringstream ss29; ss29<<obj_->material()->luculent();
		lcl_->LinkEndChild(new TiXmlText((char*)ss29.str().c_str()));
		material_->LinkEndChild(lcl_);


		TiXmlElement* shape_ = new TiXmlElement("Shape");
		shps_->LinkEndChild(shape_);
		shape_->SetAttribute("id",(char*)ss1.str().c_str());
		shape_->SetAttribute("type","triangle_mesh");

		TiXmlElement* shpfle_ = new TiXmlElement("File");
		std::ostringstream ss30; ss30<<"obj" <<i<< ".raw";
		shpfle_->SetAttribute("path",(char*)ss30.str().c_str());
		shape_->LinkEndChild(shpfle_);

		TiXmlElement* primitive_ = new TiXmlElement("Primitive");
		prms_->LinkEndChild(primitive_);
		primitive_->SetAttribute("id",(char*)ss1.str().c_str());

		TiXmlElement* pSha_ = new TiXmlElement("Shape");
		pSha_->LinkEndChild(new TiXmlText((char*)ss1.str().c_str()));
		primitive_->LinkEndChild(pSha_);

		TiXmlElement* pMat_ = new TiXmlElement("Material");
		pMat_->LinkEndChild(new TiXmlText((char*)ss1.str().c_str()));
		primitive_->LinkEndChild(pMat_);

		TiXmlElement* pTrns_ = new TiXmlElement("Transformation");
		pTrns_->LinkEndChild(new TiXmlText((char*)ss1.str().c_str()));
		primitive_->LinkEndChild(pTrns_);
	}

	if (skyLight)
	{
		TiXmlElement* lghtElm_ = new TiXmlElement("Light");
		lgts_->LinkEndChild(lghtElm_);
		lghtElm_->SetAttribute("id","0");
		lghtElm_->SetAttribute("type","sky");

		TiXmlElement* sc_ = new TiXmlElement("Position");
		lghtElm_->LinkEndChild(sc_);
		std::ostringstream ss6; ss6<<0;
		std::ostringstream ss7; ss7<<7;
		std::ostringstream ss8; ss8<<-5;
		sc_->SetAttribute("x",(char*)ss6.str().c_str());
		sc_->SetAttribute("y",(char*)ss7.str().c_str());
		sc_->SetAttribute("z",(char*)ss8.str().c_str());

		TiXmlElement* translation_ = new TiXmlElement("Direction");
		lghtElm_->LinkEndChild(translation_);
		std::ostringstream ss9; ss9<<0;
		std::ostringstream ss10; ss10<<1;
		std::ostringstream ss11; ss11<<0;
		translation_->SetAttribute("x",(char*)ss9.str().c_str());
		translation_->SetAttribute("y",(char*)ss10.str().c_str());
		translation_->SetAttribute("z",(char*)ss11.str().c_str());

		TiXmlElement* pTrns_ = new TiXmlElement("Coefficient");
		std::ostringstream ss12; ss12<<skyCoeff;
		pTrns_->LinkEndChild(new TiXmlText((char*)ss12.str().c_str()));
		lghtElm_->LinkEndChild(pTrns_);
	}

	for(int i=0 ; i<scene_->lights().size();i++)
	{
		TiXmlElement* lghtElm_ = new TiXmlElement("Light");
		lgts_->LinkEndChild(lghtElm_);

		std::ostringstream ss1;
		if(skyLight)ss1<<i+1;
		else ss1<<i;

		lghtElm_->SetAttribute("id",(char*)ss1.str().c_str());
		if(scene_->lights()[i]->type() == POINT_LIGHT) lghtElm_->SetAttribute("type","point");
		else lghtElm_->SetAttribute("type","area");

		TiXmlElement* sc_ = new TiXmlElement("Position");
		lghtElm_->LinkEndChild(sc_);
		std::ostringstream ss6; ss6<<scene_->lights()[i]->p().x();
		std::ostringstream ss7; ss7<<scene_->lights()[i]->p().y();
		std::ostringstream ss8; ss8<<scene_->lights()[i]->p().z();
		sc_->SetAttribute("x",(char*)ss6.str().c_str());
		sc_->SetAttribute("y",(char*)ss7.str().c_str());
		sc_->SetAttribute("z",(char*)ss8.str().c_str());

		TiXmlElement* translation_ = new TiXmlElement("Direction");
		lghtElm_->LinkEndChild(translation_);
		std::ostringstream ss9; ss9<<0;
		std::ostringstream ss10; ss10<<1;
		std::ostringstream ss11; ss11<<0;
		translation_->SetAttribute("x",(char*)ss9.str().c_str());
		translation_->SetAttribute("y",(char*)ss10.str().c_str());
		translation_->SetAttribute("z",(char*)ss11.str().c_str());

		TiXmlElement* pTrns_ = new TiXmlElement("Coefficient");
		std::ostringstream ss12; ss12<<scene_->lights()[i]->coeff();
		pTrns_->LinkEndChild(new TiXmlText((char*)ss12.str().c_str()));
		lghtElm_->LinkEndChild(pTrns_);
	}

	cmr_->SetAttribute("type","perspective");

	TiXmlElement* sc_ = new TiXmlElement("Position");
	cmr_->LinkEndChild(sc_);
	std::ostringstream ss6; ss6<<cm_->position().x();
	std::ostringstream ss7; ss7<<cm_->position().y();
	std::ostringstream ss8; ss8<<cm_->position().z();
	sc_->SetAttribute("x",(char*)ss6.str().c_str());
	sc_->SetAttribute("y",(char*)ss7.str().c_str());
	sc_->SetAttribute("z",(char*)ss8.str().c_str());

	TiXmlElement* translation_ = new TiXmlElement("Up");
	cmr_->LinkEndChild(translation_);
	std::ostringstream ss9; ss9<<cm_->upVector().x();
	std::ostringstream ss10; ss10<<cm_->upVector().y();
	std::ostringstream ss11; ss11<<cm_->upVector().z();
	translation_->SetAttribute("x",(char*)ss9.str().c_str());
	translation_->SetAttribute("y",(char*)ss10.str().c_str());
	translation_->SetAttribute("z",(char*)ss11.str().c_str());

	TiXmlElement* normal_ = new TiXmlElement("Target");
	cmr_->LinkEndChild(normal_);
	std::ostringstream ss12; ss12<<cm_->lookAtPoint().x();
	std::ostringstream ss13; ss13<<cm_->lookAtPoint().y();
	std::ostringstream ss14; ss14<<cm_->lookAtPoint().z();
	normal_->SetAttribute("x",(char*)ss12.str().c_str());
	normal_->SetAttribute("y",(char*)ss13.str().c_str());
	normal_->SetAttribute("z",(char*)ss14.str().c_str());

	TiXmlElement* pMat_ = new TiXmlElement("Width");
	std::ostringstream ss15; ss15<<width;
	pMat_->LinkEndChild(new TiXmlText((char*)ss15.str().c_str()));
	scrn_->LinkEndChild(pMat_);

	TiXmlElement* pTrns_ = new TiXmlElement("Height");
	std::ostringstream ss16; ss16<<height;
	pTrns_->LinkEndChild(new TiXmlText((char*)ss16.str().c_str()));
	scrn_->LinkEndChild(pTrns_);

	TiXmlElement* pSha_ = new TiXmlElement("AntiAlias");
	if(antiAlisng) pSha_->LinkEndChild(new TiXmlText("true"));
	else pSha_->LinkEndChild(new TiXmlText("false"));
	props_->LinkEndChild(pSha_);


	doc.SaveFile("scene.xml");

}

void RenderController::saveRawFiles(Scene* m_scene)
{
	RawDevice* m_raw_device = new RawDevice();
	for(int i=0 ; i<m_scene->objects().size() ; i++)
	{
		std::ostringstream ss;
		ss <<"obj"<<i<<".raw";

		if(m_scene->objects()[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* meshShape_ = static_cast<TriangleMesh*>(m_scene->objects()[i]->getShape());
			m_raw_device->saveMesh(ss.str(),meshShape_);
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

			m_raw_device->saveMesh(ss.str(), meshShape_);
			delete meshShape_;
		}
	}
}
