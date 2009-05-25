


#ifndef MATERIAL_H
#define MATERIAL_H

#include "film.h"
#include "vector3.h"
#include "texture.h"
#include <string>

struct StructTexture
{
	StructTexture()
	{
		m_n = Vector3(0,0,1);
		m_scale_x = 1;
		m_scale_y = 1;
		m_path = "texture/floor.bmp";
	}
	Vector3 m_n;
	double m_scale_x;
	double m_scale_y;
	std::string m_path;
};

class Material
{
	public:	
		Material(TRadiance d,TRadiance s,TRadiance a) 
		: m_diffusecolor(d),m_speccolor(s),m_ambientcolor(a) 
		{
			m_reflection_coeff = 0.0;
			m_luculent_coeff = 0.0;
			m_solid_coeff = 1.0;
			m_index_of_refraction = 1.0;

			m_is_texture = false;

		};	
		Material() 
		{
			m_reflection_coeff = 0.0;
			m_luculent_coeff = 0.0;
			m_solid_coeff = 1.0;
			m_index_of_refraction = 1.0;

			m_is_texture = false;

		};

	

		Material(Texture* t,TRadiance s,TRadiance a) 
			: m_img_texture(t),m_speccolor(s),m_ambientcolor(a)
		{
			m_reflection_coeff = 0.0;
			m_luculent_coeff = 0.0;
			m_solid_coeff = 1.0;
			m_index_of_refraction = 1.0;
			srand(500);
		};

		const TRadiance& diffcolor() const { return m_diffusecolor; };
		const TRadiance& speccolor() const { return m_speccolor; };
		const TRadiance& ambientcolor() const { return m_ambientcolor; };

		void setDiffColor(TRadiance r) { m_diffusecolor = r; }
		void setSpecColor(TRadiance r) { m_speccolor = r; }
		void setAmbienColor(TRadiance r) { m_ambientcolor = r; }
		
		double solid() const { return m_solid_coeff; };
		void set_solid(double r) { (r > 1.0) ? m_solid_coeff = 1.0 : m_solid_coeff = r; };

		double refraction_index() const { return m_index_of_refraction; };
		void set_refraction_index(double r) { m_index_of_refraction = r; };
											
		void set_reflective(double r) { (r > 1.0) ? m_reflection_coeff = 1.0 : m_reflection_coeff = r; };
		double reflection() const { return m_reflection_coeff; };
		
		void set_luculent(double r) { (r > 1.0) ? m_luculent_coeff = 1.0 : m_luculent_coeff = r; };
		double luculent() const { return m_luculent_coeff; };		

		bool reflective() { return (m_reflection_coeff > 0); };
		bool transparent(){ return (m_luculent_coeff > 0); };

		void setName(std::string st_){ m_name = st_; }
		std::string getName() { return m_name; }

		void setTexture(StructTexture txt_)
		{
			m_texture = txt_;
			m_is_texture = true;
		}
		StructTexture& getTexture(){ return m_texture; }

		void enableTexture(bool bl_){ m_is_texture = bl_; };
		bool isTextureEnabled(){ return m_is_texture; }

		//const space::Point3& center,const space::Point3& p
		const TRadiance diffcolor(float u,float v,float w) const {
			if (m_img_texture != NULL)
				return m_img_texture->map(u,v,w);
			else
				return m_diffusecolor;
		};

	private:		
		std::string m_name;

		TRadiance m_diffusecolor;
		TRadiance m_speccolor;
		TRadiance m_ambientcolor;

		double m_reflection_coeff;
		double m_luculent_coeff;
		double m_solid_coeff;

		double m_index_of_refraction;	

		StructTexture m_texture;
		bool m_is_texture;

		Texture* m_img_texture;

};


#endif