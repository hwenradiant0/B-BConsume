#pragma once
#include "tile.h"
class CBomb_Tile2 :
	public CTile
{
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CBomb_Tile2(void);
	~CBomb_Tile2(void);
};

