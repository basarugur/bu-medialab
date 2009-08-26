#include "EditingCamera.h"

#include <math.h>

void EditingCamera::moveForvard(double scale_)
{

}
void EditingCamera::returnPhi(double scale_)
{

}
void EditingCamera::returnTheta(double scale_)
{

}

void EditingCamera::setPosition(Point3 pos_) {
	m_position = pos_; 
}
void EditingCamera::setUpVector(Vector3 up_){
	m_upvector = up_;
}
void EditingCamera::zoomIn(double fctr)
{
	Vector3 dir_ = (m_at_point-m_position).normalize();
	Vector3 direction = dir_*((m_at_point-m_position).length())*(0.001*fctr);

	m_position = m_position + direction;
}
void EditingCamera::zoomOut(double fctr)
{
	Vector3 dir_ = (m_at_point-m_position).normalize();
	Vector3 direction = dir_*((m_at_point-m_position).length())*(0.001*fctr);

	m_position = m_position - direction;
}
void EditingCamera::setToCamera(Camera* cmr_)
{
	m_position = cmr_->position();
	m_at_point = cmr_->atPoint();
	m_upvector = cmr_->upVector();
	m_name = cmr_->getName();

}
//void EditingCamera::TumbleY(double fctr)
//{
//	double x_,y_,z_;
//	matrix<double> trans(4,4);
//	for (int i=0;i<4;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			if (i==j)
//				trans.setvalue(i,j,1);
//			else
//				trans.setvalue(i,j,0);
//		}
//	}
//	trans.setvalue(0,3,-m_at_point.x());
//	trans.setvalue(1,3,-m_at_point.y());
//	trans.setvalue(1,3,-m_at_point.z());
//
//	matrix<double> rot(4,4);
//	for (int i=0;i<4;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			if (i==j)
//				rot.setvalue(i,j,1);
//			else
//				rot.setvalue(i,j,0);
//		}
//	}
//	rot.setvalue(0,0,cos(fctr*0.5));
//	rot.setvalue(0,2,sin(fctr*0.5));
//	rot.setvalue(2,0,-sin(fctr*0.5));
//	rot.setvalue(2,2,cos(fctr*0.5));
//
//	matrix<double> inv_trans(4,4);
//	for (int i=0;i<4;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			if (i==j)
//				inv_trans.setvalue(i,j,1);
//			else
//				inv_trans.setvalue(i,j,0);
//		}
//	}
//	inv_trans.setvalue(0,3,m_at_point.x());
//	inv_trans.setvalue(1,3,m_at_point.y());
//	inv_trans.setvalue(1,3,m_at_point.z());
//
//	matrix<double> val(4,1);
//	val.setvalue(0,0,m_position.x());
//	val.setvalue(1,0,m_position.y());
//	val.setvalue(2,0,m_position.z());
//	val.setvalue(3,0,1);
//
//	matrix<double> allTrans1(4,4);
//	allTrans1.settoproduct(inv_trans,rot);
//	
//	matrix<double> allTrans(4,4);
//	allTrans.settoproduct(allTrans1,trans);
//
//	matrix<double> result(4,1);
//	result.settoproduct(allTrans,val);
//
//	bool succes;
//	result.getvalue(0,0,x_,succes);
//	result.getvalue(1,0,y_,succes);
//	result.getvalue(2,0,z_,succes);
//
//	m_position = Point3(x_,y_,x_);
//
//	val.setvalue(0,0,m_upvector.x());
//	val.setvalue(1,0,m_upvector.y());
//	val.setvalue(2,0,m_upvector.z());
//	val.setvalue(3,0,1);
//
//	result.settoproduct(allTrans,val);
//	result.getvalue(0,0,x_,succes);
//	result.getvalue(1,0,y_,succes);
//	result.getvalue(2,0,z_,succes);
//
//	m_upvector = Vector3(x_,y_,z_);
//
//}
//void EditingCamera::TumbleX(double fctr)
//{
//	double x_,y_,z_;
//	matrix<double> trans(4,4);
//	for (int i=0;i<4;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			if (i==j)
//				trans.setvalue(i,j,1);
//			else
//				trans.setvalue(i,j,0);
//		}
//	}
//
//	trans.setvalue(0,3,-m_at_point.x());
//	trans.setvalue(1,3,-m_at_point.y());
//	trans.setvalue(1,3,-m_at_point.z());
//
//	matrix<double> rot(4,4);
//	for (int i=0;i<4;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			if (i==j)
//				rot.setvalue(i,j,1);
//			else
//				rot.setvalue(i,j,0);
//		}
//	}
//	rot.setvalue(1,1,cos(fctr*0.5));
//	rot.setvalue(1,2,-sin(fctr*0.5));
//	rot.setvalue(2,1,sin(fctr*0.5));
//	rot.setvalue(2,2,cos(fctr*0.5));
//
//	matrix<double> inv_trans(4,4);
//	for (int i=0;i<4;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			if (i==j)
//				inv_trans.setvalue(i,j,1);
//			else
//				inv_trans.setvalue(i,j,0);
//		}
//	}
//	inv_trans.setvalue(0,3,m_at_point.x());
//	inv_trans.setvalue(1,3,m_at_point.y());
//	inv_trans.setvalue(1,3,m_at_point.z());
//
//	matrix<double> val(4,1);
//	val.setvalue(0,0,m_position.x());
//	val.setvalue(1,0,m_position.y());
//	val.setvalue(2,0,m_position.z());
//	val.setvalue(3,0,1);
//
//	matrix<double> allTrans1(4,4);
//	allTrans1.settoproduct(inv_trans,rot);
//
//	matrix<double> allTrans(4,4);
//	allTrans.settoproduct(allTrans1,trans);
//
//	matrix<double> result(4,1);
//	result.settoproduct(allTrans,val);
//
//	bool succes;
//	result.getvalue(0,0,x_,succes);
//	result.getvalue(1,0,y_,succes);
//	result.getvalue(2,0,z_,succes);
//
//	m_position = Point3(x_,y_,z_);
//
//	val.setvalue(0,0,m_upvector.x());
//	val.setvalue(1,0,m_upvector.y());
//	val.setvalue(2,0,m_upvector.z());
//	val.setvalue(3,0,1);
//
//	result.settoproduct(allTrans,val);
//	result.getvalue(0,0,x_,succes);
//	result.getvalue(1,0,y_,succes);
//	result.getvalue(2,0,z_,succes);
//
//	m_upvector = Vector3(x_,y_,z_);
//}