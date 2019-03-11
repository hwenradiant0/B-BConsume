#pragma once
#include "Define.h"
#ifndef _COLLISION_H//재정의 오류 막기
#define _COLLISION_H


struct CollModel
{
	D3DXVECTOR3 centerPos;		
	D3DXVECTOR3 rotateAngle;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 collisionPoint;
};
struct Plane : public CollModel
{


	D3DXVECTOR3 vfaceNormal;//회전시 갱신
	float fFaceD;//평행이동시 갱신
	void CaculateNormal(D3DXVECTOR3 m1,D3DXVECTOR3 m2);

};

enum Cube_Face
{
	front,back,top,bottom,right,left
};
struct Cube :public CollModel
{
	Plane face[6];
	D3DXVECTOR3 Degree_face[6];//페이스센터 와 박스 센터의 거리차
	float length;
	float heigth;
	float depth;
	
};
struct Sphere : public CollModel
{
	float rad;
};

class CCollision//
{
	
	Sphere	m_SpereModel;
	Cube	m_CubeModel;
	Plane	m_PlaneModel;
	//충돌 교점
	//
public:
	CCollision(void);
	~CCollision(void);
	void CreateMMB(D3DXVECTOR3 vMin , D3DXVECTOR3 vMax);//(MinMaxBox,정확한 명칭이 있는지는 모르지만 최소,최대 점으로 박스를 만든다. 이 함수를 실행하면 모델은 박스형이 된다.)
	void CreateSphere(D3DXVECTOR3 vCenter , float Rad);

	bool CheckSp_B(Sphere Ball ,  Cube Box,D3DXVECTOR3*Value);//구와 박스간의 충돌여부와 충돌시 밀어낼 벡터를 리턴한다.
	bool CheckSp_B(D3DXVECTOR3 Pos,float Rad ,  Cube Box);
	bool CheckSp_B(Sphere Ball ,  Cube Box, D3DXVECTOR3*Value,D3DXVECTOR3*PlaneNormal);


	bool CheckSp_Sp(Sphere Ball , Sphere Ball2,D3DXVECTOR3*Value);//구와 박스간의 충돌여부와 충돌시 밀어낼 벡터를 리턴한다.
	
	void ReviceSRT(D3DXVECTOR3 scale,D3DXVECTOR3 rotateAngle,D3DXVECTOR3 centerPos);//갱신해야할 정보 갱신
	bool AABBvec_B(Cube Box, D3DXVECTOR3 Point, float error );

	D3DXVECTOR3 Find_Intersection_Box(D3DXVECTOR3 Point,D3DXVECTOR3 Vector,Cube Box);

	D3DXVECTOR3 CCollision::Find_IntersectPlane(D3DXVECTOR3 Point,D3DXVECTOR3 Vector,Cube Box);//반직선과 최초충돌한 면의 법벡을 리턴

	D3DXVECTOR3* Find_Intersection_Plane_To_VanRay(D3DXVECTOR3 Point,D3DXVECTOR3 Dirvec,D3DXVECTOR3 Normal,float D);
	bool		Find_Intersection_PlaneFromBox(Sphere Ball,Cube Box,D3DXVECTOR3 intersecPoint,int*FaceNum);
	Sphere	Get_Sp_Model(){return m_SpereModel;}
	Cube	Get_Cube_Model(){return m_CubeModel;}
	Plane	Get_Pl_Model(){return m_PlaneModel;}

	void Set_CP(D3DXVECTOR3 CCP);

	bool AABB_B_B(Cube Box, Cube Box2);

};
#endif

