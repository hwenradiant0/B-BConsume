#pragma once
#include "tile.h"
 class COne_Wind_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	COne_Wind_Tile(void);
	~COne_Wind_Tile(void);
};