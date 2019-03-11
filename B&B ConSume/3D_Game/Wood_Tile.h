#pragma once
#include "tile.h"
class CWood_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CWood_Tile(void);
	~CWood_Tile(void);
};