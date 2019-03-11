#pragma once
#include "tile.h"
class CBomb_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CBomb_Tile(void);
	~CBomb_Tile(void);
};

