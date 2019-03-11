#include "UI_Mesh.h"


CUI_Mesh::CUI_Mesh(void)
{
}


CUI_Mesh::~CUI_Mesh(void)
{
}

void CUI_Mesh::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//���� �ε��� �Ǹ� ��ȣ�� �Է��ϵ��� ����
{
	cmObject=new CMesh();
	cmObject->Init(pFile, Shader);
	cmObject->InitGeometry_Total();
	cmObject->SetPos(loadPos);
	m_vPos=loadPos;
	cmObject->SetSize(Size);
	cmObject->SetupMatrices();
	m_PhyData = new CPhysicData;
	Red=0;
	Green=0;
	Blue=0;

	if(strcmp(pCollType,Coll_TYPE_MMB)==0)
	{
		m_Coll =new CCollision;//����ڷ� ���������� ��
		m_Coll->CreateMMB(D3DXVECTOR3(-Tile_Size/2,-Tile_Size/2,-Tile_Size/2),D3DXVECTOR3(Tile_Size/2,Tile_Size/2,Tile_Size/2));
	}
	else if(strcmp(pCollType,Coll_TYPE_Sphere)==0)
	{
		m_Coll			=	new CCollision;//
		m_Coll			->	CreateSphere(loadPos,Ball_Radius);
	}
}

bool CUI_Mesh::Move()
{
	return false;
}

void CUI_Mesh::Color_Change(int Loading_Num)
{
	m_Loading_Num=Loading_Num%6+1;

	if(Loading_Num==1)//������(0,0,0)
	{
		ColorRed(0,0,0,1);
		ColorGreen(0,0,0,1);
		ColorBlue(0,0,0,1);
	}
	else if(Loading_Num==2)		//������(1,0,0)
	{
		ColorRed(1,0,0,1);
		ColorGreen(0,0,0,1);
		ColorBlue(0,0,0,1);
	}
	else if(Loading_Num==3)	//�����(1,1,0)
	{
		ColorRed(1,0,0,1);
		ColorGreen(1,0,0,1);
		ColorBlue(0,0,0,1);
	}
	else if(Loading_Num==4)	//�����(1,1,0)
	{
		ColorRed(0.5,0,0,1);
		ColorGreen(1,0,0,1);
		ColorBlue(0,0,0,1);
	}
	else if(Loading_Num==5)	//�Ͼ��(1,1,1)
	{
		ColorRed(1,0,0,1);
		ColorGreen(1,0,0,1);
		ColorBlue(1,0,0,1);
	}
	else if(Loading_Num==6)	//�Ķ���(0,0,1)
	{
		ColorRed(0,0,0,1);
		ColorGreen(0,0,0,1);
		ColorBlue(1,0,0,1);
	}
	else if(Loading_Num==7)	//�Ķ���(0,0,1)
	{
		ColorRed(0,0,0,1);
		ColorGreen(0,0,0,1);
		ColorBlue(1,0,0,1);
	}
}