#include "stldevice.h"


#include <QHash>
#include <QString>

#include "../core/sphere.h"
#include "../core/cube.h"
#include "../core/cone.h"
#include "../core/trianglemesh.h"
#include "../core/cylinder.h"
#include "../core/twosidedcylinder.h"
#include "../core/torus.h"
#include "../core/triangleshape.h"
#include "../core/rectangle.h"
#include "../core/circle.h"
#include "../core/disk.h"
#include "../core/partialdisk.h"


StlDevice::StlDevice() : SMIODevice()
{

}
StlDevice::~StlDevice()
{

}
void StlDevice::loadScene(std::string fl_ , Scene* sce_)
{
	std::fstream stream;


	stream.open(fl_.c_str(),std::ios::in);

	if (stream.is_open())
	{
		std::string currentString;
		TriangleMesh* currentObject = NULL;
		std::string currentObjectName;
		double x_,y_,z_;

		QHash<QString, int> vertex_hash; 
		QString hash_key;


		stream >> currentString;
		while( !stream.eof() && currentString!="")
		{			
			if (currentString == "facet")
			{
				stream >> currentString;

				Vertex *newVertexa;
				Vertex *newVertexb;
				Vertex *newVertexc;

				stream >> currentString; // newFace->normal.x;
				stream >> currentString; //newFace->normal.y;
				stream >> currentString; //newFace->normal.z;			

				stream >> currentString ;
				stream >> currentString ;
				stream >> currentString ;

				stream >> x_ ;
				stream >> y_ ;
				stream >> z_ ;

				hash_key = QString::number(x_)+QString::number(y_)+QString::number(z_);
				if (vertex_hash.contains(hash_key))
				{
					newVertexa = currentObject->vertexList()[vertex_hash[hash_key]];
				}
				else
				{
					newVertexa = new Vertex(x_,y_,z_);
					currentObject->vertexList().push_back(newVertexa);
					vertex_hash.insert(hash_key,
						currentObject->vertexList().size()-1);
				}

				stream>>currentString;
				stream >> x_ ;
				stream >> y_ ;
				stream >> z_ ;
				hash_key = QString::number(x_)+QString::number(y_)+QString::number(z_);
				if (vertex_hash.contains(hash_key))
				{
					newVertexb = currentObject->vertexList()[vertex_hash[hash_key]];
				}
				else
				{
					newVertexb = new Vertex(x_,y_,z_);
					currentObject->vertexList().push_back(newVertexb);
					vertex_hash.insert(hash_key,
						currentObject->vertexList().size()-1);
				}

				stream>>currentString;
				stream >> x_ ;
				stream >> y_ ;
				stream >> z_ ;
				hash_key = QString::number(x_)+QString::number(y_)+QString::number(z_);
				if (vertex_hash.contains(hash_key))
				{
					newVertexc = currentObject->vertexList()[vertex_hash[hash_key]];
				}
				else
				{
					newVertexc = new Vertex(x_,y_,z_);
					currentObject->vertexList().push_back(newVertexc);
					vertex_hash.insert(hash_key,
						currentObject->vertexList().size()-1);
				}

				currentObject->faceList().push_back(new Triangle(newVertexa,
					newVertexb,newVertexc));

				
				//face end loops
				stream>>currentString;
				stream>>currentString;

				stream >> currentString;
			}
			else if (currentString == "endsolid")
			{
				GfxObject* newObj_ = new GfxObject(currentObject,new Material(),new Transformation());
				newObj_->setName(currentObjectName);
				*sce_+=newObj_;

				while( currentString!="solid" && !stream.eof())
				{
					stream >> currentString;
				}
			}
			else if (currentString == "solid")
			{
				currentObject = new TriangleMesh();

				stream >> currentObjectName;
				stream >> currentString;
				while( currentString!="facet" && !stream.eof())
				{
					currentObjectName += " ";
					currentObjectName += currentString;
					stream >> currentString;
				}
			}
			//else
			//{
			//	if (currentObject != NULL)				
			//	{
			//		GfxObject* newObj_ = new GfxObject(currentObject,new Material(),new Transformation());
			//		newObj_->setName(currentObjectName);
			//		*sce_+=newObj_;
			//	}

			//	currentObject = new TriangleMesh();
			//	currentObjectName = currentString;

			//	stream >> currentString;
			//	while(!((currentString.at(0)>='0' && currentString.at(0)<='9')
			//		||currentString.at(0)=='-'||currentString.at(0)=='+') && !stream.eof())
			//	{
			//		currentObjectName += " ";
			//		currentObjectName += currentString;
			//		stream >> currentString;
			//	}
			//}
		}
	} 
	stream.close();
}
void StlDevice::loadObject(std::string fl_ , GfxObject* obj_)
{
}
void StlDevice::saveToFile(std::string fl_ , Scene* sce_)
{
	std::ofstream stltream;
	stltream.open(fl_.c_str(),std::ios::out);
	if (stltream.is_open())
	{
		Transformation trns_;
		TriangleMesh* msh_ ; 
		Vertex tmpVera_,tmpVerb_,tmpVerc_;
		Vector3 tmpNorm_;

		for (int i=0 ; i<sce_->objects().size() ; i++)
		{
			GfxObject* obj_ = sce_->objects()[i];
			trns_ =  *obj_->getIndividualTranform()+
				*obj_->getPublicTranform();
			GfxObject* tmp_ = obj_->getParent();
			while(tmp_ != NULL)
			{
				trns_ = trns_*(*tmp_->getPublicTranform());
				tmp_ = tmp_->getParent();
			}
			stltream << "solid " << obj_->getName() << std::endl;

            
			//
			if (obj_->getShape()->type() == TRIANGLE_MESH)
			{
				msh_ = static_cast<TriangleMesh*>(obj_->getShape());

				for (int k=0;k<msh_->faceList().size();k++)
				{
					tmpVera_ = trns_.applyToVertex(msh_->faceList()[k]->a());
					tmpVerb_ = trns_.applyToVertex(msh_->faceList()[k]->b());
					tmpVerc_ = trns_.applyToVertex(msh_->faceList()[k]->c());
					tmpNorm_ = ((tmpVerc_ - tmpVera_) ^ (tmpVerb_ - tmpVera_)).normalize();

					stltream << "facet normal ";
					stltream << tmpNorm_.x() << " ";
					stltream << tmpNorm_.y() << " ";
					stltream << tmpNorm_.z() << std::endl;

					stltream << "outer loop" << std::endl;

					stltream << "vertex ";
					stltream << tmpVera_.x() << " ";
					stltream << tmpVera_.y() << " ";
					stltream << tmpVera_.z() << std::endl;

					stltream << "vertex ";
					stltream << tmpVerb_.x() << " ";
					stltream << tmpVerb_.y() << " ";
					stltream << tmpVerb_.z() << std::endl;

					stltream << "vertex ";
					stltream << tmpVerc_.x() << " ";
					stltream << tmpVerc_.y() << " ";
					stltream << tmpVerc_.z() << std::endl;

					stltream << "endloop" << std::endl;
					stltream << "endfacet" << std::endl;			
				}

			}
			else
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
				msh_ = new TriangleMesh();
				switch(obj_->getShape()->type())
				{
				case CUBE:
					cp_ = static_cast<Cube*>(obj_->getShape());
					cp_->copyToMesh(msh_);
					break;
				case SPHERE:
					sph_ = static_cast<Sphere*>(obj_->getShape());
					sph_->copyToMesh(msh_);
					break;
				case CONE:
					cne_ = static_cast<Cone*>(obj_->getShape());
					cne_->copyToMesh(msh_);
					break;
				case CYLINDER:
					cyld_ = static_cast<Cylinder*>(obj_->getShape());
					cyld_->copyToMesh(msh_);
					break;
				case TWO_SIDED_CYLINDER:
					twcyl_ = static_cast<TwoSidedCylinder*>(obj_->getShape());
					twcyl_->copyToMesh(msh_);
					break;
				case TORUS:
					trs_ = static_cast<Torus*>(obj_->getShape());
					trs_->copyToMesh(msh_);
					break;
				case TRIANGLE_SHAPE:
					trngshp_ = static_cast<TriangleShape*>(obj_->getShape());
					trngshp_->copyToMesh(msh_);
					break;
				case RECTANGLE:
					rect_ = static_cast<RectangleShape*>(obj_->getShape());
					rect_->copyToMesh(msh_);
					break;
				case CIRCLE:
					circle_ = static_cast<Circle*>(obj_->getShape());
					circle_->copyToMesh(msh_);
					break;
				case DISK:
					disk_ = static_cast<Disk*>(obj_->getShape());
					disk_->copyToMesh(msh_);
					break;
				case PARTIAL_DISK:
					pdisk_ = static_cast<PartialDisk*>(obj_->getShape());
					pdisk_->copyToMesh(msh_);
					break;
				default:
					break;
				}


				for (int k=0;k<msh_->faceList().size();k++)
				{
					tmpVera_ = trns_.applyToVertex(msh_->faceList()[k]->a());
					tmpVerb_ = trns_.applyToVertex(msh_->faceList()[k]->b());
					tmpVerc_ = trns_.applyToVertex(msh_->faceList()[k]->c());
					tmpNorm_ = ((tmpVerc_ - tmpVera_) ^ (tmpVerb_ - tmpVera_)).normalize();

					stltream << "facet normal ";
					stltream << tmpNorm_.x() << " ";
					stltream << tmpNorm_.y() << " ";
					stltream << tmpNorm_.z() << std::endl;

					stltream << "outer loop" << std::endl;

					stltream << "vertex ";
					stltream << tmpVera_.x() << " ";
					stltream << tmpVera_.y() << " ";
					stltream << tmpVera_.z() << std::endl;

					stltream << "vertex ";
					stltream << tmpVerb_.x() << " ";
					stltream << tmpVerb_.y() << " ";
					stltream << tmpVerb_.z() << std::endl;

					stltream << "vertex ";
					stltream << tmpVerc_.x() << " ";
					stltream << tmpVerc_.y() << " ";
					stltream << tmpVerc_.z() << std::endl;

					stltream << "endloop" << std::endl;
					stltream << "endfacet" << std::endl;			
				}

				delete msh_;
			}

			stltream << "endsolid " << obj_->getName() << std::endl;
		}
	}
	stltream.close();
}
void StlDevice::saveMesh(std::string fl_ , TriangleMesh* obj_)
{
}
void StlDevice::loadMesh(std::string fl_ , TriangleMesh* obj_)
{
}