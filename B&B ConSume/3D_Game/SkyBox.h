#pragma once
#include "background.h"


class CSkyBox : public CBackground
{
protected:
	LPDIRECT3DTEXTURE9			m_pTex[6];
	LPDIRECT3DVERTEXBUFFER9		m_pVtx;

	D3DXMATRIX				m_matTrans;
	D3DXMATRIX				m_matWorld;

public:
	CSkyBox(void);
	~CSkyBox(void);

	virtual int	 Create(LPDIRECT3DTEXTURE9 pTex[]);
	virtual void FrameMove(D3DXVECTOR3 camera);
	virtual void Render();
	virtual void CleanUp();
};

