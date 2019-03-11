#pragma once
#include "Entity.h"
#include "Frustum.h"
#include "Shader.h"
class CTile :
	public CEntity
{
protected:
	int m_Material;
	int m_Energy;
	float Player_Energy;

	float m_Tick;
	float m_Stack;// 얼마 까지 움직일 것인가?

	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	D3DXVECTOR3 t_vMin;
	D3DXVECTOR3	t_vMax;
	bool		m_Put;
public:
	CTile(void);
	~CTile(void);

	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);

	bool Move();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Set_Material(int now_material);
	int Get_Material();
	void Set_Tile_Energy(float now_energy);
	int Get_Tile_Energy();
	void Set_Player_Energy(float now_energy);
	void Set_Stack(float now_Stack);
	float Get_Stack();
	virtual void SetPos(D3DXVECTOR3 Pos);
	void		Set_Put(bool ornot){m_Put=ornot;};
	bool		Get_Put(){return m_Put;};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//타일관련이라 여기에 추가하긴 했는데 나중에 문제생기면 옮기겠음

	

	virtual bool		Render(CFrustum* frustum);
};

