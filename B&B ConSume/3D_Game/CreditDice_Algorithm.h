#pragma once
#include "Entity.h"
#include "Sound.h"

class CCredit_Mesh : public CEntity
{

	bool bSelected;
	
	float Radian_Y;//y축 회전각도
	
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

	Dicenum*		m_Diceinfo;//주사위의 회전 정보 트리
	Dicenum*		m_DicePointer;

	CCredit_Mesh* m_Mesh_Dice;//주사위 메쉬
	CCredit_Mesh* m_Mesh_Credit[6];//텍스트 메쉬
	bool m_bMesh_Still_Moving;//메쉬 보간 여부

	D3DXVECTOR3		m_NextAngle;//보간 최종지점
	D3DXVECTOR3		m_DiceAngle;//주사위 회전각도
	int				m_frame;
	float			m_tick_Dice;
	D3DXVECTOR3    Dice_DeviceAngle;//움직임 외에 전체적인 각도
	D3DXVECTOR3    Text_DeviceAngle;//움직임 외에 전체적인 각도
		CShader			*m_Shader;
	
public:
	CCreditDice_Algorithm(void);
	~CCreditDice_Algorithm(void);


	void	Credit_Init(D3DXVECTOR3 CreditPos,D3DXVECTOR3 TextPos,D3DXVECTOR3 CreditAngle,D3DXVECTOR3 TextAngle);
	float	Angle_LinerInterpo(float v0,float v1,float FrameperMax);

	bool	Credit_Run(bool Up,bool Down,bool Cancle,float tick);//펄스라면 크레딧 화면에서 나올것

	void	Credit_Render();
	void	Clean_Up();
	void	Set_CEye_LEye(D3DXVECTOR3,D3DXVECTOR3);
	D3DXVECTOR3  Get_DicePos(){return m_Mesh_Dice->Get_Pos();};

};

