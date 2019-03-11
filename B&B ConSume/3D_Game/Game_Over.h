#pragma once
#include "Entity.h"


class COver_Mesh : public CEntity
{	
	float Radian_Y;//y�� ȸ������
	bool m_bSelected;
public:
	COver_Mesh();
	~COver_Mesh();
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
	bool Move();
	void Set_Selected(bool Choice);
	bool Get_Selected(){return m_bSelected;}
};






class CGame_Over
{

	COver_Mesh*Game_Over_Title;
	COver_Mesh*Game_Over_Replay;
	COver_Mesh*Game_Over_BTT;

	float m_tick_GO_Run;
	int m_Max_Frame;
	int Now_Frame;

	int m_Left_Rotate_Frame;
	int m_Right_Rotate_Frame;
	int m_Normal_Rotate_Frame;

	int m_Rotate_Frame;

	float m_SelectColor_R;
	float m_SelectColor_G;
	float m_SelectColor_B;


	float Default_X_Angle;
	float Replay_Y_Angle;
	float BTT_Y_Angle;
	int cCurserCount;
	CShader * m_Shader;
public:
	CGame_Over(void);
	~CGame_Over(void);

	void Game_Over_Init(D3DXVECTOR3 TitlePos,D3DXVECTOR3 RePlayPos,D3DXVECTOR3 BTTPos);

	bool Game_OverTitle_Animation();//�ִϸ��̼� ������ Ʈ��
	void Game_OverReplay_Animation();
	void Game_OverBTT_Animation();
	int Game_Over_Move(bool Get_UP,bool Get_DOWN,bool Get_ENTER,float tick);//�޽��� Ŭ���� ȭ�� ������(�Ƹ� Ÿ��Ʋ�� ���� ����)



	float	LinerInterpo(float v0,float v1,float FrameperMax);
	

	
	void Clean_Up();
	void Render();//�׳� �ٷ� ȭ�� ���翵�� ���ִ°� ���� �� ����
};

