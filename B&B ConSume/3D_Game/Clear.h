#pragma once
#include "Entity.h"
#include "Sound.h"


class CClear_Mesh : public CEntity
{	
	float Radian_Y;//y�� ȸ������
	
public:
	CClear_Mesh();
	~CClear_Mesh();
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
	bool Move();

};






class CClear_System
{
	Sound				*sound;
	LPDIRECTSOUNDBUFFER   g_lpDSBG[1];

	CClear_Mesh*Clear_Title;
	CClear_Mesh*Clear_Next;

	float m_tick_Clear_Run;
	int m_Max_Frame;
	int Now_Frame;

	float Default_X_Angle;
	float Next_Y_Angle;
	CShader * m_Shader;
public:
	CClear_System(void);
	~CClear_System(void);

	void Clear_Init(D3DXVECTOR3 TitlePos,D3DXVECTOR3 NextPos);

	bool ClearTitle_Animation();//�ִϸ��̼� ������ Ʈ��
	void ClearNext_Animation();
	bool Clear_Move(bool Enter,float tick);//�޽��� Ŭ���� ȭ�� ������(�Ƹ� Ÿ��Ʋ�� ���� ����)



	float	LinerInterpo(float v0,float v1,float FrameperMax);
	

	
	void Clean_Up();
	void Render();//�׳� �ٷ� ȭ�� ���翵�� ���ִ°� ���� �� ����

	void Volume(int num);
};

