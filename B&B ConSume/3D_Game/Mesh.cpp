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
	m_pMesh =NULL;//�޽� �ʱ�ȭ
	m_pchFilecourse=pFile;

	m_vPos=D3DXVECTOR3(0,0,0);//������ǥ��

	m_vSize=D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_vRotAngle=D3DXVECTOR3(0.0f,0.0f,0.0f);//�� ����

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
		//�ڽ�(����)
		if(FAILED(InitGeometry_Cube()))
			return E_FAIL;
	}
	else if(strcmp(m_pchFilecourse,Command_Sphere)==0)
	{
		//�÷��̾�
		D3DXCreateSphere(Get_Device,10,10,10,&m_pMesh,0);
		if(FAILED(InitGeometry_Sphere()))
			return E_FAIL;
	}
	else if(strcmp(m_pchFilecourse,Command_Cylinder) == 0)
	{
		//�����
		if(FAILED(InitGeometry_Cylinder()))
			return E_FAIL;
	}
	else
	{
		//x����
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
		OutputDebugString("�ؽ�ó �ε� ����: ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	}

	return ret;

}

HRESULT CMesh::InitGeometry_XFile()
{
	/// ������ �ӽ÷� ������ ���ۼ���
	LPD3DXBUFFER pD3DXMtrlBuffer;


	if( FAILED( D3DXLoadMeshFromX(m_pchFilecourse, D3DXMESH_SYSTEMMEM, //�ε��� ����,�޽��������-�ε������ۿ� ���ؽ� ���۸� �����ϰ� ���
		Get_Device, NULL, //�޽ø� �׸� ����̽��� ������,ID3DXBuffer ��ü�� ������,���� �̿��ϴ� ���� ������ �ٷ�
		&pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, //�Լ��� ���ϵɶ� �޽��� ���׸��� ����ü�� ä����,,���׸��� �迭�� ��ġ�� ����ü�� ����
		&m_pMesh ) ) )//�޽� ��ü�� �ּ�
	{
		MessageBox(NULL, "�޽� ������ �����", "Ȯ���غ�", MB_OK);
		return E_FAIL;		
	}	

	/// ���������� �ؽ��� ������ ���� �̾Ƴ���.
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// ����������ŭ ��������ü �迭 ����
	m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];	/// ����������ŭ �ؽ��� �迭 ����
	////////////���� ��� �����ϱ�///////////////////////////////////
	////////////�Լ��� �� ���� �־����� �����Ҵ� ������ �׳� �ڵ��////////////////////
	LPSTR Folder	= TextureFileFolder;
	LPSTR File		;
	LPSTR FileDirectory;
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{
		/// ���������� ����
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		
		/// �ֺ����������� Diffuse������
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		m_pMeshTextures[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0 )
		{	

			File		= d3dxMaterials[i].pTextureFilename;
			int len_a = strlen(Folder);
			int len_b = strlen(File);

			FileDirectory = new char[len_a+len_b+1];//�������� Ȯ��
			for(int j=0;j<len_a;j++)
			{
				*(FileDirectory+j) = *(Folder+j);
			}
			for(int j=0;j<len_b;j++)
			{
				*(FileDirectory+(len_a+j)) = *(File+j);
			}
			FileDirectory[len_a+len_b] = NULL;	




			/// �ؽ��ĸ� ���Ͽ��� �ε��Ѵ�
			if( FAILED( D3DXCreateTextureFromFileA( Get_Device, 
				FileDirectory, 
				&m_pMeshTextures[i] ) ) )

			{                        
				MessageBox(NULL, "�ؽ��� ���� �����", "Ȯ���غ�", MB_OK);
			}
			if(FileDirectory !=NULL)
				delete  FileDirectory;
		}
	}
	/// �ӽ÷� ������ �������� �Ұ�
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
		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// ����������ŭ ��������ü �迭 ����
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
		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// ����������ŭ ��������ü �迭 ����
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
		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];			/// ����������ŭ ��������ü �迭 ����
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
	/// �������
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
	
	//���ؽ� ���� Ʈ���� ����
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

	//if(m_dwNumMaterials==1)//���� ���׸����Ͻ�->�ؽ��Ĵ� ������� �ʴ´�.
	//{
	//	Get_Device->SetMaterial( m_pMeshMaterials );
	//	m_pMesh->DrawSubset( 0 );
	//}
	//else
	
	//for( DWORD i=0; i<m_dwNumMaterials; i++ )
	//{
	//	/// �κ����� �޽��� ������ �ؽ��� ����
	//	Get_Device->SetMaterial( &m_pMeshMaterials[i] );
	//	Get_Device->SetTexture( 0, m_pMeshTextures[i] );
	//	/// �κ����� �޽� ���
	//	m_pMesh->DrawSubset( i );
	//}
	if(m_pShader != NULL)
	{	
		m_pShader->SetVariable(m_vColor,matRot);
		m_pShader->Begin();
	}
	for( DWORD i=0; i<m_dwNumMaterials; i++ )
	{
		/// �κ����� �޽��� ������ �ؽ��� ����
		Get_Device->SetMaterial( &m_pMeshMaterials[i] );
		if(m_pMeshTextures[i] !=NULL)
		Get_Device->SetTexture( 0, m_pMeshTextures[i] );
		/// �κ����� �޽� ���
		m_pMesh->DrawSubset( i );
	}
	if(m_pShader != NULL)	
		m_pShader->End();
}


VOID CMesh:: Render(float energy)
{

	//if(m_dwNumMaterials==1)//���� ���׸����Ͻ�->�ؽ��Ĵ� ������� �ʴ´�.
	//{
	//	Get_Device->SetMaterial( m_pMeshMaterials );
	//	m_pMesh->DrawSubset( 0 );
	//}
	//else
	
	//for( DWORD i=0; i<m_dwNumMaterials; i++ )
	//{
	//	/// �κ����� �޽��� ������ �ؽ��� ����
	//	Get_Device->SetMaterial( &m_pMeshMaterials[i] );
	//	Get_Device->SetTexture( 0, m_pMeshTextures[i] );
	//	/// �κ����� �޽� ���
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
		/// �κ����� �޽��� ������ �ؽ��� ����
		Get_Device->SetMaterial( &m_pMeshMaterials[i] );
		if(m_pShader == NULL)
		Get_Device->SetTexture( 0, m_pMeshTextures[i] );
		/// �κ����� �޽� ���
		m_pMesh->DrawSubset( i );
	}
	if(m_pShader != NULL)	
		m_pShader->End();
}


LPD3DXMESH CMesh::Get_Mesh()
{
	return m_pMesh;
}