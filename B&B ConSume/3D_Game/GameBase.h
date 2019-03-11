#pragma once
#include "ZCamera.h"
#include "ZFLog.h"
#include "Particle.h"
#include "SkyBox.h"
#include "Background.h"
#include "Texture.h"
#include "FileLoad.h"
#include "Event_Process.h"
#include "Sound.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "MainMenu.h"
#include "Particle_Petal.h"
#include "Particle_Rise.h"
#include "Particle_Explosion.h"
#include "Particle_Wind.h"
#include "Particle_Send.h"
#include "Particle_Die.h"
#include "Frustum.h"
#include "Shader.h"

#include "Iron_Tile.h"
#include "Fire_Tile.h"
#include "Water_Tile.h"
#include "Wind_Tile.h"
#include "Wood_Tile.h"
#include "Styro_Tile.h"
#include "Time_Tile.h"
#include "Clear_Tile.h"
#include "One_Wind_Tile.h"
#include "Move_Wind_Tile.h"
#include "Move_Tile.h"
#include "UpDown_Tile.h"
#include "UpDownIron_Tile.h"
#include "Bomb_Tile.h"
#include "Bomb_Tile2.h"
#include "Bomb_Tile3.h"
#include "Bomb_Tile4.h"
#include "UI_Mesh.h"
#include "Pause_System.h"
#include "Clear.h"
#include "Hp_Bar.h"
#include "Game_Over.h"

class CGameBase
{
public:
	ZCamera				*Camera;
	float				m_fCamera_Eye_Postion_Y; // ī�޶� ���� Y��ġ�� ��ȭ��Ű�� ���� ���� ����

private:
	float Angle_X_Limt;
	D3DXMATRIXA16		*m_Base_World_mat;//�ʱ�ȭ�� ���� ��
	bool collision; //�浹üũ �οﺯ��
	D3DXVECTOR3 PlayerMove;

	//�ʱ�ȭ �� ����
	float				m_fTick_Game_run;//
	float				m_Menu_Tick; //�޴� ƽ�̿�


	std::list<CTile*>	*Objectlist;//������Ʈ ����Ʈ
	std::list<CTile*>	*Movelist;//������Ʈ ����Ʈ
	std::list<CParticle*> *Particlelist; // ��ƼŬ ����Ʈ
	CPlayer				*Player;//�÷��̾�
	CEvent_Process		*Event;//�̺�Ʈ

	CTexture			*Sky_Texture;
	CBackground			*SkyBox;

	CTexture			*Space_Sky_Texture;
	CBackground			*Space_SkyBox;
	Sound				*sound;
	LPDIRECTSOUNDBUFFER   g_lpDSBG[8];

	KeyInput			keyboard;
	MouseInput			mouseinput;
	CMainMenu			menu;
	CPause_System*		Pause;

	CFrustum			*m_pFrustum;
	CParticle_Petal		*m_pPetal;
	CTexture			*m_pPetal_Tex;
	CParticle_Rise		*m_pRise;
	CTexture			*m_pRise_Tex;
	CParticle_Explosion	*m_pExplosion;
	CTexture			*m_pExplosion_Tex;
	CParticle_Wind		*m_pWind;
	CTexture			*m_pWind_Tex;
	CParticle_Send		*m_pSend;
	CTexture			*m_pSend_Tex;
	CParticle_Die		*m_pDie;
	CTexture			*m_pDie_Tex;
	CParticle_Send		*m_pIce;
	CTexture			*m_pIce_Tex;

	CShader*		m_pTileShader;
	CShader*		m_pIronTileShader;
	CShader*		m_pWaterTileShader;
	CShader*		m_pFireTileShader;
	CShader*		m_pWindTileShader;
	CShader*		m_pWoodTileShader;
	CShader*		m_pStyroTileShader;
	CShader*		m_IceTileShader;
	CShader*		m_pBallShader;
	CShader*		m_pAlphaShader;
	CShader*		m_pIronAlphaShader;
	CShader*		m_pClearShader;

	CUI_Mesh*		m_UIMesh;
	CClear_System		*m_Clear;
	CHp_Bar_System   *m_HpBar;
	CGame_Over		*m_GO;
	int				cFps;
	float			m_fTick_Game_FPS;
	int				m_Stack;
	bool			m_Move_State;
	bool			m_Move_State2;
	bool			m_Move_State3;
	bool			m_Move_State4;
	bool			Stage1_Is_Clear;
	bool			m_Key_State;

	std::list<CPlayer*>	*Ballslist;//�� ����Ʈ
	//
	//�ε�����
	int				m_game_state;	//���� ������ ���� -> TRUE : �ΰ���, FALSE : �ε�
	int				Loading_Num;

	int				Particle_Die;
	int				m_Stage_Number;
	float			Fall_Height;
	int				Volume;

public:
	CGameBase(void);
	~CGameBase(void);
	//���� �ʱⰪ ����
	void			GB_Init();

	//Ÿ��Ʋ
	void Title_Balls_Move();//Ÿ��Ʋ���� �� ������ ó�� �Լ�
	//���� ������ ����ó��, �ʿ信 ���� bool�� �ڷ��� ����
	void			GB_Run(float tick);
	void			Stage_Loading(char *File_Name);//��������  �ҷ�����, ���߿� �������� ��ȣ�� �ҷ����� �ε����� �ű�� ���� �ʿ�
	//��Ʈ���� ����,������ 
	void			Game_Move(float tick);
	void			Player_Move();
	void			Render();
	void			Event_Move();

	void			Menu_Render(float tick);
	//�޸� ����

	void			Title_Clear_Up();
	void			Game_Clear_Up();
	void			All_Clear_Up();
	void			Pause_Move(float tick);
	void			Pause_Render();
	void			Create_Game_Over();
	void			Game_Over_Run(float tick);
	//�ý��۰����� �Է� ó��,ī�޶� ���⼭ ó��
	void			Set_Key_State(bool Key_State){m_Key_State=Key_State;};
	void			Player_Command();//�÷��̾��� �̵�,�ý������� ������ ���� ��

	void			CountFPS(float Tick);
	//ī�޶�ȸ��ó���� ȸ���ǵ��� �÷��̾� �̵�ó��
	void Player_Camera();

	//�ε��� �Լ� -> ���߿� Ŭ����ȭ �Ǹ� �� ����
	void Game_Loading(float tick);
	void Game_Loading_Render();
	void Move_Tile();
	void GB_Bomb_Tile();
	int Loading_Energy;
	float Loading_Tick;
	float m_Loading_Tick;
	float m_Angle;

};

