#include "octree.h"

namespace acc 
{
	bool Octree::inside(const acc::OctreeNode* node, const scene::Triangle* triangle) const
	{				
			float p0, p1, p2, R;
			float a0, a1, a2;
			space::Vector3 N, D, E0, E1, E2, A0(1,0,0), A1(0,1,0), A2(0,0,1);
			const space::Vector3 v1 = triangle->a();
			const space::Vector3 v2 = triangle->b();
			const space::Vector3 v3 = triangle->c();
			
			// initialize
			a0 = m_halfdims[node->depth()].x();
			a1 = m_halfdims[node->depth()].y();
			a2 = m_halfdims[node->depth()].z();
			D  = v1 - node->center();
			E0 = v2 - v1; E1 = v3 - v1;	E2 = E1 - E0;
			N  = E0 ^ E1;
			
			// N
			p0 = N*D;	p1 = p0;	p2 = p0;
			R = a0*fabs(N*A0) + a1*fabs(N*A1) + a2*fabs(N*A2);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A0
			p0 = A0*D;	p1 = p0 + A0*E0; p2 = p0 + A0*E1; R = a0;
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A1
			p0 = A1*D;  p1 = p0 + A1*E0;  p2 = p0 + A1*E1;  R = a1;
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A2
			p0 = A2*D;  p1 = p0 + A2*E0;  p2 = p0 + A2*E1;  R = a2;
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A0 x E0
			p0 = (A0^E0)*D;  p1 = p0;  p2 = p0 + A0*N;  R = a1*fabs(A2*E0) + a2*fabs(A1*E0);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A0 x E1
			p0 = (A0^E1)*D;  p1 = p0 - A0*N;  p2 = p0;  R = a1*fabs(A2*E1) + a2*fabs(A1*E1);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;


			// A0 x E2
			p0 = (A0^E2)*D;  p1 = p0 - A0*N;  p2 = p0 - A0*N;  R = a1*fabs(A2*E2) + a2*fabs(A1*E2);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;		

			// A1 x E0
			p0 = (A1^E0)*D;  p1 = p0;  p2 = p0 + A1*N;  R = a0*fabs(A2*E0) + a2*fabs(A0*E0);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A1 x E1
			p0 = (A1^E1)*D;  p1 = p0 - A1*N;  p2 = p0;  R = a0*fabs(A2*E1) + a2*fabs(A0*E1);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A1 x E2
			p0 = (A1^E2)*D;  p1 = p0 - A1*N;  p2 = p0 - A1*N;  R = a0*fabs(A2*E2) + a2*fabs(A0*E2);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;

			// A2 x E0
			p0 = (A2^E0)*D;  p1 = p0;  p2 = p0 + A2*N;  R = a0*fabs(A1*E0) + a1*fabs(A0*E0);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;


			// A2 x E1
			p0 = (A2^E1)*D;  p1 = p0 - A2*N;  p2 = p0;  R = a0*fabs(A1*E1) + a1*fabs(A0*E1);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;


			// A2 x E2
			p0 = (A2^E2)*D;  p1 = p0 - A2*N;  p2 = p0 - A2*N;  R = a0*fabs(A1*E2) + a1*fabs(A0*E2);
			if( (min(p0,p1,p2) > R)  ||  (max(p0,p1,p2) < -R) )
				return false;


			// all non-intersection tests have failed -> intersection exists...	
			return true;
	}
}