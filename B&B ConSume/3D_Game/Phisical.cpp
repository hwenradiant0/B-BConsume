#include "Phisical.h"


//������ �Լ�//////////////////
CPhysicData::CPhysicData()
{}
CPhysicData::~CPhysicData()
{

}
void	CPhysicData::Init_Phydata(float Mass,float Elas,float Fric,D3DXVECTOR3 Velocity ,D3DXVECTOR3 Accel )
{
	m_fMass					=Mass;
	m_fElasticity			= Elas;
	m_vecLinerVelocity		= Velocity;
	m_vecLinerAcceleration	= Accel;
	m_fFric					= Fric;
	m_vecGravityVelocity	= 0;
	m_fGravity				= Gravity;
	m_vecForce = D3DXVECTOR3(0,0,0);
	m_Resistance = D3DXVECTOR3(0,0,0);
}
void	CPhysicData::SetMass(float mass)
{
	m_fMass =mass;//����

}
void	CPhysicData::SetElasticity(float Elasticity)
{
	m_fElasticity = Elasticity;//ź�����

}
void	CPhysicData::SetLinerVelocity(D3DXVECTOR3 vecLinerVelocity)
{
	m_vecLinerVelocity = vecLinerVelocity;//��

}
void	CPhysicData::SetLinerAcceleration(D3DXVECTOR3 vecLinerAcceleration)
{
	m_vecLinerAcceleration = vecLinerAcceleration;

}

void	CPhysicData::SetGravityVelocity(float GV)
{
	m_vecGravityVelocity = GV;
}
void	CPhysicData::SetGravity(float g)
{
	m_fGravity = g;
}
void CPhysicData::SetResistance(D3DXVECTOR3 R)
{
	m_Resistance =R;
}
void		CPhysicData::AddForce(D3DXVECTOR3 m_Force)
{
	m_vecForce +=m_Force;
}
void		CPhysicData::ResetForce()
{
	m_vecForce = D3DXVECTOR3(0,0,0);
}
///������ �Լ�////////////////
CPhisical::CPhisical(void)
{
}


CPhisical::~CPhisical(void)
{
}


void CPhisical::PhysicActing(CPhysicData* Object)//������ �μ��� ���� ������� �� ��ġ ������� �Ű������� ����
{
	D3DXVECTOR3 Accel ;
	D3DXVECTOR3 Velocity ;
	D3DXVECTOR3 Gravi_Velocity =  D3DXVECTOR3(0,-Gravity,0);
	D3DXVECTOR3 Foce =Gravi_Velocity + Object->GetResistance();
	D3DXVECTOR3 ImpulseForce =Object->GetForce();
	


		
	


	Foce += ImpulseForce;		
	
	Accel = Foce/Object->GetMass();
	

	Velocity = Object->GetLinerVelocity() + Accel;
	
	D3DXVECTOR3 ResistFxz =Foce/Object->GetMass();
	
	if(abs(ResistFxz.x +Velocity.x)<=abs(ResistFxz.x) &&
		abs(ResistFxz.x)>abs(Velocity.x))//�� ���� ��ȣ�� �ٸ��� �������� �ӵ����� �������
		ResistFxz.x = -Velocity.x;

	if(abs(ResistFxz.z +Velocity.z)<=abs(ResistFxz.z) &&
		abs(ResistFxz.z)>abs(Velocity.z))//�� ���� ��ȣ�� �ٸ��� �������� �ӵ����� �������
		ResistFxz.z = -Velocity.z;

	Accel=Accel+ResistFxz;
	Velocity+=ResistFxz;
	Object->SetLinerAcceleration(Accel);
	Object->SetLinerVelocity(Velocity);
	
	Object->ResetForce();

}

void CPhisical::PressGravity( CPhysicData* Object)//�߷� ����
{
	float fGravityForce = Object->GetGravity();//Object->GetGravityVelocity();//�߷°��ӵ�
	Object->SetGravityVelocity(fGravityForce);
	

}
void CPhisical::Apply_Velocity(CPhysicData* Object, D3DXVECTOR3*Pos)
{
	D3DXVECTOR3 Velocity = Object->GetLinerVelocity();

	D3DXVECTOR3 Virtical = D3DXVECTOR3(0, Velocity.y, 0);

	D3DXVECTOR3 HorizenX = D3DXVECTOR3 (Velocity.x, 0 ,0);

	D3DXVECTOR3 HorizenZ = D3DXVECTOR3 (0, 0 ,Velocity.z);

	if(D3DXVec3Dot(&HorizenX,&HorizenX) >Max_Velocity_X*Max_Velocity_X)
	{
		D3DXVec3Normalize(&HorizenX,&HorizenX);
		HorizenX*=Max_Velocity_X;

	}

	if(D3DXVec3Dot(&Virtical,&Virtical) >Max_Velocity_Y*Max_Velocity_Y)
	{
		D3DXVec3Normalize(&Virtical,&Virtical);
		Virtical*=Max_Velocity_Y;

	}

	if(D3DXVec3Dot(&HorizenZ,&HorizenZ) >Max_Velocity_Z*Max_Velocity_Z)
	{
		D3DXVec3Normalize(&HorizenZ,&HorizenZ);
		HorizenZ*=Max_Velocity_Z;

	}
	Velocity = D3DXVECTOR3(HorizenX.x,Virtical.y,HorizenZ.z);
	Object->SetLinerVelocity(Velocity);

	*Pos +=  Velocity;
}
void CPhisical::Friction(CPhysicData* Object, float rate)
{
	int a=0;;
	
	D3DXVECTOR3 LinerVelocity=Object->GetLinerVelocity();
	D3DXVECTOR3 Resist;
	float		myFric;
	float		TileResist;
	float		fricForce;

	
	
	if(rate <= 0)//��ü���� ����
	{


		// resistance
		Resist.x =  LinerVelocity.x * (AirFric);
		Resist.y =  LinerVelocity.y * (AirFric);
		Resist.z =  LinerVelocity.z * (AirFric);


	}
	else
	{
		myFric				=Object->GetFric();
		TileResist			=rate;
		myFric =(myFric+rate)/2;
		if(myFric>1.0f)myFric=1.0f;
		fricForce			= myFric*Object->GetMass()*Object->GetGravity();
		Resist				= D3DXVECTOR3(LinerVelocity.x,0,LinerVelocity.z);
		if(D3DXVec3Dot(&Resist,&Resist)>1.f)//���� �ƴ�
			D3DXVec3Normalize(&Resist,&Resist);

		Resist.x			= Resist.x*fricForce;
		Resist.y			= LinerVelocity.y * (AirFric);
		Resist.z			= Resist.z*fricForce;
	}
	
	Object->SetResistance(-Resist);
}
void CPhisical::ElasticityCrash(CPhysicData*Object,CPhysicData*Tile,D3DXVECTOR3 NormalVec)
{
	
	if(D3DXVec3Dot(&NormalVec,&NormalVec)>1.f)//���� �ƴ�
	D3DXVec3Normalize(&NormalVec,&NormalVec);

	float Velocity1 = D3DXVec3Dot(&Object->GetLinerVelocity(), &NormalVec);
	float Velocity2 = D3DXVec3Dot(&Tile->GetLinerVelocity(), &NormalVec);
	float AverageElas = (Object->GetElasticity() * Tile->GetElasticity())/2;//��� ź�����, Ÿ���� 0�̸� ��ź��, 1�̸� �����浹


	float ElasVelo1 = ((Object->GetMass() - AverageElas*Tile->GetMass())*Velocity1 
		+ (1+AverageElas)*Tile->GetMass()*Velocity2)
		/(Object->GetMass()+Tile->GetMass());

	float ElasVelo2 = ((Tile->GetMass() - AverageElas*Object->GetMass())*Velocity2 
		+ (1+AverageElas)*Object->GetMass()*Velocity1)
		/(Object->GetMass()+Tile->GetMass());

	D3DXVECTOR3 Obj_Velocity = (ElasVelo1-Velocity1)*NormalVec + Object->GetLinerVelocity();

	D3DXVECTOR3 T_Velocity = (ElasVelo2-Velocity2)*NormalVec + Tile->GetLinerVelocity();
	
	Object->SetLinerVelocity(Obj_Velocity);


	

}