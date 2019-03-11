#include "Particle.h"


CParticle::CParticle(void)
{
	m_bRender = false;

	memset(matTrans, 0, sizeof(matTrans));
}


CParticle::~CParticle(void)
{
}


int CParticle::Create(LPDIRECT3DTEXTURE9 pTex)
{
	//m_pTex = pTex;

	//m_Data = new CData[100];

	//m_num = 100;

	//m_pVtx = new CVertex[m_num*6];
	//m_pIdx = new WORD[m_num];

	return 0;
}

void CParticle::FrameMove()
{
	//if(m_bRender == true)
	//{
	//	m_last_frame = (float)timeGetTime();

	//	if((m_last_frame - m_frame)>10)
	//	{
	//		for(int i=0 ; i<m_num ; i++)
	//		{
	//			m_Data[i].m_Img_Index++;
	//			//m_Data[i].m_Img_Index = m_Data[i].m_Img_Index % 48;

	//			D3DXVECTOR3	m_vcAirR = m_Data[i].m_Current_Spe;
	//			float LengthSq = D3DXVec3LengthSq(&m_vcAirR); 

	//			D3DXVec3Normalize(&m_vcAirR, &m_vcAirR); 

	//			m_vcAirR = m_vcAirR * LengthSq * m_Data[i].m_AirR * -1;

	//			//if(m_Data[i].m_Current_Pos.y < 0)
	//			//{
	//			//	m_Data[i].m_Current_Spe.y = m_Data[i].m_Current_Spe.y * -1;
	//			//	m_Data[i].m_Current_Spe.y = m_Data[i].m_Current_Spe.y * m_Data[i].m_elasticity;
	//			//	m_Data[i].m_Current_Pos.y = m_Data[i].m_Current_Pos.y * -1;
	//			//}

	//			m_Data[i].m_Current_Acc = m_Data[i].m_Init_Acc + m_vcAirR;
	//			m_Data[i].m_Current_Spe = m_Data[i].m_Current_Spe + m_Data[i].m_Current_Acc;
	//			m_Data[i].m_Current_Pos = m_Data[i].m_Current_Pos + m_Data[i].m_Current_Spe;

	//			int	nIdxX	= m_Data[i].m_Img_Index % 8;
	//			int	nIdxY	= m_Data[i].m_Img_Index / 8;
	//			D3DXVECTOR2	uv00( (nIdxX+0)/8.f, (nIdxY+0)/8.f);
	//			D3DXVECTOR2	uv11( (nIdxX+1)/8.f, (nIdxY+1)/8.f);

	//			m_pVtx[i*6].Position = m_Data[i].m_Current_Pos;
	//			m_pVtx[i*6].u = uv00.x;
	//			m_pVtx[i*6].v = uv11.y;
	//			m_pVtx[(i*6)+1].Position = m_Data[i].m_Current_Pos + D3DXVECTOR3(0,1,0);
	//			m_pVtx[(i*6)+1].u = uv00.x;
	//			m_pVtx[(i*6)+1].v = uv00.y;
	//			m_pVtx[(i*6)+2].Position = m_Data[i].m_Current_Pos + D3DXVECTOR3(1,0,0);
	//			m_pVtx[(i*6)+2].u = uv11.x;
	//			m_pVtx[(i*6)+2].v = uv11.y;

	//			m_pVtx[(i*6)+3].Position = m_Data[i].m_Current_Pos + D3DXVECTOR3(1,1,0);
	//			m_pVtx[(i*6)+3].u = uv11.x;
	//			m_pVtx[(i*6)+3].v = uv00.y;
	//			m_pVtx[(i*6)+4].Position = m_pVtx[(i*6)+1].Position;
	//			m_pVtx[(i*6)+4].u = m_pVtx[(i*6)+1].u;
	//			m_pVtx[(i*6)+4].v = m_pVtx[(i*6)+1].v;
	//			m_pVtx[(i*6)+5].Position = m_pVtx[(i*6)+2].Position;
	//			m_pVtx[(i*6)+5].u = m_pVtx[(i*6)+2].u;
	//			m_pVtx[(i*6)+5].v = m_pVtx[(i*6)+2].v;
	//		}

	//		Device->GetTransform(D3DTS_VIEW, &matBillBoard);
	//		D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);

	//		m_frame = m_last_frame;
	//	}
	//}
}


void CParticle::Render()
{
	/*Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	
	if(m_bRender == true)
	{
		for(int i=0 ; i<m_num ; i++)
		{
			matBillBoard._41 = 0;
			matBillBoard._42 = 0;
			matBillBoard._43 = 0;

			D3DXMatrixTranslation(&matTrans, m_Data[i].m_Current_Pos.x, m_Data[i].m_Current_Pos.y, m_Data[i].m_Current_Pos.z);

			matWorld = matBillBoard * matTrans;

			Device->SetTransform(D3DTS_WORLD, &matWorld);
			Device->SetTexture(0, m_pTex);
			Device->SetFVF(CVertex::FVF);
			Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, m_pVtx, sizeof(CVertex));

			D3DXMatrixIdentity(&matWorld);
			Device->SetTransform(D3DTS_WORLD, &matWorld);
		}
	}

	Device->SetTexture(0, NULL);
	Device->SetRenderState(D3DRS_LIGHTING,FALSE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/
}


void CParticle::SetRender(bool Render, D3DXVECTOR3 Pos)
{
	m_bRender = Render;

	if(m_bRender == true)
	{
		for(int i=0 ; i<m_num ; i++)
		{
			SetParticle(i,Pos);
		}
	}
}


void CParticle::SetParticle(int i, D3DXVECTOR3 Pos)
{
	float fSpdR;
	float fSpdY;
	float fAngle;

	float fTheta;
	float fPhi;

	m_Data[i].m_AirR = (100+rand()%101) * 0.00001f;
	m_Data[i].m_elasticity = (50+rand()%51)*0.01f;

	//±¸
	fTheta = (-60.f + float(rand()%61)) - 30; 
	fPhi = float(rand()%360); 
	fSpdR = (-50.f + rand()%101) * 0.1f; 

	fTheta = D3DXToRadian(fTheta); 
	fPhi = D3DXToRadian(fPhi); 

	m_Data[i].m_Init_Acc = D3DXVECTOR3(0, -0.1f, 0); 

	m_Data[i].m_Init_Spe.x = fSpdR * sinf(fTheta) * sinf(fPhi); 
	m_Data[i].m_Init_Spe.y = fSpdR * cosf(fTheta); 
	m_Data[i].m_Init_Spe.z = fSpdR * sinf(fTheta) * cosf(fPhi); 

	m_Data[i].m_Init_Pos = Pos;

	m_Data[i].m_Current_Acc = m_Data[i].m_Init_Acc;
	m_Data[i].m_Current_Pos = m_Data[i].m_Init_Pos;
	m_Data[i].m_Current_Spe = m_Data[i].m_Init_Spe;

	m_Data[i].m_Img_Index = 0;
}


void CParticle::CleanUp()
{
	delete[] m_Data;
	m_Data = NULL;
}


void CParticle::SetLive(bool state)
{
	m_bRender = state;
}


bool CParticle::GetLive()
{
	return m_bRender;
}
