#include "scene.h"

int main()
{	
   	scene::Shape* s = new scene::TriangleMesh("../models/planor.raw");	
	output::TRadiance ambiance(0.2,0.2,0.2);
	scene::Material* m = new scene::Material(output::TRadiance(1.0,1.0,1.0),output::TRadiance(1.0,1.0,1.0),ambiance);	
  	scene::Primitive* prim = new scene::GeomPrimitive(s,m);
	scene::Aggregate* objects = new scene::Aggregate();

   	objects->add_primitive(prim);	
	objects->post();

	scene::Light* l = new scene::PointLight(space::Point3(0,8,-10),space::Vector3(0,-1,0));
	scene::Camera* c = new scene::Perspective(space::Point3(0,0,-30),space::Vector3(0,0,1));
	output::Screen* scr = new output::Screen(400,400);
	output::Sampler* sm = new output::Sampler(15,15,-12,scr);
	scene::Scene* sc = new scene::Scene(l,c,sm,objects);	
	sc->render();

	return 0;
}