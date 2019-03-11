#pragma once
#include "tile.h"
class CMove_Wind_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CMove_Wind_Tile(void);
	~CMove_Wind_Tile(void);

	virtual void SetPos(D3DXVECTOR3 Pos);
};