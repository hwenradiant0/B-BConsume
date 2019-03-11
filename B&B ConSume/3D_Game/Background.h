#pragma once
#include "Device.h"


class CBackground
{
protected:
	class CVertex
	{
	public:
		D3DXVECTOR3		m_vPosition;
		DWORD			m_dwDiffuse;
		float			u,v;

		CVertex() : m_vPosition(0,0,0), u(0), v(0), m_dwDiffuse(0xFFFFFFFF){};
		CVertex(float x, float y, float z, float u, float v, DWORD d)
			:m_vPosition(x,y,z), u(u), v(v), m_dwDiffuse(d){};

		enum { FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1) };
	};

public:
	CBackground(void);
	~CBackground(void);

	virtual int	 Create(LPDIRECT3DTEXTURE9 pTex[]);
	virtual void FrameMove(D3DXVECTOR3 camera);
	virtual void Render();
	virtual void CleanUp();
};

