#pragma once
#include "particle.h"


class CParticle_Die : public CParticle
{
private:
	int count;

public:
	CParticle_Die(void);
	virtual ~CParticle_Die(void);

	virtual int			Create(LPDIRECT3DTEXTURE9 pTex);
	virtual void		FrameMove();
	virtual void		Render();

	virtual void		SetRender(bool Render, D3DXVECTOR3 Pos);	//활성화 비활성화
};

