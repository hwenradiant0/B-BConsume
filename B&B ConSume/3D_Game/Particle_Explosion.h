#pragma once
#include "particle.h"


class CParticle_Explosion : public CParticle
{
private:
	int count;

public:
	CParticle_Explosion(void);
	~CParticle_Explosion(void);

	virtual int			Create(LPDIRECT3DTEXTURE9 pTex);
	virtual void		FrameMove();
	virtual void		Render();
	virtual void		CleanUp();

	virtual void		SetRender(bool Render, D3DXVECTOR3 Pos);	//활성화 비활성화
};

