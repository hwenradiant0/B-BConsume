#pragma once
#include "entity.h"
#include "ZCamera.h"
#include "MenuMesh.h"
#include "Shader.h"
#include "Mouse.h"
#include "FileLoad.h"
#include "Keyboard.h"
#include "CreditDice_Algorithm.h"
#include "Sound.h"

class CMainMenu
{

private:
	D3DXVECTOR3			eye;
	D3DXVECTOR3			look;
	D3DXVECTOR3			UP;

	D3DXVECTOR3			Vector[700];
	D3DXVECTOR3			Target[700];
	D3DXVECTOR3			Menu_Target[700];
	D3DXVECTOR3			mouse_pos;

	DWORD				dwEventTime; //1000 -> 1��
	DWORD				StartTime; // ó���ð�
	DWORD				dwCurTime; // ����ð�

	Sound				*sound;
	LPDIRECTSOUNDBUFFER   g_lpDSBG[4];

	MouseInput					mouse;
	MenuMesh					*mesh;
	MenuMesh					*SMmesh;
	MenuMesh					*key_mash;
	MenuMesh					*Key_Explain_Mesh;//Ű ���� �Լ�
	MenuMesh					*Selet_Stage;
	MenuMesh					*Satge;
	MenuMesh					*How;
	CShader						*Shader; 
	CFileLoad					fileload;
	KeyInput					key;
	
	CCreditDice_Algorithm		*Credit;

	float				randem;
	int					move_num;
	float				Interpolation; // ���� ���� ���� ����
	float				Interpolation_N; // ���� ���� N��°
	float				R_Interpolation; // ���� ���� ���� ����
	float				R_Interpolation_N; // ���� ���� N��°
	float				EInterpolation;
	float				EInterpolation_N;

	bool				game_start;
	int					select;
	int					Stage;
	int					Stage_Select;
	bool				control;
	bool				credit;
	bool				Exit;
	bool				B_control;
	bool				B_credit;
	bool				Select_stage;
	bool				B_Select_stage;
	bool				se_howtoplay;
	bool				se_howtoplay_check;
	int				    Key_Down_Num;
	int					Render_Key_Down;
	bool				Any_Key_Down;
	bool				KeyEx_Now_Change;//�ٲ� �� ��Ÿ��
	float				Rotate_Cursor_XAngle;
	float				tick;
	float				m_tick_menu_Explain_pause;
	int					Middle_Plane_Num;
	int					Max_Plane_Num;
	float				Default_Y_Angle;

	bool				How_To_On;
	bool				Plain_On;
	float				Off_Y_Angle;
	bool				Plain_Still_Moving;
	int					Plain_Frame;
	D3DXVECTOR3			Plain_Default_Pos;
	D3DXVECTOR3         Plain_Last_Pos[4];
public:
	CMainMenu(void);
	~CMainMenu(void);

	ZCamera				*Mcamera;


	void Menu_Select(BOOL UP , BOOL DOUN , BOOL Enter);
	void Stage_select();
	void Start();
	void init();
	bool Get_gamestart();
	void menu_kyeDown();//Ű �����̴� ���ϸ��̼�
	void Render();
	int	 rog();
	void menu_move(float tick);
	void Menu_Camera();
	void CleenUp();


	void S_Stage();//s_ =>ī�޶� ȸ�� �Լ��ΰ�? SB_�ٽ� ���ư��� �Լ� ��
	void SB_Stage();

	void S_HowToPlay(); 
	void SB_HowToPlay();

	void S_Credit();
	void SB_Credit();

	void SE_HowToPlay();//�̳��� ť�꼳��
	void SEB_HowToPlay();

	void S_Exit();
	void Pan_move();//���� �Ƕ���
	void Pan_render();
	int Get_Stage();
	

	void Volume(int num);
};

