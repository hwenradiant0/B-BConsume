#pragma once
#include "Entity.h"


class CHPB_Mesh : public CEntity
{	
	float Radian_Y;//y�� ȸ������
	
public:
	CHPB_Mesh();
	~CHPB_Mesh();
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
	bool Move();

};






class CHp_Bar_System
{

	CHPB_Mesh *m_Gage;
	CHPB_Mesh *m_Bar[8];

	//float m_tick_HP_Run;
	int m_Max_Frame;
	int Now_Frame;
	D3DXVECTOR3 Default_Pos;
	D3DXVECTOR3 Bar_Default_Pos[8];
	float Default_X_Angle;
	float Next_Y_Angle;
	float Presen_Energy;
	float Max_Energy;
	float Default_Scale;

	CShader * m_Gage_Shader;
	CShader * m_Bar_Shader;
public:
	CHp_Bar_System(void);
	~CHp_Bar_System(void);

	void HP_Sys_Init(D3DXVECTOR3 SetPos,float max_Energy);

	bool HP_SysGage_Animation();//
	void HP_SysBar_Animation();
	bool HP_Sys_Move(float Energy,float tick);//���ӹ��꿡 ���ϹǷ� ƽ�� ���� �ʿ䰡 ����.

	void Planet_tempeture_Algorithm(float *R,float *G , float *B);

	float	LinerInterpo(float v0,float v1,float FrameperMax);
	void	SettingCameraEyePos(D3DXVECTOR3 EyePos,D3DXVECTOR3 PlayerPos);
	

	D3DXVECTOR3 Get_Default_Pos(){return Default_Pos;};
	void Clean_Up();
	void Render();//�׳� �ٷ� ȭ�� ���翵�� ���ִ°� ���� �� ����->�Ͻ������� �����Ƿ� ���� 
};

