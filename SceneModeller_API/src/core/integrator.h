//Author: Ufuk Tiryaki @ 2009
//Desc:

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../sm_api_dll.h"

	class Scene;

	class SM_API_EXPORT Integrator
	{
		public:	
			Integrator() {};
		private:
	};

	class SM_API_EXPORT SurfaceIntegrator : public Integrator
	{
		public:
			SurfaceIntegrator() {};

		private:
	};

#endif