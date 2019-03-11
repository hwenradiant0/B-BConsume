#include "Mesh.h"


CMesh::CMesh(void)
{	
}

CMesh::~CMesh(void)
{
	
}

VOID CMesh::Cleanup()
{	
	if( m_pMeshTextures )
	{
		for( DWORD i = 0; i < m_dwNumMaterials; i++ )
		{
			if( m_pMeshTextures[i] )
				m_pMeshTextures[i]->Release();
		}
		delete[] m_pMeshTextures;
	}
	if( m_pMesh != NULL )
		m_pMesh->Release();
}
VOID CMesh::Init(LPCSTR pFile, CShader* Shader)
{
	m_pMeshMaterials = NULL;
	m_pMeshTextures  = NULL;
	m_dwNumMaterials = 0L; 
	m_pMesh =NULL;//메쉬 초기화
	m_pchFilecourse=pFile;

	m_vPos=D3DXVECTOR3(0,0,0);//절대좌표상

	m_vSize=D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_vRotAngle=D3DXVECTOR3(0.0f,0.0f,0.0f);//축 각도

	m_pShader =  Shader;

	

	D3DXMatrixIdentity(&m_matWorld);

	

}
VOID CMesh::SetPos(D3DXVECTOR3 ppos)
{
	m_vPos=ppos;
}

VOID CMesh::SetRotation(FLOAT fXrot,FLOAT fYrot,FLOAT fZrot)
{
	m_vRotAngle.x=fXrot;
	m_vRotAngle.y=fYrot;
	m_vRotAngle.z=fZrot;
}
VOID CMesh::SetSize(FLOAT fSize)
{
	m_vSize=D3DXVECTOR3(fSize,fSize,fSize);
}

VOID CMesh::SetMaterial_DifAm(DWORD dwNumMaterial,float fR,float fG,float fB,float fA)
{

	//for( int i = 0 ; i < dwNumMaterial ; i++)
	//{


	//}

	m_vColor = D3DXVECTOR4(fR, fG, fB, fA);

}

VOID CMesh::Set_Size_Detail(float Sx,float Sy,float Sz)
{
	m_vSize = D3DXVECTOR3(Sx,Sy,Sz);
}
HRESULT CMesh::InitGeometry_Total()
{
	
	if(strcmp(m_pchFilecourse,Command_Cube)==0)
	{
		//박스(지형)
		if(FAILED(InitGeometry_Cube()))
			return E_FAIL;
	}
	else if(strcmp(m_pchFilecourse,Command_Sphere)==0)
	{
		//플레이어
		D3DXCreateSphere(Get_Device,10,10,10,&m_pMesh,0);
		if(FAILED(InitGeometry_Sphere()))
			return E_FAIL;
	}
	else if(strcmp(m_pchFilecourse,Command_Cylinder) == 0)
	{
		//원기둥
		if(FAILED(InitGeometry_Cylinder()))
			return E_FAIL;
	}
	else
	{
		//x파일
		if(FAILED(InitGeometry_XFile()))
			return E_FAIL;
	}

	return S_OK;
}

LPDIRECT3DTEXTURE9 CMesh::LoadTexturetwo(const char * filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if ( FAILED(D3DXCreateTextureFromFile(Get_Device, filename, &ret)) )
	{
		OutputDebugString("텍스처 로딩 실패: ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	}

	return ret;

}

HRESULT CMesh::InitGeometry_XFile()
{
	/// 재질을 임시로 보관할 버퍼선언
	LPD3DXBUFFER pD3DXMtrlBuffer;


	if( FAILED( D3DXLoadMeshFromX(m_pchFilecourse, D3DXMESH_SYSTEMMEM, //로드할 파일,메쉬생성방법-인덱스버퍼와 버텍스 버퍼를 동일하게 사용
		Get_Device, NULL, //메시를 그릴 디바이스의 포인터,ID3DXBuffer 객체의 포인터,서로 이웃하는 면의 정보를 다룸
		&pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, //함수가 리턴될때 메시의 메테리얼 구조체로 채워짐,,메테리얼 배열에 위치할 구조체의 개수
		&m_pMesh ) ) )//메시 객체의 주소
	{
		MessageBox(NULL, "메쉬 파일이 없어요", "확인해봐", MB_OK);
		return E_FAIL;		
	}	

	/// 재질정보와 텍스쳐 정보를 따로 뽑아낸다.
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// 재질개수만큼 재질구조체 배열 생성
	m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];	/// 재질개수만큼 텍스쳐 배열 생성
	////////////파일 경로 수정하기///////////////////////////////////
	////////////함수로 할 수도 있었지만 동적할당 문제로 그냥 코드로////////////////////
	LPSTR Folder	= TextureFileFolder;
	LPSTR File		;
	LPSTR FileDirectory;
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{
		/// 재질정보를 복사
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		
		/// 주변광원정보를 Diffuse정보로
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		m_pMeshTextures[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0 )
		{	

			File		= d3dxMaterials[i].pTextureFilename;
			int len_a = strlen(Folder);
			int len_b = strlen(File);

			FileDirectory = new char[len_a+len_b+1];//동적해제 확인
			for(int j=0;j<len_a;j++)
			{
				*(FileDirectory+j) = *(Folder+j);
			}
			for(int j=0;j<len_b;j++)
			{
				*(FileDirectory+(len_a+j)) = *(File+j);
			}
			FileDirectory[len_a+len_b] = NULL;	




			/// 텍스쳐를 파일에서 로드한다
			if( FAILED( D3DXCreateTextureFromFileA( Get_Device, 
				FileDirectory, 
				&m_pMeshTextures[i] ) ) )

			{                        
				MessageBox(NULL, "텍스쳐 맵이 없어요", "확인해봐", MB_OK);
			}
			if(FileDirectory !=NULL)
				delete  FileDirectory;
		}
	}
	/// 임시로 생성한 재질버퍼 소거
	pD3DXMtrlBuffer->Release();


	return S_OK;
}

HRESULT CMesh::InitGeometry_Cube()
{
	if(FAILED(D3DXCreateBox(Get_Device,Tile_Size,Tile_Size,Tile_Size,&m_pMesh,0)))
	{
		
		return E_FAIL;
	}
	else
	{
		m_dwNumMaterials=1;
		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// 재질개수만큼 재질구조체 배열 생성
		m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];	
		m_pMeshMaterials[0].Diffuse.r=1.0f;
		m_pMeshMaterials[0].Diffuse.g=0.0f;
		m_pMeshMaterials[0].Diffuse.b=1.0f;
		m_pMeshMaterials[0].Diffuse.a=1.0f;
		m_pMeshMaterials[0].Ambient =m_pMeshMaterials[0].Diffuse;
		m_pMeshTextures[0]=NULL;//LoadTexturetwo("Texture/Fieldstone.tga");
	}
	return S_OK;

}
HRESULT CMesh::InitGeometry_Sphere()
{
	if(FAILED(D3DXCreateSphere(Get_Device,Ball_Radius,Ball_Slices,Ball_Stacks,&m_pMesh,0)))
	{
	
		return E_FAIL;
	}
	else
	{
		m_dwNumMaterials=1;
		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// 재질개수만큼 재질구조체 배열 생성
		m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];	
		m_pMeshMaterials[0].Diffuse.r=1.0f;
		m_pMeshMaterials[0].Diffuse.g=0.0f;
		m_pMeshMaterials[0].Diffuse.b=1.0f;
		m_pMeshMaterials[0].Diffuse.a=1.0f;
		m_pMeshMaterials[0].Ambient =m_pMeshMaterials[0].Diffuse;
		m_pMeshTextures[0]=NULL;
		
	}
	
	return S_OK;
}

HRESULT	CMesh::InitGeometry_Cylinder()
{

	if(FAILED(D3DXCreateCylinder(Get_Device,5,5,20,10,200,&m_pMesh,0)))
	{
		return E_FAIL;
	}

	else
	{
		m_dwNumMaterials=1;
		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// 재질개수만큼 재질구조체 배열 생성
		m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];	
		m_pMeshMaterials[0].Diffuse.r=1.0f;
		m_pMeshMaterials[0].Diffuse.g=0.0f;
		m_pMeshMaterials[0].Diffuse.b=1.0f;
		m_pMeshMaterials[0].Diffuse.a=1.0f;
		m_pMeshMaterials[0].Ambient =m_pMeshMaterials[0].Diffuse;
		m_pMeshTextures[0]=NULL;


		return S_OK;
	}
}

VOID CMesh::SetupMatrices()
{
	/// 월드행렬
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matSize;

	D3DXMATRIXA16 matRot_x;
	D3DXMATRIXA16 matRot_y;
	D3DXMATRIXA16 matRot_z;

	D3DXMATRIXA16 matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matSize);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matRot_x);
	D3DXMatrixIdentity(&matRot_y);
	D3DXMatrixIdentity(&matRot_z);
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matSize,m_vSize.x,m_vSize.y,m_vSize.z);

	D3DXMatrixRotationX( &matRot_x, m_vRotAngle.x );
	D3DXMatrixRotationY( &matRot_y, m_vRotAngle.y );
	D3DXMatrixRotationZ( &matRot_z, m_vRotAngle.z );

	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);

	matRot=matRot_x*matRot_y*matRot_z;

	matWorld=matSize*matRot*matTrans;

	Get_Device->SetTransform( D3DTS_WORLD, &matWorld );

	m_matWorld = matWorld;
	
	//버텍스 정보 트랜스 수정
}




VOID CMesh::PlayerSetupMatrices(D3DXMATRIXA16 *CamerMatrix)
{

	D3DXMATRIXA16 matWorld;

	D3DXMATRIXA16 matSize;

	D3DXMATRIXA16 matRot_x;
	D3DXMATRIXA16 matRot_y;
	D3DXMATRIXA16 matRot_z;

	D3DXMATRIXA16 matTrans;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixIdentity(&matSize);

	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matRot_x);
	D3DXMatrixIdentity(&matRot_y);
	D3DXMatrixIdentity(&matRot_z);

	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matSize,m_vSize.x,m_vSize.y,m_vSize.z);

	//D3DXMatrixRotationYawPitchRoll( CamerMatrix, m_vRotAngle.x, m_vRotAngle.y, m_vRotAngle.z );
	
	D3DXMatrixRotationAxis(&matRot_x, &D3DXVECTOR3(CamerMatrix->_11,CamerMatrix->_21,CamerMatrix->_31),m_vRotAngle.x);
	D3DXMatrixRotationAxis(&matRot_y, &D3DXVECTOR3(CamerMatrix->_12,CamerMatrix->_22,CamerMatrix->_32),m_vRotAngle.y);
	D3DXMatrixRotationAxis(&matRot_z, &D3DXVECTOR3(CamerMatrix->_13,CamerMatrix->_23,CamerMatrix->_33),m_vRotAngle.z);

	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);
	matRot = matRot_x * matRot_y * matRot_z;
	matWorld=matSize*matRot*matTrans;

	Get_Device->SetTransform( D3DTS_WORLD, &matWorld );
}

VOID CMesh:: Render()
{

	//if(m_dwNumMaterials==1)//단일 메테리얼일시->텍스쳐는 사용하지 않는다.
	//{
	//	Get_Device->SetMaterial( m_pMeshMaterials );
	//	m_pMesh->DrawSubset( 0 );
	//}
	//else
	
	//for( DWORD i=0; i<m_dwNumMaterials; i++ )
	//{
	//	/// 부분집합 메시의 재질과 텍스쳐 설정
	//	Get_Device->SetMaterial( &m_pMeshMaterials[i] );
	//	Get_Device->SetTexture( 0, m_pMeshTextures[i] );
	//	/// 부분집합 메시 출력
	//	m_pMesh->DrawSubset( i );
	//}
	if(m_pShader != NULL)
	{	
		m_pShader->SetVariable(m_vColor,matRot);
		m_pShader->Begin();
	}
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{
		/// 부분집합 메시의 재질과 텍스쳐 설정
		Get_Device->SetMaterial( &m_pMeshMaterials[i] );
		if(m_pMeshTextures[i] !=NULL)
		Get_Device->SetTexture( 0, m_pMeshTextures[i] );
		/// 부분집합 메시 출력
		m_pMesh->DrawSubset( i );
	}
	if(m_pShader != NULL)	
		m_pShader->End();
}


VOID CMesh:: Render(float energy)
{

	//if(m_dwNumMaterials==1)//단일 메테리얼일시->텍스쳐는 사용하지 않는다.
	//{
	//	Get_Device->SetMaterial( m_pMeshMaterials );
	//	m_pMesh->DrawSubset( 0 );
	//}
	//else
	
	//for( DWORD i=0; i<m_dwNumMaterials; i++ )
	//{
	//	/// 부분집합 메시의 재질과 텍스쳐 설정
	//	Get_Device->SetMaterial( &m_pMeshMaterials[i] );
	//	Get_Device->SetTexture( 0, m_pMeshTextures[i] );
	//	/// 부분집합 메시 출력
	//	m_pMesh->DrawSubset( i );
	//}
	if(m_pShader != NULL)
	{	
		m_pShader->SetBrightness(energy);
		m_pShader->SetVariable(m_vColor,matRot);
		m_pShader->Begin();
	}
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{
		/// 부분집합 메시의 재질과 텍스쳐 설정
		Get_Device->SetMaterial( &m_pMeshMaterials[i] );
		if(m_pShader == NULL)
		Get_Device->SetTexture( 0, m_pMeshTextures[i] );
		/// 부분집합 메시 출력
		m_pMesh->DrawSubset( i );
	}
	if(m_pShader != NULL)	
		m_pShader->End();
}


LPD3DXMESH CMesh::Get_Mesh()
{
	return m_pMesh;
}