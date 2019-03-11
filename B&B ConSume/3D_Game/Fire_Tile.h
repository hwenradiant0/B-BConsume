/*
타일번호 3번
*/
#pragma once
#include "tile.h"
class CFire_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CFire_Tile(void);
	~CFire_Tile(void);
};

