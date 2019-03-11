#pragma once
#include "Device.h"

#define MAX_PARTICLE 10000

class CParticle
{
protected:
	class CData
	{
	public:
		D3DXVECTOR3			m_Init_Pos;
		D3DXVECTOR3			m_Init_Spe;
		D3DXVECTOR3			m_Init_Acc;
		D3DXVECTOR3			m_Current_Pos;
		D3DXVECTOR3			m_Current_Spe;
		D3DXVECTOR3			m_Current_Acc;
		D3DXVECTOR3			m_Scale;

		float				m_elasticity;
		float				m_AirR;

		bool				m_Live;
		float				m_Life;
		DWORD				m_Opacity;

		int					m_Img_Index;
	};

	class CVertex
	{
	public:
		D3DXVECTOR3		Position;
		DWORD			diffuse;
		float			u,v;

		CVertex() : Position(0,0,0), u(0), v(0), diffuse(0xFFFFFFFF){};
		CVertex(float x, float y, float z, float u, float v, DWORD d)
			:Position(x,y,z), u(u), v(v), diffuse(d){};

		enum { FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1) };
	};

	enum TYPE
	{
		EXP,
		PET,
		RIS,
	};

protected:
	LPDIRECT3DTEXTURE9			m_pTex;
	CVertex*					m_pVtx[MAX_PARTICLE];
	WORD*						m_pIdx;

	bool				m_bRender;
	int					m_num;
	int					m_type;

	CData*				m_Data;

	D3DXMATRIX			matWorld;
	D3DXMATRIX			matTrans;
	D3DXMATRIX			matRotate;
	D3DXMATRIX			matScale;

	D3DXMATRIX			matBillBoard;

	float				m_frame;
	float				m_last_frame;

public:
	CParticle(void);
	~CParticle(void);

	int					Create(LPDIRECT3DTEXTURE9 pTex);
	virtual void		FrameMove();
	virtual void		Render();
	virtual void		CleanUp();

	virtual void		SetRender(bool Render, D3DXVECTOR3 Pos);	//활성화 비활성화
	virtual void		SetParticle(int i, D3DXVECTOR3 Pos);	//활성화 비활성화

	virtual	void		SetLive(bool state);
	virtual	bool		GetLive();
};

