#pragma once
#include "tile.h"
class CWind_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CWind_Tile(void);
	~CWind_Tile(void);
};