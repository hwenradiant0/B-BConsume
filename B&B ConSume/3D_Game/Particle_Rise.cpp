#include "Particle_Rise.h"


CParticle_Rise::CParticle_Rise(void)
{
	m_type = RIS;
	stage_num = 0;
}


CParticle_Rise::~CParticle_Rise(void)
{
}


int CParticle_Rise::Create(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;

	m_Data = new CData[500];

	m_num = 500;

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
		m_pVtx[i][1].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(0,20,0);
		m_pVtx[i][2].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(20,0,0);

		m_pVtx[i][3].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(20,20,0);
		m_pVtx[i][4].Position = m_pVtx[i][1].Position;
		m_pVtx[i][5].Position = m_pVtx[i][2].Position;
	}

	return 0;
}

void CParticle_Rise::FrameMove()
{
	if(m_bRender == true)
	{
		m_last_frame = (float)timeGetTime();

		if((m_last_frame - m_frame)>10)
		{
			for(int i=0 ; i<m_num ; i++)
			{
				if(m_Data[i].m_Img_Index > 12)
					m_Data[i].m_Img_Index = 0;
				else
					m_Data[i].m_Img_Index++;
				
				D3DXVECTOR3	m_vcAirR = m_Data[i].m_Current_Spe;
				float LengthSq = D3DXVec3LengthSq(&m_vcAirR); 

				D3DXVec3Normalize(&m_vcAirR, &m_vcAirR);

				m_vcAirR = m_vcAirR * LengthSq * m_Data[i].m_AirR * -1;

				m_Data[i].m_Current_Acc = m_Data[i].m_Init_Acc + m_vcAirR;
				m_Data[i].m_Current_Spe = m_Data[i].m_Current_Spe + m_Data[i].m_Current_Acc;
				m_Data[i].m_Current_Pos = m_Data[i].m_Current_Pos + m_Data[i].m_Current_Spe;

				int	nIdxX	= m_Data[i].m_Img_Index % 12;
				int	nIdxY	= m_Data[i].m_Img_Index / 1;
				D3DXVECTOR2	uv00( (nIdxX+0)/12.f, (nIdxY+0)/1.f);
				D3DXVECTOR2	uv11( (nIdxX+1)/12.f, (nIdxY+1)/1.f);

				m_pVtx[i][0].u = uv00.x;
				m_pVtx[i][0].v = uv11.y;
				m_pVtx[i][1].u = uv00.x;
				m_pVtx[i][1].v = uv00.y;
				m_pVtx[i][2].u = uv11.x;
				m_pVtx[i][2].v = uv11.y;

				m_pVtx[i][3].u = uv11.x;
				m_pVtx[i][3].v = uv00.y;
				m_pVtx[i][4].u = m_pVtx[i][1].u;
				m_pVtx[i][4].v = m_pVtx[i][1].v;
				m_pVtx[i][5].u = m_pVtx[i][2].u;
				m_pVtx[i][5].v = m_pVtx[i][2].v;

				if(m_Data[i].m_Current_Pos.y > 300)
					SetParticle(i,D3DXVECTOR3(0,0,0));
			}

			Get_Device->GetTransform(D3DTS_VIEW, &matBillBoard);
			D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);

			m_frame = m_last_frame;
		}
	}
}


void CParticle_Rise::Render()
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

			D3DXMatrixTranslation(&matTrans, m_Data[i].m_Current_Pos.x, m_Data[i].m_Current_Pos.y, m_Data[i].m_Current_Pos.z);

			matWorld = matBillBoard * matTrans;

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


void CParticle_Rise::SetRender(bool Render, D3DXVECTOR3 Pos)
{
	m_bRender = Render;

	if(m_bRender == true)
	{
		for(int i=0 ; i<m_num ; i++)
		{
			SetParticle(i, Pos);
		}
	}
}


void CParticle_Rise::SetParticle(int i, D3DXVECTOR3 Pos)
{
	m_Data[i].m_AirR = (100+rand()%101) * 0.02f;

	m_Data[i].m_Init_Acc = D3DXVECTOR3(0, 0.1f, 0); 

	m_Data[i].m_Init_Spe.x = 0;
	m_Data[i].m_Init_Spe.y = 0;
	m_Data[i].m_Init_Spe.z = 0;

	if(stage_num == 3)
	{
		m_Data[i].m_Init_Pos.x = rand()%2000 - 1000;
		m_Data[i].m_Init_Pos.y = rand()%2000 - 1000;
		m_Data[i].m_Init_Pos.z = rand()%2000 - 1000;
	}

	else if(stage_num == 1 || stage_num == 2)
	{
		m_Data[i].m_Init_Pos.x = rand()%5000 - 100;
		m_Data[i].m_Init_Pos.y = rand()%600 - 300;
		m_Data[i].m_Init_Pos.z = rand()%600 - 300;
	}

	m_Data[i].m_Current_Acc = m_Data[i].m_Init_Acc;
	m_Data[i].m_Current_Pos = m_Data[i].m_Init_Pos;
	m_Data[i].m_Current_Spe = m_Data[i].m_Init_Spe;

	m_Data[i].m_Scale.x = (5 + rand()%10) * 0.1f;
	m_Data[i].m_Scale.y = m_Data[i].m_Scale.x;

	m_Data[i].m_Img_Index = 0;
}


void CParticle_Rise::CleanUp()
{

}


void CParticle_Rise::SetStage(int num)
{
	stage_num = num;
}