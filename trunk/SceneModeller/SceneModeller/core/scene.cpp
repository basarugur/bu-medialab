#include "scene.h"





Scene::Scene()
{		
	initialize();

	m_selected_tree_root = NULL;

	m_add_child_tmp = NULL;

	//m_light     = new PointLight(Point3(0,5,0),Vector3(0,-1,0));		
	m_screen    = new Screen(600,600);
	m_sampler   = new Sampler(15,15,-5,m_screen);
	m_camera    = new Perspective(Point3(0,0,-20),Vector3(0,1,0),Point3(0,0,0));


	//will added proper aggregate;
	m_aggregate = new Aggregate();
}
Scene::Scene(std::vector<Light*>& l,Camera* c,Sampler* s,Aggregate* a) :
m_camera(c),m_sampler(s),m_aggregate(a)
{		
	m_lights = l;
	initialize();
};


Scene::~Scene()
{	
}
void Scene::initialize()
{
	m_background_color.r = 0.6;
	m_background_color.g = 0.6;
	m_background_color.b = 0.6;

	m_background = TRadiance(1.0,1.0,1.0);
	m_intersection = new Intersection();
	m_aa_on = false;	
}

void Scene::clearAllSelections()
{
	clearobjectSelections();
	clearTreeSelection();
	clearCameraSelection();
	clearLightSelection();
	clearFaceSelections();
	clearVertexSelections();
}

void Scene::addToChild(GfxObject* obj_)
{
	if(m_add_child_tmp != NULL)
	{
		obj_->addChild(m_add_child_tmp);
		m_add_child_tmp = NULL;
	}
	else
	{
		m_add_child_tmp = obj_;
	}
}
GfxObject* Scene::getTmpChild()
{
	return m_add_child_tmp;
}
void Scene::setTmpChild(GfxObject* obj_)
{
	m_add_child_tmp = obj_ ;
}
void Scene::clearobjectSelections()
{
	for(int i=0 ; i<m_primitves.size(); i++)
		m_primitves[i]->select(false);
}
void Scene::clearLightSelection()
{
	for(int i=0 ; i<m_lights.size(); i++)
		m_lights[i]->select(false);
}
Camera* Scene::getSelectedCamera()
{
	for(int i=0 ; i<m_cameras.size(); i++)
		if(m_cameras[i]->isSelected())
			return m_cameras[i];
	return NULL;
}
void Scene::deleteSelectedCamera()
{
	for(int i=0 ; i<m_cameras.size(); i++)
		if(m_cameras[i]->isSelected())
		{
			delete m_cameras[i];
			m_cameras.erase(m_cameras.begin()+i);
			i--;
		}
}
void Scene::duplicateSelectedCamera()
{
	for(int i=0 ; i<m_cameras.size(); i++)
		if(m_cameras[i]->isSelected())
		{
			Camera* nwCmr_ = new Camera();
			nwCmr_->setPosition(m_cameras[i]->position()+Point3(1,1,1));
			nwCmr_->setName(m_cameras[i]->getName());
			nwCmr_->setUpVector(m_cameras[i]->upVector());
			nwCmr_->setAtPoint(m_cameras[i]->atPoint()+Point3(1,1,1));

			m_cameras.push_back(nwCmr_);
		}
}
void Scene::clearCameraSelection()
{
	for(int i=0 ; i<m_cameras.size(); i++)
		m_cameras[i]->select(false);
}
void Scene::clearTreeSelection()
{
	clearobjectSelections();
	m_selected_tree_root = NULL;
}
GfxObject* Scene::getSelectedTreeRoot()
{
	return m_selected_tree_root;
}
GfxObject* Scene::getSelectedObject()
{
	for(int i=0 ; i<m_primitves.size(); i++)
		if(m_primitves[i]->isSelected())
			return m_primitves[i];
	return NULL;
}
Light* Scene::getSelectedLight()
{
	for(int i=0 ; i<m_lights.size(); i++)
		if(m_lights[i]->isSelected())
			return m_lights[i];
	return NULL;
}
void Scene::deleteSelectedTree()
{
	if(m_selected_tree_root != NULL)
	{
		if(m_selected_tree_root->getParent() != NULL)
		{
			m_selected_tree_root->getParent()->removeChildAt(m_selected_tree_root->getChildIndex());
		}
		deleteSelectedObject();
		m_selected_tree_root = NULL ; 
	}
}
void Scene::duplicateSelectedTree()
{
	if(m_selected_tree_root != NULL)
	{
		GfxObject* nwObj_;
		m_selected_tree_root->getCopy(nwObj_);
		nwObj_->getPublicTranform()->translate(
			nwObj_->getPublicTranform()->translation().x()+1,
			nwObj_->getPublicTranform()->translation().y()+1,
			nwObj_->getPublicTranform()->translation().z()+1
			);
		m_primitves.push_back(nwObj_);
		for(int i=0 ; i<m_selected_tree_root->getChildList().size();i++)
			duplicateTree(m_selected_tree_root->getChildList()[i],nwObj_);
	}
}
void Scene::duplicateTree(GfxObject* obj_,GfxObject* nwPrnt_)
{
	GfxObject* nwObj_;
	obj_->getCopy(nwObj_);
	nwPrnt_->addChild(nwObj_);
	m_primitves.push_back(nwObj_);
	for(int i=0 ; i<obj_->getChildList().size();i++)
			duplicateTree(obj_->getChildList()[i],nwObj_);
}
void Scene::deleteSelectedObject()
{
	for(int i=0 ; i<m_primitves.size(); i++)
		if(m_primitves[i]->isSelected())
		{
			delete m_primitves[i];
			m_primitves.erase(m_primitves.begin()+i);
			i--;
		}
}
void Scene::deleteSelectedLight()
{
	for(int i=0 ; i<m_lights.size(); i++)
		if(m_lights[i]->isSelected())
		{
			delete m_lights[i];
			m_lights.erase(m_lights.begin()+i);
			i--;
		}
}
void Scene::duplicateSelectedLight()
{
	for(int i=0 ; i<m_lights.size(); i++)
		if(m_lights[i]->isSelected())
		{
			if(m_lights[i]->type() == POINT_LIGHT)
			{
				PointLight* pnt_ = new PointLight();
				pnt_->setPos(Point3(m_lights[i]->p().x()+1,
					                m_lights[i]->p().y()+1,
									m_lights[i]->p().z()+1));

				m_lights.push_back(pnt_);
			}
			else
			{
				AreaLight* are1_  = static_cast<AreaLight*>(m_lights[i]);
				AreaLight* are_  = new AreaLight();
				are_->setPos(Point3(m_lights[i]->p().x()+1,
					                m_lights[i]->p().y()+1,
									m_lights[i]->p().z()+1));
				are_->setH(are1_->h());
				are_->setW(are1_->w());

				m_lights.push_back(are_);
			}
		}
}
void Scene::duplicateSelectedObject()
{
	GfxObject* slected_ = getSelectedObject();
	if(slected_ != NULL)
	{
		GfxObject* nwObj_;
		slected_->getCopy(nwObj_);
		nwObj_->getIndividualTranform()->translate(
			nwObj_->getIndividualTranform()->translation().x()+1,
			nwObj_->getIndividualTranform()->translation().y()+1,
			nwObj_->getIndividualTranform()->translation().z()+1
			);
		m_primitves.push_back(nwObj_);
	}
}
GfxObject* Scene::traverseTree(int ind_)
{
	GfxObject* obj_ = NULL;

	m_tree_traverse_counter = 1;
	for(int i=0 ; i<m_primitves.size();i++)
			if(m_primitves[i]->getParent() == NULL)
			{
				if( (obj_ = traverseObject(ind_,m_primitves[i]))!= NULL)
					break;
			}
	return obj_;
}
GfxObject* Scene::traverseObject(int ind_,GfxObject* obj_)
{
	GfxObject* res_ = NULL;

	if(m_tree_traverse_counter == ind_)
		res_ = obj_;
	else
	{
		m_tree_traverse_counter++;
		for(int i=0 ; i<obj_->getChildList().size();i++)
			if( (res_ = traverseObject(ind_,obj_->getChildList()[i]))!= NULL)
				break;
	}
	return res_ ; 
}
void Scene::selectTree(GfxObject* obj_)
{
	if(m_selected_tree_root == NULL) m_selected_tree_root = obj_ ; 
	obj_->select(true);
	for(int i=0 ; i< obj_->getChildList().size() ;i++)
		selectTree(obj_->getChildList()[i]);
}
// for face
void Scene::clearFaceSelections()
{
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			ms_->clearFaceSelections();
		}
	}
}
int Scene::totalFaceCount()
{
	int rslt_ = 0;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			rslt_ += ms_->faceList().size();
		}
	}
	return rslt_;
}
int Scene::totalVertexCount()
{
	int rslt_ = 0;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			rslt_ += ms_->vertexList().size();
		}
	}
	return rslt_;
}
Triangle* Scene::getSelectedFace()
{
	Triangle* trng_ = NULL;
	std::vector<Triangle*> fc_ ;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			fc_ = ms_->getSelectedFaceList();
			if (fc_.size() != 0)
			{
				trng_ = fc_[0];
				break;
			}
		}
	}
	return trng_;
}
void Scene::splitSelectedFace()
{
	std::vector<Triangle*> fc_ ;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			fc_ = ms_->getSelectedFaceList();
			if (fc_.size() != 0)
			{
				Triangle* original_ = fc_[0];
				Vertex* v1_ = original_->a();
				Vertex* v2_ = original_->b();
				Vertex* v3_ = original_->c();

				Vertex* vm_ = new Vertex(original_->mid().x(),original_->mid().y(),original_->mid().z());
				ms_->vertexList().push_back(vm_);

				ms_->faceList().push_back(new Triangle(v1_,v2_,vm_));
				ms_->faceList().push_back(new Triangle(v2_,v3_,vm_));
				ms_->faceList()[ms_->faceList().size()-1]->restoreNormalAndMidPoint();
				ms_->faceList()[ms_->faceList().size()-2]->restoreNormalAndMidPoint();

				original_->setB(vm_);
				original_->restoreNormalAndMidPoint();
				break;
			}
		}
	}
}
void Scene::deleteSelectedFace()
{
	std::vector<Triangle*> fc_ ;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			for (int k=0 ; k<ms_->faceList().size() ; k++)
			{
				if (ms_->faceList()[k]->isSelected())
				{
					Triangle* slected_ = ms_->faceList()[k];

					int isUsA_ = 1;
					int isUsB_ = 1;
					int isUsC_ = 1;

					for(int m=0 ;m<ms_->faceList().size();m++)
					{
						if (m != k)
						{
							if (*ms_->faceList()[m]->a() == *slected_->a() ||
								*ms_->faceList()[m]->b() == *slected_->a() ||
								*ms_->faceList()[m]->c() == *slected_->a())
							{
								isUsA_ = -1;
							}
							if (*ms_->faceList()[m]->a() == *slected_->b() ||
								*ms_->faceList()[m]->b() == *slected_->b() ||
								*ms_->faceList()[m]->c() == *slected_->b())
							{
								isUsB_ = -1;
							}
							if (*ms_->faceList()[m]->a() == *slected_->c() ||
								*ms_->faceList()[m]->b() == *slected_->c() ||
								*ms_->faceList()[m]->c() == *slected_->c())
							{
								isUsC_ = -1;
							}
						}
					}

					for (int m=0 ; m<ms_->vertexList().size() ; m++)
					{
						if (isUsA_==1 && *ms_->vertexList()[m] == *slected_->a())
						{
							delete ms_->vertexList()[m];
							ms_->vertexList().erase(ms_->vertexList().begin()+m);
							m--;
						}
						if (isUsB_==1 && *ms_->vertexList()[m] == *slected_->b())
						{
							delete ms_->vertexList()[m];
							ms_->vertexList().erase(ms_->vertexList().begin()+m);
							m--;
						}
						if (isUsC_==1 && *ms_->vertexList()[m] == *slected_->c())
						{
							delete ms_->vertexList()[m];
							ms_->vertexList().erase(ms_->vertexList().begin()+m);
							m--;
						}
					}


					delete slected_;
					ms_->faceList().erase(ms_->faceList().begin() + k);
					break;
				}
			}
		}
	}
}
void Scene::restoreTriangles()
{
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			ms_->restoreTriangles();
		}
	}
}
Triangle* Scene::getExtrudingFace()
{

	std::vector<Triangle*> fc_ ;
	Triangle* original_ = NULL;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			fc_ = ms_->getSelectedFaceList();
			if (fc_.size() != 0)
			{
				original_ = fc_[0];

				Vertex* prev_v1_=original_->a();
				Vertex* prev_v2_=original_->b();
				Vertex* prev_v3_=original_->c();

				Vertex* new_v1_ = new Vertex(prev_v1_->x(),prev_v1_->y(),prev_v1_->z());
				Vertex* new_v2_ = new Vertex(prev_v2_->x(),prev_v2_->y(),prev_v2_->z());
				Vertex* new_v3_ = new Vertex(prev_v3_->x(),prev_v3_->y(),prev_v3_->z());

				ms_->vertexList().push_back(new_v1_);
				ms_->vertexList().push_back(new_v2_);
				ms_->vertexList().push_back(new_v3_);

				ms_->faceList().push_back(new Triangle(new_v1_,prev_v1_,new_v2_));
				ms_->faceList().push_back(new Triangle(new_v2_,prev_v1_,original_->b()));

				ms_->faceList().push_back(new Triangle(new_v2_,prev_v2_,new_v3_));
				ms_->faceList().push_back(new Triangle(new_v3_,prev_v2_,prev_v3_));

				ms_->faceList().push_back(new Triangle(new_v3_,prev_v3_,new_v1_));
				ms_->faceList().push_back(new Triangle(new_v1_,prev_v3_,prev_v1_));


				original_->setA(new_v1_);
				original_->setB(new_v2_);
				original_->setC(new_v3_);

				original_->restoreNormalAndMidPoint();

				break;
			}
		}
	}
	return original_;
}

// for Vertex
void Scene::clearVertexSelections()
{
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			ms_->clearVertexSelections();
		}
	}
}
Vertex* Scene::getSelectedVertex()
{
	Vertex* trng_ = NULL;
	std::vector<Vertex*> fc_ ;
	for (int i=0 ; i<m_primitves.size();i++)
	{
		if (m_primitves[i]->getShape()->type() == TRIANGLE_MESH)
		{
			TriangleMesh* ms_ = static_cast<TriangleMesh*>(m_primitves[i]->getShape());
			fc_ = ms_->getSelectedVertexList();
			if (fc_.size() != 0)
			{
				trng_ = fc_[0];
				break;
			}
		}
	}
	return trng_;
}
void Scene::clearScene()
{
	for (int i=0 ; i<m_primitves.size();i++)
	{
		delete m_primitves[i];
	}
	m_primitves.clear();

	for (int i=0 ; i<m_lights.size(); i++)
	{
		delete m_lights[i];
	}
	m_lights.clear();

	for (int i=0 ; i<m_cameras.size(); i++)
	{
		delete m_cameras[i];
	}
	m_cameras.clear();

	m_add_child_tmp = NULL;
	m_selected_tree_root = NULL;
	m_tree_traverse_counter = -1;
}


void Scene::render()
{	
	const Screen* scr = m_sampler->screen();

	char timeStr [9];
	_strtime( timeStr );
	std::cout << "> " << timeStr << " : "<< "rendering..." << std::endl;	
	CImg<unsigned char>* image = new CImg<unsigned char>(scr->width(),scr->height(),1,3,255);
	CImgDisplay disp(*image,"pbrt - ufuk tiryaki @ bogazici university");
	const unsigned char black[] = { 0,0,0 };
	const unsigned char white[] = { 255,255,255 };	

	for(int x=0;x<scr->width();x++)
	{
		for(int y=0;y<scr->height();y++)
		{		
			Ray r;
			m_sampler->next(x,y);
			m_camera->generate_ray(m_sampler,r);
			TRadiance rd = l(r);
			scr->set_color(rd,x,y);		

			(*image)(scr->width() - 1 - x,scr->height() - 1 - y,0) = 255*scr->buffer(x,y).r;
			(*image)(scr->width() - 1 - x,scr->height() - 1 - y,1) = 255*scr->buffer(x,y).g;
			(*image)(scr->width() - 1 - x,scr->height() - 1 - y,2) = 255*scr->buffer(x,y).b;
		}			
		disp.display(*image);
	}

	_strtime( timeStr );
	std::cout << "> " << timeStr << " : "<< "rendering completed." << std::endl;

	if(m_aa_on == true) {

		Screen* scr_aa = new Screen(scr->width(),scr->height());

		_strtime( timeStr );
		std::cout << "> " << timeStr << " : "<< "anti-aliasing performing...!" << std::endl;

		for(int x=0;x<scr->width();x++)
		{
			for(int y=0;y<scr->height();y++)
			{	
				anti_alias(scr_aa,x,y);

				(*image)(scr_aa->width() - 1 - x,scr_aa->height() - 1 - y,0) = 255*scr_aa->buffer(x,y).r;
				(*image)(scr_aa->width() - 1 - x,scr_aa->height() - 1 - y,1) = 255*scr_aa->buffer(x,y).g;
				(*image)(scr_aa->width() - 1 - x,scr_aa->height() - 1 - y,2) = 255*scr_aa->buffer(x,y).b;
			}

			if (x < (scr->width()-1)) {
				//red line.
				for(int j=0;j<scr->height();j++) {
					(*image)(scr_aa->width() - 2 - x,j,0) = 255;
					(*image)(scr_aa->width() - 2 - x,j,1) = 0;
					(*image)(scr_aa->width() - 2 - x,j,2) = 0;
				}
			}

			disp.display(*image);
		}


		_strtime( timeStr );
		std::cout << "> " << timeStr << " : "<< "anti-aliasing completed." << std::endl;

	}

	image->blur(0.5);
	image->draw_text("ufuk tiryaki 2009 - bogazici university",1,1,white,black,8);
	disp.display(*image);
	image->save_bmp("c:/output.bmp");
	while(!disp.is_closed) disp.wait();		
}

bool Scene::light_intersect(const Ray& r) 
{
	bool ret = false;
	for(int i=0;i<m_lights.size();i++) {
		if(m_lights[i]->intersect(r) == true)
			ret |= true;
	}

	return ret;
}

TRadiance Scene::l(const Ray& r)
{	
	if (intersect(r,m_intersection) == true) {					
		return calculate_illumination(r,m_intersection);
	} else {			
		if(light_intersect(r) == true)
			return TRadiance(1.0,1.0,1.0);

		return m_background;
	}
}

//recursive ray trace...
TRadiance Scene::calculate_illumination(const Ray& r,Intersection* isect,int depth,double n1) {

	TRadiance shade_color;
	TRadiance reflection_color;
	TRadiance refraction_color;

	DifferentialGeometry* dfg = isect->dg();
	Material* m = dfg->material();
	shade_color = calculate_shadow(r,isect);

	if(depth < 6) {

		if(m->reflective() == true) {

			Ray rr = r.reflect(dfg->n(),dfg->p());
			Intersection* is = new Intersection();

			if(intersect(rr,is) == true) {
				reflection_color = calculate_illumination(rr,is,depth+1);										
			} else { 					
				if(light_intersect(rr) == true)
					reflection_color = TRadiance(1.0,1.0,1.0);
				else
					reflection_color = m_background;
			}

			delete is;
		}	

		if(m->transparent() == true) {

			bool reflected = false;
			Ray rr = r.refract(dfg->n(),dfg->p(),n1,dfg->material()->refraction_index(),reflected);
			Intersection* is = new Intersection();

			if(reflected == false) {

				if(intersect(rr,is) == true) {

					if(is->dg()->material()->transparent() == true) {

						Ray rt = rr.refract(is->dg()->n(),is->dg()->p(),is->dg()->material()->refraction_index(),n1,reflected);

						while(reflected == true) {

							if(intersect(rt,is) == true)
								rt = rt.refract(is->dg()->n(),is->dg()->p(),is->dg()->material()->refraction_index(),n1,reflected);
						}

						if (intersect(rt,is) == true)
							refraction_color = calculate_illumination(rt,is,depth+1,n1);
						else {
							if(light_intersect(rt) == true)
								refraction_color = TRadiance(1.0,1.0,1.0);
							else
								refraction_color = m_background;
						}
					}												
				}
			} 

			delete is;
		} 

	}

	TRadiance res = reflection_color*m->reflection() + shade_color*m->solid() + refraction_color*m->luculent();
	res.normalize();
	return res;
}

TRadiance Scene::calculate_shadow(const Ray& r,Intersection* isect) {

	TRadiance res_radiance;

	for(int i=0;i<m_lights.size();i++) {
		if(m_lights[i]->type() == 0)				
			res_radiance = res_radiance + calculate_hardshadow(r,isect,m_lights[i])*m_lights[i]->coeff();			

		if(m_lights[i]->type() == 1)
			res_radiance = res_radiance + calculate_softshadow(r,isect,m_lights[i])*m_lights[i]->coeff();

		if(m_lights[i]->type() == 2)
			res_radiance = res_radiance + calculate_ambient_occlusion(r,isect,m_lights[i])*m_lights[i]->coeff();
	}

	res_radiance.normalize();
	return res_radiance;
}

TRadiance Scene::calculate_hardshadow(const Ray& r,Intersection* isect,Light* light) {

	Point3 pp = light->p();
	Point3 pp2= isect->dg()->p();			
	Vector3 dv = (pp-pp2);

	Ray sr(pp2,dv);			
	sr.set_maxt(dv.length());

	if(intersectp(sr) == true) {
		return TRadiance(light->s(r,isect->dg()));		
	}
	else {
		return TRadiance(light->l(r,isect->dg()));								 		
	}
}

TRadiance Scene::calculate_softshadow(const Ray& r,Intersection* isect,Light* light) {

	int shadow_sample = 128;
	Point3 pp2= isect->dg()->p();
	Normal3 nn= isect->dg()->n();
	TRadiance color_avg;
	bool is_shadow = true;
	bool is_litted = true;
	Intersection *is = new Intersection();		

	for(int i=0;i<16;i++)
	{
		Point3 pp = light->pick_point();						
		Vector3 dv = (pp-pp2);
		Ray sr(pp2,dv);
		sr.set_maxt(dv.length());

		if(intersectp(sr) == true) {
			is_litted &= false;
			is_shadow &= true;
		} else {
			is_shadow &= false;
			is_litted &= true;
		}

	}

	if ( (is_shadow == false) && (is_litted == false))
	{
		for(int i=0;i<shadow_sample;i++)
		{
			Point3 pp = light->pick_point();						
			Vector3 dv = (pp-pp2);
			Ray sr(pp2,dv);
			sr.set_maxt(dv.length());

			if(intersectp(sr) == true) {
				color_avg = color_avg + light->s(r,isect->dg());
			} else {
				color_avg = color_avg + light->l(r,isect->dg());
			}
		}

		color_avg = color_avg / (double)shadow_sample;
		return color_avg;			
	}

	if ((is_shadow == true) && (is_litted == false)) {
		return light->s(r,isect->dg());		 		
	} 

	if ((is_litted == true) && (is_shadow == false)) { 
		return light->l(r,isect->dg());
	}



}

TRadiance Scene::calculate_ambient_occlusion(const Ray& r,Intersection* isect,Light* light) {

	TRadiance rd = light->l(r,isect->dg());
	Point3  p = isect->dg()->p();
	Normal3 n = isect->dg()->n();
	double vo = 0;
	int sample = 225;	
	Vector3* samples = new Vector3[225];
	random_stratified(samples,15);

	Vector3 h(1,0,0);
	if (( abs(n*h) <= 1 + ZERO ) && ( abs(n*h) >= 1 - ZERO )) 
		h = Vector3(1,1,0);

	Vector3 u = (n ^ h).normalize();
	Vector3 v = n ^ u;	

	for(int i=0;i<sample;i++) {

		double e1 = samples[i].x();
		double e2 = samples[i].y();
		double x = sqrt(e1)*cos(e2*2*PI);
		double y = sqrt(e1)*sin(e2*2*PI);					
		double z = sqrt(max(0.f,1.f - x*x - y*y));
		Vector3 vv = x*u + y*v + z*n;			
		Ray rr(p,vv);

		if(intersectp(rr) == false) {
			vo += 1;
		} 
	}		

	delete[] samples;
	vo = vo / (double)sample;	
	return rd*vo;
}


bool Scene::intersect(const Ray& ray,Intersection* isect) const {		
	return m_aggregate->intersect(ray,isect);		
}		

bool Scene::intersectp(const Ray& ray) const {
	return m_aggregate->intersectp(ray);	
}


void Scene::anti_alias(Screen* s,int x, int y) {

	const Screen* scr = m_sampler->screen();

	m_sampler->next(x,y);
	s->set_color(scr->buffer(x,y),x,y);
	double threshold = 0.5;

	if ( ((x-1) >=0) && ((y-1) >=0) && ((y+1) < scr->height()) &&  ((x+1) < scr->width())) {

		bool performaa = false;
		TRadiance m[9];

		m[0] = scr->buffer(x-1,y-1); m[1] = scr->buffer(x-1,y);	m[2] = scr->buffer(x-1,y+1);
		m[3] = scr->buffer(x,y-1); 	 m[4] = scr->buffer(x,y);	m[5] = scr->buffer(x,y+1);
		m[6] = scr->buffer(x+1,y-1); m[7] = scr->buffer(x+1,y);	m[8] = scr->buffer(x+1,y+1);

		double maxx,minn;						
		double data_r[9];
		double data_g[9];
		double data_b[9];

		for(int i=0;i<9;i++) {
			data_r[i] = m[i].r;	data_g[i] = m[i].g;	data_b[i] = m[i].b;
		}

		double ll = 0.0;

		//sobel matrix is used to detect edges.
		double g = abs( (data_r[0] + 2*data_r[1] + data_r[2]) - (data_r[6] + 2*data_r[7] + data_r[8]) ) +
			abs( (data_r[2] + 2*data_r[5] + data_r[8]) - (data_r[0] + 2*data_r[3] + data_r[6]) );

		if (g > threshold) performaa = true;
		if (g > ll) ll = g;

		g = abs( (data_g[0] + 2*data_g[1] + data_g[2]) - (data_g[6] + 2*data_g[7] + data_g[8]) ) +
			abs( (data_g[2] + 2*data_g[5] + data_g[8]) - (data_g[0] + 2*data_g[3] + data_g[6]) );

		if (g > threshold) performaa = true;
		if (g > ll) ll = g;

		g = abs( (data_b[0] + 2*data_b[1] + data_b[2]) - (data_b[6] + 2*data_b[7] + data_b[8]) ) +
			abs( (data_b[2] + 2*data_b[5] + data_b[8]) - (data_b[0] + 2*data_b[3] + data_b[6]) );

		if (g > threshold) performaa = true;
		if (g > ll) ll = g;

		if(performaa == true) {

			TRadiance aac;
			int count = 1;

			if((ll <= 1.0) && (ll > 0.5)) count = 4;
			if((ll <= 2.0) && (ll > 1.0)) count = 9;
			if((ll <= 3.0) && (ll > 2.0)) count = 16;
			if(ll>3.0) count = 25;

			Vector3* samples = new Vector3[count];
			Ray* rays = new Ray[count];

			random_stratified(samples,sqrt((double)count));

			m_camera->generate_rays(m_sampler,rays,samples,count);

			for(int i=0;i<count;i++) { 								
				aac = aac + l(rays[i]);								
			}

			aac = aac / (double)count;
			s->set_color(aac,x,y);
			//s->set_color(TRadiance(1.0,0.0,0.0),x,y);
		} 							

	}
}
