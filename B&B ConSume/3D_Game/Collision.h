#pragma once
#include "Define.h"
#ifndef _COLLISION_H//������ ���� ����
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


	D3DXVECTOR3 vfaceNormal;//ȸ���� ����
	float fFaceD;//�����̵��� ����
	void CaculateNormal(D3DXVECTOR3 m1,D3DXVECTOR3 m2);

};

enum Cube_Face
{
	front,back,top,bottom,right,left
};
struct Cube :public CollModel
{
	Plane face[6];
	D3DXVECTOR3 Degree_face[6];//���̽����� �� �ڽ� ������ �Ÿ���
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
	//�浹 ����
	//
public:
	CCollision(void);
	~CCollision(void);
	void CreateMMB(D3DXVECTOR3 vMin , D3DXVECTOR3 vMax);//(MinMaxBox,��Ȯ�� ��Ī�� �ִ����� ������ �ּ�,�ִ� ������ �ڽ��� �����. �� �Լ��� �����ϸ� ���� �ڽ����� �ȴ�.)
	void CreateSphere(D3DXVECTOR3 vCenter , float Rad);

	bool CheckSp_B(Sphere Ball ,  Cube Box,D3DXVECTOR3*Value);//���� �ڽ����� �浹���ο� �浹�� �о ���͸� �����Ѵ�.
	bool CheckSp_B(D3DXVECTOR3 Pos,float Rad ,  Cube Box);
	bool CheckSp_B(Sphere Ball ,  Cube Box, D3DXVECTOR3*Value,D3DXVECTOR3*PlaneNormal);


	bool CheckSp_Sp(Sphere Ball , Sphere Ball2,D3DXVECTOR3*Value);//���� �ڽ����� �浹���ο� �浹�� �о ���͸� �����Ѵ�.
	
	void ReviceSRT(D3DXVECTOR3 scale,D3DXVECTOR3 rotateAngle,D3DXVECTOR3 centerPos);//�����ؾ��� ���� ����
	bool AABBvec_B(Cube Box, D3DXVECTOR3 Point, float error );

	D3DXVECTOR3 Find_Intersection_Box(D3DXVECTOR3 Point,D3DXVECTOR3 Vector,Cube Box);

	D3DXVECTOR3 CCollision::Find_IntersectPlane(D3DXVECTOR3 Point,D3DXVECTOR3 Vector,Cube Box);//�������� �����浹�� ���� ������ ����

	D3DXVECTOR3* Find_Intersection_Plane_To_VanRay(D3DXVECTOR3 Point,D3DXVECTOR3 Dirvec,D3DXVECTOR3 Normal,float D);
	bool		Find_Intersection_PlaneFromBox(Sphere Ball,Cube Box,D3DXVECTOR3 intersecPoint,int*FaceNum);
	Sphere	Get_Sp_Model(){return m_SpereModel;}
	Cube	Get_Cube_Model(){return m_CubeModel;}
	Plane	Get_Pl_Model(){return m_PlaneModel;}

	void Set_CP(D3DXVECTOR3 CCP);

	bool AABB_B_B(Cube Box, Cube Box2);

};
#endif

