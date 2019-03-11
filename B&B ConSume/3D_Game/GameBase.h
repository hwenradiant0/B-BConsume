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
	float				m_fCamera_Eye_Postion_Y; // 카메라 눈의 Y위치를 변화시키기 위해 만든 변수

private:
	float Angle_X_Limt;
	D3DXMATRIXA16		*m_Base_World_mat;//초기화용 월드 맵
	bool collision; //충돌체크 부울변수
	D3DXVECTOR3 PlayerMove;

	//초기화 할 값들
	float				m_fTick_Game_run;//
	float				m_Menu_Tick; //메뉴 틱이요


	std::list<CTile*>	*Objectlist;//오브젝트 리스트
	std::list<CTile*>	*Movelist;//오브젝트 리스트
	std::list<CParticle*> *Particlelist; // 파티클 리스트
	CPlayer				*Player;//플레이어
	CEvent_Process		*Event;//이벤트

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

	std::list<CPlayer*>	*Ballslist;//공 리스트
	//
	//로딩관련
	int				m_game_state;	//현재 게임의 상태 -> TRUE : 인게임, FALSE : 로딩
	int				Loading_Num;

	int				Particle_Die;
	int				m_Stage_Number;
	float			Fall_Height;
	int				Volume;

public:
	CGameBase(void);
	~CGameBase(void);
	//각종 초기값 설정
	void			GB_Init();

	//타이틀
	void Title_Balls_Move();//타이틀에서 공 움직임 처리 함수
	//렌더 포함한 연산처리, 필요에 따라 bool로 자료형 수정
	void			GB_Run(float tick);
	void			Stage_Loading(char *File_Name);//스테이지  불러오기, 나중에 스테이지 번호를 불러오던 로딩으로 옮기던 수정 필요
	//매트릭스 설정,렌더링 
	void			Game_Move(float tick);
	void			Player_Move();
	void			Render();
	void			Event_Move();

	void			Menu_Render(float tick);
	//메모리 해제

	void			Title_Clear_Up();
	void			Game_Clear_Up();
	void			All_Clear_Up();
	void			Pause_Move(float tick);
	void			Pause_Render();
	void			Create_Game_Over();
	void			Game_Over_Run(float tick);
	//시스템관련의 입력 처리,카메라도 여기서 처리
	void			Set_Key_State(bool Key_State){m_Key_State=Key_State;};
	void			Player_Command();//플레이어의 이동,시스템으로 나갈시 막을 것

	void			CountFPS(float Tick);
	//카메라회전처리와 회전의따른 플레이어 이동처리
	void Player_Camera();

	//로딩용 함수 -> 나중에 클래스화 되면 할 예정
	void Game_Loading(float tick);
	void Game_Loading_Render();
	void Move_Tile();
	void GB_Bomb_Tile();
	int Loading_Energy;
	float Loading_Tick;
	float m_Loading_Tick;
	float m_Angle;

};

