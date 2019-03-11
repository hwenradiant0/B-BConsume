/*
타일번호 2번
*/
#pragma once
#include "tile.h"
class CWater_Tile :
	public CTile
{
public:
	CWater_Tile(void);
	~CWater_Tile(void);

	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
};

