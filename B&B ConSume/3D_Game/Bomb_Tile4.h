#pragma once
#include "tile.h"
class CBomb_Tile4 :
	public CTile
{
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CBomb_Tile4(void);
	~CBomb_Tile4(void);
};

