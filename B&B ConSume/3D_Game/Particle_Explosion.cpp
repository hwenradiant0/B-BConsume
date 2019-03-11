#include "Particle_Explosion.h"


CParticle_Explosion::CParticle_Explosion(void)
{
	m_bRender = false;
	count = 0;
	m_type = EXP;
	memset(matTrans, 0, sizeof(matTrans));
}


CParticle_Explosion::~CParticle_Explosion(void)
{
}


int CParticle_Explosion::Create(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;

	m_num = 500;

	m_Data = new CData[m_num];

	for(int i=0 ; i<m_num ; ++i)
	{
		m_pVtx[i] = new CVertex[6];
		m_pIdx = new WORD[m_num];
	}

	for(int i=0; i<m_num; i++)
	{
		m_Data[i].m_AirR = 0;
		m_Data[i].m_Init_Acc = D3DXVECTOR3(0,0,0);
		m_Data[i].m_Init_Spe = D3DXVECTOR3(0,0,0);
		m_Data[i].m_Init_Pos = D3DXVECTOR3(0,0,0);
		m_Data[i].m_Current_Acc = D3DXVECTOR3(0,0,0);
		m_Data[i].m_Current_Spe = D3DXVECTOR3(0,0,0);
		m_Data[i].m_Current_Pos = D3DXVECTOR3(0,0,0);

		m_pVtx[i][0].Position = m_Data[i].m_Init_Pos;
		m_pVtx[i][1].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(0,2,0);
		m_pVtx[i][2].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(2,0,0);

		m_pVtx[i][3].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(2,2,0);
		m_pVtx[i][4].Position = m_pVtx[i][1].Position;
		m_pVtx[i][5].Position = m_pVtx[i][2].Position;
	}

	return 0;
}

void CParticle_Explosion::FrameMove()
{
	if(m_bRender == true)
	{
		m_last_frame = (float)timeGetTime();

		if((m_last_frame - m_frame)>10)
		{
			for(int i=0 ; i<m_num ; i++)
			{
				m_Data[i].m_Img_Index++;
				//m_Data[i].m_Img_Index = m_Data[i].m_Img_Index % 48;

				D3DXVECTOR3	m_vcAirR = m_Data[i].m_Current_Spe;
				float LengthSq = D3DXVec3LengthSq(&m_vcAirR); 

				D3DXVec3Normalize(&m_vcAirR, &m_vcAirR); 

				m_vcAirR = m_vcAirR * LengthSq * m_Data[i].m_AirR * -1;

				//if(m_Data[i].m_Current_Pos.y < 0)
				//{
				//	m_Data[i].m_Current_Spe.y = m_Data[i].m_Current_Spe.y * -1;
				//	m_Data[i].m_Current_Spe.y = m_Data[i].m_Current_Spe.y * m_Data[i].m_elasticity;
				//	m_Data[i].m_Current_Pos.y = m_Data[i].m_Current_Pos.y * -1;
				//}

				m_Data[i].m_Current_Acc = m_Data[i].m_Init_Acc + m_vcAirR;
				m_Data[i].m_Current_Spe = m_Data[i].m_Current_Spe + m_Data[i].m_Current_Acc;
				m_Data[i].m_Current_Pos = m_Data[i].m_Current_Pos + m_Data[i].m_Current_Spe;

				int	nIdxX	= m_Data[i].m_Img_Index % 8;
				int	nIdxY	= m_Data[i].m_Img_Index / 8;
				D3DXVECTOR2	uv00( (nIdxX+0)/8.f, (nIdxY+0)/8.f);
				D3DXVECTOR2	uv11( (nIdxX+1)/8.f, (nIdxY+1)/8.f);

				m_pVtx[i][0].u = uv00.x;
				m_pVtx[i][0].v = uv11.y;
				m_pVtx[i][0].diffuse = m_Data[i].m_Opacity;
				m_pVtx[i][1].u = uv00.x;
				m_pVtx[i][1].v = uv00.y;
				m_pVtx[i][1].diffuse = m_Data[i].m_Opacity;
				m_pVtx[i][2].u = uv11.x;
				m_pVtx[i][2].v = uv11.y;
				m_pVtx[i][2].diffuse = m_Data[i].m_Opacity;

				m_pVtx[i][3].u = uv11.x;
				m_pVtx[i][3].v = uv00.y;
				m_pVtx[i][3].diffuse = m_Data[i].m_Opacity;
				m_pVtx[i][4].u = m_pVtx[i][1].u;
				m_pVtx[i][4].v = m_pVtx[i][1].v;
				m_pVtx[i][4].diffuse = m_Data[i].m_Opacity;
				m_pVtx[i][5].u = m_pVtx[i][2].u;
				m_pVtx[i][5].v = m_pVtx[i][2].v;
				m_pVtx[i][5].diffuse = m_Data[i].m_Opacity;
			}

			//파티클 생명
			for(int i=0 ; i<m_num ; i++)
			{
				if(m_Data[i].m_Live == false)
					continue;

				m_Data[i].m_Life = m_Data[i].m_Life - 0.01f;
				m_Data[i].m_Opacity = D3DXCOLOR(1,1,1,m_Data[i].m_Life);
				if(m_Data[i].m_Life < 0)
				{
					m_Data[i].m_Live = false;
					continue;
				}
			}

			for(int i=0 ; i<m_num ; i++)
			{
				if(m_Data[i].m_Live == false)
					count++;
				if(count == m_num)
					m_bRender = false;
			}

			Get_Device->GetTransform(D3DTS_VIEW, &matBillBoard);
			D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);

			m_frame = m_last_frame;
		}
	}
}


void CParticle_Explosion::Render()
{
	Get_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Get_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Get_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Get_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Get_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	Get_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Get_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	Get_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Get_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Get_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	if(m_bRender == true)
	{
		for(int i=0 ; i<m_num ; i++)
		{
			matBillBoard._41 = m_Data[i].m_Current_Pos.x;
			matBillBoard._42 = m_Data[i].m_Current_Pos.y;
			matBillBoard._43 = m_Data[i].m_Current_Pos.z;

			matWorld = matBillBoard;

			Get_Device->SetTransform(D3DTS_WORLD, &matWorld);
			Get_Device->SetTexture(0, m_pTex);
			Get_Device->SetFVF(CVertex::FVF);
			Get_Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, m_pVtx[i], sizeof(CVertex));
		}
	}

	Get_Device->SetTexture(0, NULL);
	Get_Device->SetRenderState(D3DRS_LIGHTING,FALSE);
	Get_Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Get_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}


void CParticle_Explosion::SetRender(bool Render, D3DXVECTOR3 Pos)
{
	m_bRender = Render;

	float fSpdR;



	float fTheta;
	float fPhi;

	if(m_bRender == true)
	{
		for(int i=0 ; i<m_num ; i++)
		{
			m_Data[i].m_AirR = (100+rand()%101) * 0.00001f;
			m_Data[i].m_elasticity = (50+rand()%51)*0.01f;

			//구
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

			m_Data[i].m_Live = true;
			m_Data[i].m_Life = (30 + rand()%71) * 0.01f;

			m_Data[i].m_Opacity = D3DXCOLOR(1,1,1,m_Data[i].m_Life);
			m_Data[i].m_Img_Index = 0;
		}
	}
}


void CParticle_Explosion::CleanUp()
{

}