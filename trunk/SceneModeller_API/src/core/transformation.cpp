#include "transformation.h"

Transformation::Transformation()
{
    m_scale_vector = Vector3(1,1,1);
    m_rotation_vector = Rotation4();
    m_translation_vector = Vector3(0,0,0);
};

void Transformation::rotate(double x,double y,double z,double angle)
{
    m_rotation_vector = Rotation4(x,y,z,angle);

    double c = cos(angle);
    double s = sin(angle);

    m_rotation.setcell(0,0,x*x*(1-c)+c);
    m_rotation.setcell(0,1,x*y*(1-c)-z*s);
    m_rotation.setcell(0,2,x*z*(1-c)+y*s);
    m_rotation.setcell(0,3,0);

    m_rotation.setcell(1,0,y*x*(1-c)+z*s);
    m_rotation.setcell(1,1,y*y*(1-c)+c);
    m_rotation.setcell(1,2,y*z*(1-c)-x*s);
    m_rotation.setcell(1,3,0);

    m_rotation.setcell(2,0,x*z*(1-c)-y*s);
    m_rotation.setcell(2,1,y*z*(1-c)+x*s);
    m_rotation.setcell(2,2,z*z*(1-c)+c);
    m_rotation.setcell(2,3,0);

    m_rotation.setcell(3,0,0);
    m_rotation.setcell(3,1,0);
    m_rotation.setcell(3,2,0);
    m_rotation.setcell(3,3,1);

    // update m_transform
    //m_transform = m_rotation * m_transform;
}

void Transformation::scale(double x, double y, double z)
{
    m_scale_vector = Vector3(x, y, z);

    // update m_scale & m_transform
    m_scale.setcell(0, 0, x);
    m_scale.setcell(1, 1, y);
    m_scale.setcell(2, 2, z);

    //m_transform = m_scale * m_transform;
}

void Transformation::translate(double x,double y,double z)
{
    m_translation_vector = Vector3(x, y, z);

    // update m_translate & m_transform
    m_translate.setcol(3, m_translation_vector);
    //m_transform = m_translate * m_transform;
}

Vector3& Transformation::scale(){ return m_scale_vector; }
Vector3& Transformation::translation() { return m_translation_vector; }
Rotation4& Transformation::rotation() { return m_rotation_vector; }

Matrix& Transformation::rotationMatrix() { return m_rotation; }

Transformation Transformation::operator+(Transformation rhs)
{
    Transformation res_ ;
    res_.rotation() = m_rotation_vector * rhs.rotation();
    res_.scale()    = rhs.scale() + m_scale_vector - Vector3(1,1,1);
    res_.translation() = m_translation_vector + rhs.translation();

    return res_;
}

Transformation Transformation::operator*(Transformation rhs)
{
    Transformation res_ ;
    res_.rotation() = m_rotation_vector * rhs.rotation();
    res_.scale()    = rhs.scale() + rhs.rotation().applyToVector(m_scale_vector-Vector3(1,1,1));
    res_.translation() = rhs.rotation().applyToVector(m_translation_vector.scale(rhs.scale()))+rhs.translation();

    return res_;
}

Point3 Transformation::apply(Point3& p)
{
    Point3 ret_(p.x() + m_translation_vector.x(),
                p.y() + m_translation_vector.y(),
                p.z() + m_translation_vector.z() );

    ret_ = Point3(ret_.x() * m_scale_vector.x(),
                  ret_.y() * m_scale_vector.y(),
                  ret_.z() * m_scale_vector.z() );

    Vector3 vec_(ret_.x(), ret_.y(), ret_.z());
    vec_ = m_rotation_vector.applyToVector(vec_);

    return Point3(vec_.x(), vec_.y(), vec_.z());
    //return m_transform * p;
}

Vertex Transformation::applyToVertex(Vertex* vrt_)
{
    Vertex res_ ;
    res_.setX(vrt_->x()+m_translation_vector.x());
    res_.setY(vrt_->y()+m_translation_vector.y());
    res_.setZ(vrt_->z()+m_translation_vector.z());

    res_.setX(res_.x()*m_scale_vector.x());
    res_.setY(res_.y()*m_scale_vector.y());
    res_.setZ(res_.z()*m_scale_vector.z());

    Vector3 vct_(res_.x(),res_.y(),res_.z());
    vct_ = m_rotation_vector.applyToVector(vct_);

    return Vertex(vct_.x(), vct_.y(), vct_.z());
}

Shape* Transformation::apply(Shape* s)
{

    if (s->can_intersect() == false)
    {
        std::vector<Triangle*> list = s->refine();
        std::vector<Triangle*> list2;
        for(int i=0;i<list.size();i++)
        {
            Vector3 v1 = m_transform * (*(list[i]->a()));
            Vector3 v2 = m_transform * (*(list[i]->b()));
            Vector3 v3 = m_transform * (*(list[i]->c()));

            Triangle* t = new Triangle(Vertex(v1),Vertex(v2),Vertex(v3));
            list2.push_back(t);
        }

        Shape* rets = new TriangleMesh(list2);

        return rets;

    }
    else
    {
        return NULL;
    }
}
