#include "scene.h"
#include <time.h>


namespace scene
{

	Scene::Scene()
	{		
		m_light     = new PointLight(space::Point3(0,5,0),space::Vector3(0,-1,0));		
		m_screen    = new output::Screen(600,600);
		m_sampler   = new output::Sampler(15,15,-5,m_screen);
		m_camera    = new scene::Perspective(space::Point3(0,0,-20),space::Vector3(0,0,1));


		//will added proper aggregate;
		m_aggregate = new scene::Aggregate();
		initialize();
		
	}

	Scene::Scene(Light* l,Camera* c,output::Sampler* s,scene::Aggregate* a) : 
		m_light(l),m_camera(c),m_sampler(s),m_aggregate(a)
	{		
		initialize();
	};

	void Scene::initialize()
	{
		m_intersection = new Intersection();
		m_aa_on = false;
	}

	void Scene::render()
	{	
		const output::Screen* scr = m_sampler->screen();

		char timeStr [9];
		_strtime( timeStr );
		std::cout << "> " << timeStr << " : "<< "rendering..." << std::endl;			
		for(int x=0;x<scr->width();x++)
			for(int y=0;y<scr->height();y++)
			{		
				scene::Ray r;
				m_sampler->next(x,y);
				m_camera->generate_ray(m_sampler,r);
				scr->set_color(l(r),x,y);				
			}

			
		output::Screen* scr_aa = new output::Screen(scr->width(),scr->height());
		if(m_aa_on == true)
			 anti_alias(scr_aa);
		else 
			*scr_aa = *scr;		
		
		CImg<unsigned char>* image = new CImg<unsigned char>(scr->width(),scr->height(),1,3,255);

		for(std::size_t i=0;i<scr->width();i++)
			for(std::size_t j=0;j<scr->height();j++)
			{
				(*image)(scr->width() - 1 - i,scr->height() - 1 - j,0) = 255*scr_aa->buffer(i,j).r;
				(*image)(scr->width() - 1 - i,scr->height() - 1 - j,1) = 255*scr_aa->buffer(i,j).g;
				(*image)(scr->width() - 1 - i,scr->height() - 1 - j,2) = 255*scr_aa->buffer(i,j).b;
			}

		
		
		_strtime( timeStr );
		std::cout << "> " << timeStr << " : "<< "rendering completed!" << std::endl;	
		image->blur(0.8);
		image->save_bmp("c:/output.bmp");

		CImgDisplay disp(*image,"pbrt - ufuk tiryaki @ bogazici university");
		while(!disp.is_closed) disp.wait();		
	}

	output::TRadiance Scene::l(const Ray& r)
	{	
		if (intersect(r,m_intersection) == true) {					
			return calculate_illumination(r,m_intersection);
		} else {			
			if(m_light->intersect(r) == true)
				return output::TRadiance(1.0,1.0,1.0);
			
			return output::TRadiance(0,0,0);
		}
	}

	//recursive ray trace...
	output::TRadiance Scene::calculate_illumination(const Ray& r,Intersection* isect,int depth,double n1) {
		
		output::TRadiance shade_color;
		output::TRadiance reflection_color;		

		scene::DifferentialGeometry* dfg = isect->dg();
		Material* m = dfg->material();
		shade_color = calculate_shadow(r,isect);

		if(depth < 6) {
	
			if(m->reflective() == true) {

				scene::Ray rr = r.reflect(dfg->n(),dfg->p());
				Intersection* is = new Intersection();
				
				if(intersect(rr,is) == true) {
					reflection_color = calculate_illumination(rr,is,depth+1);										
				} else { 					
					if(m_light->intersect(rr) == true)
						reflection_color = output::TRadiance(1.0,1.0,1.0);
					else
						reflection_color = output::TRadiance(0,0,0);
				}

				delete is;
			}	

		}
		
		return ( reflection_color*m->reflection() + shade_color*m->solid() );
	}

	output::TRadiance Scene::calculate_shadow(const Ray& r,Intersection* isect) {
			if(m_light->type() == 0) {				
				return calculate_hardshadow(r,isect);
			}

			if(m_light->type() == 1)
				return calculate_softshadow(r,isect);
	}

	output::TRadiance Scene::calculate_hardshadow(const Ray& r,Intersection* isect) {
	
		space::Point3 pp = m_light->p();
		space::Point3 pp2= isect->dg()->p();			
		space::Vector3 dv = (pp-pp2);
		
		Ray sr(pp2,dv);			
		sr.set_maxt(dv.length());

		if(intersectp(sr) == true) {
			return output::TRadiance(m_light->s(r,isect->dg()));		
		}
		else {
			return output::TRadiance(m_light->l(r,isect->dg()));								 		
		}
	}

	output::TRadiance Scene::calculate_softshadow(const Ray& r,Intersection* isect) {

		int shadow_sample = 128;
		space::Point3 pp2= isect->dg()->p();
		space::Normal3 nn= isect->dg()->n();
		output::TRadiance color_avg;
		bool is_shadow = true;
		bool is_litted = true;
		Intersection *is = new Intersection();		
	
		for(int i=0;i<16;i++)
		{
		 	space::Point3 pp = m_light->pick_point();						
		 	space::Vector3 dv = (pp-pp2);
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
				space::Point3 pp = m_light->pick_point();						
		 		space::Vector3 dv = (pp-pp2);
		 		Ray sr(pp2,dv);
				sr.set_maxt(dv.length());

				if(intersectp(sr) == true) {
					color_avg = color_avg + m_light->s(r,isect->dg());
				} else {
		 			color_avg = color_avg + m_light->l(r,isect->dg());
				}
		 	}
	
		 	color_avg = color_avg / (double)shadow_sample;
		 	return color_avg;			
		}
	
		if ((is_shadow == true) && (is_litted == false)) {
		 	return m_light->s(r,isect->dg());		 		
		} 
	
		if ((is_litted == true) && (is_shadow == false)) { 
		 	return m_light->l(r,isect->dg());
		}

		

	}


	bool Scene::intersect(const Ray& ray,Intersection* isect) const {		
		return m_aggregate->intersect(ray,isect);		
	}		

	bool Scene::intersectp(const Ray& ray) const {
		return m_aggregate->intersectp(ray);	
	}


	void Scene::anti_alias(output::Screen* s) {
		//Not implemented yet...
	}


};