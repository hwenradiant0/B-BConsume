#pragma once
#include "tile.h"
class CStyro_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CStyro_Tile(void);
	~CStyro_Tile(void);
};

