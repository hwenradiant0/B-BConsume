#pragma once
#include "Define.h"

#ifndef	_PHYSICS_H
#define _PHYSICS_H
class CPhysicData
{
private:
	//
	D3DXVECTOR3 m_vecLinerVelocity;//속도
	D3DXVECTOR3 m_vecLinerAcceleration;//가속도
	D3DXVECTOR3 m_vecForce;
	D3DXVECTOR3 m_Resistance;

	float m_fFric;//마찰계수
	float m_fMass;//질량
	float m_fElasticity;//탄성계수
	float m_vecGravityVelocity;//중력가속으로 인한 속도,일방향 이므로 플롯형으로 값만 저장
	float m_fGravity;//중력 계수

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
	float					GetFric(){return m_fFric;}//속도
	D3DXVECTOR3				GetLinerVelocity(){return m_vecLinerVelocity;}
	D3DXVECTOR3				GetLinerAcceleration(){return m_vecLinerAcceleration;}
	
	D3DXVECTOR3				GetResistance(){return m_Resistance;}
	D3DXVECTOR3				GetForce(){return m_vecForce;}

	float					GetGravityVelocity(){return m_vecGravityVelocity;}//속도
	float					GetGravity(){return m_fGravity;}//속도


};
class CPhisical//매개변수를 물리연산으로 계산하여 리턴해주는 클래스,연산만 하므로 굳이 어딘가에 선언하지 않아도 된다.
{	
public:
	CPhisical(void);
	~CPhisical(void);
	static CPhisical* GetInstance()
	{
		static CPhisical  Instance;
		return &Instance;
	}

	void PhysicActing(CPhysicData* Object);//데이터 인수에 따른 물리계산 후 위치 결과값을 매개변수에 대입
	void Apply_Velocity(CPhysicData* Object, D3DXVECTOR3*Pos);
	void PressGravity( CPhysicData* Object);//중력 적용
	void ElasticityCrash(CPhysicData*Object,CPhysicData*Tile,D3DXVECTOR3 NormalVec);//탄성충돌
	

	void Friction(CPhysicData* Object, float OutFric);//실행될때마다 지정 비율로 값을 초기값으로 되돌린다.
	
	
};
#endif

