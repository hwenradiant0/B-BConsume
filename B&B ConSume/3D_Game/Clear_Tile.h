#pragma once
#include "tile.h"
class CClear_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CClear_Tile(void);
	~CClear_Tile(void);
};