/*
타일번호 1번
*/
#pragma once
#include "tile.h"
class CIron_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CIron_Tile(void);
	~CIron_Tile(void);
};