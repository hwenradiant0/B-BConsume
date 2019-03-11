#pragma once
#include "Entity.h"
class CPlayer :public CEntity
{
	float RotateRotateSpeed;
	float Rotate;

	bool	m_bInput_SPACE;
	bool	m_bInput_W;
	bool	m_bInput_S;
	bool	m_bInput_D;
	bool	m_bInput_A;

	int		m_icJump;
	bool	m_bJump_State;
	bool	m_bScale_Change;

	float m_Player_Energy;


	D3DXVECTOR3	Moving_Direction;//������ ����
	float		Moving_DirAngle;

	D3DXVECTOR3 Transe_Scale;
	int			count;
	bool		rise;
	
public:
	CPlayer(void);
	~CPlayer(void);
	
	float Red;
	float Green;
	float Blue;

	bool Move();
	void PlayerMove(D3DXMATRIXA16 *CamerMatrix);
	bool PlayerRender(D3DXMATRIXA16 *CamerMatrix);//��Ĺ� ����	
	void Direction_RotatigSetupMatrices(D3DXMATRIXA16 *CamerMatrix);

	bool CollisionCheck;
	//ó�� ��ġ, ������ ��ġ, ���̰�, ���̰� �ִ�- ���̰� �ּ�
	//�������� �̿��� ���� Į��
	void ColorRed(float Start, float End, float difference, float time)
	{
		Red = Start + (difference/time)*(End - Start);
	}

	//�������� �̿��� �׸� Į��
	void ColorGreen(float Start, float End, float difference, float time)
	{
		Green = Start + (difference/time)*(End - Start);
	}

	//�������� �̿��� ��� Į��
	void ColorBlue(float Start, float End, float difference, float time)
	{
		Blue = Start + (difference/time)*(End - Start);
	}

	void ColorUpdate();

	void Set_Player_Energy(float now_Player_Energy);
	float Get_Player_Energy();

	float GetTS();


};

