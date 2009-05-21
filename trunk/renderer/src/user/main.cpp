#ifndef MAIN_H
#define MAIN_H

#include "../include/tinyxml.h"
#include "../include/tinystr.h"
#include "scene.h"

std::vector<scene::Transformation*> transformations;
std::vector<scene::Texture*> textures;
std::vector<scene::Material*> materials;
std::vector<scene::Shape*> shapes;
std::vector<scene::Light*> lights;
std::vector<scene::Primitive*> primitives; 

scene::Camera* camera;
output::Screen* screen;

bool aa_on;

bool load_scene(std::string filename) 
{
	bool result;

	TiXmlDocument doc;
	result=doc.LoadFile(filename.c_str());

	if (result)
	{
		TiXmlElement *root =doc.RootElement();
		TiXmlElement *transform_root_element = root->FirstChildElement();
		TiXmlElement *transform_element = transform_root_element->FirstChildElement();

		while (transform_element != 0)
		{		
			scene::Transformation* t = new scene::Transformation();

			TiXmlElement *rotation_element = transform_element->FirstChildElement();
			double x = atof(rotation_element->Attribute("x"));
			double y = atof(rotation_element->Attribute("y"));
			double z = atof(rotation_element->Attribute("z"));
			int r = atoi(rotation_element->Attribute("r"));

			t->rotate(x,y,z,r);

			TiXmlElement *scale_element = rotation_element->NextSiblingElement();
			x = atof(scale_element->Attribute("x"));
			y = atof(scale_element->Attribute("y"));
			z = atof(scale_element->Attribute("z"));

			t->scale(x,y,z);

			TiXmlElement *translate_element = scale_element->NextSiblingElement();
			x = atof(translate_element->Attribute("x"));
			y = atof(translate_element->Attribute("y"));
			z = atof(translate_element->Attribute("z"));		

			t->translate(x,y,z);
			transformations.push_back(t);

			transform_element = transform_element->NextSiblingElement();
		}

		TiXmlElement *texture_root_element = transform_root_element->NextSiblingElement();
		TiXmlElement *texture_element = texture_root_element->FirstChildElement();

		while (texture_element != 0)
		{		
			TiXmlElement *file = texture_element->FirstChildElement();
			std::string path = file->Attribute("path");

			TiXmlElement *normal_element = file->NextSiblingElement();
			double x = atof(normal_element->Attribute("x"));
			double y = atof(normal_element->Attribute("y"));
			double z = atof(normal_element->Attribute("z"));

			TiXmlElement *scale_element = normal_element->NextSiblingElement();
			double sx = atof(scale_element->Attribute("x"));
			double sy = atof(scale_element->Attribute("y"));
				
			scene::Texture* t = new scene::Texture2D(load_texture(path.c_str()),space::Vector3(x,y,z),sx,sy);
			textures.push_back(t);

			texture_element = texture_element->NextSiblingElement();
		}

		TiXmlElement *material_root_element = texture_root_element->NextSiblingElement();
		TiXmlElement *material_element = material_root_element->FirstChildElement();

		while (material_element != 0)
		{
			int texture_id = atoi(material_element->Attribute("texture_id"));
			TiXmlElement *diffuse_color = material_element->FirstChildElement();
			output::TRadiance diffuse(atof(diffuse_color->Attribute("r")),atof(diffuse_color->Attribute("g")),atof(diffuse_color->Attribute("b")));
			
			TiXmlElement *spec_color = diffuse_color->NextSiblingElement();            		
			output::TRadiance specular(atof(spec_color->Attribute("r")),atof(spec_color->Attribute("g")),atof(spec_color->Attribute("b")));

			TiXmlElement *amb_color = spec_color->NextSiblingElement();
			output::TRadiance ambient(atof(amb_color->Attribute("r")),atof(amb_color->Attribute("g")),atof(amb_color->Attribute("b")));

			TiXmlElement *sol = amb_color->NextSiblingElement();
			TiXmlElement *ref = sol->NextSiblingElement();
			TiXmlElement *ref_indx = ref->NextSiblingElement();
			TiXmlElement *luc = ref_indx->NextSiblingElement();

			double solid = atof(sol->GetText());
			double reflection = atof(ref->GetText());
			double refrac_indx = atof(ref_indx->GetText());
			double luculent = atof(luc->GetText());

			scene::Material* m;

			if (texture_id == -1)
				m = new scene::Material(diffuse,specular,ambient);
			else
				m = new scene::Material(textures[texture_id],specular,ambient);

				m->set_solid(solid);
				m->set_reflective(reflection);
				m->set_luculent(luculent);
				m->set_refraction_index(refrac_indx);

			materials.push_back(m);

			material_element = material_element->NextSiblingElement();
		}

		TiXmlElement *light_root_element = material_root_element->NextSiblingElement();
		TiXmlElement *light_element = light_root_element->FirstChildElement();

		while(light_element != 0)
		{
			std::string type = light_element->Attribute("type");
			TiXmlElement *position = light_element->FirstChildElement();
			space::Point3 pos(atof(position->Attribute("x")),atof(position->Attribute("y")),atof(position->Attribute("z")));

			TiXmlElement *direction = position->NextSiblingElement();
			space::Vector3 dir(atof(direction->Attribute("x")),atof(direction->Attribute("y")),atof(direction->Attribute("z")));

			TiXmlElement *coeff = direction->NextSiblingElement();
			double c = atof(coeff->GetText());

			scene::Light* l;

			if(strcmp(type.c_str(),"point") == 0)
				l = new scene::PointLight(pos,dir);
			
			if(strcmp(type.c_str(),"area") == 0)
				l = new scene::AreaLight(pos,dir);
			
			if(strcmp(type.c_str(),"sky") == 0)
				l = new scene::SkyLight(pos,dir);

			l->set_coeff(c);

			lights.push_back(l);
			light_element = light_element->NextSiblingElement();

		}

		//camera
		TiXmlElement *camera_root_element = light_root_element->NextSiblingElement();
		std::string type = camera_root_element->Attribute("type");

		TiXmlElement *position = camera_root_element->FirstChildElement();
		space::Point3 pos(atof(position->Attribute("x")),atof(position->Attribute("y")),atof(position->Attribute("z")));

		TiXmlElement *up = position->NextSiblingElement();
		space::Vector3 u(atof(up->Attribute("x")),atof(up->Attribute("y")),atof(up->Attribute("z")));

		TiXmlElement *target = up->NextSiblingElement();
		space::Point3 t(atof(target->Attribute("x")),atof(target->Attribute("y")),atof(target->Attribute("z")));

		if(strcmp(type.c_str(),"perspective") == 0)
			camera = new scene::Perspective(pos,u,t);

		//screen
		TiXmlElement *screen_root_element = camera_root_element->NextSiblingElement();

		TiXmlElement *width = screen_root_element->FirstChildElement();
		int w = atoi(width->GetText());

		TiXmlElement *height = width->NextSiblingElement();
		int h = atoi(height->GetText());

		screen = new output::Screen(w,h);

		TiXmlElement *shape_root_element = screen_root_element->NextSiblingElement();
		TiXmlElement *shape_element = shape_root_element->FirstChildElement();

		while(shape_element != 0)
		{
			std::string type = shape_element->Attribute("type");

			TiXmlElement *file = shape_element->FirstChildElement();
			std::string path = file->Attribute("path");

			scene::Shape* s;

			if(strcmp(type.c_str(),"triangle_mesh") == 0)
				s = new scene::TriangleMesh(path);

			shapes.push_back(s);
			shape_element = shape_element->NextSiblingElement();
		}

		TiXmlElement *primitive_root_element = shape_root_element->NextSiblingElement();
		TiXmlElement *primitive_element = primitive_root_element->FirstChildElement();

		while(primitive_element != 0)
		{
			TiXmlElement *shape = primitive_element->FirstChildElement();
			int shape_id = atoi(shape->GetText());

			TiXmlElement *mt = shape->NextSiblingElement();
			int mat_id = atoi(mt->GetText());

			TiXmlElement *tr = mt->NextSiblingElement();
			int trans_id = atoi(tr->GetText());

			scene::Primitive* p = new scene::GeomPrimitive(shapes[shape_id],materials[mat_id],transformations[trans_id]);
			primitives.push_back(p);

			primitive_element = primitive_element->NextSiblingElement();
		}

		TiXmlElement *props_root_element = primitive_root_element->NextSiblingElement();
		TiXmlElement *antialias = props_root_element->FirstChildElement();
		
		if(strcmp(antialias->GetText(),"true") == 0)
			aa_on = true;
		else
			aa_on = false;

	}

	return result;
}

int main(int argc, char *argv[])
{	
	if (load_scene(argv[1]) == true) {
	
		scene::Aggregate* objects = new scene::Aggregate();

		for(int i=0;i<primitives.size();i++)
			objects->add_primitive(primitives[i]);

		objects->post();

		output::Sampler* sm = new output::Sampler(1,1,0,screen);
		scene::Scene* sc = new scene::Scene(lights,camera,sm,objects);	
		
		if(aa_on == true)
			sc->antialias_on();
		else
			sc->antialias_off();
		
		sc->render();

	}

	return 0;
}

#endif