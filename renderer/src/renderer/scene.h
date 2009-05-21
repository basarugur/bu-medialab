//Author: Ufuk Tiryaki @ 2009
//Desc:

#define _WIN32_WINNT 0x0400

#ifndef SCENE_H
#define SCENE_H

#include "integrator.h"
#include "camera.h"
#include "light.h"
#include "primitive.h"
#include "film.h"
#include "shape.h"
#include "sampler.h"
#include "CImg.h"

using namespace cimg_library;

inline scene::TextureBuffer* load_texture(std::string str) {
	
	CImg<unsigned char> tex(str.c_str()); 

	int w = tex.dimx();
	int h = tex.dimy();

	scene::TextureBuffer* buff = new scene::TextureBuffer(w,h);

	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++) {
			
			output::TRadiance r(tex(i,j,0)/255.0,tex(i,j,1)/255.0,tex(i,j,2)/255.0);
			buff->set_radiance(i,j,r);
		}

	return buff;
};

namespace scene
{
	class Scene
	{
		public:	
			Scene();
			Scene(std::vector<Light*>& l,Camera* c,output::Sampler* s,scene::Aggregate*);		
			
			//method, which traces the given ray into the scene and returns a boolean value 
			//indication whether it intersected any of the primitives. If so, it returns information 
			//about the closest intersection point in the Intersection structure.
			bool intersect(const Ray& ray,Intersection* isect) const;
			
			//method, which checks for any intersection  along a ray, again returning a boolean 
			//result. Because it doesn’t return information about the geometry at the intersection 
			//point and because it doesn’t need to search for the closest intersection, it can be more efficient
			bool intersectp(const Ray& ray) const;		
			void antialias_on() { m_aa_on = true; };
			void antialias_off() { m_aa_on = false; };
			void render();	
		private:	
			void initialize();			
			output::TRadiance l(const Ray&);			
			output::TRadiance calculate_illumination(const Ray& r,Intersection* isect,int depth = 0,double n1 = 1.0);
			output::TRadiance calculate_hardshadow(const Ray& r,Intersection* isect,Light* light);
			output::TRadiance calculate_softshadow(const Ray& r,Intersection* isect,Light* light);	
			output::TRadiance calculate_ambient_occlusion(const Ray& r,Intersection* isect,Light* light);
			output::TRadiance calculate_shadow(const Ray& r,Intersection* isect);			
			void anti_alias(output::Screen*,int,int);

			bool light_intersect(const Ray&);

			output::TRadiance m_background;
			Intersection* m_intersection;
			Aggregate* m_aggregate;
			//Light* m_light;			
			std::vector<Light*> m_lights;
			Camera* m_camera;
			output::Sampler* m_sampler;
			output::Screen* m_screen;			
			double m_screen_size;
			output::TRadiance **m_buffer;				
			bool m_aa_on;
	};
};

#endif