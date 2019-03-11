#include "Particle_Petal.h"


CParticle_Petal::CParticle_Petal(void)
{
	m_type = PET;
}


CParticle_Petal::~CParticle_Petal(void)
{
}


int CParticle_Petal::Create(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;

	m_num = 100;

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
		m_pVtx[i][1].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(0,3,0);
		m_pVtx[i][2].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(3,0,0);

		m_pVtx[i][3].Position = m_Data[i].m_Init_Pos + D3DXVECTOR3(3,3,0);
		m_pVtx[i][4].Position = m_pVtx[i][1].Position;
		m_pVtx[i][5].Position = m_pVtx[i][2].Position;
	}

	return 0;
}

void CParticle_Petal::FrameMove()
{
	if(m_bRender == true)
	{
		m_last_frame = (float)timeGetTime();

		if((m_last_frame - m_frame)>10)
		{
			for(int i=0 ; i<m_num ; i++)
			{
				if(m_Data[i].m_Img_Index > 16)
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

				int	nIdxX	= m_Data[i].m_Img_Index % 4;
				int	nIdxY	= m_Data[i].m_Img_Index / 4;
				D3DXVECTOR2	uv00( (nIdxX+0)/4.f, (nIdxY+0)/4.f);
				D3DXVECTOR2	uv11( (nIdxX+1)/4.f, (nIdxY+1)/4.f);

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

				if(m_Data[i].m_Current_Pos.y < Player_Pos.y - 10)
					SetParticle(i,D3DXVECTOR3(Player_Pos.x,Player_Pos.y-10,Player_Pos.z));
				if(m_Data[i].m_Current_Pos.y > Player_Pos.y - 5)
					SetParticle(i,D3DXVECTOR3(Player_Pos.x,Player_Pos.y-10,Player_Pos.z));
			}


			//��ƼŬ ����
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

			//��ƼŬ �����
			for(int i=0 ; i<m_num ; i++)
			{
				if(m_Data[i].m_Live == true)
					continue;
				this->SetParticle(i,D3DXVECTOR3(Player_Pos.x,Player_Pos.y-10,Player_Pos.z));
			}

			Get_Device->GetTransform(D3DTS_VIEW, &matBillBoard);
			D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);

			m_frame = m_last_frame;
		}
	}
}


void CParticle_Petal::Render()
{
	if(m_bRender == true)
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

		for(int i=0 ; i<m_num ; i++)
		{
			matBillBoard._41 = m_Data[i].m_Current_Pos.x;
			matBillBoard._42 = m_Data[i].m_Current_Pos.y;
			matBillBoard._43 = m_Data[i].m_Current_Pos.z;

			//D3DXMatrixTranslation(&matTrans, m_Data[i].m_Current_Pos.x, m_Data[i].m_Current_Pos.y, m_Data[i].m_Current_Pos.z);

			matWorld = matBillBoard;

			Get_Device->SetTransform(D3DTS_WORLD, &matWorld);
			Get_Device->SetTexture(0, m_pTex);
			Get_Device->SetFVF(CVertex::FVF);
			Get_Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, m_pVtx[i], sizeof(CVertex));
		}

		Get_Device->SetTexture(0, NULL);
		Get_Device->SetRenderState(D3DRS_LIGHTING,FALSE);
		Get_Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		Get_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		Get_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}


void CParticle_Petal::SetRender(bool Render, D3DXVECTOR3 Pos)
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


void CParticle_Petal::SetParticle(int i, D3DXVECTOR3 Pos)
{
	m_Data[i].m_AirR = (100+rand()%101) * 0.0002f;

	m_Data[i].m_Init_Acc = D3DXVECTOR3(0, -0.16f, 0); 

	if(Player_Velocity == D3DXVECTOR3(0,0,0))
		Player_Velocity.y = -1;

	m_Data[i].m_Init_Spe.x = (-15 + rand()%30) * 0.08f + Player_Velocity.x;
	m_Data[i].m_Init_Spe.y = (-15 + rand()%30) * 0.08f + Player_Velocity.y;
	m_Data[i].m_Init_Spe.z = (-15 + rand()%30) * 0.08f + Player_Velocity.z;

	m_Data[i].m_Init_Pos = Pos;

	m_Data[i].m_Current_Acc = m_Data[i].m_Init_Acc;
	m_Data[i].m_Current_Pos = m_Data[i].m_Init_Pos;
	m_Data[i].m_Current_Spe = m_Data[i].m_Init_Spe;

	m_Data[i].m_Live = true;
	m_Data[i].m_Life = (30 + rand()%71) * 0.01f;

	m_Data[i].m_Opacity = D3DXCOLOR(1,1,1,m_Data[i].m_Life);

	m_Data[i].m_Img_Index = 0;
}


void CParticle_Petal::SetPos(D3DXVECTOR3 Pos)
{
	Player_Pos = Pos;
}


void CParticle_Petal::SetVelocity(D3DXVECTOR3 Velocity)
{
	D3DXVec3Normalize(&Player_Velocity, &Velocity);
}