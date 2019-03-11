#include "GameBase.h"


CGameBase::CGameBase(void)
{
	Volume = 100;
}

CGameBase::~CGameBase(void)
{	
	All_Clear_Up();
}

void CGameBase::GB_Init()
{
	m_fCamera_Eye_Postion_Y = 200;
	PlayerMove=D3DXVECTOR3(0,0,0);

	int m_idx=0;	// 마우스의 변화값
	int m_idy=0;	// 마우스의 변화값


	for( int i = 0 ; i < 8 ; ++i )
	{
		g_lpDSBG[i] = NULL;
	}

	m_Base_World_mat=new D3DXMATRIXA16();
	D3DXMatrixIdentity(m_Base_World_mat);//베이스 월드 행렬 초기화
	keyboard.Key_input_Init();
	mouseinput.Init();

	//리스트 초기화



	char* Sky_Pos[MAX_SKY_TEX] = {"Texture/SkyBox/Top_Dark.jpg", "Texture/SkyBox/Front_Dark.jpg", "Texture/SkyBox/Back_Dark.jpg",
		"Texture/SkyBox/Right_Dark.jpg", "Texture/SkyBox/Left_Dark.jpg", "Texture/SkyBox/Bottom_Dark.jpg"};

	char* SpaceSky_Pos[MAX_SKY_TEX] = {"Texture/SkyBox/Space.jpg", "Texture/SkyBox/Space.jpg", "Texture/SkyBox/Space.jpg",
		"Texture/SkyBox/Space.jpg", "Texture/SkyBox/Space.jpg", "Texture/SkyBox/Space.jpg"};

	//하늘 텍스쳐 로드
	Sky_Texture = new CTexture;
	Sky_Texture->Arry_Create(Sky_Pos, MAX_SKY_TEX);

	Space_Sky_Texture = new CTexture;
	Space_Sky_Texture->Arry_Create(SpaceSky_Pos, MAX_SKY_TEX);

	m_UIMesh = NULL;

	//하늘 생성
	SkyBox = new CSkyBox;
	SkyBox->Create(Sky_Texture->Arry_GetTexture());

	Space_SkyBox = new CSkyBox;
	Space_SkyBox->Create(Space_Sky_Texture->Arry_GetTexture());


	//카메라 초기화
	Camera=new ZCamera();


	//사운드 파일 로드
	sound=new Sound();
	sound->LoadWave("Sound/BGM/Main/01+To+The+Moon+-+Main+Theme.wav", &g_lpDSBG[0]);//메인화면 BGM
	sound->LoadWave("Sound/BGM/Stage/Bossfight - The Maze Of Mayonnaise.wav", &g_lpDSBG[1]);//스테이지 BGM
	sound->LoadWave("Sound/BGM/Stage2/Bossfight - Captain Cool.wav", &g_lpDSBG[2]);//스테이지2 BGM
	sound->LoadWave("Sound/BGM/Stage3/Avicii - X You (Vocal Radio Edit) [feat. Wailin].wav", &g_lpDSBG[3]);//스테이지3 BGM
	sound->LoadWave("Sound/SE/Tile/Bomb_SE.wav", &g_lpDSBG[4]);//폭탄 사운드이펙트
	sound->LoadWave("Sound/SE/Tile/Wind_SE.wav", &g_lpDSBG[5]);//바람타일소
	sound->LoadWave("Sound/SE/Tile/Send_SE.wav", &g_lpDSBG[6]);//모래타일
	sound->LoadWave("Sound/SE/005-Defeat01.wav", &g_lpDSBG[7]);//게임오버

	//기타값 초기화
	cFps =0;
	m_fTick_Game_FPS=0.f;




	m_pFrustum = new CFrustum();

	m_game_state = 0;

	Loading_Num = 0;

	menu.init();

	m_Menu_Tick = 1;
	Loading_Tick=0.005;
	m_Loading_Tick=3;
	Loading_Energy=1;


	//리스트 초기화
	Objectlist =NULL;
	Particlelist =NULL;
	Movelist =NULL;


	m_Stage_Number = 2;
	m_Key_State = true;
}  

void CGameBase::Game_Loading(float tick)
{
	Loading_Tick=Loading_Tick+tick;
	m_Loading_Tick=m_Loading_Tick+tick;

	if(Loading_Tick>=0.0001)
	{
		m_Angle=m_Angle+D3DX_PI/45;
		Loading_Tick=0;
	}
	if(m_Loading_Tick >= 1)
	{
		m_Loading_Tick=0;
		switch(Loading_Num)
		{
		case 0:
			//구버젼 추후 태양추가후 비교
			//m_pTileShader = new CShader();
			//m_pTileShader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/Fieldstone_DM(원본).tga","Texture/Fieldstone_SM(원본).tga");

			//m_pIronTileShader = new CShader();
			//m_pIronTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Tile/Stone_tex.jpg","Texture/Shader/Stone_DM.jpg");

			//m_pWaterTileShader = new CShader();
			//m_pWaterTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Tile/Water_tex.jpg","Texture/Shader/Water_DM.jpg");

			//m_pFireTileShader = new CShader();
			//m_pFireTileShader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/Tile/Fire_tex.jpg","Texture/Shader/Fire_DM.jpg");

			//m_pWindTileShader = new CShader();
			//m_pWindTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Tile/Wind_tex.jpg","Texture/Shader/Wind_DM.jpg");

			//m_pWoodTileShader = new CShader();
			//m_pWoodTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Tile/Sand_tex.jpg","Texture/Shader/Sand_DM.jpg");

			//m_pStyroTileShader = new CShader();
			//m_pStyroTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Tile/Bomb_tex.jpg","Texture/Shader/Styro_DM.jpg");

			//m_IceTileShader = new CShader();
			//m_IceTileShader->LoadAssets("Data/Alpha.fx","Texture/Tile/Ice_tex.jpg","Texture/Shader/Ice_DM.jpg");

			//m_pBallShader = new CShader();
			//m_pBallShader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/NONE.jpg","Texture/Shader/Stone_DM.jpg");

			//m_pAlphaShader = new CShader();
			//m_pAlphaShader->LoadAssets("Data/Alpha.fx", "Texture/Tile/Wind_tex.jpg","Texture/Shader/Wind_DM.jpg");

			//m_pIronAlphaShader = new CShader();
			//m_pIronAlphaShader->LoadAssets("Data/Alpha.fx", "Texture/Tile/Stone_tex.jpg","Texture/Shader/Stone_DM.jpg");

			//m_UIMesh = new CUI_Mesh();
			//m_UIMesh->Init("XFile/Loading2.x",D3DXVECTOR3(10,50,-230),1.5f,Coll_TYPE_Sphere, m_pTileShader);

			//m_pClearShader = new CShader();
			//m_pClearShader->LoadAssets("Data/Alpha.fx","Texture/Shader/Goal_DM.jpg","Texture/Shader/Goal_SM.jpg");

			m_pTileShader = new CShader();
			m_pTileShader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/Shader/Stone_DM.jpg","Texture/Shader/Stone_SM.jpg");

			m_pIronTileShader = new CShader();
			m_pIronTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Shader/Stone_DM.jpg","Texture/Shader/Stone_SM.jpg");

			m_pWaterTileShader = new CShader();
			m_pWaterTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Shader/Water_DM.jpg","Texture/Shader/Water_SM.jpg");

			m_pFireTileShader = new CShader();
			m_pFireTileShader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/Shader/Fire_DM.jpg","Texture/Shader/Fire_SM.jpg");

			m_pWindTileShader = new CShader();
			m_pWindTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Shader/Wind_DM.jpg","Texture/Shader/Wind_SM.jpg");

			m_pWoodTileShader = new CShader();
			m_pWoodTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Shader/Sand_DM.jpg","Texture/Shader/Sand_SM.jpg");

			m_pStyroTileShader = new CShader();
			m_pStyroTileShader->LoadAssets("Data/BallBoxConSume(NoColor).fx","Texture/Shader/Styro_DM.jpg","Texture/Shader/Styro_SM.jpg");

			m_IceTileShader = new CShader();
			m_IceTileShader->LoadAssets("Data/Alpha.fx","Texture/Shader/Ice_DM.jpg","Texture/Shader/Ice_SM.jpg");

			m_pBallShader = new CShader();
			m_pBallShader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/NONE.jpg","Texture/Shader/Fire_SM.jpg");

			m_pAlphaShader = new CShader();
			m_pAlphaShader->LoadAssets("Data/Alpha.fx","Texture/Shader/Ice_DM.jpg","Texture/Shader/Ice_SM.jpg");

			m_pIronAlphaShader = new CShader();
			m_pIronAlphaShader->LoadAssets("Data/Alpha.fx","Texture/Shader/Stone_DM.jpg","Texture/Shader/Stone_SM.jpg");

			m_pClearShader = new CShader();
			m_pClearShader->LoadAssets("Data/Alpha.fx","Texture/Shader/Goal_DM.jpg","Texture/Shader/Goal_SM.jpg");


			m_UIMesh = new CUI_Mesh();
			m_UIMesh->Init("XFile/Loading2.x",D3DXVECTOR3(10,50,-230),1.5f,Coll_TYPE_Sphere, m_pTileShader);
			Loading_Num++;
			break;
		case 1:
			//스테이지VECTOR3(20,20,-40) 스테이지2VECTOR3(20,20,-40) 스테이지3D3DXVECTOR3(10,50,-230)
			Player= new CPlayer();
			if(menu.Get_Stage() == 1)
			{
				Player->Init("XFile/Gara_Ball.x",D3DXVECTOR3(20,20,-40),1.0f,Coll_TYPE_Sphere, m_pTileShader);

			}
			else if(menu.Get_Stage() ==2)
			{
				Player->Init("XFile/Gara_Ball.x",D3DXVECTOR3(20,20,-40),1.0f,Coll_TYPE_Sphere, m_pTileShader);
				//여기에 플레이어 시작 위치를 Init로 선언!
			}
			else if(menu.Get_Stage() ==3)
			{
				//27	-48	49
				Player->Init("XFile/Gara_Ball.x",D3DXVECTOR3(10,50,-230),1.0f,Coll_TYPE_Sphere, m_pTileShader);
			}
			Player->m_PhyData->Init_Phydata(1.0f,1.0f,0.3f,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0));
			Objectlist= new std::list<CTile*>;
			Particlelist = new std::list<CParticle*>;
			Movelist = new std::list<CTile*>;
			Loading_Num++;
			break;

		case 2:
			if(menu.Get_Stage() ==1)
			{
				Stage_Loading("Text/Stage.txt");
			}
			else if(menu.Get_Stage() ==2)
			{
				Stage_Loading("Text/Stage2.txt");
			}
			else if(menu.Get_Stage() == 3)
			{
				Stage_Loading("Text/Stage3.txt");
			}

			Loading_Num++;
			break;


		case 3:
			Event = new CEvent_Process;
			Loading_Num++;
			break;


		case 4:
			//이벤트 생성
			m_pRise_Tex = new CTexture();
			m_pRise_Tex->Create("Texture/K3tB92.png");

			m_pRise = new CParticle_Rise();
			m_pRise->Create(m_pRise_Tex->GetTexture());

			m_pPetal_Tex = new CTexture();
			m_pPetal_Tex->Create("Texture/light.jpg");

			m_pPetal = new CParticle_Petal;
			m_pPetal->Create(m_pPetal_Tex->GetTexture());

			m_pExplosion_Tex = new CTexture();
			m_pExplosion_Tex->Create("Texture/크기변환_fs2_ani_expl_tex.jpg");


			Loading_Num++;
			break;

		case 5:
			m_pWind_Tex = new CTexture();
			m_pWind_Tex->Create("Texture/wind_TeDuri.png");

			m_pSend_Tex = new CTexture();
			m_pSend_Tex->Create("Texture/light.jpg");

			m_pDie_Tex = new CTexture();
			m_pDie_Tex->Create("Texture/크기변환_fs2_ani_expl_tex.jpg");

			m_pIce_Tex = new CTexture();
			m_pIce_Tex->Create("Texture/light_Blue.jpg");

			if(menu.Get_Stage() ==1)
				m_pRise->SetStage(1);
			else if(menu.Get_Stage() ==2)
				m_pRise->SetStage(2);
			else if(menu.Get_Stage() ==3)
				m_pRise->SetStage(3);

			m_pRise->SetRender(true, D3DXVECTOR3(0,0,0));
			m_pPetal->SetRender(false, D3DXVECTOR3(0,10,-230));

			Particlelist->push_back(m_pRise);
			Particlelist->push_back(m_pPetal);

			m_HpBar  = new  CHp_Bar_System;


			m_HpBar->HP_Sys_Init( D3DXVECTOR3(Window_Width*0.95f,Window_Height*0.5f,0),1000);


			Loading_Num++;
			break;
		case 6:
			//다음 로딩을 위한 초기화
			m_GO = NULL;



			Pause = NULL;

			m_Clear = NULL;


			Stage1_Is_Clear=false;	

			delete m_UIMesh;
			m_UIMesh=NULL;

			m_Move_State	= true;
			m_Move_State2	= true;
			m_Move_State3	= false;
			m_Move_State4	= true;


			if(menu.Get_Stage() ==1)
			{
				sound->Stop(g_lpDSBG[0]);
				sound->Play(g_lpDSBG[1],TRUE);
				Fall_Height=-100;
			}
			else if(menu.Get_Stage() ==2)
			{
				sound->Stop(g_lpDSBG[0]);
				sound->Play(g_lpDSBG[2],TRUE);
				Fall_Height=-50*20-10;
			}
			else if(menu.Get_Stage() ==3 )
			{
				sound->Stop(g_lpDSBG[0]);
				sound->Play(g_lpDSBG[3],TRUE);
				Fall_Height=-50*20-10;
			}
			Loading_Num++;

			//다음 단계로 진행
			break;
		case 7:
			Loading_Tick=1;
			m_Loading_Tick =0;
			Loading_Energy=1;
			Loading_Num = 0;
			m_Angle=0;
			m_Stack=0;
			m_game_state = 2;
			break;
		default:
			break;
		}
		// 로딩 타이틀, 인게임 카메라 초기 위치 관리
		if(m_game_state == 1)//로딩
			Camera->SetViewMatrix(&D3DXVECTOR3(0,250.0f,-730.0f), &D3DXVECTOR3(0,50,-230),&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		else if(m_game_state ==2 )//인게임
		{
			Angle_X_Limt = 0;
			Camera->SetViewMatrix(&(Player->Get_Pos() + D3DXVECTOR3(-100.0f,100.0f,0.0f)),&Player->Get_Pos(),&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
		}
	}
	if(m_UIMesh !=NULL)
	{
		if(Loading_Num>=6)
		{
			m_UIMesh->Color_Change(6);
			m_UIMesh->SetMeshColor(0,m_UIMesh->Red,m_UIMesh->Green,m_UIMesh->Blue,1.0f);

			m_UIMesh->SetRotation(0,m_Angle,0);
			Game_Loading_Render();
		}
		else
		{
			m_UIMesh->Color_Change(Loading_Num);
			m_UIMesh->SetMeshColor(0,m_UIMesh->Red,m_UIMesh->Green,m_UIMesh->Blue,1.0f);

			m_UIMesh->SetRotation(0,m_Angle,0);
			Game_Loading_Render();
		}
	}
}

void CGameBase::Game_Loading_Render()
{
	/// 후면버퍼와 Z버퍼를 지운다.
	Get_Device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	/// 렌더링 시작
	if( SUCCEEDED( Get_Device->BeginScene() ) )
	{
		SkyBox->FrameMove(Camera->GetEye());
		SkyBox->Render();
		/// 월드,뷰,프로젝션 행렬을 설정한다.////////

		Get_Device->SetTransform(D3DTS_WORLD,m_Base_World_mat);//기본 월드 행렬로 설정

		/// 뷰행렬을 설정
		Get_Device->SetTransform( D3DTS_VIEW, &Camera->GetViewMatrix() );

		/// 프로젝션 행렬 설정
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 10000.0f );
		Get_Device->SetTransform( D3DTS_PROJECTION, &matProj );

		///렌더링///		

		m_UIMesh->Render();

		//메뉴 렌더


		/// 렌더링 종료
		Get_Device->EndScene();
	}

	/// 후면버퍼를 보이는 화면으로!
	Get_Device->Present( NULL, NULL, NULL, NULL );
}


void CGameBase::Stage_Loading(char *File_Name)
{ 
	CFileLoad Loader;
	Tile_Data a[1600];

	if(menu.Get_Stage() == 1 )
	{
		Loader.Stage_Read1(File_Name,a);
	}
	else if(menu.Get_Stage() == 2 )
	{
		Loader.Stage_Read2(File_Name,a);
	}
	else if(menu.Get_Stage() == 3)
	{
		Loader.Stage_Read3(File_Name,a);
	}
	CTile*Temp;
	for(int i=0;i<1600;i++)
	{
		Temp= new CTile;//나중에 상속을 하던지 스위치로 다른 타일로 설정해야 함
		switch(a[i].iMaterial)
		{
		case 1://철
			Temp = new CIron_Tile;
			Temp->Init("XFile/Tile/Stone.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pIronTileShader);
			Objectlist->push_back(Temp);
			break;	
		case 2://물
			Temp = new CWater_Tile;
			Temp->Init("XFile/Tile/Water.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pWaterTileShader);
			Objectlist->push_back(Temp);
			break;
		case 3://불
			Temp = new CFire_Tile;
			Temp->Init("XFile/Tile/Fire.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pFireTileShader);
			Objectlist->push_back(Temp);
			break;				
		case 4:	//바람	//XFile/firecube.X	
			Temp = new CWind_Tile;
			Temp->Init("XFile/Tile/Wind.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pWindTileShader);
			Objectlist->push_back(Temp);
			break;																
		case 5://나무	
			Temp = new CWood_Tile;
			Temp->Init("XFile/Tile/Sand.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pWoodTileShader);
			Objectlist->push_back(Temp);
			break;																
		case 6://스티로폼		
			Temp = new CStyro_Tile;
			Temp->Init("XFile/Tile/Bomb.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pStyroTileShader);
			Objectlist->push_back(Temp);
			break;																
		case 7://타임타일
			Temp = new CTime_Tile;
			Temp->Init("XFile/Tile/Ice.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_IceTileShader);
			Objectlist->push_back(Temp);
			break;		
		case 8://도착
			Temp = new CClear_Tile;
			Temp->Init("XFile/Box.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pClearShader);
			Objectlist->push_back(Temp);
			break;	
		case 9:
			Temp = new COne_Wind_Tile;
			Temp->Init("XFile/Tile/Wind.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pWindTileShader);
			Objectlist->push_back(Temp);
			break;
		case 10:
			Temp = new CMove_Wind_Tile;
			Temp->Init("XFile/Tile/Wind.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pWindTileShader);
			Movelist->push_back(Temp);
			Objectlist->push_back(Temp);
			break;
		case 11:
			Temp = new CMove_Tile;
			Temp->Init("XFile/Tile/Wind.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pIronTileShader);
			Movelist->push_back(Temp);
			Objectlist->push_back(Temp);
			break;
		case 12:
			Temp = new CUpDown_Tile;
			Temp->Init("XFile/Tile/Wind.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pAlphaShader);
			Movelist->push_back(Temp);
			Objectlist->push_back(Temp);
			break;
		case 13:
			Temp = new CBomb_Tile;
			Temp->Init("XFile/Tile/Bomb.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pStyroTileShader);
			Objectlist->push_back(Temp);
			break;		
		case 14:
			Temp = new CBomb_Tile2;
			Temp->Init("XFile/Tile/Bomb.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pStyroTileShader);
			Objectlist->push_back(Temp);
			break;		
		case 15:
			Temp = new CBomb_Tile3;
			Temp->Init("XFile/Tile/Bomb.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pStyroTileShader);
			Objectlist->push_back(Temp);
			break;		
		case 16:
			Temp = new CUpDownIron_Tile;
			Temp->Init("XFile/Tile/Stone.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pIronTileShader);
			Movelist->push_back(Temp);
			Objectlist->push_back(Temp);
			break;	
		case 17:
			Temp = new CBomb_Tile4;
			Temp->Init("XFile/Tile/Bomb.x",D3DXVECTOR3(a[i].ix*20,a[i].iy*20,-a[i].iz*20),1.0f,Coll_TYPE_MMB, m_pStyroTileShader);
			Objectlist->push_back(Temp);
			break;		

		default:
			break;
		}
		Temp = NULL;
	}
}
void CGameBase::Title_Clear_Up()
{
	menu.CleenUp();
}

void CGameBase::Game_Clear_Up()
{
	Particle_Die = 0;

	if(Player !=NULL)
	{
		delete Player;
		Player=NULL;
	}

	if (Event != NULL)
	{
		delete Event;
		Event = NULL;
	}
	if(Objectlist != NULL)
	{
		std::list<CTile*>::iterator Tile_iter=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
		while(Tile_iter != Objectlist->end())
		{
			delete(*Tile_iter);
			Tile_iter = Objectlist->erase(Tile_iter++);
			continue;
		}

		delete Objectlist;
		Objectlist=NULL;
		delete Movelist;
		Movelist=NULL;//연결되어 있으므로 같이 제거
	}


	if(Particlelist != NULL)
	{

		std::list<CParticle*>::iterator Particle_iter=Particlelist->begin();//리스트 자체는 삭제 안해도 되는지
		while(Particle_iter != Particlelist->end())
		{
			delete(*Particle_iter);
			Particle_iter = Particlelist->erase(Particle_iter++);
			continue;
		}

		delete Particlelist;
		Particlelist =NULL;
	}



	if(m_pTileShader!=NULL)
	{
		delete m_pTileShader;
		m_pTileShader=NULL;
	}
	if(m_pIronTileShader!=NULL)
	{
		delete m_pIronTileShader;
		m_pIronTileShader=NULL;
	}
	if(m_pWaterTileShader!=NULL)
	{
		delete m_pWaterTileShader;
		m_pWaterTileShader=NULL;
	}
	if(m_pFireTileShader!=NULL)
	{
		delete m_pFireTileShader;
		m_pFireTileShader=NULL;
	}
	if(m_pWindTileShader!=NULL)
	{
		delete m_pWindTileShader;
		m_pWindTileShader=NULL;
	}
	if(m_pWoodTileShader!=NULL)
	{
		delete m_pWoodTileShader;
		m_pWoodTileShader=NULL;
	}
	if(m_pStyroTileShader!=NULL)
	{
		delete m_pStyroTileShader;
		m_pStyroTileShader=NULL;
	}
	if(m_IceTileShader!=NULL)
	{
		delete m_IceTileShader;
		m_IceTileShader=NULL;
	}
	if(m_pBallShader!=NULL)
	{
		delete m_pBallShader;
		m_pBallShader=NULL;
	}
	if(m_pAlphaShader!=NULL)
	{
		delete m_pAlphaShader;
		m_pAlphaShader=NULL;
	}
	if(m_pIronAlphaShader!=NULL)
	{
		delete m_pIronAlphaShader;
		m_pIronAlphaShader=NULL;
	}
	if(m_pClearShader!=NULL)
	{
		delete m_pClearShader;
		m_pClearShader=NULL;
	}





	if(m_HpBar!=NULL)
	{
		delete m_HpBar;
		m_HpBar=NULL;
	}
	if(m_GO != NULL)
	{
		delete m_GO;
		m_GO =NULL;
	}
	if(m_pRise_Tex!= NULL)
	{
		delete m_pRise_Tex;
		m_pRise_Tex =NULL;
	} 

	if(m_pPetal_Tex != NULL)
	{
		delete	m_pPetal_Tex;
		m_pPetal_Tex = NULL;
	}

	if(m_pIce_Tex != NULL)
	{
		delete	m_pIce_Tex;
		m_pIce_Tex = NULL;
	}
	if(m_pExplosion_Tex != NULL)
	{
		delete	m_pExplosion_Tex;
		m_pExplosion_Tex = NULL;
	}

	if(m_pWind_Tex != NULL)
	{
		delete	m_pWind_Tex;
		m_pWind_Tex = NULL;
	}

	if(m_pSend_Tex != NULL)
	{
		delete	m_pSend_Tex;
		m_pSend_Tex = NULL;
	}

	if(m_pDie_Tex != NULL)
	{
		delete	m_pDie_Tex;
		m_pDie_Tex = NULL;
	}

	sound->Stop(g_lpDSBG[1]);
	sound->Stop(g_lpDSBG[2]);
	sound->Stop(g_lpDSBG[3]);
}

void CGameBase::All_Clear_Up()
{


	if(Objectlist != NULL)
	{

		std::list<CTile*>::iterator Tile_iter=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
		while(Tile_iter != Objectlist->end())
		{
			delete(*Tile_iter);
			Tile_iter = Objectlist->erase(Tile_iter++);
			continue;
		}

		delete Objectlist;
		Objectlist=NULL;
		delete Movelist;
		Movelist=NULL;//연결되어 있으므로 같이 제거
	}



	if(Particlelist != NULL)
	{

		std::list<CParticle*>::iterator Particle_iter=Particlelist->begin();//리스트 자체는 삭제 안해도 되는지
		while(Particle_iter != Particlelist->end())
		{
			delete(*Particle_iter);
			Particle_iter = Particlelist->erase(Particle_iter++);
			continue;
		}
		delete Particlelist;
		Particlelist =NULL;
	}

	if(m_HpBar!=NULL)
	{
		delete m_HpBar;
		m_HpBar=NULL;
	}


	if(Player !=NULL)
	{
		delete Player;
		Player=NULL;
	}
	if (Camera != NULL)
	{
		delete Camera;
		Camera = NULL;
	}

	if (Event != NULL)
	{
		delete Event;
		Event = NULL;
	}

	if (Sky_Texture != NULL)
	{
		delete Sky_Texture;
		Sky_Texture = NULL;
	}
	if (Space_Sky_Texture != NULL)
	{
		delete Space_Sky_Texture;
		Space_Sky_Texture = NULL;
	}

	if(m_Base_World_mat!=NULL)
	{
		delete m_Base_World_mat;
		m_Base_World_mat = NULL;
	}
	if(Pause != NULL)
	{
		delete Pause;
		Pause = NULL;
	}
	if(SkyBox !=NULL)
	{
		delete SkyBox;
		SkyBox=NULL;
	}
	if(Space_SkyBox !=NULL)
	{
		delete Space_SkyBox;
		Space_SkyBox=NULL;
	}
	if(sound !=NULL)
	{
		delete sound;
		sound=NULL;
	}
	if(m_pFrustum!= NULL)
	{
		delete m_pFrustum;
		m_pFrustum =NULL;
	} 


	if(m_pTileShader!= NULL)
	{
		delete m_pTileShader;
		m_pTileShader =NULL;
	} 
	if(m_pFireTileShader!= NULL)
	{
		delete m_pFireTileShader;
		m_pFireTileShader =NULL;
	} 

	if(m_pBallShader!= NULL)
	{
		delete m_pBallShader;
		m_pBallShader =NULL;
	} 

	if(m_UIMesh!= NULL)
	{
		delete m_UIMesh;
		m_UIMesh =NULL;
	} 

	if(m_GO != NULL)
	{
		delete m_GO;
		m_GO =NULL;
	}
	if(sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
	Title_Clear_Up();
}

void CGameBase::CountFPS(float Tick)
{
	m_fTick_Game_FPS +=Tick;
	if(m_fTick_Game_FPS>1)
	{
		m_fTick_Game_FPS=0;

		cFps=0;

	}
	else
		cFps++;
}

void CGameBase::GB_Run(float tick)
{
	CountFPS(tick);
	if(m_Key_State==false)
		tick=0;
	switch(m_game_state)
	{
	case 0:	/// 뷰행렬을 설정
		sound->Play(g_lpDSBG[0],TRUE);
		Menu_Render(tick);
		//타이틀
		break;
	case 1: //로딩ing
		sound->Stop(g_lpDSBG[0]);
		Game_Loading(tick);
		break;
	case 2:	//인게임
		Game_Move(tick);
		break;
	case 3://일시정지
		Pause_Move(tick);
		break;
	case 4://stage1 Clear!!!
		keyboard.key_State();
		mouseinput.mouse_state();

		if(!m_Clear->Clear_Move(keyboard.Get_Enter(),tick))
		{
			delete m_Clear;
			m_Clear=NULL;

			mouseinput.Clean();

			Game_Clear_Up();
			menu.init();
			m_game_state=0;
		}
		else
			Render();
		break;
	case 5://game over
		Game_Over_Run(tick);		
		break;
	}

	if(keyboard.Get_F7())
	{
		if(Volume > 0)
		{
			Volume -= 10;
			for(int i=0 ; i<8 ; i++)
				sound->SetVolume(g_lpDSBG[i], Volume);
		}
	}

	if(keyboard.Get_F8())
	{
		if(Volume < 100)
		{
			Volume += 10;
			for(int i=0 ; i<8 ; i++)
				sound->SetVolume(g_lpDSBG[i], Volume);
		}
	}
}

void CGameBase::Pause_Move(float tick)
{
	keyboard.key_State();
	mouseinput.mouse_state();


	m_fTick_Game_run += tick;
	if(m_fTick_Game_run>Tick_Gb_run_minmum)
	{
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
		m_pFrustum->FrameMove(&Camera->GetViewMatrix(), &matProj);
		m_pRise->FrameMove();
		m_pPetal->SetPos(Player->Get_Pos());
		m_pPetal->SetVelocity(Player->m_PhyData->GetLinerVelocity());
		m_pPetal->FrameMove();

		m_fTick_Game_run=0;
		int Choice = Pause->Pause_Move(keyboard.Get_UP(),keyboard.Get_Down(),keyboard.Get_Enter());
		if(Choice==0)//계속
		{
			delete Pause;
			Pause =NULL;
			m_game_state=2;

		}
		else if(Choice==1)//타이틀로
		{


			sound->Stop(g_lpDSBG[1]);
			mouseinput.Clean();


			Game_Clear_Up();
			menu.init();
			m_game_state=0;

		}
		else if(Choice == -1)
		{
			Render();
		}



	}
}
void CGameBase::Game_Over_Run(float tick)
{
	keyboard.key_State();
	mouseinput.mouse_state();
	int choice = 0;
	choice =m_GO->Game_Over_Move(keyboard.Get_UP(),keyboard.Get_Down(),keyboard.Get_Enter(),tick);

	if(choice == 0)
	{

		Game_Clear_Up();
		m_game_state= 1;
	}
	else if(choice ==1)
	{

		sound->Stop(g_lpDSBG[1]);
		mouseinput.Clean();

		Game_Clear_Up();
		menu.init();
		m_game_state=0;
	}
	else if(choice ==-1)
	{
		Render();
	}
}
void CGameBase::Move_Tile()
{
	std::list<CTile*>::iterator Tile_iter;

	std::list<CTile*>::iterator Move_Tile_iter;
	Move_Tile_iter = Movelist->begin();
	Tile_iter = Objectlist->begin();
	D3DXVECTOR3		MoveVec;
	D3DXVECTOR3		vPlayer_Pos=D3DXVECTOR3(0,0,0);
	D3DXVECTOR3		vTest_Player_move=D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 PlayerMoveBefore = Player->Get_Pos();

	while(Move_Tile_iter != Movelist->end())
	{
		if(Event->Get_Tile_Switch()==true)
		{
			m_Move_State3=true;
		}

		if((*Move_Tile_iter)->Get_Material()==10)
		{
			if(m_Move_State==true)//true이면 +방향으로, false면 -방향으로!
			{
				if((*Move_Tile_iter)->Get_Stack()>=80)
				{
					m_Move_State=false;
				}
				else
				{
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()+1);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y+1,(*Move_Tile_iter)->Get_Pos().z+1));
				}
			}
			else
			{
				if((*Move_Tile_iter)->Get_Stack()<=0)
				{
					m_Move_State=true;
				}
				else
				{
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()-1);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y-1,(*Move_Tile_iter)->Get_Pos().z-1));
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////직선움직타일
		else if((*Move_Tile_iter)->Get_Material()==11)
		{
			if(m_Move_State2==true)//true이면 +방향으로, false면 -방향으로!
			{
				if((*Move_Tile_iter)->Get_Stack()>=340)
				{
					m_Move_State2=false;
				}
				else
				{
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()+1);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x-1,(*Move_Tile_iter)->Get_Pos().y,(*Move_Tile_iter)->Get_Pos().z));
					MoveVec = D3DXVECTOR3(-1,0,0);
				}
			}
			else
			{
				if((*Move_Tile_iter)->Get_Stack()<=20)
				{
					m_Move_State2=true;
				}
				else
				{
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()-1);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x+1,(*Move_Tile_iter)->Get_Pos().y,(*Move_Tile_iter)->Get_Pos().z));
					MoveVec = D3DXVECTOR3(1,0,0);
				}			
			}
			if((*Move_Tile_iter)->Get_Put()==true)
			{
				Player->SetPos(Player->Get_Pos()+MoveVec);
			}
		}

		else if((*Move_Tile_iter)->Get_Material()==12)
		{
			if(m_Move_State3==true)
			{
				if((*Move_Tile_iter)->Get_Stack()>=240)
				{
					m_Move_State3=false;
				}
				else
				{

					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()+1);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y-1,(*Move_Tile_iter)->Get_Pos().z));
				}
			}

			else
			{
				if((*Move_Tile_iter)->Get_Stack()>0)
				{
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack());
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y,(*Move_Tile_iter)->Get_Pos().z));

				}
				else
				{
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack());
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y,(*Move_Tile_iter)->Get_Pos().z));
				}
			}
		}
		else if((*Move_Tile_iter)->Get_Material()==16)
		{
			if(m_Move_State4==true)//true이면 +방향으로, false면 -방향으로!
			{
				if((*Move_Tile_iter)->Get_Stack()>=200)
				{
					m_Move_State4=false;
				}
				else
				{	//내려가는데
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()+Gravity);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y-Gravity,(*Move_Tile_iter)->Get_Pos().z));
				}
			}
			else
			{
				if((*Move_Tile_iter)->Get_Stack()<=0)
				{
					m_Move_State4=true;
				}
				else
				{	//올라가는데
					(*Move_Tile_iter)->Set_Stack((*Move_Tile_iter)->Get_Stack()-Gravity);
					(*Move_Tile_iter)->SetPos(D3DXVECTOR3((*Move_Tile_iter)->Get_Pos().x,(*Move_Tile_iter)->Get_Pos().y+Gravity,(*Move_Tile_iter)->Get_Pos().z));
				}
			}
		}
		Move_Tile_iter++;
	}
	D3DXVECTOR3 PlayerMoveAfter = Player->Get_Pos();
	PlayerMove = PlayerMoveAfter - PlayerMoveBefore; //움직이기 전과 움직임 후의 플레이어좌표의 차이값
	Player_Camera();
}

void CGameBase::GB_Bomb_Tile()
{
	Cube			PlayerArea;//플레이어 주위로 블럭 3개 크기의 영역

	PlayerArea.centerPos=Player->Get_Pos();
	PlayerArea.depth  = Tile_Size*3;
	PlayerArea.heigth = Tile_Size*3;
	PlayerArea.length = Tile_Size*3;
	D3DXVECTOR3		vNormalVetor=D3DXVECTOR3(0,0,0);
	D3DXVECTOR3		vTest_Player_move=D3DXVECTOR3(0,0,0);

	std::list<CTile*>::iterator Tile_iter =Objectlist->begin();
	while(Tile_iter != Objectlist->end())
	{
		if((*Tile_iter)->m_Coll->AABB_B_B((*Tile_iter)->m_Coll->Get_Cube_Model(),PlayerArea)){
			if((*Tile_iter)->m_Coll->CheckSp_B((Player->m_Coll->Get_Sp_Model()),((*Tile_iter)->m_Coll->Get_Cube_Model()),&vTest_Player_move,&vNormalVetor))
			{
				if((*Tile_iter)->Get_Material() ==6)
				{
					Cube ExplsionArea;
					ExplsionArea.centerPos = (*Tile_iter)->Get_Pos();
					ExplsionArea.depth = Tile_Size*0;	//z축 
					ExplsionArea.heigth = Tile_Size*0;	//y축
					ExplsionArea.length = Tile_Size*3;	//x축
					std::list<CTile*>::iterator Tile_iter2=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
					while(Tile_iter2 != Objectlist->end())
					{
						if((*Tile_iter2)->m_Coll->AABB_B_B((*Tile_iter2)->m_Coll->Get_Cube_Model(),ExplsionArea))
							(*Tile_iter2)->Set_Material(0);
						if((*Tile_iter2)->Get_Material() == 0)
						{
							sound->Stop(g_lpDSBG[4]);
							m_pExplosion = new CParticle_Explosion;
							m_pExplosion->Create(m_pExplosion_Tex->GetTexture());
							m_pExplosion->SetRender(true, (*Tile_iter2)->Get_Pos());
							Particlelist->push_back(m_pExplosion);
							sound->Play(g_lpDSBG[4], false);
						}
						Tile_iter2++;
					}
				}
				else if((*Tile_iter)->Get_Material() ==13)
				{
					Cube ExplsionArea2;
					ExplsionArea2.centerPos = (*Tile_iter)->Get_Pos();
					ExplsionArea2.depth = Tile_Size*0;	//z축 
					ExplsionArea2.heigth = Tile_Size*0;	//y축
					ExplsionArea2.length = Tile_Size*1;	//x축
					std::list<CTile*>::iterator Tile_iter2=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
					while(Tile_iter2 != Objectlist->end())
					{
						if((*Tile_iter2)->m_Coll->AABB_B_B((*Tile_iter2)->m_Coll->Get_Cube_Model(),ExplsionArea2))
							(*Tile_iter2)->Set_Material(0);
						if((*Tile_iter2)->Get_Material() == 0)
						{
							sound->Stop(g_lpDSBG[4]);
							m_pExplosion = new CParticle_Explosion;
							m_pExplosion->Create(m_pExplosion_Tex->GetTexture());
							m_pExplosion->SetRender(true, (*Tile_iter2)->Get_Pos());
							Particlelist->push_back(m_pExplosion);
							sound->Play(g_lpDSBG[4], false);
						}
						Tile_iter2++;
					}
				}
				else if((*Tile_iter)->Get_Material() ==14)
				{
					Cube ExplsionArea3;
					ExplsionArea3.centerPos = (*Tile_iter)->Get_Pos();
					ExplsionArea3.depth = Tile_Size*1;	//z축 
					ExplsionArea3.heigth = Tile_Size*0;	//y축
					ExplsionArea3.length = Tile_Size*0;	//x축
					std::list<CTile*>::iterator Tile_iter2=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
					while(Tile_iter2 != Objectlist->end())
					{
						if((*Tile_iter2)->m_Coll->AABB_B_B((*Tile_iter2)->m_Coll->Get_Cube_Model(),ExplsionArea3))
							(*Tile_iter2)->Set_Material(0);
						if((*Tile_iter2)->Get_Material() == 0)
						{
							sound->Stop(g_lpDSBG[4]);
							m_pExplosion = new CParticle_Explosion;
							m_pExplosion->Create(m_pExplosion_Tex->GetTexture());
							m_pExplosion->SetRender(true, (*Tile_iter2)->Get_Pos());
							Particlelist->push_back(m_pExplosion);
							sound->Play(g_lpDSBG[4], false);
						}
						Tile_iter2++;
					}
				}
				else if((*Tile_iter)->Get_Material() ==15)
				{
					Cube ExplsionArea2;
					ExplsionArea2.centerPos = (*Tile_iter)->Get_Pos();
					ExplsionArea2.depth = Tile_Size*3;	//z축 
					ExplsionArea2.heigth = Tile_Size*0;	//y축
					ExplsionArea2.length = Tile_Size*0;	//x축
					std::list<CTile*>::iterator Tile_iter2=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
					while(Tile_iter2 != Objectlist->end())
					{
						if((*Tile_iter2)->m_Coll->AABB_B_B((*Tile_iter2)->m_Coll->Get_Cube_Model(),ExplsionArea2))
							(*Tile_iter2)->Set_Material(0);
						if((*Tile_iter2)->Get_Material() == 0)
						{
							sound->Stop(g_lpDSBG[4]);
							m_pExplosion = new CParticle_Explosion;
							m_pExplosion->Create(m_pExplosion_Tex->GetTexture());
							m_pExplosion->SetRender(true, (*Tile_iter2)->Get_Pos());
							Particlelist->push_back(m_pExplosion);
							sound->Play(g_lpDSBG[4], false);
						}
						Tile_iter2++;
					}
				}
				else if((*Tile_iter)->Get_Material() ==17)
				{
					Cube ExplsionArea2;
					ExplsionArea2.centerPos = (*Tile_iter)->Get_Pos();
					ExplsionArea2.depth = Tile_Size*3;	//z축 
					ExplsionArea2.heigth = Tile_Size*1;	//y축
					ExplsionArea2.length = Tile_Size*3;	//x축
					std::list<CTile*>::iterator Tile_iter2=Objectlist->begin();//리스트 자체는 삭제 안해도 되는지
					while(Tile_iter2 != Objectlist->end())
					{
						if((*Tile_iter2)->m_Coll->AABB_B_B((*Tile_iter2)->m_Coll->Get_Cube_Model(),ExplsionArea2))
							(*Tile_iter2)->Set_Material(0);
						if((*Tile_iter2)->Get_Material() == 0)
						{
							sound->Stop(g_lpDSBG[4]);
							m_pExplosion = new CParticle_Explosion;
							m_pExplosion->Create(m_pExplosion_Tex->GetTexture());
							m_pExplosion->SetRender(true, (*Tile_iter2)->Get_Pos());
							Particlelist->push_back(m_pExplosion);
							sound->Play(g_lpDSBG[4], false);
						}
						Tile_iter2++;
					}
				}
			}
		}
		Tile_iter++;
	}
}

void CGameBase:: Game_Move(float tick)
{
	keyboard.key_State();
	mouseinput.mouse_state();

	if(keyboard.Get_Esc())//일시정지로 넘어감	
	{
		Pause = new CPause_System();
		Pause->Pause_init();
		m_game_state=3;
	}
	m_fTick_Game_run+=tick;

	if(m_fTick_Game_run>Tick_Gb_run_minmum)
	{
		m_fTick_Game_run=0;
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 500.0f );
		m_pFrustum->FrameMove(&Camera->GetViewMatrix(), &matProj);
		m_pPetal->SetPos(Player->Get_Pos());
		m_pPetal->SetVelocity(Player->m_PhyData->GetLinerVelocity());

		std::list<CParticle*>::iterator Particle_iter = Particlelist->begin();
		while(Particle_iter != Particlelist->end())
		{
			(*Particle_iter)->FrameMove();
			Particle_iter++;
		}





		m_HpBar->HP_Sys_Move(Player->Get_Player_Energy(),tick);

		Event_Move();
		Move_Tile();



		SkyBox->FrameMove(Camera->GetEye());
		//클리어 조건 처리
		if(Stage1_Is_Clear)
		{
			m_Clear = new CClear_System;
			m_Clear->Clear_Init(D3DXVECTOR3(Window_Width*0.5,Window_Height*0.7,0.f),D3DXVECTOR3(Window_Width*0.5,Window_Height*0.2,0.f));
			m_game_state=4;
			m_Clear->Volume(Volume);
			sound->Stop(g_lpDSBG[1]);
			sound->Stop(g_lpDSBG[2]);
			sound->Stop(g_lpDSBG[3]);
		}

		//저체온 사망 처리

		if(Player->GetTS() == 0.1f)
		{
			if(Particle_Die == 0)
			{
				m_pDie = new CParticle_Die();
				m_pDie->Create(m_pDie_Tex->GetTexture());
				m_pDie->SetRender(true, Player->Get_Pos());
				Particlelist->push_back(m_pDie);
				Particle_Die++;
			}
			else if(m_pDie->GetLive() == false)
			{
				Create_Game_Over();
			}
		}
		Player_Move();
	}		
	//렌더에 필요한 값을 지속적으로 갱신	
	Render();
}

void CGameBase::Event_Move()
{
	Event->Volume(Volume);
	Event->Set_Pos(Player->Get_Pos());


	if(Player->Get_Pos().y<Fall_Height)
	{

		Create_Game_Over();
	}
}



void ChangeToSimple_Vec(D3DXVECTOR3* Vector)
{
	if(abs(Vector->x)>abs(Vector->y))
	{
		Vector->y=0;
		if(abs(Vector->x)>abs(Vector->z))
			Vector->z=0;
		else
			Vector->x=0;
	}
	else
	{
		Vector->x=0;
		if(abs(Vector->y)>abs(Vector->z))
			Vector->z=0;
		else
			Vector->y=0;
	}
}

void CGameBase::Player_Move()
{
	float			fDegree = 0.f ;
	D3DXVECTOR3		vIntersection =D3DXVECTOR3(0,0,0);
	D3DXVECTOR3		vlength       =D3DXVECTOR3(0,0,0);
	float			fIntersec=0.f;
	D3DXVECTOR3		vPlayer_Pos=D3DXVECTOR3(0,0,0);
	D3DXVECTOR3		vTest_Player_move=D3DXVECTOR3(0,0,0);

	D3DXVECTOR3		vNormalVetor=D3DXVECTOR3(0,0,0);
	CPhysicData		CollPhy;//충돌한 타일의 물리데이터

	D3DXVECTOR3 PlayerMoveBefore = Player->Get_Pos();
	Player->PlayerMove(&Camera->GetViewMatrix());
	Player->Move();
	/*Player->SetMeshColor(0,0.4f , 0.3f ,0.6f,1.0f);*/
	Cube			PlayerArea;//플레이어 주위로 블럭 3개 크기의 영역
	PlayerArea.centerPos=Player->Get_Pos();
	PlayerArea.depth  = Tile_Size*3;
	PlayerArea.heigth = Tile_Size*3;
	PlayerArea.length = Tile_Size*3;

	//미리 플레이어의 교착점 도출//

	fDegree = D3DXVec3Dot(&Player->m_PhyData->GetLinerVelocity(),&Player->m_PhyData->GetLinerVelocity());//거리 비교대상
	std::list<CTile*>::iterator Tile_iter =Objectlist->begin();
	while(Tile_iter != Objectlist->end())
	{
		if(!(*Tile_iter)->Move())
		{
			delete(*Tile_iter);
			Tile_iter = Objectlist->erase(Tile_iter++);
			continue;
		}

		(*Tile_iter)->Set_Player_Energy(Player->Get_Player_Energy());

		if((*Tile_iter)->m_Coll->AABB_B_B((*Tile_iter)->m_Coll->Get_Cube_Model(),PlayerArea)){
			if((*Tile_iter)->m_Coll->CheckSp_B(
				Player->Get_Pos()+Player->m_PhyData->GetLinerVelocity(),Player->m_Coll->Get_Sp_Model().rad
				,(*Tile_iter)->m_Coll->Get_Cube_Model()))
			{
				vIntersection =(*Tile_iter)->m_Coll->
					Find_Intersection_Box(Player->Get_Pos(),
					Player->m_PhyData->GetLinerVelocity(),
					(*Tile_iter)->m_Coll->Get_Cube_Model());
				vlength = Player->Get_Pos() -vIntersection;
				fIntersec = D3DXVec3Dot(&vlength,&vlength);
				if(fDegree >fIntersec)//거리가 짧을 때 가장 가까운 교착점
				{
					Player->m_Coll->Set_CP(vIntersection);
					fDegree = fIntersec;
				}
			}


		}
		Tile_iter++;			
	}

	//플레이어에게 속도 적용//
	vPlayer_Pos = Player->Get_Pos();
	CPhisical::GetInstance()->Apply_Velocity(Player->m_PhyData,&vPlayer_Pos);
	//위치 변화 적용//
	Player->SetPos(vPlayer_Pos);
	Player->m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0,0,0),Player->Get_Pos());

	vTest_Player_move	= D3DXVECTOR3(0,0,0);		
	Tile_iter			= Objectlist->begin();
	PlayerArea.centerPos = Player->Get_Pos();
	float Tile_Fric=-1.0f;

	m_pPetal->SetLive(false);

	while(Tile_iter != Objectlist->end())
	{

		(*Tile_iter)->Set_Put(false);
		if((*Tile_iter)->m_Coll->AABB_B_B((*Tile_iter)->m_Coll->Get_Cube_Model(),PlayerArea)){
			if((*Tile_iter)->m_Coll->CheckSp_B((Player->m_Coll->Get_Sp_Model()),((*Tile_iter)->m_Coll->Get_Cube_Model()),&vTest_Player_move,&vNormalVetor))
			{
				Player->SetPos(Player->Get_Pos() + vTest_Player_move);	
				Player->m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0,0,0),Player->Get_Pos());


				//타일간 충돌시 이벤트 처리//
				Event->Event_Cheaking(*Tile_iter,Player);
				if((*Tile_iter)->Get_Material()== 8)
					Stage1_Is_Clear=true;



				if(D3DXVec3Dot(&vTest_Player_move,&vTest_Player_move)>1.f)//여기 아님
					D3DXVec3Normalize(&vTest_Player_move,&vTest_Player_move);
				ChangeToSimple_Vec(&vTest_Player_move);
				//vNormalVetor += vTest_Player_move;



				if((*Tile_iter)->m_Coll->CheckSp_B((Player->m_Coll->Get_Sp_Model()),
					((*Tile_iter)->m_Coll->Get_Cube_Model()),&vTest_Player_move))//교착점 이동 후 위치 보정용
				{
					Player->SetPos(Player->Get_Pos() + vTest_Player_move);	
					Player->m_Coll->ReviceSRT(D3DXVECTOR3(1.0f,1.0f,1.0f),
						D3DXVECTOR3(0,0,0),
						Player->Get_Pos());
					//vNormalVetor+=vTest_Player_move;
					m_pPetal->SetLive(true);
				}




				CollPhy =*((*Tile_iter)->m_PhyData);
				Tile_Fric = (*Tile_iter)->m_PhyData->GetFric();//리스트 순서상 마지막 충돌한 타일의 속성이 오므로 정확하지 않다.
				D3DXVec3Normalize(&vNormalVetor,&vNormalVetor);


				Player->m_PhyData->AddForce((vNormalVetor*CollPhy.GetElasticity())/Player->m_PhyData->GetMass());
				if(vNormalVetor.y>0.0f)
				{
					Player->m_PhyData->SetLinerVelocity(D3DXVECTOR3(Player->m_PhyData->GetLinerVelocity().x,0,Player->m_PhyData->GetLinerVelocity().z));
				}
				////////////////
				//올라서기
				/////////////
				if((*Tile_iter)->Get_Material()==11 && vNormalVetor.y>0.f)				
					(*Tile_iter)->Set_Put(true);				



				//
				GB_Bomb_Tile();
				//

				if((*Tile_iter)->Get_Material() == 4)
				{
					sound->Stop(g_lpDSBG[5]);
					m_pWind = new CParticle_Wind();

					//vNormalVetor
					m_pWind->Create(m_pWind_Tex->GetTexture());
					m_pWind->SetRender(true, (*Tile_iter)->Get_Pos(), vNormalVetor);
					Particlelist->push_back(m_pWind);
					sound->Play(g_lpDSBG[5], false);
				}
				else if((*Tile_iter)->Get_Material() == -2)
				{
					sound->Stop(g_lpDSBG[5]);
					m_pWind = new CParticle_Wind();

					//vNormalVetor
					m_pWind->Create(m_pWind_Tex->GetTexture());
					m_pWind->SetRender(true, (*Tile_iter)->Get_Pos(), vNormalVetor);
					Particlelist->push_back(m_pWind);
					sound->Play(g_lpDSBG[5], false);
				}
				else if((*Tile_iter)->Get_Material() == 0)
				{
					sound->Stop(g_lpDSBG[6]);
					m_pSend = new CParticle_Send();
					m_pSend->Create(m_pSend_Tex->GetTexture());
					m_pSend->SetRender(true, (*Tile_iter)->Get_Pos());
					Particlelist->push_back(m_pSend);
					sound->Play(g_lpDSBG[6], false);
				}
				else if((*Tile_iter)->Get_Material() == -1)
				{
					m_pIce = new CParticle_Send();
					m_pIce->Create(m_pIce_Tex->GetTexture());
					m_pIce->SetRender(true, (*Tile_iter)->Get_Pos());
					Particlelist->push_back(m_pIce);
				}
			}
		}
		Tile_iter++;	
	}

	if(Particlelist->size() >= 3)
	{
		std::list<CParticle*>::iterator iterEnd = Particlelist->end();
		std::list<CParticle*>::iterator iterBegin = Particlelist->begin();
		iterBegin++;
		iterBegin++;
		for(std::list<CParticle*>::iterator iterPos = iterBegin ; iterPos != iterEnd ; )
		{
			if((*iterPos)->GetLive() == false)
			{
				delete (*iterPos);
				(*iterPos) = NULL;
				Particlelist->erase(iterPos++);
			}
			else
				++iterPos;
		}
	}

	if(Tile_Fric >= 0.0f)//충돌시에만 연산한다.
	{
		//ChangeToSimple_Vec(&vNormalVetor);

		//CPhisical::GetInstance()->ElasticityCrash(Player->m_PhyData,&CollPhy,vNormalVetor);
		Player->CollisionCheck = true;//충돌이되면 충돌체크를 true
	}
	else
	{
		Player->CollisionCheck = false;//충돌이되면 충돌체크를 false
	}
	CPhisical::GetInstance()->Friction(Player->m_PhyData,Tile_Fric);

	Player->Set_Player_Energy(Player->Get_Player_Energy()+Spontaneous_Loss_Energy);



	D3DXVECTOR3 PlayerMoveAfter = Player->Get_Pos();
	PlayerMove = PlayerMoveAfter - PlayerMoveBefore; //움직이기 전과 움직임 후의 플레이어좌표의 차이값
	Player_Camera();
	Player->ColorUpdate();
	Player->SetMeshColor(0,Player->Red,Player->Green,Player->Blue,1.0f);
}


void CGameBase::Menu_Render(float tick)
{
	menu.Volume(Volume);
	keyboard.key_State();
	/// 후면버퍼와 Z버퍼를 지운다.
	Get_Device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	Get_Device->BeginScene();

	Get_Device->SetTransform(D3DTS_WORLD,m_Base_World_mat);//기본 월드 행렬로 설정
	Get_Device->SetTransform( D3DTS_VIEW, &menu.Mcamera->GetViewMatrix() );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 10000.0f );
	Get_Device->SetTransform( D3DTS_PROJECTION, &matProj );

	SkyBox->FrameMove(menu.Mcamera->GetEye());
	SkyBox->Render();



	m_Menu_Tick+=tick;
	if(m_Menu_Tick>Tick_Gb_run_minmum)
	{
		m_Menu_Tick = 0;
		menu.menu_move(tick);
		menu.Menu_Select(keyboard.Get_UP(),keyboard.Get_Down(),keyboard.Get_Enter());


	}		
	menu.Render();


	if(menu.Get_gamestart() == true )
	{
		Title_Clear_Up();
		m_game_state = 1;

	}



	Get_Device->EndScene();

	/// 후면버퍼를 보이는 화면으로!
	Get_Device->Present( NULL, NULL, NULL, NULL );
}

void CGameBase::Create_Game_Over()
{
	m_GO = new CGame_Over;
	m_GO->Game_Over_Init(D3DXVECTOR3(Window_Width*0.5f,Window_Height*0.8f,0.f),
		D3DXVECTOR3(Window_Width*0.5f,Window_Height*0.3f,0.f),
		D3DXVECTOR3(Window_Width*0.5f,Window_Height*0.1f,0.f));
	m_game_state=5;

	sound->Stop(g_lpDSBG[1]);
	sound->Stop(g_lpDSBG[2]);
	sound->Stop(g_lpDSBG[3]);

	sound->Play(g_lpDSBG[7], false);
}
void CGameBase::Render()
{
	/// 후면버퍼와 Z버퍼를 지운다.
	Get_Device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	/// 렌더링 시작
	if( SUCCEEDED( Get_Device->BeginScene() ) )
	{
		//Test_Lighting();
		//SkyBox->Render();
		/// 월드,뷰,프로젝션 행렬을 설정한다.////////


		//기본 월드 행렬로 설정

		/// 뷰행렬을 설정
		//Get_Device->SetTransform( D3DTS_VIEW, &Camera->GetViewMatrix() );
		//Get_Device->SetTransform( D3DTS_VIEW, &menu.Mcamera->GetViewMatrix() );


		///렌더링///		

		/// 뷰행렬을 설정
		Get_Device->SetTransform( D3DTS_VIEW, &Camera->GetViewMatrix() );

		Get_Device->SetTransform(D3DTS_WORLD,m_Base_World_mat);
		/// 프로젝션 행렬 설정
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 10000.0f );
		Get_Device->SetTransform( D3DTS_PROJECTION, &matProj );
		///////////////////////
		//스카이박스,타일 렌더.  일시정지에서는 렌더하지 않는다.
		//////////////////////
		if(Pause == NULL)
		{
			Space_SkyBox->FrameMove(Camera->GetEye());
			Space_SkyBox->Render();			

			Player->PlayerRender(&Camera->GetViewMatrix());

			std::list<CTile*>::iterator Tile_iter=Objectlist->begin();
			while(Tile_iter != Objectlist->end())		
				(*Tile_iter++)->Render(m_pFrustum);
		}
		else
		{
			//SkyBox->Render();
			SkyBox->Render();
			Player->PlayerRender(&Camera->GetViewMatrix());
		}
		std::list<CParticle*>::iterator Particle_iter = Particlelist->begin();

		Player->PlayerRender(&Camera->GetViewMatrix());
		while(Particle_iter != Particlelist->end())
		{
			(*Particle_iter)->Render();
			Particle_iter++;
		}



		/////////////////////////////////////////////////////
		//여기부터는 평면 UI 렌더입니다.
		// 3d좌표 쓰는 것들은 위에서 렌더하세요
		//////////////////////////////////////////////////////

		D3DXMatrixIdentity(&matProj);
		Get_Device->SetTransform( D3DTS_VIEW, &matProj );
		Get_Device->SetTransform(D3DTS_WORLD,&matProj);

		D3DXMatrixOrthoOffCenterLH( &matProj, 0.0f, Window_Width, 0,Window_Height, -600.0f, 600.0f );
		Get_Device->SetTransform( D3DTS_PROJECTION, &matProj );
		//일시 정지시 렌더

		if(Pause!= NULL)								
			Pause->Pause_Render();		

		if(m_Clear!= NULL)		
			m_Clear->Render();		

		if(m_GO!= NULL)		
			m_GO->Render();	

		if(m_GO==NULL && Pause==NULL &&m_Clear==NULL )
			m_HpBar->Render();


		Get_Device->SetTransform( D3DTS_VIEW, &Camera->GetViewMatrix() );
		/// 렌더링 종료
		Get_Device->EndScene();

	}

	/// 후면버퍼를 보이는 화면으로!
	Get_Device->Present( NULL, NULL, NULL, NULL );
}

void CGameBase::Player_Camera()
{
	Camera->SetEye(&(Camera->GetEye()+PlayerMove));
	Camera->SetLookAt(&Player->Get_Pos());
	Camera->RotateWorldLookAtY(mouseinput.Get_mouse_x()*0.1);
	Angle_X_Limt = Angle_X_Limt + (float)mouseinput.Get_mouse_y()*0.1;
	if(Angle_X_Limt > 20)
	{
		Angle_X_Limt = 20;
	}
	else if(Angle_X_Limt <-70)
	{
		Angle_X_Limt = -70;
	}
	else
	{
		Camera->RotateLookAtX(mouseinput.Get_mouse_y()*0.1);
	}


	m_pTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pIronTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pWaterTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pFireTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pWindTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pWoodTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pStyroTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_IceTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pBallShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pAlphaShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pIronTileShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	m_pClearShader->SetCameraEyePos(Camera->GetEye(),Player->Get_Pos());
	//////////////////////////////////////////////
	///에너지바 카메라 아이포스 세팅
	/////////////////////////////////////////
	if(m_GO==NULL && Pause==NULL &&m_Clear==NULL )
		m_HpBar->SettingCameraEyePos(Camera->GetEye(),Player->Get_Pos());

	if(GetAsyncKeyState(VK_F2)&0x8001 )
	{
		Player->Set_Player_Energy(Player->Get_Player_Energy()-10);
	}

	if(GetAsyncKeyState(VK_F3)&0x8001 )
	{
		Player->Set_Player_Energy(Player->Get_Player_Energy()+10);
	}

}