#pragma once
#include "Entity.h"
#include "Sound.h"

class CCredit_Mesh : public CEntity
{

	bool bSelected;
	
	float Radian_Y;//y�� ȸ������
	
public:
	CCredit_Mesh();
	~CCredit_Mesh();
	void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);
	bool Move();
	

};

struct sDicenum
{
	int Num;
	D3DXVECTOR3 Angle;
	sDicenum*Up;
	sDicenum*Down;
	
}typedef Dicenum;

#define Max_Frame   30
class CCreditDice_Algorithm
{
	Sound				*sound;
	LPDIRECTSOUNDBUFFER   g_lpDSBG[1];

	Dicenum*		m_Diceinfo;//�ֻ����� ȸ�� ���� Ʈ��
	Dicenum*		m_DicePointer;

	CCredit_Mesh* m_Mesh_Dice;//�ֻ��� �޽�
	CCredit_Mesh* m_Mesh_Credit[6];//�ؽ�Ʈ �޽�
	bool m_bMesh_Still_Moving;//�޽� ���� ����

	D3DXVECTOR3		m_NextAngle;//���� ��������
	D3DXVECTOR3		m_DiceAngle;//�ֻ��� ȸ������
	int				m_frame;
	float			m_tick_Dice;
	D3DXVECTOR3    Dice_DeviceAngle;//������ �ܿ� ��ü���� ����
	D3DXVECTOR3    Text_DeviceAngle;//������ �ܿ� ��ü���� ����
		CShader			*m_Shader;
	
public:
	CCreditDice_Algorithm(void);
	~CCreditDice_Algorithm(void);


	void	Credit_Init(D3DXVECTOR3 CreditPos,D3DXVECTOR3 TextPos,D3DXVECTOR3 CreditAngle,D3DXVECTOR3 TextAngle);
	float	Angle_LinerInterpo(float v0,float v1,float FrameperMax);

	bool	Credit_Run(bool Up,bool Down,bool Cancle,float tick);//�޽���� ũ���� ȭ�鿡�� ���ð�

	void	Credit_Render();
	void	Clean_Up();
	void	Set_CEye_LEye(D3DXVECTOR3,D3DXVECTOR3);
	D3DXVECTOR3  Get_DicePos(){return m_Mesh_Dice->Get_Pos();};

};

