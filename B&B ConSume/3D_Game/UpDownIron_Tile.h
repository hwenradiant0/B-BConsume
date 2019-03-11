#pragma once
#include "tile.h"
class CUpDownIron_Tile : public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CUpDownIron_Tile(void);
	~CUpDownIron_Tile(void);

	virtual void SetPos(D3DXVECTOR3 Pos);
};

