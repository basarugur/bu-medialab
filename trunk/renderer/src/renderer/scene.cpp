#include "scene.h"
#include <time.h>

namespace scene
{

	Scene::Scene()
	{		
		//m_light     = new PointLight(space::Point3(0,5,0),space::Vector3(0,-1,0));		
		m_screen    = new output::Screen(600,600);
		m_sampler   = new output::Sampler(15,15,-5,m_screen);
		m_camera    = new scene::Perspective(space::Point3(0,0,-20),space::Vector3(0,1,0),space::Point3(0,0,0));


		//will added proper aggregate;
		m_aggregate = new scene::Aggregate();
		initialize();
		
	}

	Scene::Scene(std::vector<Light*>& l,Camera* c,output::Sampler* s,scene::Aggregate* a) : 
		m_camera(c),m_sampler(s),m_aggregate(a)
	{		
		m_lights = l;
		initialize();
	};

	void Scene::initialize()
	{
		m_background = output::TRadiance(1.0,1.0,1.0);
		m_intersection = new Intersection();
		m_aa_on = false;		
	}

	void Scene::render()
	{	
		const output::Screen* scr = m_sampler->screen();

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
				scene::Ray r;
				m_sampler->next(x,y);
				m_camera->generate_ray(m_sampler,r);
				output::TRadiance rd = l(r);
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
				
			output::Screen* scr_aa = new output::Screen(scr->width(),scr->height());

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

	output::TRadiance Scene::l(const Ray& r)
	{	
		if (intersect(r,m_intersection) == true) {					
			return calculate_illumination(r,m_intersection);
		} else {			
			if(light_intersect(r) == true)
				return output::TRadiance(1.0,1.0,1.0);
			
			return m_background;
		}
	}

	//recursive ray trace...
	output::TRadiance Scene::calculate_illumination(const Ray& r,Intersection* isect,int depth,double n1) {
		
		output::TRadiance shade_color;
		output::TRadiance reflection_color;
		output::TRadiance refraction_color;

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
					if(light_intersect(rr) == true)
						reflection_color = output::TRadiance(1.0,1.0,1.0);
					else
						reflection_color = m_background;
				}

				delete is;
			}	

			if(m->transparent() == true) {

				bool reflected = false;
				scene::Ray rr = r.refract(dfg->n(),dfg->p(),n1,dfg->material()->refraction_index(),reflected);
				Intersection* is = new Intersection();

					if(reflected == false) {

						if(intersect(rr,is) == true) {

							if(is->dg()->material()->transparent() == true) {
									
									scene::Ray rt = rr.refract(is->dg()->n(),is->dg()->p(),is->dg()->material()->refraction_index(),n1,reflected);

									while(reflected == true) {
										
										if(intersect(rt,is) == true)
											rt = rt.refract(is->dg()->n(),is->dg()->p(),is->dg()->material()->refraction_index(),n1,reflected);
									}

									if (intersect(rt,is) == true)
										refraction_color = calculate_illumination(rt,is,depth+1,n1);
									else {
										if(light_intersect(rt) == true)
											refraction_color = output::TRadiance(1.0,1.0,1.0);
										else
											refraction_color = m_background;
									}
							}												
						}
					} 

				delete is;
			} 

		}

		output::TRadiance res = reflection_color*m->reflection() + shade_color*m->solid() + refraction_color*m->luculent();
		res.normalize();
		return res;
	}

	output::TRadiance Scene::calculate_shadow(const Ray& r,Intersection* isect) {
			
		output::TRadiance res_radiance;

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

	output::TRadiance Scene::calculate_hardshadow(const Ray& r,Intersection* isect,Light* light) {
	
		space::Point3 pp = light->p();
		space::Point3 pp2= isect->dg()->p();			
		space::Vector3 dv = (pp-pp2);
		
		Ray sr(pp2,dv);			
		sr.set_maxt(dv.length());

		if(intersectp(sr) == true) {
			return output::TRadiance(light->s(r,isect->dg()));		
		}
		else {
			return output::TRadiance(light->l(r,isect->dg()));								 		
		}
	}

	output::TRadiance Scene::calculate_softshadow(const Ray& r,Intersection* isect,Light* light) {

		int shadow_sample = 128;
		space::Point3 pp2= isect->dg()->p();
		space::Normal3 nn= isect->dg()->n();
		output::TRadiance color_avg;
		bool is_shadow = true;
		bool is_litted = true;
		Intersection *is = new Intersection();		
	
		for(int i=0;i<16;i++)
		{
		 	space::Point3 pp = light->pick_point();						
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
				space::Point3 pp = light->pick_point();						
		 		space::Vector3 dv = (pp-pp2);
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

	output::TRadiance Scene::calculate_ambient_occlusion(const Ray& r,Intersection* isect,Light* light) {
		
		output::TRadiance rd = light->l(r,isect->dg());
		space::Point3  p = isect->dg()->p();
		space::Normal3 n = isect->dg()->n();
		double vo = 0;
		int sample = 225;	
		space::Vector3* samples = new space::Vector3[225];
		random_stratified(samples,15);

		space::Vector3 h(1,0,0);
		if (( abs(n*h) <= 1 + ZERO ) && ( abs(n*h) >= 1 - ZERO )) 
			h = space::Vector3(1,1,0);

		space::Vector3 u = (n ^ h).normalize();
		space::Vector3 v = n ^ u;	

		for(int i=0;i<sample;i++) {

			double e1 = samples[i].x();
			double e2 = samples[i].y();
			double x = sqrt(e1)*cos(e2*2*PI);
			double y = sqrt(e1)*sin(e2*2*PI);					
			double z = sqrt(max(0.f,1.f - x*x - y*y));
			space::Vector3 vv = x*u + y*v + z*n;			
			scene::Ray rr(p,vv);
			
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


	void Scene::anti_alias(output::Screen* s,int x, int y) {

		const output::Screen* scr = m_sampler->screen();
	
					m_sampler->next(x,y);
					s->set_color(scr->buffer(x,y),x,y);
					double threshold = 0.5;

					if ( ((x-1) >=0) && ((y-1) >=0) && ((y+1) < scr->height()) &&  ((x+1) < scr->width())) {
						
						bool performaa = false;
						output::TRadiance m[9];

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
							
 							output::TRadiance aac;
							int count = 1;

							if((ll <= 1.0) && (ll > 0.5)) count = 4;
							if((ll <= 2.0) && (ll > 1.0)) count = 9;
							if((ll <= 3.0) && (ll > 2.0)) count = 16;
							if(ll>3.0) count = 25;

							space::Vector3* samples = new space::Vector3[count];
							scene::Ray* rays = new scene::Ray[count];

							random_stratified(samples,sqrt((double)count));

							m_camera->generate_rays(m_sampler,rays,samples,count);

 							for(int i=0;i<count;i++) { 								
 								aac = aac + l(rays[i]);								
 							}

 							aac = aac / (double)count;
 							s->set_color(aac,x,y);
							//s->set_color(output::TRadiance(1.0,0.0,0.0),x,y);
						} 							

					}
	}


};