#include "Tile.h"


CTile::CTile(void)
{
	m_Energy = 100;
	m_Stack  = 0;
}


CTile::~CTile(void)
{
	if(m_Coll != NULL)
		delete m_Coll;
}
bool CTile::Move()
{
	m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0,0,0),m_vPos);

	cmObject->SetupMatrices();
	if(m_Material > 0)
		return true;
	else
	{
		return false;
	}
}

void CTile::Set_Material(int now_material)
{
	m_Material = now_material;
}

int CTile::Get_Material()
{
	return m_Material;
}

void CTile::Set_Tile_Energy(float now_energy)
{
	m_Energy = now_energy;
}

void CTile::Set_Player_Energy(float now_energy)
{
	Player_Energy = now_energy;
}

int CTile::Get_Tile_Energy()
{
	return m_Energy;
}

void CTile::Set_Stack(float now_Stack)
{
	m_Stack=now_Stack;
}

float CTile::Get_Stack()
{
	return m_Stack;
}

void CTile::SetPos(D3DXVECTOR3 Move)
{
	m_vPos=Move;

	m_vMin = t_vMin + m_vPos;
	m_vMax = t_vMax + m_vPos;

	cmObject->SetPos(m_vPos);
	m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0,0,0),m_vPos);
}

void CTile::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//파일 로딩만 되면 번호만 입력하도록 변경
{
	cmObject=new CMesh();
	cmObject->Init(pFile, Shader);
	cmObject->InitGeometry_Total();
	cmObject->SetPos(loadPos);
	m_vPos=loadPos;
	cmObject->SetSize(Size);
	//cmObject->SetupMatrices();
	m_PhyData = new CPhysicData;
	m_Put=false;
	if(strcmp(pCollType,Coll_TYPE_MMB)==0)
	{
		m_Coll =new CCollision;//상속자로 내려가야할 듯
		m_Coll->CreateMMB(D3DXVECTOR3(-Tile_Size/2,-Tile_Size/2,-Tile_Size/2),D3DXVECTOR3(Tile_Size/2,Tile_Size/2,Tile_Size/2));
	}
	else if(strcmp(pCollType,Coll_TYPE_Sphere)==0)
	{
		m_Coll			=	new CCollision;//
		m_Coll			->	CreateSphere(loadPos,Ball_Radius);
	}

	D3DXVECTOR3* pVtx = NULL;
	if (FAILED(cmObject->Get_Mesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtx)))
		return ;

	D3DXComputeBoundingBox((D3DXVECTOR3*)pVtx
		, cmObject->Get_Mesh()->GetNumVertices()
		, D3DXGetFVFVertexSize(cmObject->Get_Mesh()->GetFVF())
		, &m_vMin, &m_vMax);

	t_vMin = m_vMin;
	t_vMax = m_vMax;

	cmObject->Get_Mesh()->UnlockVertexBuffer();
}

bool CTile::Render(CFrustum* frustum)//행렬및 렌더
{	
	Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Get_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Get_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	cmObject->SetupMatrices();
	if(frustum->IsInCube(m_vMin, m_vMax) == true)
		cmObject->Render(Player_Energy);

	Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return 0;
}