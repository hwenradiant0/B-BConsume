#pragma once
#include "Define.h"

#ifndef	_PHYSICS_H
#define _PHYSICS_H
class CPhysicData
{
private:
	//
	D3DXVECTOR3 m_vecLinerVelocity;//�ӵ�
	D3DXVECTOR3 m_vecLinerAcceleration;//���ӵ�
	D3DXVECTOR3 m_vecForce;
	D3DXVECTOR3 m_Resistance;

	float m_fFric;//�������
	float m_fMass;//����
	float m_fElasticity;//ź�����
	float m_vecGravityVelocity;//�߷°������� ���� �ӵ�,�Ϲ��� �̹Ƿ� �÷������� ���� ����
	float m_fGravity;//�߷� ���

public:
	CPhysicData(void);
	~CPhysicData(void);

	void			Init_Phydata(float Mass,float Elas,float Fric,D3DXVECTOR3 Velocity ,D3DXVECTOR3 Accel);

	void					SetMass(float mass);
	void					SetElasticity(float Elasticity);
	void					SetLinerVelocity(D3DXVECTOR3 m_vecLinerVelocity);
	void					SetLinerAcceleration(D3DXVECTOR3 m_vecLinerAcceleration);	
	void					SetGravityVelocity(float GV);
	void					SetGravity(float g);
	void					SetResistance(D3DXVECTOR3 R);

	void					AddForce(D3DXVECTOR3 m_Force);
	void					ResetForce();

	float					GetMass(){return m_fMass;}
	float					GetElasticity(){return m_fElasticity;}
	float					GetFric(){return m_fFric;}//�ӵ�
	D3DXVECTOR3				GetLinerVelocity(){return m_vecLinerVelocity;}
	D3DXVECTOR3				GetLinerAcceleration(){return m_vecLinerAcceleration;}
	
	D3DXVECTOR3				GetResistance(){return m_Resistance;}
	D3DXVECTOR3				GetForce(){return m_vecForce;}

	float					GetGravityVelocity(){return m_vecGravityVelocity;}//�ӵ�
	float					GetGravity(){return m_fGravity;}//�ӵ�


};
class CPhisical//�Ű������� ������������ ����Ͽ� �������ִ� Ŭ����,���길 �ϹǷ� ���� ��򰡿� �������� �ʾƵ� �ȴ�.
{	
public:
	CPhisical(void);
	~CPhisical(void);
	static CPhisical* GetInstance()
	{
		static CPhisical  Instance;
		return &Instance;
	}

	void PhysicActing(CPhysicData* Object);//������ �μ��� ���� ������� �� ��ġ ������� �Ű������� ����
	void Apply_Velocity(CPhysicData* Object, D3DXVECTOR3*Pos);
	void PressGravity( CPhysicData* Object);//�߷� ����
	void ElasticityCrash(CPhysicData*Object,CPhysicData*Tile,D3DXVECTOR3 NormalVec);//ź���浹
	

	void Friction(CPhysicData* Object, float OutFric);//����ɶ����� ���� ������ ���� �ʱⰪ���� �ǵ�����.
	
	
};
#endif

