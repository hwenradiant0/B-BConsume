#include "Entity.h"


CEntity::CEntity(void)
{
	
}


CEntity::~CEntity(void)
{
	if(cmObject!=NULL)//��������
	{
		cmObject->Cleanup();
		delete cmObject;
	}

	if(m_PhyData !=NULL)
		delete m_PhyData;


	
}
void CEntity::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//���� �ε��� �Ǹ� ��ȣ�� �Է��ϵ��� ����
{
	cmObject=new CMesh();
	cmObject->Init(pFile, Shader);
	cmObject->InitGeometry_Total();
	cmObject->SetPos(loadPos);
	m_vPos=loadPos;
	cmObject->SetSize(Size);
	//cmObject->SetupMatrices();
	m_PhyData = new CPhysicData;

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

void CEntity::SetPos(D3DXVECTOR3 Move)
{
	m_vPos=Move;
	cmObject->SetPos(m_vPos);
	m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0,0,0),m_vPos);

}
VOID CEntity::SetMeshColor(DWORD dwNumMaterial,float fR,float fG,float fB,float fA)
{
	cmObject->SetMaterial_DifAm(dwNumMaterial,fR, fG, fB, fA);
}

bool CEntity::Render()//��Ĺ� ����
{	
	cmObject->SetupMatrices();
	cmObject->Render();
	return 0;
}

VOID CEntity::SetRotation(FLOAT fXrot,FLOAT fYrot,FLOAT fZrot)
{
	m_vRotAngle.x=fXrot;
	m_vRotAngle.y=fYrot;
	m_vRotAngle.z=fZrot;

	cmObject->SetRotation(m_vRotAngle.x,m_vRotAngle.y,m_vRotAngle.z);
}

	void		CEntity::SetScale(D3DXVECTOR3 Move)
	{
		cmObject->Set_Size_Detail(Move.x,Move.y,Move.z);
	}