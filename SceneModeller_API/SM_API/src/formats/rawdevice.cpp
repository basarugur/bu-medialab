#include "rawdevice.h"

#include "fstream"

#include <map>
#include <sstream>

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

RawDevice::RawDevice() : SMIODevice()
{

}
RawDevice::~RawDevice()
{

}
void RawDevice::loadScene(std::string fl_ , Scene* sce_)
{
	std::fstream stream;


	stream.open(fl_.c_str(),std::ios::in);

	if (stream.is_open())
	{
		std::string currentString;
		TriangleMesh* currentObject = NULL;
		std::string currentObjectName;
		double x_,y_,z_;

		std::map<std::string, int> vertex_hash; 
		


		stream >> currentString;
		if ((currentString.at(0)>='0' && currentString.at(0)<='9')
			||currentString.at(0)=='-'||currentString.at(0)=='+')
		{
			currentObject = new TriangleMesh();
			currentObjectName = "unnamed object";
		}
		while( !stream.eof() && currentString!="")
		{			
			if ((currentString.at(0)>='0' && currentString.at(0)<='9')
				||currentString.at(0)=='-'||currentString.at(0)=='+')
			{

				Vertex *newVertexa;
				Vertex *newVertexb;
				Vertex *newVertexc;

				x_ = atof(currentString.c_str());
				stream >> y_ ;
				stream >> z_ ;

				std::ostringstream hash_key;
				hash_key  << x_ <<";"<< y_ <<";"<< z_ ; 
				if (vertex_hash.find(hash_key.str()) != vertex_hash.end())
				{
					newVertexa = currentObject->vertexList()[vertex_hash.find(hash_key.str())->second];
				}
				else
				{
					newVertexa = new Vertex(x_,y_,z_);
					currentObject->vertexList().push_back(newVertexa);
					vertex_hash.insert(std::pair<std::string,int>(hash_key.str(),
						currentObject->vertexList().size()-1));
				}

				stream >> x_ ;
				stream >> y_ ;
				stream >> z_ ;
				std::ostringstream hash_key1;
				hash_key1  << x_ <<";"<< y_ <<";"<< z_ ; 
				if (vertex_hash.find(hash_key1.str()) != vertex_hash.end())
				{
					newVertexb = currentObject->vertexList()[vertex_hash.find(hash_key1.str())->second];
				}
				else
				{
					newVertexb = new Vertex(x_,y_,z_);
					currentObject->vertexList().push_back(newVertexb);
					vertex_hash.insert(std::pair<std::string,int>(hash_key1.str(),
						currentObject->vertexList().size()-1));
				}

				stream >> x_ ;
				stream >> y_ ;
				stream >> z_ ;
				std::ostringstream hash_key2;
				hash_key2  << x_ <<";"<< y_ <<";"<< z_ ; 
				if (vertex_hash.find(hash_key2.str()) != vertex_hash.end())
				{
					newVertexc = currentObject->vertexList()[vertex_hash.find(hash_key2.str())->second];
				}
				else
				{
					newVertexc = new Vertex(x_,y_,z_);
					currentObject->vertexList().push_back(newVertexc);
					vertex_hash.insert(std::pair<std::string,int>(hash_key2.str(),
						currentObject->vertexList().size()-1));
				}

				currentObject->faceList().push_back(new Triangle(newVertexa,
					newVertexb,newVertexc));

				stream >> currentString;
			}
			else
			{
				if (currentObject != NULL)				
				{
					GfxObject* newObj_ = new GfxObject(currentObject,new Material(),new Transformation());
					newObj_->setName(currentObjectName);
					*sce_+=newObj_;
				}
				
				currentObject = new TriangleMesh();
				currentObjectName = currentString;
				vertex_hash.clear();

				stream >> currentString;
				while(!((currentString.at(0)>='0' && currentString.at(0)<='9')
					||currentString.at(0)=='-'||currentString.at(0)=='+') && !stream.eof())
				{
					currentObjectName += " ";
					currentObjectName += currentString;
					stream >> currentString;
				}
			}
		}
		GfxObject* newObj_ = new GfxObject(currentObject,new Material(),new Transformation());
		newObj_->setName(currentObjectName);
		*sce_+=newObj_;
	} 
	stream.close();
}
void RawDevice::loadObject(std::string fl_ , GfxObject* obj_)
{
}
void RawDevice::saveToFile(std::string fl_ , Scene* sce_)
{
	std::ofstream stream;

	stream.open(fl_.c_str(),std::ios::out);

	if (stream.is_open())
	{
		Transformation trns_;
		TriangleMesh* msh_ ; 
		Vertex tmpVer_;

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

			stream << obj_->getName() << std::endl;

			//
			if (obj_->getShape()->type() == TRIANGLE_MESH)
			{
				msh_ = static_cast<TriangleMesh*>(obj_->getShape());
				for (int faceInd=0;faceInd<msh_->faceList().size();faceInd++)
				{
					tmpVer_ = trns_.applyToVertex(msh_->faceList()[faceInd]->a());
					stream<<tmpVer_.x()<<" ";
					stream<<tmpVer_.y()<<" ";
					stream<<tmpVer_.z()<<" ";

					tmpVer_ = trns_.applyToVertex(msh_->faceList()[faceInd]->b());
					stream<<tmpVer_.x()<<" ";
					stream<<tmpVer_.y()<<" ";
					stream<<tmpVer_.z()<<" ";

					tmpVer_ = trns_.applyToVertex(msh_->faceList()[faceInd]->c());
					stream<<tmpVer_.x()<<" ";
					stream<<tmpVer_.y()<<" ";
					stream<<tmpVer_.z()<<std::endl;			
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

				for (int faceInd=0;faceInd<msh_->faceList().size();faceInd++)
				{
					tmpVer_ = trns_.applyToVertex(msh_->faceList()[faceInd]->a());
					stream<<tmpVer_.x()<<" ";
					stream<<tmpVer_.y()<<" ";
					stream<<tmpVer_.z()<<" ";

					tmpVer_ = trns_.applyToVertex(msh_->faceList()[faceInd]->b());
					stream<<tmpVer_.x()<<" ";
					stream<<tmpVer_.y()<<" ";
					stream<<tmpVer_.z()<<" ";

					tmpVer_ = trns_.applyToVertex(msh_->faceList()[faceInd]->c());
					stream<<tmpVer_.x()<<" ";
					stream<<tmpVer_.y()<<" ";
					stream<<tmpVer_.z()<<std::endl;			
				}

				delete msh_;
			}
		}
	}
	stream.close();
}
void RawDevice::saveMesh(std::string fl_ , TriangleMesh* obj_)
{
	std::ofstream stream;

	stream.open(fl_.c_str(),std::ios::out);

	if (stream.is_open())
	{
		for (int faceInd=0;faceInd<obj_->faceList().size();faceInd++)
		{
			stream<<obj_->faceList()[faceInd]->a()->x()<<" ";
			stream<<obj_->faceList()[faceInd]->a()->y()<<" ";
			stream<<obj_->faceList()[faceInd]->a()->z()<<" ";

			stream<<obj_->faceList()[faceInd]->b()->x()<<" ";
			stream<<obj_->faceList()[faceInd]->b()->y()<<" ";
			stream<<obj_->faceList()[faceInd]->b()->z()<<" ";

			stream<<obj_->faceList()[faceInd]->c()->x()<<" ";
			stream<<obj_->faceList()[faceInd]->c()->y()<<" ";
			stream<<obj_->faceList()[faceInd]->c()->z()<<std::endl;				
		}
		stream.close();
	} else 
	{
		stream.close();
	}
}
void RawDevice::loadMesh(std::string fl_ , TriangleMesh* obj_)
{
}