//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include "film.h"
#include "vector3.h"
#include "point3.h"

namespace scene
{		
	class Material
	{
		public:	
			Material(output::TRadiance d,output::TRadiance s,output::TRadiance a) 
			: m_diffusecolor(d),m_speccolor(s),m_ambientcolor(a),m_texture(NULL) 
			{
				m_reflection_coeff = 0.0;
				m_luculent_coeff = 0.0;
				m_solid_coeff = 1.0;
				m_index_of_refraction = 1.0;
				srand(500);
			};		

			Material(Texture* t,output::TRadiance s,output::TRadiance a) 
			: m_texture(t),m_speccolor(s),m_ambientcolor(a)
			{
				m_reflection_coeff = 0.0;
				m_luculent_coeff = 0.0;
				m_solid_coeff = 1.0;
				m_index_of_refraction = 1.0;
				srand(500);
			};

			
			//const output::TRadiance& texture_color(const space::Point3& center,const space::Point3& p) const {
			//	return m_texture->map(center,p);
			//};

			//const space::Point3& center,const space::Point3& p
			const output::TRadiance diffcolor(float u,float v,float w) const {
				if (m_texture != NULL)
					return m_texture->map(u,v,w);
				else
					return m_diffusecolor;
			};
			//const output::TRadiance& diffcolor() const { return m_diffusecolor; };
			const output::TRadiance& speccolor() const { return m_speccolor; };
			const output::TRadiance& ambientcolor() const { return m_ambientcolor; };
			
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

		private:			
			Texture* m_texture;

			output::TRadiance m_diffusecolor;
			output::TRadiance m_speccolor;
			output::TRadiance m_ambientcolor;

			double m_reflection_coeff;
			double m_luculent_coeff;
			double m_solid_coeff;

			double m_index_of_refraction;			

	};
};

#endif