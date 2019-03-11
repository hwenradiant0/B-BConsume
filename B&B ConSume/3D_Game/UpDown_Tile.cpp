#include "UpDown_Tile.h"


CUpDown_Tile::CUpDown_Tile(void)
{
}


CUpDown_Tile::~CUpDown_Tile(void)
{
}

void CUpDown_Tile::SetPos(D3DXVECTOR3 Move)
{
	m_vPos=Move;

	m_vMin = t_vMin + m_vPos;
	m_vMax = t_vMax + m_vPos;

	cmObject->SetPos(m_vPos);
	m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0,0,0),m_vPos);
}


void CUpDown_Tile::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)
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

	SetMeshColor(0, 0.75f , 0.75f, 0.75f,1.0f);

	m_PhyData->Init_Phydata(1.0f,0.0f,0.5f,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0));

	m_Material = 12;
}


bool CUpDown_Tile::Render(CFrustum* frustum)//행렬및 렌더
{	
	Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Get_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Get_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	cmObject->SetupMatrices();
	if(frustum->IsInCube(m_vMin, m_vMax) == true)
		cmObject->Render();

	Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return 0;
}