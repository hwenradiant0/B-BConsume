#pragma once
#include "tile.h"
class CUpDown_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CUpDown_Tile(void);
	~CUpDown_Tile(void);

	virtual bool		Render(CFrustum* frustum);

	virtual void SetPos(D3DXVECTOR3 Pos);
};

