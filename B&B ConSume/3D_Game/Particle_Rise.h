#pragma once
#include "particle.h"


class CParticle_Rise : public CParticle
{
private:
	int stage_num;

public:
	CParticle_Rise(void);
	virtual ~CParticle_Rise(void);

	virtual int			Create(LPDIRECT3DTEXTURE9 pTex);
	virtual void		FrameMove();
	virtual void		Render();
	virtual void		CleanUp();

	virtual void		SetRender(bool Render, D3DXVECTOR3 Pos);	//Ȱ��ȭ ��Ȱ��ȭ
	virtual void		SetParticle(int i, D3DXVECTOR3 Pos);	//Ȱ��ȭ ��Ȱ��ȭ

	void				SetStage(int num);
};

