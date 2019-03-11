#pragma once
#include "particle.h"

class CParticle_Petal : public CParticle
{
private:
	D3DXVECTOR3			Player_Pos;
	D3DXVECTOR3			Player_Velocity;

public:
	CParticle_Petal(void);
	~CParticle_Petal(void);

	virtual int			Create(LPDIRECT3DTEXTURE9 pTex);
	virtual void		FrameMove();
	virtual void		Render();

	virtual void		SetRender(bool Render, D3DXVECTOR3 Pos);	//활성화 비활성화
	virtual void		SetParticle(int i, D3DXVECTOR3 Pos);	//활성화 비활성화

	void				SetPos(D3DXVECTOR3 Pos);
	void				SetVelocity(D3DXVECTOR3 Velocity);
};

