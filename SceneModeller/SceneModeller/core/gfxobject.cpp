#include "gfxobject.h"

#include "sphere.h"
#include "cube.h"
#include "cone.h"
#include "trianglemesh.h"
#include "cylinder.h"
#include "twosidedcylinder.h"
#include "torus.h"
#include "triangleshape.h"
#include "rectangle.h"
#include "circle.h"
#include "disk.h"
#include "partialdisk.h"

void GfxObject::getCopy(GfxObject*& nwObj_)
{
		TriangleMesh* msh_,*msh1_;
		Cube* cp_,*cp1_;
		Sphere* sph_,*sph1_;
		Cone* cne_,*cne1_;
		Cylinder* cyld_,*cyld1_;
		TwoSidedCylinder* twcyl_,*twcyl1_;
		Torus* trs_,*trs1_ ; 
		TriangleShape* trngshp_,*trngshp1_;
		RectangleShape* rect_,*rect1_;
		Circle* circle_,*circle1_;
		Disk* disk_,*disk1_;
		PartialDisk* pdisk_,*pdisk1_;

		Material* mt_ = new Material(m_material->diffcolor(),
									 m_material->speccolor(),
									 m_material->ambientcolor());
		mt_->set_reflective(m_material->reflection());
		mt_->set_luculent(m_material->luculent());
		mt_->set_solid(m_material->solid());
		mt_->set_refraction_index(m_material->refraction_index());

		Transformation* trns_ = new Transformation();
		trns_->rotation() = m_public_tranform->rotation();
		trns_->scale() = m_public_tranform->scale();
		trns_->translation() = m_public_tranform->translation();

		switch(m_shape->type())
		{
		case TRIANGLE_MESH:
			msh_ = static_cast<TriangleMesh*>(m_shape);
			msh1_ = new TriangleMesh();
			msh_->copyToMesh(msh1_);
			nwObj_ = new GfxObject(msh1_,mt_,trns_);
			break;
		case CUBE:
			cp_ = static_cast<Cube*>(m_shape);
			cp1_ = new Cube();
			cp1_->m_d = cp_->m_d;
			nwObj_ = new GfxObject(cp1_,mt_,trns_);
			break;
		case SPHERE:
			sph_ = static_cast<Sphere*>(m_shape);
			sph1_ = new Sphere();
			sph1_->m_r = sph_->m_r;
			nwObj_ = new GfxObject(sph1_,mt_,trns_);
			break;
		case CONE:
			cne_ = static_cast<Cone*>(m_shape);
			cne1_ = new Cone();
			cne1_->m_h = cne_->m_h;
			cne1_->m_r = cne_->m_r;
			cne1_->m_slices = cne_->m_slices;
			cne1_->m_stacks = cne_->m_stacks;
			nwObj_ = new GfxObject(cne1_,mt_,trns_);
			break;
		case CYLINDER:
			cyld_ = static_cast<Cylinder*>(m_shape);
			cyld1_ = new Cylinder();
			cyld1_->m_h = cyld_->m_h;
			cyld1_->m_r = cyld_->m_r;
			cyld1_->m_slices = cyld_->m_slices;
			cyld1_->m_stacks = cyld_->m_stacks;
			nwObj_ = new GfxObject(cyld1_,mt_,trns_);
			break;
		case TWO_SIDED_CYLINDER:
			twcyl_ = static_cast<TwoSidedCylinder*>(m_shape);
			twcyl1_ = new TwoSidedCylinder();
			twcyl1_->m_base_r = twcyl_->m_base_r;
			twcyl1_->m_top_r = twcyl_->m_top_r;
			twcyl1_->m_h = twcyl_->m_h;
			twcyl1_->m_slices = twcyl_->m_slices;
			twcyl1_->m_stacks = twcyl_->m_stacks;
			nwObj_ = new GfxObject(twcyl1_,mt_,trns_);
			break;
		case TORUS:
			trs_ = static_cast<Torus*>(m_shape);
			trs1_ = new Torus();
			trs1_->m_in_r = trs_->m_in_r;
			trs1_->m_out_r = trs_->m_out_r;
			trs1_->m_rings = trs_->m_rings;
			trs1_->m_sides = trs_->m_sides;
			nwObj_ = new GfxObject(trs1_,mt_,trns_);
			break;
		case TRIANGLE_SHAPE:
			trngshp_ = static_cast<TriangleShape*>(m_shape);
			trngshp1_ = new TriangleShape();
			trngshp1_->m_p1 = trngshp_->m_p1; 
			trngshp1_->m_p2 = trngshp_->m_p2; 
			trngshp1_->m_p3 = trngshp_->m_p3; 
			nwObj_ = new GfxObject(trngshp1_,mt_,trns_);
			break;
		case RECTANGLE:
			rect_ = static_cast<RectangleShape*>(m_shape);
			rect1_ = new RectangleShape();
			rect1_->m_x = rect_->m_x;
			rect1_->m_y = rect_->m_y;
			nwObj_ = new GfxObject(rect1_,mt_,trns_);
			break;
		case CIRCLE:
			circle_ = static_cast<Circle*>(m_shape);
			circle1_ = new Circle();
			circle1_->m_r = circle_->m_r;
			circle1_->m_loops = circle_->m_loops;
			circle1_->m_slices = circle_->m_slices;
			nwObj_ = new GfxObject(circle1_,mt_,trns_);
			break;
		case DISK:
			disk_ = static_cast<Disk*>(m_shape);
			disk1_ = new Disk();
			disk1_->m_in_r = disk_->m_in_r;
			disk1_->m_out_r = disk_->m_out_r;
			disk1_->m_slices = disk_->m_slices;
			disk1_->m_loops = disk_->m_loops;
			nwObj_ = new GfxObject(disk1_,mt_,trns_);
			break;
		case PARTIAL_DISK:
			pdisk_ = static_cast<PartialDisk*>(m_shape);
			pdisk1_ = new PartialDisk();
			pdisk1_->m_in_r = pdisk_->m_in_r;
			pdisk1_->m_out_r = pdisk_->m_out_r;
			pdisk1_->m_loops = pdisk_->m_loops;
			pdisk1_->m_slices = pdisk_->m_slices;
			pdisk1_->start_ang = pdisk_->start_ang;
			pdisk1_->sweep_ang = pdisk_->sweep_ang;
			nwObj_ = new GfxObject(pdisk1_,mt_,trns_);
			break;
		default:
			break;
		}
		nwObj_->setName(m_name);

		nwObj_->getIndividualTranform()->rotation() = m_individual_transform->rotation();
		nwObj_->getIndividualTranform()->scale() = m_individual_transform->scale();
		nwObj_->getIndividualTranform()->translation() = m_individual_transform->translation();

}

void GfxObject::convertToMesh()
{
	if(m_shape->type() != TRIANGLE_MESH)
	{
		Cube* cp_;
		Sphere* sph_;
		Cone* cne_;
		Cylinder* cyld_;
		TwoSidedCylinder* twcyl_;
		Torus* trs_; 
		TriangleShape* trngshp_;
		RectangleShape* rect_;
		Circle* circle_;
		Disk* disk_;
		PartialDisk* pdisk_;
		TriangleMesh* meshShape_ = new TriangleMesh();
		switch(m_shape->type())
		{
		case CUBE:
			cp_ = static_cast<Cube*>(m_shape);
			cp_->copyToMesh(meshShape_);
			break;
		case SPHERE:
			sph_ = static_cast<Sphere*>(m_shape);
			sph_->copyToMesh(meshShape_);
			break;
		case CONE:
			cne_ = static_cast<Cone*>(m_shape);
			cne_->copyToMesh(meshShape_);
			break;
		case CYLINDER:
			cyld_ = static_cast<Cylinder*>(m_shape);
			cyld_->copyToMesh(meshShape_);
			break;
		case TWO_SIDED_CYLINDER:
			twcyl_ = static_cast<TwoSidedCylinder*>(m_shape);
			twcyl_->copyToMesh(meshShape_);
			break;
		case TORUS:
			trs_ = static_cast<Torus*>(m_shape);
			trs_->copyToMesh(meshShape_);
			break;
		case TRIANGLE_SHAPE:
			trngshp_ = static_cast<TriangleShape*>(m_shape);
			trngshp_->copyToMesh(meshShape_);
			break;
		case RECTANGLE:
			rect_ = static_cast<RectangleShape*>(m_shape);
			rect_->copyToMesh(meshShape_);
			break;
		case CIRCLE:
			circle_ = static_cast<Circle*>(m_shape);
			circle_->copyToMesh(meshShape_);
			break;
		case DISK:
			disk_ = static_cast<Disk*>(m_shape);
			disk_->copyToMesh(meshShape_);
			break;
		case PARTIAL_DISK:
			pdisk_ = static_cast<PartialDisk*>(m_shape);
			pdisk_->copyToMesh(meshShape_);
			break;
		default:
			break;
		}

		delete m_shape;
		m_shape = meshShape_;
	}
}