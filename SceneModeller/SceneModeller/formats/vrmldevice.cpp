#include "vrmldevice.h"


#include "../core/sphere.h"
#include "../core/cube.h"
#include "../core/cone.h"
#include "../core/cylinder.h"
#include "../core/twosidedcylinder.h"
#include "../core/torus.h"

#include "../core/triangleshape.h"
#include "../core/rectangle.h"
#include "../core/circle.h"
#include "../core/disk.h"
#include "../core/partialdisk.h"

#include "../common.h"

#include <iostream>

VrmlDevice::VrmlDevice() : SMIODevice()
{

}
VrmlDevice::~VrmlDevice()
{

}
void VrmlDevice::loadScene(std::string fl_ , Scene* sce_)
{
	SceneGraph *nw_ = new SceneGraph();
	nw_->load((char*)fl_.c_str());

	Node* node_ = nw_->getNodes();

	while(node_)
	{
		std::string ndType_ = node_->getType();

		if (ndType_ == "Transform")
		{
			TransformNode* tnrsNode_ = static_cast<TransformNode*>(node_);
            addTransformNode(sce_,NULL,tnrsNode_);
		}
		else if (ndType_ == "Shape")
		{
			Material* nwMat_ = new Material();
			Shape* shp_  = NULL; 
			ShapeNode* shapeNode_ = static_cast<ShapeNode*>(node_);
			addShapeNode(shp_,nwMat_,shapeNode_);
			if (shp_ != NULL)
			{
				GfxObject* nwObj_ = new GfxObject(shp_,nwMat_,new Transformation());
				*sce_+= nwObj_;
			}
		}
		else if (ndType_ == "Switch")
		{
			SwitchNode* swtNode_ = static_cast<SwitchNode*>(node_);
			Node* switchChild_ = swtNode_->getChildNodes();
			while(switchChild_)
			{
				std::string swtchNodeName_  = switchChild_->getType();
				if (swtchNodeName_ == "Shape")
				{
					Material* nwMat_ = new Material();
					Shape* shp_  = NULL; 
					ShapeNode* shapeNode_ = static_cast<ShapeNode*>(switchChild_);
					addShapeNode(shp_,nwMat_,shapeNode_);
					if (shp_ != NULL)
					{
						GfxObject* nwObj_ = new GfxObject(shp_,nwMat_,new Transformation());
						*sce_+=nwObj_;
					}
				}
				switchChild_ = switchChild_->next();
			}
		}
		else if (ndType_ == "PointLight")
		{
			PointLightNode* pntNode_ = static_cast<PointLightNode*>(node_);
			double rad_ = pntNode_->getRadius();
			float pos_[3];
			pntNode_->getLocation(pos_);
			if (rad_ == 0)
			{
				AreaLight* lght_ = new AreaLight();
				lght_->setPos(Point3(pos_[0],pos_[1],pos_[2]));
				lght_->set_coeff(pntNode_->getIntensity());
				sce_->lights().push_back(lght_);
			}
			else
			{
				PointLight* lght_ = new PointLight();
				lght_->setPos(Point3(pos_[0],pos_[1],pos_[2]));
				lght_->set_coeff(pntNode_->getIntensity());
				sce_->lights().push_back(lght_);
			}
		}
		else if (ndType_ == "Viewpoint")
		{
			ViewpointNode* vpntnd_ = static_cast<ViewpointNode*>(node_);
			float loc_[3];
			float rot_[4];
			vpntnd_->getPosition(loc_);
			vpntnd_->getOrientation(rot_);

			
			Camera* cmr_ = new Camera();

			cmr_->setName(vpntnd_->getName());
			cmr_->setPosition(Point3(loc_[0],loc_[1],loc_[2]));

			//Rotation4 rotation4_(rot_[0],rot_[1],rot_[2],rot_[3]);
			//cmr_->setUpVector(rotation4_.applyToVector(Vector3(0,1,0)).normalize());
			cmr_->setUpVector(RotateVectorAroundVector(Vector3(0,1,0),Vector3(rot_[0],rot_[1],rot_[2]),rot_[3]));

			//Vector3 dir_ = rotation4_.applyToVector(Vector3(0,0,-1)).normalize();
			Vector3 dir_ =RotateVectorAroundVector(Vector3(0,0,-1),Vector3(rot_[0],rot_[1],rot_[2]),rot_[3]).normalize();
			cmr_->setAtPoint(cmr_->position()+10*dir_);

			sce_->cameras().push_back(cmr_);
		}
		node_ = node_->next();
	}
}
void VrmlDevice::loadObject(std::string fl_ , GfxObject* obj_)
{

}
void VrmlDevice::addTransformNode(Scene* scn_,GfxObject* parnt_,TransformNode* tnsNode_)
{
	GfxObject* curretObjct_ = NULL;

	float tr_[3] ;
	float scl_[3];
	float rot_[4];
	float clr_[3];
	Transformation* publicTrns_ = new Transformation();
	tnsNode_->getTranslation(tr_); 
	publicTrns_->translate(tr_[0],tr_[1],tr_[2]);
	tnsNode_->getScale(scl_);
	publicTrns_->scale(scl_[0],scl_[1],scl_[2]);
	tnsNode_->getRotation(rot_);
	publicTrns_->rotate(rot_[0],rot_[1],rot_[2],rot_[3]);

	Node* childNodes_ = tnsNode_->getChildNodes();
	if (childNodes_ && std::string(childNodes_->getType()) == "Transform")
	{
		TransformNode* indTrnsNode_ = static_cast<TransformNode*>(childNodes_);

		Transformation* IndTrns_ = new Transformation();
		indTrnsNode_->getTranslation(tr_); 
		IndTrns_->translate(tr_[0],tr_[1],tr_[2]);
		indTrnsNode_->getScale(scl_);
		IndTrns_->scale(scl_[0],scl_[1],scl_[2]);
		indTrnsNode_->getRotation(rot_);
		IndTrns_->rotate(rot_[0],rot_[1],rot_[2],rot_[3]);

		Node* chlNode_ = indTrnsNode_->getChildNodes();
		if (std::string(chlNode_->getType()) == "Shape")
		{
			ShapeNode* shpNode_ = static_cast<ShapeNode*>(chlNode_);

			Material* mat_ = new Material();
			Shape* shap_ = NULL;

			addShapeNode(shap_,mat_,shpNode_);

			curretObjct_ = new GfxObject(shap_,mat_,publicTrns_,parnt_);
			curretObjct_->setIndividualTransform(IndTrns_);
			curretObjct_->setName(tnsNode_->getName());
			*scn_+=curretObjct_;

			if (parnt_ != NULL)
			{
				parnt_->addChild(curretObjct_);
			}
		}
		childNodes_ = childNodes_->next();
	}
	
	// add childs
	if (childNodes_)
	{
		if (std::string(childNodes_->getType()) == "Group" )
		{
			GroupNode* grpNode_ = static_cast<GroupNode*> (childNodes_);

			childNodes_ = grpNode_->getChildNodes();
			while(childNodes_)
			{
				if ( std::string(childNodes_->getType()) == "Transform")
				{
					TransformNode* tN_ = static_cast<TransformNode*>(childNodes_);
					addTransformNode(scn_,curretObjct_,tN_);
				}
				childNodes_ = childNodes_->next();
			}
		}
	}

}
void VrmlDevice::saveToFile(std::string fl_ , Scene* sce_)
{
	float colorf[3];

	SceneGraph *nw_ = new SceneGraph();

	WorldInfoNode *wi_ = new WorldInfoNode();
	wi_->setTitle("Scene Modeler for Resposive Workbench");
	wi_->addInfo("VRML 2.0 created by Scene Modeler for Resposive Workbench by SERHAT ANGIN");
	nw_->addNode(wi_);

	BackgroundNode *bnde = new BackgroundNode();
	colorf[0] = sce_->backgroundColor().r;
	colorf[1] = sce_->backgroundColor().g;
	colorf[2] = sce_->backgroundColor().b;
	bnde->addSkyColor(colorf);
	nw_->addNode(bnde);

	// save objects
	for(int i=0 ; i<sce_->objects().size() ; i++)
	{
		if( sce_->objects()[i]->getParent() == NULL )
		{
			TransformNode* tnsNode_ = new TransformNode();
			saveToTransformNode(sce_->objects()[i],tnsNode_);
			nw_->addNode(tnsNode_);
		}
	}

	//save lights
	float pos_[3];
	for (int i=0 ; i<sce_->lights().size();i++)
	{
		if (sce_->lights()[i]->type() == POINT_LIGHT)
		{
			PointLightNode* nde_ = new PointLightNode();
			pos_[0]=sce_->lights()[i]->p().x();
			pos_[1]=sce_->lights()[i]->p().y();
			pos_[2]=sce_->lights()[i]->p().z();

			nde_->setRadius(1);
			nde_->setLocation(pos_);
			nw_->addNode(nde_);
		}
		else if(sce_->lights()[i]->type() == AREA_LIGHT) 
		{
			PointLightNode* nde_ = new PointLightNode();
			pos_[0]=sce_->lights()[i]->p().x();
			pos_[1]=sce_->lights()[i]->p().y();
			pos_[2]=sce_->lights()[i]->p().z();

			nde_->setRadius(0);
			nde_->setLocation(pos_);
			nw_->addNode(nde_);
		}
	}

	// save cameras
	for (int i=0 ; i<sce_->cameras().size() ; i++ )
	{
		// calculate camera totation
		Matrix rotationMat; 
		Vector3 vz_ = (sce_->cameras()[i]->atPoint()-sce_->cameras()[i]->position()).normalize();
		Vector3 vx_ = (vz_^sce_->cameras()[i]->upVector()).normalize();
		Vector3 vy_ = sce_->cameras()[i]->upVector();
		rotationMat.setcell(0,0, vx_.x() );
		rotationMat.setcell(0,1, vx_.y() );
		rotationMat.setcell(0,2, vx_.z() );

		rotationMat.setcell(1,0, vy_.x());
		rotationMat.setcell(1,1, vy_.y());
		rotationMat.setcell(1,2, vy_.z());

		rotationMat.setcell(2,0, -(vz_.x()));
		rotationMat.setcell(2,1, -(vz_.y()));
		rotationMat.setcell(2,2, -(vz_.z()));
		Rotation4 rot_;
		rot_.setFromMatrix(rotationMat);

		ViewpointNode* vp_ = new ViewpointNode();
		vp_->setName((char*)sce_->cameras()[i]->getName().c_str());
		vp_->setPosition(sce_->cameras()[i]->position().x(),
			             sce_->cameras()[i]->position().y(),
						 sce_->cameras()[i]->position().z());
		vp_->setOrientation(rot_.ax(),rot_.ay(),rot_.az(),-rot_.theta());

		nw_->addNode(vp_);
	}

	nw_->save((char*)fl_.c_str());
}
void VrmlDevice::addShapeNode(Shape*& shp,Material* mt_,ShapeNode* shpNode_)
{
	// apperance
	AppearanceNode* appNode_ = shpNode_->getAppearanceNodes();
	if (appNode_)
	{
		float color_[3];
		MaterialNode* matNode_ = appNode_->getMaterialNodes();
		if (matNode_)
		{
			matNode_->getDiffuseColor(color_);
			mt_->setDiffColor(TRadiance(color_[0],color_[1],color_[2]));
			matNode_->getSpecularColor(color_);
			mt_->setSpecColor(TRadiance(color_[0],color_[1],color_[2]));
			matNode_->getEmissiveColor(color_);
			mt_->setAmbienColor(TRadiance(color_[0],color_[1],color_[2]));
			mt_->set_luculent(matNode_->getTransparency());
			mt_->set_reflective(matNode_->getShininess());
		}
		TextureNode* txtNode_ = appNode_->getTextureNode();
		if (txtNode_)
		{
			ImageTextureNode* imgN_ = static_cast<ImageTextureNode*>(txtNode_);
			mt_->enableTexture(true);
			mt_->getTexture().m_path = imgN_->getUrl(0);
		}
	}
	// geometry
	GeometryNode* geomNode_ = shpNode_->getGeometry();
	if (geomNode_)
	{
		std::string type_ = geomNode_->getType();
		if (type_ == "Cone")
		{
			ConeNode* cnNode_ = static_cast<ConeNode*>(geomNode_);
			shp = new Cone();
			Cone* cn_ = static_cast<Cone*>(shp);
			cn_->m_h = cnNode_->getHeight();
			cn_->m_r = cnNode_->getBottomRadius();
		}
		else if (type_ == "Box")
		{
			BoxNode* bxNode_ = static_cast<BoxNode*>(geomNode_);
			shp = new Cube();
			Cube* cn_ = static_cast<Cube*>(shp);
			cn_->m_d = bxNode_->getX(); // y and z must be the same
		}
		else if (type_ == "Cylinder")
		{
			CylinderNode* cynl_ = static_cast<CylinderNode*>(geomNode_);
			shp = new Cylinder();
			Cylinder* cn_ = static_cast<Cylinder*>(shp);
			cn_->m_r = cynl_->getRadius();
			cn_->m_h = cynl_->getHeight();
		}
		else if (type_ == "Sphere")
		{
			SphereNode* sphNode_ = static_cast<SphereNode*>(geomNode_);
			shp = new Sphere();
			Sphere* cn_ = static_cast<Sphere*>(shp);
			cn_->m_r = sphNode_->getRadius();
		}
		else if ( type_ == "IndexedFaceSet")
		{
			IndexedFaceSetNode* indFNode_ = static_cast<IndexedFaceSetNode*>(geomNode_);
			shp = new TriangleMesh();
			TriangleMesh* trngMesh_ = static_cast<TriangleMesh*>(shp);

			float vertex_[3];
			CoordinateNode* coordNode_ = indFNode_->getCoordinateNodes();
			for (int i=0 ; i<coordNode_->getPointField()->getSize() ; i++)
			{
				coordNode_->getPoint(i,vertex_);
				trngMesh_->vertexList().push_back(new Vertex(vertex_[0],vertex_[1],vertex_[2]));
			}

			std::vector<int> indexList;
			for ( int i=0 ; i<indFNode_->getCoordIndexField()->getSize() ; i++ )
			{
				int ind_ = indFNode_->getCoordIndexField()->get1Value(i);
				if (ind_ == -1 )
				{
					TriangulateFace(trngMesh_->faceList(),trngMesh_->vertexList(),indexList);
					indexList.clear();
				}
				else
				{
					indexList.push_back(ind_);
				}
			}
			trngMesh_->calculatebounds();
		}
	}
}
void VrmlDevice::TriangulateFace(std::vector<Triangle*>& trList,std::vector<Vertex*>& vrtList,std::vector<int> indList)
{
	if (indList.size() == 3)
	{
		Vertex* v1_ = vrtList[ indList[0] ];
		Vertex* v2_ = vrtList[ indList[1] ];
		Vertex* v3_ = vrtList[ indList[2] ];

		trList.push_back(new Triangle(
			v1_,
			v2_,
			v3_
			));
	}
	else if (indList.size() >3)
	{
		std::vector<int> newList;
		newList.push_back(indList[0]);
		for (int i=1 ; i<indList.size()-1 ; i+=2)
		{
			Vertex* v1_ = vrtList[ indList[i-1] ];
			Vertex* v2_ = vrtList[ indList[i] ];
			Vertex* v3_ = vrtList[ indList[i+1] ];

			trList.push_back(new Triangle(
				v1_,
				v2_,
				v3_
				));
			newList.push_back(indList[i+1]);
		}
		if (indList.size()%2 == 0)
		{
			Vertex* v1_ = vrtList[ indList[indList.size()-2] ];
			Vertex* v2_ = vrtList[ indList[indList.size()-1] ];
			Vertex* v3_ = vrtList[ indList[0] ];
			trList.push_back(new Triangle(
				v1_,
				v2_,
				v3_
				));
		}
		TriangulateFace(trList,vrtList,newList);
	}
}
void VrmlDevice::createShapeNode(Shape* shp_,Material* mt_,ShapeNode* shpNode_)
{
	AppearanceNode* appNde_ = new AppearanceNode();
	MaterialNode* mtrlNde_ = new MaterialNode();

	float colorf[3];

	colorf[0] = mt_->diffcolor().r;
	colorf[1] = mt_->diffcolor().g;
	colorf[2] = mt_->diffcolor().b;
	mtrlNde_->setDiffuseColor(colorf);

	colorf[0] = mt_->speccolor().r;
	colorf[1] = mt_->speccolor().g;
	colorf[2] = mt_->speccolor().b;
	mtrlNde_->setSpecularColor(colorf);

	colorf[0] = mt_->ambientcolor().r;
	colorf[1] = mt_->ambientcolor().g;
	colorf[2] = mt_->ambientcolor().b;
	mtrlNde_->setEmissiveColor(colorf);

	mtrlNde_->setTransparency(mt_->luculent());
	mtrlNde_->setShininess(mt_->reflection());

	appNde_->addChildNode(mtrlNde_);

	if(mt_->isTextureEnabled())
	{
		ImageTextureNode* img_ = new ImageTextureNode();
		img_->addUrl((char*)mt_->getTexture().m_path.c_str());
		appNde_->addChildNode(img_);
	}
	shpNode_->addChildNode(appNde_);

	if (shp_->type() == SPHERE)
	{
		Sphere* sph_ = static_cast<Sphere*>(shp_);
		SphereNode* spN_ = new SphereNode();
		spN_->setRadius(sph_->m_r);
		shpNode_->addChildNode(spN_);
	}
	else if(shp_->type() == CUBE)
	{
		Cube* cb_ = static_cast<Cube*>(shp_);
		BoxNode* bxN_ = new BoxNode();
		bxN_->setSize(cb_->m_d,cb_->m_d,cb_->m_d);
		shpNode_->addChildNode(bxN_);
	}
	else if(shp_->type() == CONE)
	{
		Cone* cb_ = static_cast<Cone*>(shp_);
		ConeNode* cnN_ = new ConeNode();
		cnN_->setBottomRadius(cb_->m_r);
		cnN_->setHeight(cb_->m_h);
		shpNode_->addChildNode(cnN_);
	}
	else if(shp_->type() == CYLINDER)
	{
		Cylinder* cy_ = static_cast<Cylinder*>(shp_);
		CylinderNode* cyN_ = new CylinderNode();
		cyN_->setRadius(cy_->m_r);
		cyN_->setHeight(cy_->m_h);
		shpNode_->addChildNode(cyN_);
	}
	else if (shp_->type() == TRIANGLE_MESH)
	{
		TriangleMesh* msh_ = static_cast<TriangleMesh*>(shp_);
		IndexedFaceSetNode* nwNode_ = new IndexedFaceSetNode();
		saveMeshToIndexedSet(msh_,nwNode_);
		shpNode_->addChildNode(nwNode_);
	}
	else
	{
		TwoSidedCylinder* twcyl_;
		Torus* trs_; 
		TriangleShape* trngshp_;
		RectangleShape* rect_;
		Circle* circle_;
		Disk* disk_;
		PartialDisk* pdisk_;

		TriangleMesh* meshShape_ = new TriangleMesh();
		switch(shp_->type())
		{
		case TWO_SIDED_CYLINDER:
			twcyl_ = static_cast<TwoSidedCylinder*>(shp_);
			twcyl_->copyToMesh(meshShape_);
			break;
		case TORUS:
			trs_ = static_cast<Torus*>(shp_);
			trs_->copyToMesh(meshShape_);
			break;
		case TRIANGLE_SHAPE:
			trngshp_ = static_cast<TriangleShape*>(shp_);
			trngshp_->copyToMesh(meshShape_);
			break;
		case RECTANGLE:
			rect_ = static_cast<RectangleShape*>(shp_);
			rect_->copyToMesh(meshShape_);
			break;
		case CIRCLE:
			circle_ = static_cast<Circle*>(shp_);
			circle_->copyToMesh(meshShape_);
			break;
		case DISK:
			disk_ = static_cast<Disk*>(shp_);
			disk_->copyToMesh(meshShape_);
			break;
		case PARTIAL_DISK:
			pdisk_ = static_cast<PartialDisk*>(shp_);
			pdisk_->copyToMesh(meshShape_);
			break;
		default:
			break;
		}

		IndexedFaceSetNode* nwNode_ = new IndexedFaceSetNode();
		saveMeshToIndexedSet(meshShape_,nwNode_);
		shpNode_->addChildNode(nwNode_);

		delete meshShape_;
	}
}
void VrmlDevice::saveMeshToIndexedSet(TriangleMesh* msh_ , IndexedFaceSetNode* fst_)
{

	CoordinateNode* coord_= new CoordinateNode(); 
	float vertexf[3];
	std::map<std::string,int> vertexHash_;

	for (int k=0 ; k< msh_->vertexList().size() ; k++)
	{
		std::ostringstream ss;

		vertexf[0] = msh_->vertexList()[k]->x();
		vertexf[1] = msh_->vertexList()[k]->y();
		vertexf[2] = msh_->vertexList()[k]->z();


		coord_->addPoint(vertexf);

		ss << msh_->vertexList()[k]->x() <<";"<< msh_->vertexList()[k]->y() <<";"<< msh_->vertexList()[k]->z() ; 

		vertexHash_.insert(std::pair<std::string,int>(ss.str(),k));
	}

	for (int k=0 ; k< msh_->faceList().size() ; k++)
	{
		std::ostringstream ss;
		ss << msh_->faceList()[k]->a()->x() <<";"<< msh_->faceList()[k]->a()->y() <<";"<< msh_->faceList()[k]->a()->z() ;
		fst_->getCoordIndexField()->addValue(vertexHash_.find(ss.str())->second);

		std::ostringstream ss1;
		ss1 << msh_->faceList()[k]->b()->x() <<";"<< msh_->faceList()[k]->b()->y() <<";"<< msh_->faceList()[k]->b()->z() ;
		fst_->getCoordIndexField()->addValue(vertexHash_.find(ss1.str())->second);

		std::ostringstream ss2;
		ss2 << msh_->faceList()[k]->c()->x() <<";"<< msh_->faceList()[k]->c()->y() <<";"<< msh_->faceList()[k]->c()->z() ;
		fst_->getCoordIndexField()->addValue(vertexHash_.find(ss2.str())->second);

		fst_->getCoordIndexField()->addValue(-1);
	}

	fst_->addChildNode(coord_);
}
void VrmlDevice::saveToTransformNode( GfxObject* obj_ , TransformNode *nde_ )
{
	float colorf[3];
	float rot_[4];
	float scl_[3];
	float trs_[3];

	nde_->setName((char*)obj_->getName().c_str());

	Transformation* crnTrans_ = obj_->getPublicTranform();
	Material* crntMat_ = obj_->getMaterial();
	Shape* crnShp_ = obj_->getShape();

	// public
	rot_[0]=crnTrans_->rotation().ax();
	rot_[1]=crnTrans_->rotation().ay();
	rot_[2]=crnTrans_->rotation().az();
	rot_[3]=crnTrans_->rotation().theta();
	nde_->setRotation(rot_);

	scl_[0] = crnTrans_->scale().x();
	scl_[1] = crnTrans_->scale().y();
	scl_[2] = crnTrans_->scale().z();
	nde_->setScale(scl_);

	trs_[0] = crnTrans_->translation().x();
	trs_[1] = crnTrans_->translation().y();
	trs_[2] = crnTrans_->translation().z();
	nde_->setTranslation(trs_);

	// individual
	crnTrans_ = obj_->getIndividualTranform();
	TransformNode* trnsNode1_ = new TransformNode();
	rot_[0]=crnTrans_->rotation().ax();
	rot_[1]=crnTrans_->rotation().ay();
	rot_[2]=crnTrans_->rotation().az();
	rot_[3]=crnTrans_->rotation().theta();
	trnsNode1_->setRotation(rot_);

	scl_[0] = crnTrans_->scale().x();
	scl_[1] = crnTrans_->scale().y();
	scl_[2] = crnTrans_->scale().z();
	trnsNode1_->setScale(scl_);

	trs_[0] = crnTrans_->translation().x();
	trs_[1] = crnTrans_->translation().y();
	trs_[2] = crnTrans_->translation().z();
	trnsNode1_->setTranslation(trs_);

	ShapeNode* shpNode_ = new ShapeNode();
	createShapeNode(crnShp_,crntMat_,shpNode_);
	trnsNode1_->addChildNode(shpNode_);
	nde_->addChildNode(trnsNode1_,true);

	if(obj_->getChildList().size()>0)
	{
		GroupNode* grpNode_ = new GroupNode();
		for (int i=0 ; i< obj_->getChildList().size() ; i++)
		{
			TransformNode* newTrns_ = new TransformNode();
			saveToTransformNode(obj_->getChildList()[i],newTrns_);
			grpNode_->addChildNode(newTrns_);
		}
		nde_->addChildNode(grpNode_);
	}
}