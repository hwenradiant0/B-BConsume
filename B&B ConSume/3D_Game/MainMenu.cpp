#include "MainMenu.h"


CMainMenu::CMainMenu(void)
{
	
}

CMainMenu::~CMainMenu(void)
{
}


void CMainMenu::Volume(int num)
{
	for(int i=0 ; i<3 ; i++)
		sound->SetVolume(g_lpDSBG[i], num);
}


void CMainMenu::Menu_Select(BOOL UP , BOOL DOUN , BOOL Enter)
{	
	if( look == D3DXVECTOR3(0,0,0))
	{
		if(UP)
		{
			sound->Stop(g_lpDSBG[0]);
			select += 1;
			sound->Play(g_lpDSBG[0], false);
		}
		else if(DOUN)
		{
			sound->Stop(g_lpDSBG[0]);
			select -= 1;

			sound->Play(g_lpDSBG[0], false);
		}
	}

	if( select >=5 ){select = 1;}
	if( select <= 0){select = 4;}

	if(look == D3DXVECTOR3(0,0,0))
	{
		if(select == 4 && Enter)
		{
			Select_stage = true;

			sound->Play(g_lpDSBG[1], false);
		}

		if(select == 3 && Enter)//하우투 플레이
		{
			control = true;
			sound->Play(g_lpDSBG[1], false);
		}

		if(select == 2 && Enter)
		{
			credit = true;
			sound->Play(g_lpDSBG[1], false);
		}

		if(select == 1 && Enter)
		{
			Exit = true;
			sound->Play(g_lpDSBG[1], false);
		}
		switch(select)
	{
	case 4:	SMmesh[0].change_color();
		SMmesh[1].old_color();
		SMmesh[2].old_color();
		SMmesh[3].old_color();
		break;
	case 3:	SMmesh[1].change_color();
		SMmesh[0].old_color();
		SMmesh[2].old_color();
		SMmesh[3].old_color();
		break;
	case 2:	SMmesh[2].change_color();
		SMmesh[0].old_color();
		SMmesh[1].old_color();
		SMmesh[3].old_color();
		break;
	case 1:	SMmesh[3].change_color();
		SMmesh[0].old_color();
		SMmesh[1].old_color();
		SMmesh[2].old_color();
		break;
	}
	}


	

}


void CMainMenu::init()
{
	Select_stage = false;
	game_start = false;
	control = false;
	credit = false;
	Exit = false;

	B_control = false;
	B_credit = false;
	B_Select_stage = false;
	se_howtoplay = false;
	se_howtoplay_check = false;

	Rotate_Cursor_XAngle = 0;

	select = 1;
	randem = 1;
	Stage  = 3;
	Stage_Select = 0;

	game_start = false;
	select = 4;
	Vector[700] = D3DXVECTOR3(0,0,0);
	Target[0] = D3DXVECTOR3(0,0,0);
	mouse_pos = D3DXVECTOR3(0,0,0);


	Interpolation = 20;
	Interpolation_N = 0;

	R_Interpolation = 20;
	R_Interpolation_N = 0;

	EInterpolation = 20;
	EInterpolation_N = 0;

	mouse.Init();


	srand((unsigned int)time(NULL)); //시간 받아와서 램덤으로 돌러줘염

	eye		=	D3DXVECTOR3(0,0,-300);
	look	=	D3DXVECTOR3(0,0,0);
	UP		=   D3DXVECTOR3(0.0f,1.0f,0.0f);

	Mcamera = new ZCamera();
	Mcamera->SetViewMatrix(&(D3DXVECTOR3(0,0,-300.0f)),&D3DXVECTOR3(0,0,0),&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));


	Shader = new CShader();
	Shader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/NONE.png","Texture/NONE.jpg");

	Credit = new CCreditDice_Algorithm();
	Credit->Credit_Init(D3DXVECTOR3(220,0,-275),D3DXVECTOR3(300,0,-350),D3DXVECTOR3(0,D3DX_PI/2-D3DX_PI/20,0),
		D3DXVECTOR3(-D3DX_PI/2,D3DX_PI/2+D3DX_PI/20,0));

	sound = new Sound();
	sound->LoadWave("Sound/SE/Main/Main_Select_Move_SE.wav", &g_lpDSBG[0]);//메인 이동키 소리
	sound->LoadWave("Sound/SE/Main/Main_Select_SE.wav", &g_lpDSBG[1]);//메인 셀렉 소리
	sound->LoadWave("Sound/SE/Main/Main_HowToPlay_Key_SE.wav", &g_lpDSBG[2]);//메인 How To Play 키보드소리
	sound->LoadWave("Sound/SE/Main/menu_select_4.wav", &g_lpDSBG[3]); //타일 설명 넘기는 종이소리 추후 구현

	///하우투플레이 메쉬들->셰이더 필요없을 듯
	How = new MenuMesh[4]; //325
	How[0].Init("XFile/Plane_Explain1.X",D3DXVECTOR3(0, 0 ,-365),0.1f,Coll_TYPE_Sphere,NULL);
	How[1].Init("XFile/Plane_Explain2.X",D3DXVECTOR3(50, 0 ,-365),0.1f,Coll_TYPE_Sphere,NULL);
	How[2].Init("XFile/Plane_Explain3.X",D3DXVECTOR3(100, 0 ,-365),0.1f,Coll_TYPE_Sphere,NULL);
	How[3].Init("XFile/Plane_Explain4.X",D3DXVECTOR3(150, 0 ,-365),0.1f,Coll_TYPE_Sphere,NULL);
	Plain_Default_Pos = D3DXVECTOR3(0, 0 ,-350);


	Selet_Stage = new MenuMesh[4];
	Selet_Stage[0].Init("XFile/Stage 1.X",D3DXVECTOR3(0, 60 ,-306),0.1f,Coll_TYPE_Sphere,Shader);
	Selet_Stage[0].SetRotation(D3DX_PI,0,0);
	Selet_Stage[0].SetMeshColor(0,1.f,0.f,0.f,1.f);

	Selet_Stage[1].Init("XFile/Stage 2.X",D3DXVECTOR3(0, 60 ,-299),0.1f,Coll_TYPE_Sphere,Shader);
	Selet_Stage[1].SetRotation(D3DX_PI,0,0);
	Selet_Stage[1].SetMeshColor(0,0.2f,0.2f,0.2f,1.f);

	Selet_Stage[2].Init("XFile/Stage 3.X",D3DXVECTOR3(0, 60 ,-292),0.1f,Coll_TYPE_Sphere,Shader);
	Selet_Stage[2].SetRotation(D3DX_PI,0,0);
	Selet_Stage[2].SetMeshColor(0,0.f,0.f,1.f,1.f);

	Selet_Stage[3].Init("XFile/Cursor.X",D3DXVECTOR3(0, 60 ,-306),0.1f,Coll_TYPE_Sphere,Shader);
	Selet_Stage[3].SetRotation(D3DX_PI,0,0);
	Selet_Stage[3].SetMeshColor(0,0.05f,0.05f,0.05f,1.f);


	key_mash = new MenuMesh[8];
	key_mash[0].Init("XFile/Key_A.X",D3DXVECTOR3(-45, -1.f ,-311.2f),0.1f,Coll_TYPE_Sphere,Shader);
	key_mash[0].keyboard_rot();
	key_mash[0].SetMeshColor(0,0.05f,0.05f,0.05f,1.f);

	key_mash[1].Init("XFile/Key_S.X",D3DXVECTOR3(-45, -1.f ,-307.2f),0.1f,Coll_TYPE_Sphere,Shader);
	key_mash[1].keyboard_rot();
	key_mash[1].SetMeshColor(0,0.05f,0.05f,0.05f,1.f);

	key_mash[2].Init("XFile/Key_D.X",D3DXVECTOR3(-45, -1.f ,-303.2f),0.1f,Coll_TYPE_Sphere,Shader);
	key_mash[2].keyboard_rot();
	key_mash[2].SetMeshColor(0,0.05f,0.05f,0.05f,1.f);

	key_mash[3].Init("XFile/Key_W.X",D3DXVECTOR3(-45, 3.0f ,-307.2f),0.1f,Coll_TYPE_Sphere,Shader);
	key_mash[3].keyboard_rot();
	key_mash[3].SetMeshColor(0,0.05f,0.05f,0.05f,1.f);

	key_mash[4].Init("XFile/Key_Space.X",D3DXVECTOR3(-35, -7.0f ,-301.5f),0.1f,Coll_TYPE_Sphere,Shader);
	key_mash[4].keyboard_rot();
	key_mash[4].SetMeshColor(0,0.05f,0.05f,0.05f,1.f);

	key_mash[5].Init("XFile/Real_Black_Mouse.X",D3DXVECTOR3(-40, 6.f ,-290.0f),0.03f,Coll_TYPE_Sphere,Shader);
	key_mash[5].keyboard_rot();
	key_mash[5].SetMeshColor(0,0.0001f,0.0001f,0.0001f,1.f);

	key_mash[6].Init("XFile/Key_ESC_Texture.X",D3DXVECTOR3(-35.f, 7.5f ,-307.5f),0.07f,Coll_TYPE_Sphere,Shader);
	key_mash[6].keyboard_rot();
	key_mash[6].SetMeshColor(0,0,0,0,1.f);

	key_mash[7].Init("XFile/Key_Enter.X",D3DXVECTOR3(-60.f, -6.f ,-285.0f),0.15f,Coll_TYPE_Sphere,Shader);
	key_mash[7].keyboard_rot();
	key_mash[7].SetMeshColor(0,0.0001f,0.0001f,0.0001f,1.f);

	//키 설명 메쉬
	Key_Explain_Mesh = new MenuMesh[11];
	Key_Explain_Mesh[0].Init("XFile/Explain_Left.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[1].Init("XFile/Explain_Back.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[2].Init("XFile/Explain_Right.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[3].Init("XFile/Explain_Foword.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[4].Init("XFile/Explain_Jump.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[5].Init("XFile/Explain_Rotate.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[6].Init("XFile/Explain_Zoom.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[7].Init("XFile/Explain_Out.X",D3DXVECTOR3(-35, 6 ,-298.5f),0.1f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[8].Init("XFile/Explain_Esc.X",D3DXVECTOR3(-30.f, 4.4f ,-305.5f),0.05f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[9].Init("XFile/Explain_Enter.X",D3DXVECTOR3(-30, -6.8f ,-292.0f),0.05f,Coll_TYPE_Sphere,Shader);
	Key_Explain_Mesh[10].Init("XFile/Next_Page.X",D3DXVECTOR3(-30.f, 9.7f ,-310.5f),0.05f,Coll_TYPE_Sphere,Shader);
	for(int i=0;i<11;i++)	
	{
		Key_Explain_Mesh[i].keyboard_rot_pluse();
		Key_Explain_Mesh[i].SetMeshColor(0,0.2f,0.2f,0.2f,1.f);
	}
	Key_Explain_Mesh[8].SetMeshColor(0,0.2f,0.2f,0.2f,1.f);
	Key_Explain_Mesh[9].SetMeshColor(0,0.2f,0.2f,0.2f,1.f);
	Key_Explain_Mesh[9].keyboard_rot_Enter_Fix();
	Key_Explain_Mesh[10].SetMeshColor(0,0.8f,0.2f,0.2f,1.f);


	SMmesh= new MenuMesh[5];
	SMmesh[0].Init("XFile/Game_Strat.X",D3DXVECTOR3(0, -5 ,-150),0.1f,Coll_TYPE_Sphere,Shader);
	SMmesh[0].old_color();

	SMmesh[1].Init("XFile/HowtoPlay.X",D3DXVECTOR3(0, -15 ,-150),0.1f,Coll_TYPE_Sphere,Shader);
	SMmesh[1].old_color();

	SMmesh[2].Init("XFile/Credit.X",D3DXVECTOR3(0, -25 ,-150),0.1f,Coll_TYPE_Sphere,Shader);
	SMmesh[2].old_color();

	SMmesh[3].Init("XFile/Exit.X",D3DXVECTOR3(0, -35 ,-150),0.1f,Coll_TYPE_Sphere,Shader);
	SMmesh[3].old_color();

	SMmesh[4].Init("XFile/BYEBYE.X",D3DXVECTOR3(0, -30 ,-300),0.1f,Coll_TYPE_Sphere,Shader);
	SMmesh[4].SetMeshColor(1,0.f,0.f,0.f,1.f);

	mesh = new MenuMesh[700];
	for(int i = 0 ; i < 700 ;i++)
	{
		mesh[i].Init(Command_Cube,D3DXVECTOR3((rand()%30+1)*21 -180 ,(rand()%30+1)*21 - 80 ,(rand()%30+1)*21 + -200 ),
			0.6f,Coll_TYPE_Sphere,Shader);
		mesh[i].SetMeshColor(1.0f, 1.0f , 0.0f , 0.0f ,1.0f);

	}
	KeyEx_Now_Change=false;
	Middle_Plane_Num=0;
	Max_Plane_Num=4;
	Plain_Still_Moving=false;
	Plain_Frame=0;
	Plain_On=false;
	tick =0;
	Any_Key_Down=false;
	Key_Down_Num=-1;
	How_To_On=false;
	Render_Key_Down=-1;
	m_tick_menu_Explain_pause =0;
	Shader->SetCameraEyePos(Mcamera->GetEye(),Mcamera->GetEye()+D3DXVECTOR3(0,0,-100));
}

void CMainMenu::Stage_select()
{
	if(  look == D3DXVECTOR3(0, 300 ,-299) )
	{

		if(key.Get_UP()){Stage += 1;}
		else if(key.Get_Down()){Stage -= 1;}

		if( Stage >=4 ){Stage = 1;}
		if( Stage <=0){Stage =3;}


		if(Stage == 3 && key.Get_Enter() )
		{
			Stage_Select =1;
			Select_stage = false;
			game_start = true;

		}
		else if(Stage == 2 &&  key.Get_Enter() )
		{
			Stage_Select =2;
			Select_stage = false;
			game_start = true;
		}
		else if(Stage == 1 &&  key.Get_Enter() )
		{
			Stage_Select =3;
			Select_stage = false;
			game_start = true;
		}
	}
}

void CMainMenu::menu_kyeDown()
{
	if(How_To_On)
	{
		Any_Key_Down=false;
		if(mouse.Get_mouse_x() && mouse.Get_mouse_y())
		{
			mouse_pos.z = mouse.Get_mouse_x()*0.05f;
			mouse_pos.y = -mouse.Get_mouse_y()*0.1f;
			key_mash[5].SetPos(D3DXVECTOR3(-40, 6.f ,-290.0f) + mouse_pos);
			Key_Down_Num=5;
			Any_Key_Down=true;
		}
		else
		{
			if(key_mash[5].Get_Pos() == D3DXVECTOR3(-40, 3 ,-290.0f) )
			{

			}
			key_mash[5].SetPos(D3DXVECTOR3(-40, 6.f ,-290.0f) );
		}
		if(key.Get_A())
		{
			sound->Stop(g_lpDSBG[2]);
			key_mash[0].SetPos( D3DXVECTOR3(-45-5.f, -1.f ,-311.2f) );
			Key_Down_Num=0;
			Any_Key_Down=true;
			sound->Play(g_lpDSBG[2], FALSE);
		}
		else
		{
			key_mash[0].SetPos(D3DXVECTOR3(-45, -1.f ,-311.2f) );

		}

		if(key.Get_S())
		{
			sound->Stop(g_lpDSBG[2]);
			key_mash[1].SetPos(D3DXVECTOR3(-45-5.f, -1.f ,-307.2f) );
			Key_Down_Num=1;
			Any_Key_Down=true;
			sound->Play(g_lpDSBG[2], FALSE);
		}
		else
		{
			key_mash[1].SetPos(D3DXVECTOR3(-45, -1.f ,-307.2f) );

		}

		if(key.Get_D())
		{
			sound->Stop(g_lpDSBG[2]);
			key_mash[2].SetPos(D3DXVECTOR3(-45-5.f, -1.f ,-303.2f) );
			Key_Down_Num=2;
			Any_Key_Down=true;
			sound->Play(g_lpDSBG[2], FALSE);
		}
		else
		{
			key_mash[2].SetPos(D3DXVECTOR3(-45, -1.f ,-303.2f) );
		}

		if(key.Get_W())
		{
			sound->Stop(g_lpDSBG[2]);
			key_mash[3].SetPos(D3DXVECTOR3(-45-5.f, 3.0f ,-307.2f) );
			Key_Down_Num=3;
			Any_Key_Down=true;
			sound->Play(g_lpDSBG[2], FALSE);
		}
		else
		{
			key_mash[3].SetPos(D3DXVECTOR3(-45, 3.0f ,-307.2f) );
		}

		if(key.Get_Space())
		{
			sound->Stop(g_lpDSBG[2]);
			key_mash[4].SetPos(D3DXVECTOR3(-35-5.f, -7.0f ,-301.5f));
			Key_Down_Num=4;
			Any_Key_Down=true;
			sound->Play(g_lpDSBG[2], FALSE);
		}
		else
		{
			key_mash[4].SetPos(D3DXVECTOR3(-35, -7.0f ,-301.5f));
		}



		if(mouse.Get_Wheel() >0)
		{
			Key_Down_Num=6;
			Any_Key_Down=true;
			mouse.Set_Wheel(0);
		}
	    else if(mouse.Get_Wheel() <0)
		{
			Key_Down_Num=7;
			Any_Key_Down=true;
			mouse.Set_Wheel(0);
		}
		


		if( Key_Down_Num != Render_Key_Down)//좀 늦게 반응하도록
		{
			Render_Key_Down = Key_Down_Num;
			KeyEx_Now_Change=true;
			m_tick_menu_Explain_pause=0;
		}

		if(KeyEx_Now_Change==true)
		{
			m_tick_menu_Explain_pause +=tick;
			if(m_tick_menu_Explain_pause>1)
			{
				Key_Down_Num=-1;
				m_tick_menu_Explain_pause=0;
				KeyEx_Now_Change=false;
			}

		}
	}


}

float Angle_LinerInterpo(float v0,float v1,float FrameperMax)
{
	return (v0*(1-FrameperMax) + v1*FrameperMax);
}
void CMainMenu::Pan_move()
{
	if(Plain_On)
	{
	if(Plain_Still_Moving==false)
	{
		
		if(key.Get_Right()&&!key.Get_Left() )
		{
			Middle_Plane_Num = Middle_Plane_Num-1;			
			Plain_Still_Moving=true;
			Plain_Frame=0;
	

		}
		else if(key.Get_Left()&&!key.Get_Right() )
		{

			Middle_Plane_Num = Middle_Plane_Num+1;			
			Plain_Still_Moving=true;
			Plain_Frame=0;
	
		}

		if(Middle_Plane_Num>Max_Plane_Num-1)	
		{
			Middle_Plane_Num = Max_Plane_Num-1;
			Plain_Still_Moving=false;
		}

		if(Middle_Plane_Num<0)	
		{
			Middle_Plane_Num = 0;
			Plain_Still_Moving=false;
		}
		if(Plain_Still_Moving == true)
		{
			for(int i = 0;i<4;i++)
			{
				Plain_Last_Pos[i] = How[i].Get_Pos();
			}
		}
	}
	float Move_X = Plain_Default_Pos.x;
	float Move_Y_Angle = D3DX_PI;
	if(Plain_Still_Moving==true)
	{	
		if(Plain_Frame<=20)//굳이 4번씩 할 필요없어서 보기 안좋지만 밖으로 뺐음
				Move_Y_Angle = Angle_LinerInterpo(D3DX_PI,D3DX_PI/2.f,(float)((float)Plain_Frame/(float)20.f));
			else if(Plain_Frame>=20)
				Move_Y_Angle =D3DX_PI/2.f;

		if(Plain_Frame>=60 &&Plain_Frame<=80)
		{
				Move_Y_Angle = Angle_LinerInterpo((D3DX_PI/2.f),D3DX_PI,(float)((float)(Plain_Frame-60)/(float)20.f));
				
		}
			else if(Plain_Frame>80)
				Move_Y_Angle= D3DX_PI;

		for(int i=0;i<4;i++)
		{	
			Move_X = Plain_Last_Pos[i].x;

			if(Plain_Frame>=20 &&Plain_Frame<=60)
				Move_X = Angle_LinerInterpo(Plain_Last_Pos[i].x,Plain_Default_Pos.x +50*(i-Middle_Plane_Num),
				(float)((float)(Plain_Frame-20)/(float)40.f));
			else if(Plain_Frame>=60)
				Move_X=	Plain_Default_Pos.x +50*(i-Middle_Plane_Num);

		
			How[i].SetRotation(-D3DX_PI/2.f,Move_Y_Angle,0);
			How[i].SetPos(D3DXVECTOR3( Move_X,Plain_Last_Pos[i].y,Plain_Last_Pos[i].z));
		}

		Plain_Frame++;
		if(Plain_Frame>=80)
		{
			Plain_Frame=0;
			Plain_Still_Moving=false;			
		}

	}
	else
		for(int i = 0 ; i < 4 ; i++)
		{
			How[i].SetRotation(-D3DX_PI/2.f,D3DX_PI,0);		

		}
	}
}



void CMainMenu::menu_move(float ttick)
{
	tick =ttick;

	Menu_Camera();
	mouse.mouse_state();
	key.key_State();
	menu_kyeDown();
	Stage_select();
	Pan_move();
	title_Data a[700];

	fileload.Title_Read("Text/title_document.txt",a);

	for(int i = 0 ; i < 700 ; i++)
	{
		Menu_Target[i].x = a[i].ix*20-485;
		Menu_Target[i].y = -(a[i].iy*20) + 420;
		Menu_Target[i].z = a[i].iz*20+900;

		Vector[i] =  (Target[i] - mesh[i].Get_Pos())  ;
		D3DXVec3Normalize(&Vector[i],&Vector[i]);
		Vector[i] *=4;

		mesh[i].m_vPos += Vector[i];
		mesh[i].SetPos(mesh[i].m_vPos);
		mesh[i].menu_box_move();

		Target[i] = Menu_Target[i];
	}

	if(look == D3DXVECTOR3(300,0,-300) )
		Credit->Credit_Run(key.Get_UP(),key.Get_Down(),key.Get_Esc(),0);


	if(look == D3DXVECTOR3(0, 300 ,-299) )
	{  
		if(Stage == 3)
			Selet_Stage[3].SetPos(D3DXVECTOR3(0, 60 ,-306.8f));
		else if( Stage == 2)
			Selet_Stage[3].SetPos(D3DXVECTOR3(0, 60 ,-299.8f));
		else if( Stage == 1)
			Selet_Stage[3].SetPos(D3DXVECTOR3(0, 60 ,-292.8f));
	}
	Rotate_Cursor_XAngle+= D3DX_PI/30;
	Selet_Stage[3].SetRotation(Rotate_Cursor_XAngle,0,0);



}

void CMainMenu::S_Stage()
{
	if( look != D3DXVECTOR3(0, 300 ,-299) ) 
	{
		R_Interpolation = 20;
		R_Interpolation_N = 0;

		look =  D3DXVECTOR3(0,0,0) * (1.0f - (Interpolation_N / Interpolation) ) +
			D3DXVECTOR3(0, 300 ,-299) * (Interpolation_N / Interpolation);
		if( Interpolation_N != 20)
			Interpolation_N += 1;
	}

	else if(  look == D3DXVECTOR3(0, 300 ,-299) )
	{
		if(key.Get_Esc())
		{
			sound->Stop(g_lpDSBG[1]);
			Select_stage = false;
			B_Select_stage = true;
			sound->Play(g_lpDSBG[1], false);
		}
	}
}

void CMainMenu::SB_Stage()
{
	if( look != D3DXVECTOR3(0,0,0) )
	{
		Interpolation = 20;
		Interpolation_N = 0;

		look = D3DXVECTOR3(0, 300 ,-299) * (1.0f - (R_Interpolation_N / R_Interpolation) ) +
			D3DXVECTOR3(0,0,0) * (R_Interpolation_N / R_Interpolation);
		R_Interpolation_N++;
	}

	else if( look == D3DXVECTOR3(0,0,0) )
	{
		B_Select_stage = false;
		Interpolation = 20;
		Interpolation_N = 0;
		R_Interpolation = 20;
		R_Interpolation_N = 0;

	}
}

void CMainMenu::SE_HowToPlay()
{
	Plain_On=true;
	if( look != D3DXVECTOR3(0,0,-600) )
	{
		look =  D3DXVECTOR3(-300,0,-300) * (1.0f - (EInterpolation_N / EInterpolation) ) +
			D3DXVECTOR3(0,0,-600) * (EInterpolation_N / EInterpolation);
		EInterpolation_N++;
	}

	if(look == D3DXVECTOR3(0,0,-600) )
	{

		if(key.Get_Esc())
		{
			sound->Stop(g_lpDSBG[1]);
			se_howtoplay = false;
			se_howtoplay_check = true;

			EInterpolation = 20;
			EInterpolation_N = 0;
			sound->Play(g_lpDSBG[1], false);
		}
	}
}

void CMainMenu::SEB_HowToPlay()
{
	if( look != D3DXVECTOR3(-300,0,-300) )
	{
		look =  D3DXVECTOR3(0,0,-600) * (1.0f - (EInterpolation_N / EInterpolation) ) +
			D3DXVECTOR3(-300,0,-300) * (EInterpolation_N / EInterpolation);
		EInterpolation_N++;
	}
	else if(  look == D3DXVECTOR3(-300,0,-300) )
	{
		Plain_On =false;
		EInterpolation = 20;
		EInterpolation_N = 0;


		if( key.Get_Esc() )
		{
			sound->Stop(g_lpDSBG[1]);
			control = true;
			se_howtoplay_check = false;
			sound->Play(g_lpDSBG[1], false);
		}

		if(key.Get_Enter())
		{
			sound->Stop(g_lpDSBG[1]);
			control = false;
			se_howtoplay = true;
				se_howtoplay_check = false;
			sound->Play(g_lpDSBG[1], false);
		}
	}
}

void CMainMenu::S_HowToPlay()
{
	How_To_On=true;
	if( look != D3DXVECTOR3(-300,0,-300) )
	{
		R_Interpolation = 20;
		R_Interpolation_N = 0;

		look =  D3DXVECTOR3(0,0,0) * (1.0f - (Interpolation_N / Interpolation) ) +
			D3DXVECTOR3(-300,0,-300) * (Interpolation_N / Interpolation);
		Interpolation_N++;
	}

	else if(  look == D3DXVECTOR3(-300,0,-300) )
	{
		
		
		if(key.Get_Esc())
		{
			sound->Stop(g_lpDSBG[1]);
			control = false;
			B_control = true;
			sound->Play(g_lpDSBG[1], false);
		}
		if(key.Get_Enter())
		{
			sound->Stop(g_lpDSBG[1]);
			control = false;
			se_howtoplay = true;
			sound->Play(g_lpDSBG[1], false);
		}
	}
}

void CMainMenu::SB_HowToPlay()
{
	if( look != D3DXVECTOR3(0,0,0) )
	{
		Interpolation = 20;
		Interpolation_N = 0;

		look = D3DXVECTOR3(-300,0,-300)  * (1.0f - (R_Interpolation_N / R_Interpolation) ) +
			D3DXVECTOR3(0,0,0) * (R_Interpolation_N / R_Interpolation);
		R_Interpolation_N++;
	}

	else if( look == D3DXVECTOR3(0,0,0) )
	{
		How_To_On=false;
		
		B_control = false;
		Interpolation = 20;
		Interpolation_N = 0;
		R_Interpolation = 20;
		R_Interpolation_N = 0;

	}
}

void CMainMenu::S_Credit()
{

	if( look != D3DXVECTOR3(300, 0,-300) )
	{
		R_Interpolation = 20;
		R_Interpolation_N = 0;

		look =  D3DXVECTOR3(0,0,0) * (1.0f - (Interpolation_N / Interpolation) ) +
			D3DXVECTOR3(300, 0,-300) * (Interpolation_N / Interpolation);
		Interpolation_N++;
	}

	else if(  look == D3DXVECTOR3(300,0,-300) )
	{
		if(key.Get_Esc())
		{
			sound->Stop(g_lpDSBG[1]);
			credit = false;
			B_credit = true;
			sound->Play(g_lpDSBG[1], false);
		}
	}
}

void CMainMenu::SB_Credit()
{
	if( look != D3DXVECTOR3(0,0,0) )
	{
		Interpolation = 20;
		Interpolation_N = 0;

		look = D3DXVECTOR3(300,0,-300)  * (1.0f - (R_Interpolation_N / R_Interpolation) ) +
			D3DXVECTOR3(0,0,0) * (R_Interpolation_N / R_Interpolation);
		R_Interpolation_N++;

	}
	else if( look == D3DXVECTOR3(0,0,0) )
	{
		B_credit = false;
		Interpolation = 20;
		Interpolation_N = 0;
		R_Interpolation = 20;
		R_Interpolation_N = 0;
	}
}

void CMainMenu::S_Exit()
{
	if( look != D3DXVECTOR3(0, -300 ,-299) ) 
	{
		look =  D3DXVECTOR3(0,0,0) * (1.0f - (Interpolation_N / Interpolation) ) +
			D3DXVECTOR3(0, -300 ,-299) * (Interpolation_N / Interpolation);
		if( Interpolation_N != 20)
			Interpolation_N += 1;

		StartTime = GetTickCount(); // 처음시간
	}

	dwEventTime = 500; //원하는 시간

	dwCurTime = GetTickCount(); // 현재 시간
	if( StartTime + dwEventTime  <= dwCurTime )
	{
		exit(0);
	}
}

void CMainMenu::Menu_Camera()
{
	if(Select_stage == true){S_Stage();}
	else if(B_Select_stage == true){SB_Stage();}

	if(control == true){S_HowToPlay();}
	else if(B_control == true){SB_HowToPlay();}

	if(se_howtoplay == true){SE_HowToPlay();}
	else if(se_howtoplay_check == true){SEB_HowToPlay();}

	if(credit == true){S_Credit();}
	else if( B_credit == true){SB_Credit();}


	if(Exit == true)
	{
		S_Exit();
	}

	Mcamera->SetViewMatrix(&eye,&look,&UP);					//// 뷰 메트리스 설정

	//Mcamera->RotateWorldX(mouse.Get_mouse_y()*0.1);		//// 마우스 회전  
	//Mcamera->RotateWorldY(mouse.Get_mouse_x()*0.1);		//// 마우스 회전
	//Mcamera->RotateWorldLookAtX(mouse.Get_mouse_y()*0.1);
	//Mcamera->RotateWorldLookAtY(mouse.Get_mouse_y()*0.1);
	//Mcamera->SetEye(&(Mcamera->GetEye()));						//// 눈 
	//Mcamera->SetLookAt(&look);									//// 보는곳 설정
}

bool CMainMenu::Get_gamestart()
{
	return game_start;
}

int CMainMenu::rog()
{
	return select;
}

void CMainMenu::Render()
{
	if(game_start != true)
	{
		for(int i = 0 ; i < 685 ; i++ )
		{
			mesh[i].Render();
		}

		for(int i = 0 ; i < 5 ; i ++)
		{
			SMmesh[i].Render();
		}
		if(How_To_On)
		{
			for(int i = 0 ; i < 8 ; i++)
			{
				key_mash[i].Render();
			}
			if(Render_Key_Down!=-1)
			{
				Key_Explain_Mesh[Render_Key_Down].Render();
			}
			Key_Explain_Mesh[8].Render();
			Key_Explain_Mesh[9].Render();
			Key_Explain_Mesh[10].Render();
			
		}
		for(int i = 0 ; i < 4 ; i ++)
		{
			Selet_Stage[i].Render();
		}

		Credit->Credit_Render();
		if(Plain_On==true)
			for(int i = 0 ; i < 4 ; i++)
			{			
				How[i].Render();
			}
	}
}

int CMainMenu::Get_Stage()
{
	return Stage_Select;
}

void CMainMenu::CleenUp()
{

	if(mesh != NULL)
	{
		delete [] mesh;
		mesh = NULL;
	}
	if(key_mash != NULL)
	{
		delete [] key_mash;
		key_mash =NULL;
	}
	if(mesh != NULL)
	{
		delete Credit;
		Credit =NULL;
	}
	if(Shader != NULL)
	{
		delete Shader;
		Shader =NULL;
	}
	if(Mcamera != NULL)
	{
		delete Mcamera;
		Mcamera =NULL;
	}
	if(SMmesh != NULL)
	{
		delete [] SMmesh;
		SMmesh =NULL;
	}
	if(Key_Explain_Mesh !=NULL)
	{
		delete [] Key_Explain_Mesh;
		Key_Explain_Mesh=NULL;
	}
	if(sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
}