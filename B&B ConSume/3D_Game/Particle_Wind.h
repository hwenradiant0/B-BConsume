#pragma once
#include "particle.h"

class CParticle_Wind : public CParticle
{
private:
	int count;

public:
	CParticle_Wind(void);
	virtual ~CParticle_Wind(void);

	virtual int			Create(LPDIRECT3DTEXTURE9 pTex);
	virtual void		FrameMove();
	virtual void		Render();

	virtual void		SetRender(bool Render, D3DXVECTOR3 Pos, D3DXVECTOR3 Nor);	//활성화 비활성화
};

