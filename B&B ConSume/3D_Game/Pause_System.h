#pragma once
#include "Entity.h"
struct sColorType
{
	float r;
	float g;
	float b;
	float a;
};

class CPause_Mesh :public CEntity
{
	bool bSelected;
	sColorType  DefaultColor;
	sColorType  SelectedColor;
	float Radian_Y;//y축 회전각도
	
public:
	CPause_Mesh();
	~CPause_Mesh();
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
	bool Move();
	void Is_Selected(bool Ans);
	void Set_DefaultColor(float R,float G,float B,float A );
	void Set_SelectedColor(float R,float G,float B,float A );
};


class CPause_System
{
	int cCurserCount;//현재 커서의 위치
	CPause_Mesh* PauMesh_Continue;
	CPause_Mesh* PauMesh_BtoT;
	CPause_Mesh* PauMesh_Pause;
	CShader*m_Shader;

public:
	CPause_System(void);
	~CPause_System(void);
	void Pause_init();
	int Pause_Move(bool Get_UP,bool Get_DOWN,bool Get_ENTER);
	void Clear_Up();//렌더객체 삭제
	void PickUp_Scene();//화면좌표설정에 필요한 정보 가져오기
	void Pause_Render();
};

