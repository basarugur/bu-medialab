



#ifndef SCENE_H
#define SCENE_H

#define _WIN32_WINNT 0x0400


#include "camera.h"
#include "light.h"
#include "primitive.h"
#include "film.h"
#include "shape.h"
#include "gfxobject.h"

#include "integrator.h"
#include "sampler.h"
#include "CImg.h"

using namespace cimg_library;

inline TextureBuffer* load_texture(std::string str) {

	CImg<unsigned char> tex(str.c_str());

	int w = tex.dimx();
	int h = tex.dimy();

	TextureBuffer* buff = new TextureBuffer(w,h);

	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++) {

			TRadiance r(tex(i,j,0)/255.0,tex(i,j,1)/255.0,tex(i,j,2)/255.0);
			buff->set_radiance(i,j,r);
		}

		return buff;
};

class SM_API_EXPORT Scene
{
	public:
		Scene();
		~Scene();

		Scene(std::vector<Light*>& l,Camera* c,Sampler* s,Aggregate*);

		//method, which traces the given ray into the scene and returns a boolean value
		//indication whether it intersected any of the primitives. If so, it returns information
		//about the closest intersection point in the Intersection structure.
		bool intersect(const Ray& ray,Intersection* isect) const;

		//method, which checks for any intersection  along a ray, again returning a boolean
		//result. Because it doesn't return information about the geometry at the intersection
		//point and because it doesn't need to search for the closest intersection, it can be more efficient
		bool intersectp(const Ray& ray) const;
		void antialias_on() { m_aa_on = true; };
		void antialias_off() { m_aa_on = false; };
		void render();

		void operator += (GfxObject *obj_)
		{
			m_primitves.push_back(obj_);
		}
		void operator += (Camera *cmr_)
		{
			m_cameras.push_back(cmr_);
		}
		void operator += (Light *lgh_)
		{
			m_lights.push_back(lgh_);
		}

		TRadiance& backgroundColor()
		{
			return m_background_color;
		};

		std::vector<GfxObject*>& objects(){ return m_primitves; };
		std::vector<Light*>& lights(){ return m_lights; };
		std::vector<Camera*>& cameras(){ return m_cameras; };

		GfxObject* traverseTree(int ind_);

		void addToChild(GfxObject* obj_);
		GfxObject* getTmpChild();
		void setTmpChild(GfxObject* );

		void clearAllSelections();

		// for light
		void clearLightSelection();
		Light* getSelectedLight();
		void deleteSelectedLight();
		void duplicateSelectedLight();

		// for camera
		Camera* getSelectedCamera();
		void deleteSelectedCamera();
		void duplicateSelectedCamera();
		void clearCameraSelection();

		// for single object
		void clearobjectSelections();
		GfxObject* getSelectedObject();
		void deleteSelectedObject();
		void duplicateSelectedObject();

		// for face
		void clearFaceSelections();
		int totalFaceCount();

		// for Vertex
		void clearVertexSelections();
		Vertex* getSelectedVertex();
		int totalVertexCount();


		// for object tree
		void clearTreeSelection();
		GfxObject* getSelectedTreeRoot();
		void deleteSelectedTree();
		void duplicateSelectedTree();
		void selectTree(GfxObject* obj_);

		//
		void clearScene();

		// face editing
		void splitSelectedFace();
		void deleteSelectedFace();
		Triangle* getExtrudingFace();
		Triangle* getSelectedFace();
		void restoreTriangles();

	private:
		void initialize();

		void duplicateTree(GfxObject* obj_,GfxObject* nwPrnt_);

		GfxObject* traverseObject(int ind_,GfxObject* obj_);

		std::vector<GfxObject*> m_primitves;
		std::vector<Light*> m_lights;
		std::vector<Camera*> m_cameras;

		GfxObject* m_selected_tree_root;

		GfxObject* m_add_child_tmp;

		TRadiance m_background_color;

		int m_tree_traverse_counter;

		TRadiance l(const Ray&);
		TRadiance calculate_illumination(const Ray& r,Intersection* isect,int depth = 0,double n1 = 1.0);
		TRadiance calculate_hardshadow(const Ray& r,Intersection* isect,Light* light);
		TRadiance calculate_softshadow(const Ray& r,Intersection* isect,Light* light);
		TRadiance calculate_ambient_occlusion(const Ray& r,Intersection* isect,Light* light);
		TRadiance calculate_shadow(const Ray& r,Intersection* isect);
		void anti_alias(SMScreen*,int,int);

		bool light_intersect(const Ray&);

		TRadiance m_background;
		Intersection* m_intersection;
		Aggregate* m_aggregate;
		//Light* m_light;
		Camera* m_camera;
		Sampler* m_sampler;
		SMScreen* m_screen;
		double m_screen_size;
		TRadiance **m_buffer;
		bool m_aa_on;
};




#endif
