#include "CreditDice_Algorithm.h"
CCredit_Mesh::CCredit_Mesh()
{
}
CCredit_Mesh::~CCredit_Mesh()
{}





void CCredit_Mesh::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)
{
	cmObject=new CMesh();
	cmObject->Init(pFile, Shader);
	cmObject->InitGeometry_Total();
	cmObject->SetPos(loadPos);
	m_vPos=loadPos;
	cmObject->SetSize(Size);
	//cmObject->SetupMatrices();
	m_PhyData = new CPhysicData;

	if(strcmp(pCollType,Coll_TYPE_MMB)==0)
	{
		m_Coll =new CCollision;//상속자로 내려가야할 듯
		m_Coll->CreateMMB(D3DXVECTOR3(-Tile_Size/2,-Tile_Size/2,-Tile_Size/2),D3DXVECTOR3(Tile_Size/2,Tile_Size/2,Tile_Size/2));
	}
	else if(strcmp(pCollType,Coll_TYPE_Sphere)==0)
	{
		m_Coll			=	new CCollision;//
		m_Coll			->	CreateSphere(loadPos,Ball_Radius);

	}

}
bool CCredit_Mesh::Move()
{
	return 0;
}










///////////////////////////////////////////////////////////////////////////////////////////////
//
//            크레딧 알고리즘 
//////////////////////////////////////////////////////////////////////////////////////////////

CCreditDice_Algorithm::CCreditDice_Algorithm(void)
{

}


CCreditDice_Algorithm::~CCreditDice_Algorithm(void)
{

	Clean_Up();

}

void CCreditDice_Algorithm::Clean_Up()
{
	if(m_Diceinfo!=NULL)
	{
		delete [] m_Diceinfo;
		m_Diceinfo=NULL;
	}


	if(m_DicePointer!=NULL)
	{
		delete m_DicePointer;
		m_DicePointer=NULL;
	}
	if(m_Mesh_Dice!=NULL)
	{
		delete m_Mesh_Dice;
		m_Mesh_Dice=NULL;
	}
	if(m_Mesh_Credit[0]!=NULL)
	{
		for(int i =0;i<6;i++)
		{
			delete m_Mesh_Credit[i]; 
			m_Mesh_Credit[i] = NULL; 
		}
	}
	if(m_Shader != NULL)
	{
		delete m_Shader;
		m_Shader = NULL;
	}
	if(sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
	
}
void CCreditDice_Algorithm::Credit_Init(D3DXVECTOR3 CreditPos,D3DXVECTOR3 TextPos ,D3DXVECTOR3 CreditAngle,D3DXVECTOR3 TextAngle)
{
	sound = new Sound();
	sound->LoadWave("Sound/SE/Main/Main_Credit_UpDown_SE.wav", &g_lpDSBG[0]);

	m_DicePointer = new Dicenum;
	m_Diceinfo= new Dicenum[6];

	//알고리즘 수작업;;
	m_Diceinfo[0].Up = &m_Diceinfo[1];
	m_Diceinfo[0].Down = &m_Diceinfo[5];
	

	m_Diceinfo[1].Up = &m_Diceinfo[2];
	m_Diceinfo[1].Down = &m_Diceinfo[0];
	

	m_Diceinfo[2].Up = &m_Diceinfo[3];
	m_Diceinfo[2].Down = &m_Diceinfo[1];

	m_Diceinfo[3].Up = &m_Diceinfo[4];
	m_Diceinfo[3].Down = &m_Diceinfo[2];
	

	m_Diceinfo[4].Up = &m_Diceinfo[5];
	m_Diceinfo[4].Down = &m_Diceinfo[3];
	

	m_Diceinfo[5].Up = &m_Diceinfo[0];
	m_Diceinfo[5].Down = &m_Diceinfo[4];
	
	
	m_DicePointer			= &m_Diceinfo[0];
	m_bMesh_Still_Moving	=false;
	m_NextAngle				=D3DXVECTOR3(-2*D3DX_PI,0,0);//보간 최종지점
	m_DiceAngle				=D3DXVECTOR3(0,0,0);
	m_frame					=0;
	m_tick_Dice=0;


	m_Shader =new CShader();
	m_Shader->LoadAssets("Data/BallBoxConSume(Diffuse,Specular).fx","Texture/NONE.jpg","Texture/NONE.jpg");

	m_Mesh_Dice = new CCredit_Mesh();
	m_Mesh_Dice->Init("xFile/Credit_Cube.x",CreditPos,1.0f,Coll_TYPE_MMB,NULL);
	m_Mesh_Dice->m_PhyData=NULL;

	for(int i =0 ;i<6;i++)//텍스트 정해지면
	{
		m_Mesh_Credit[i] = new CCredit_Mesh();	
		m_Mesh_Credit[i]->m_PhyData=NULL;
		
	}
	m_Mesh_Credit[0]->Init("xFile/Credit_Ser.x",TextPos,1.0f,Coll_TYPE_MMB,m_Shader);
	m_Mesh_Credit[1]->Init("xFile/SpecialThanksTo_10.x",TextPos+D3DXVECTOR3(0,20.f,0),1.0f,Coll_TYPE_MMB,m_Shader);
	m_Mesh_Credit[2]->Init("xFile/Credit_Han.x",TextPos,1.0f,Coll_TYPE_MMB,m_Shader);
	m_Mesh_Credit[3]->Init("xFile/Credit_Kim.x",TextPos,1.0f,Coll_TYPE_MMB,m_Shader);
	m_Mesh_Credit[4]->Init("xFile/Credit_Han2.x",TextPos,1.0f,Coll_TYPE_MMB,m_Shader);
	m_Mesh_Credit[5]->Init("xFile/Credit_Song.x",TextPos,1.0f,Coll_TYPE_MMB,m_Shader);

	m_Mesh_Credit[0]->SetMeshColor(0,0.05f,0.05f,0.05f,1.f);
	m_Mesh_Credit[1]->SetMeshColor(0,0.05f,0.05f,0.05f,1.f);
	m_Mesh_Credit[2]->SetMeshColor(0,0.05f,0.05f,0.05f,1.f);
	m_Mesh_Credit[3]->SetMeshColor(0,0.05f,0.05f,0.05f,1.f);
	m_Mesh_Credit[4]->SetMeshColor(0,0.05f,0.05f,0.05f,1.f);
	m_Mesh_Credit[5]->SetMeshColor(0,0.05f,0.05f,0.05f,1.f);
	Dice_DeviceAngle = CreditAngle;
	Text_DeviceAngle = TextAngle;

	for(int i=0;i<6;i++)	
		m_Diceinfo[i].Num=i+1;
	
	m_Diceinfo[0].Angle = D3DXVECTOR3(-2*D3DX_PI,0,0);
	m_Diceinfo[1].Angle = D3DXVECTOR3(-D3DX_PI/2,0,0);
	m_Diceinfo[2].Angle = D3DXVECTOR3(-D3DX_PI,0,0);
	m_Diceinfo[3].Angle = D3DXVECTOR3(-(3*D3DX_PI)/2,D3DX_PI/2,0);
	m_Diceinfo[4].Angle = D3DXVECTOR3(-(3*D3DX_PI)/2,-D3DX_PI/2,0);
	m_Diceinfo[5].Angle = D3DXVECTOR3(-(3*D3DX_PI)/2,0,0);




}
float CCreditDice_Algorithm::Angle_LinerInterpo(float v0,float v1,float FrameperMax)
{
	return (v0*(1-FrameperMax) + v1*FrameperMax);
}


bool CCreditDice_Algorithm::Credit_Run(bool Up,bool Down,bool Cancle,float tick)//펄스라면 크레딧 화면에서 나올것
{
	//나가기//
	if(Cancle ==true)
		return false;
	m_tick_Dice+=tick;
	//if(m_tick_Dice>=Tick_Gb_run_minmum)
//	{
		m_tick_Dice=0;
		if(m_bMesh_Still_Moving==false)//움직임이 끝났을때 키입력을 받는다.
		{
			if(Up &&!Down)
			{
				sound->Stop(g_lpDSBG[0]);
				m_DicePointer = m_DicePointer->Up;
				sound->Play(g_lpDSBG[0], FALSE);
			}
			else if(!Up &&Down)
			{
				sound->Stop(g_lpDSBG[0]);
				m_DicePointer = m_DicePointer->Down;
				sound->Play(g_lpDSBG[0], FALSE);
			}

			

			if(m_NextAngle != m_DicePointer->Angle)
			{
				m_NextAngle=m_DicePointer->Angle;
				m_frame=0;
		
				m_bMesh_Still_Moving=true;
			}
		}
		else
		{
			m_DiceAngle.x=Angle_LinerInterpo(m_DiceAngle.x,m_NextAngle.x,(float)((float)m_frame/(float)Max_Frame));
			m_DiceAngle.y=Angle_LinerInterpo(m_DiceAngle.y,m_NextAngle.y,(float)((float)m_frame/(float)Max_Frame));
			m_DiceAngle.z=Angle_LinerInterpo(m_DiceAngle.z,m_NextAngle.z,(float)((float)m_frame/(float)Max_Frame));
			m_frame++;

			if(m_frame>=Max_Frame)
				m_bMesh_Still_Moving=false;
		}

		//m_DiceAngle+=Dice_DeviceAngle;		
		for(int i=0;i<6;i++)
			m_Mesh_Credit[i]->SetRotation(Text_DeviceAngle.x,
			Text_DeviceAngle.y,
			Text_DeviceAngle.z);
		
		m_Mesh_Dice->SetRotation(m_DiceAngle.x+Dice_DeviceAngle.x,m_DiceAngle.y+Dice_DeviceAngle.y,m_DiceAngle.z+Dice_DeviceAngle.z);

		m_Mesh_Dice->Move();
		for(int i=0;i<6;i++)
			m_Mesh_Credit[i]->Move();
	//}
	return true;

}
void CCreditDice_Algorithm::Credit_Render()
{
	m_Mesh_Dice->Render();
	
	m_Mesh_Credit[m_DicePointer->Num-1]->Render();
}
void CCreditDice_Algorithm::Set_CEye_LEye(D3DXVECTOR3 CameraEye,D3DXVECTOR3 LightEye)
{
	m_Shader->SetCameraEyePos(CameraEye,LightEye);
}

