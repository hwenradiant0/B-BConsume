#include "SkyBox.h"


CSkyBox::CSkyBox(void)
{
}


CSkyBox::~CSkyBox(void)
{
}


int CSkyBox::Create(LPDIRECT3DTEXTURE9 pTex[])
{
	for(int i=0 ; i<MAX_SKY_TEX ; ++i)
		m_pTex[i] = pTex[i];

	if( FAILED( Get_Device->CreateVertexBuffer(
		sizeof(CVertex) * 24,
		0,
		CVertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVtx, 0 ) ) )

		return -1;

	CVertex pVtx[24];

	pVtx[0] = CVertex(	  -250.0f, 250.0f,	   -250.0f, 0.0f, 1.0f, 0xFFFFFFFF );		// Top vertices
	pVtx[1] = CVertex(  250.0f, 250.0f,	   -250.0f, 0.0f, 0.0f, 0xFFFFFFFF );
	pVtx[2] = CVertex(    -250.0f, 250.0f,  250.0f, 1.0f, 1.0f, 0xFFFFFFFF );
	pVtx[3] = CVertex(  250.0f, 250.0f,  250.0f, 1.0f, 0.0f, 0xFFFFFFFF );

	pVtx[4] = CVertex(    -250.0f,  250.0f, 250.0f, 0.0f, 0.0f, 0xFFFFFFFF );		// Front vertices
	pVtx[5] = CVertex(  250.0f,  250.0f, 250.0f, 1.0f, 0.0f, 0xFFFFFFFF );
	pVtx[6] = CVertex(    -250.0f,    -250.0f, 250.0f, 0.0f, 1.0f, 0xFFFFFFFF );
	pVtx[7] = CVertex(  250.0f,    -250.0f, 250.0f, 1.0f, 1.0f, 0xFFFFFFFF );

	pVtx[8] = CVertex(   250.0f,  250.0f,    -250.0f, 0.0f, 0.0f, 0xFFFFFFFF );		// Back vertices
	pVtx[9] = CVertex(     -250.0f,  250.0f,    -250.0f, 1.0f, 0.0f, 0xFFFFFFFF );
	pVtx[10] = CVertex(  250.0f,    -250.0f,    -250.0f, 0.0f, 1.0f, 0xFFFFFFFF );
	pVtx[11] = CVertex(    -250.0f,    -250.0f,    -250.0f, 1.0f, 1.0f, 0xFFFFFFFF );

	pVtx[12] = CVertex(    -250.0f,  250.0f,    -250.0f, 0.0f, 0.0f, 0xFFFFFFFF );		// Left vertices
	pVtx[13] = CVertex(    -250.0f,  250.0f,  250.0f, 1.0f, 0.0f, 0xFFFFFFFF );
	pVtx[14] = CVertex(    -250.0f,    -250.0f,    -250.0f, 0.0f, 1.0f, 0xFFFFFFFF );
	pVtx[15] = CVertex(    -250.0f,    -250.0f,  250.0f, 1.0f, 1.0f, 0xFFFFFFFF );

	pVtx[16] = CVertex( 250.0f,  250.0f,  250.0f, 0.0f, 0.0f, 0xFFFFFFFF );		// Right vertices
	pVtx[17] = CVertex( 250.0f,  250.0f,    -250.0f, 1.0f, 0.0f, 0xFFFFFFFF );
	pVtx[18] = CVertex( 250.0f,    -250.0f,  250.0f, 0.0f, 1.0f, 0xFFFFFFFF );
	pVtx[19] = CVertex( 250.0f,    -250.0f,    -250.0f, 1.0f, 1.0f, 0xFFFFFFFF );

	pVtx[20] = CVertex(    -250.0f,    -250.0f,  250.0f, 1.0f, 0.0f, 0xFFFFFFFF );		// Bottom vertices
	pVtx[21] = CVertex(  250.0f,    -250.0f,  250.0f, 1.0f, 1.0f, 0xFFFFFFFF );
	pVtx[22] = CVertex(    -250.0f,    -250.0f,    -250.0f, 0.0f, 0.0f, 0xFFFFFFFF );
	pVtx[23] = CVertex(  250.0f,    -250.0f,    -250.0f, 0.0f, 1.0f, 0xFFFFFFFF );

	CVertex* pVertices;

	if( FAILED( m_pVtx->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return -1;

	memcpy( pVertices, pVtx, sizeof(CVertex) * 24);

	m_pVtx->Unlock();

	return 0;
}


void CSkyBox::FrameMove(D3DXVECTOR3 camera)
{
	D3DXMatrixTranslation(&m_matTrans, camera.x, camera.y, camera.z);
}


void CSkyBox::Render()
{
	Get_Device->SetRenderState( D3DRS_ZENABLE, FALSE );
	//D3DCULL_CCW  : 뒷면을 왼쪽 회전으로 컬링(Culling) 한다. 
	Get_Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	Get_Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	Get_Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	Get_Device->SetFVF(CVertex::FVF);
	Get_Device->SetStreamSource(0, m_pVtx, 0, sizeof(CVertex));

	m_matWorld =  m_matTrans;
	Get_Device->SetTransform(D3DTS_WORLD, &m_matWorld);

	for(int i=0; i< 6 ; ++i)
	{
		Get_Device->SetTexture(0, m_pTex[i]);
		Get_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2);
	}

	D3DXMatrixIdentity(&m_matWorld);

	Get_Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	Get_Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	Get_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
}


void CSkyBox::CleanUp()
{
}