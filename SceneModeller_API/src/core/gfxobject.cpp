#include "gfxobject.h"

#include "shape.h"

#include <iostream>

void GfxObject::getCopy(GfxObject*& newObj_)
{

    Material* mt_ = new Material(m_material->diffcolor(),
                                 m_material->speccolor(),
                                 m_material->ambientcolor());

    mt_->set_reflective(m_material->reflection());
    mt_->set_luculent(m_material->luculent());
    mt_->set_solid(m_material->solid());
    mt_->set_refraction_index(m_material->refraction_index());

    Transformation* trns_ = new Transformation();
    trns_->rotation() = m_global_transform->rotation();
    trns_->scale() = m_global_transform->scale();
    trns_->translation() = m_global_transform->translation();

    newObj_ = new GfxObject(m_shape->getNewCopy(), mt_, trns_);

    newObj_->setName(m_name);

    newObj_->getLocalTransform()->rotation() = m_local_transform->rotation();
    newObj_->getLocalTransform()->scale() = m_local_transform->scale();
    newObj_->getLocalTransform()->translation() = m_local_transform->translation();

}

void GfxObject::convertToMesh()
{
	if(m_shape->type() != TRIANGLE_MESH)
	{
		TriangleMesh* meshShape_ = new TriangleMesh();

        m_shape->copyToMesh( meshShape_ );


		delete m_shape;

		m_shape = meshShape_;
	}
}

void GfxObject::draw( drawType dt_ )
{
	glPushMatrix();

    if ( m_parent != NULL )
    {   cout << "CT: " << m_local_transform->translation().x() << endl;
        cout << "CS: " << m_shape->type() << endl;
        cout << "CM: " << m_material->diffcolor().r << endl << endl;
    }

	glTranslatef( m_local_transform->translation().x(),
                  m_local_transform->translation().y(),
                  m_local_transform->translation().z() );

	glScalef( m_local_transform->scale().x(),
              m_local_transform->scale().y(),
              m_local_transform->scale().z());

	glRotatef( m_local_transform->rotation().theta(),
               m_local_transform->rotation().ax(),
               m_local_transform->rotation().ay(),
               m_local_transform->rotation().az());

	if( m_selected )
		glColor3f(SELECTED_COLOR);
	else
		glColor3f( m_material->diffcolor().r,
                   m_material->diffcolor().g,
                   m_material->diffcolor().b );

    /// Now let my own shape (if exists) draw itself:
    m_shape->draw( dt_ );

    /// And call my children to draw()
    for (int c=0; c < m_child_list.size(); c++)
    {
        m_child_list[c]->draw( dt_ );
    }

    glPopMatrix();

}
