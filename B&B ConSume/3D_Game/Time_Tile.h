#pragma once
#include "tile.h"
class CTime_Tile :
	public CTile
{
private:
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
public:
	CTime_Tile(void);
	~CTime_Tile(void);

	virtual bool		Render(CFrustum* frustum);
};
