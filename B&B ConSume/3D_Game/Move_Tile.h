#pragma once
#include "tile.h"
class CMove_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CMove_Tile(void);
	~CMove_Tile(void);

	virtual void SetPos(D3DXVECTOR3 Pos);
};

