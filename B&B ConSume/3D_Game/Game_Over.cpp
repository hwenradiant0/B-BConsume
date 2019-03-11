#include "Game_Over.h"


#include "Game_Over.h"
COver_Mesh::COver_Mesh()
{

}
COver_Mesh::~COver_Mesh()
{

}
bool COver_Mesh::Move()
{
	return 0;

}
void COver_Mesh::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//파일 로딩만 되면 번호만 입력하도록 변경
{
	cmObject=new CMesh();
	cmObject->Init(pFile, Shader);
	cmObject->InitGeometry_Total();
	cmObject->SetPos(loadPos);
	m_vPos=loadPos;
	cmObject->SetSize(Size);
	//cmObject->SetupMatrices();
	m_PhyData = new CPhysicData;
	m_bSelected =false;
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
	
	Radian_Y=0.0f;

}
void COver_Mesh::Set_Selected(bool Choice)
{
	m_bSelected = Choice;
}
/////////////////////////////
//
//
//////////////////////////////////////////




////////////////////////////////////////////////////////////////
//게임 오버
///////////////////////////////////////////////////////////////////

CGame_Over::CGame_Over(void)
{
}


CGame_Over::~CGame_Over(void)
{
	Clean_Up();
}
void CGame_Over::Clean_Up()
{
	if(Game_Over_Title !=NULL)
	{
		delete Game_Over_Title;
		Game_Over_Title=NULL;
	}

	if(Game_Over_Replay !=NULL)
	{
		delete Game_Over_Replay;
		Game_Over_Replay=NULL;
	}

	if(Game_Over_Replay !=NULL)
	{
		delete Game_Over_Replay;
		Game_Over_Replay=NULL;
	}

	if(m_Shader !=NULL)
	{
		delete m_Shader;
		m_Shader=NULL;
	}
	
}

void CGame_Over::Game_Over_Init(D3DXVECTOR3 TitlePos,D3DXVECTOR3 RePlayPos,D3DXVECTOR3 BTTPos)
{
	Game_Over_Title = new COver_Mesh();
	Game_Over_Replay = new COver_Mesh();
	Game_Over_BTT= new COver_Mesh();
	m_Shader = new CShader();
	m_Shader->LoadAssets("Data/BallBoxConSume.fx","Texture/NONE.jpg","Texture/NONE.jpg");

	Game_Over_Title->Init("xFile/Game_Over.x",TitlePos,14.0f,Coll_TYPE_MMB,m_Shader);
	Game_Over_Title->m_PhyData=NULL;
	Game_Over_Title->SetMeshColor(0,1.0f,0.f,0.f,1.0f);

	Game_Over_Replay->Init("xFile/Play_Again.x",RePlayPos,6.0f,Coll_TYPE_MMB,m_Shader);
	Game_Over_Replay->m_PhyData=NULL;
	Game_Over_Replay->SetMeshColor(0,0.f,0.f,1.5f,1.0f);


	Game_Over_BTT->Init("xFile/BackToTitle.x",BTTPos,8.0f,Coll_TYPE_MMB,m_Shader);
	Game_Over_BTT->m_PhyData=NULL;
	Game_Over_BTT->SetMeshColor(0,0.f,0.f,1.5f,1.0f);
	



	m_SelectColor_R=1.0f;
	m_SelectColor_G=0;
	m_SelectColor_B=0;

	 m_Max_Frame=80;
	 Now_Frame=0;


	 m_Left_Rotate_Frame =0;
	 m_Right_Rotate_Frame =0;
	 m_Right_Rotate_Frame =0;
	 m_Normal_Rotate_Frame=0;

	 m_Rotate_Frame=0;

	 m_tick_GO_Run=0;

	 Replay_Y_Angle=0;
	 BTT_Y_Angle=0;

	 Default_X_Angle = -D3DX_PI/2.0f;
	 cCurserCount=0;
}
float	CGame_Over::LinerInterpo(float v0,float v1,float FrameperMax)
{
	return (v0*(1-FrameperMax) + v1*FrameperMax);
}

bool CGame_Over::Game_OverTitle_Animation()
{
	if(Now_Frame<=m_Max_Frame)
	{
		D3DXVECTOR3 Angle;
		Angle.x  = Default_X_Angle;
		Angle.y=0;
		Angle.z = LinerInterpo(0.0f,6*D3DX_PI,float((float)Now_Frame/(float)m_Max_Frame));

		Game_Over_Title->SetRotation(Angle.x,Angle.y,Angle.z);

		D3DXVECTOR3 Scale;
		Scale.x  = LinerInterpo(1.f,14.f,float((float)Now_Frame/(float)m_Max_Frame));
		Scale.y=  Scale.x;
		Scale.z = Scale.x;
		Game_Over_Title->SetScale(Scale);
		
		Now_Frame++;
		return true;
	}
	return false;
}

void CGame_Over::Game_OverReplay_Animation()
{
	D3DXVECTOR3 Rotate;
	if(	Game_Over_Replay->Get_Selected())
	{
		
		if(m_Rotate_Frame<=30)		
			Rotate.z =LinerInterpo(0.f,D3DX_PI/(6.f),float((float)m_Rotate_Frame/(float)30.f));		
		else if(m_Rotate_Frame<=50)		
			Rotate.z=	LinerInterpo(D3DX_PI/(6.f),0.f,float((float)(m_Rotate_Frame-30.f)/(float)20.f));		
		 else if(m_Rotate_Frame<=80)		
			Rotate.z = 	LinerInterpo(0,-(D3DX_PI/(6.f)),float((float)(m_Rotate_Frame-50.f)/(float)30.f));		
		else if(m_Rotate_Frame<=100)		
			Rotate.z =	LinerInterpo(-(D3DX_PI/(6.f)),0,float((float)(m_Rotate_Frame-80.f)/(float)20.f));		

		m_Rotate_Frame++;

		if(m_Rotate_Frame>100)		
			m_Rotate_Frame=0;

		Rotate.x= -D3DX_PI/2;
		Rotate.y= 0;	
		
		Game_Over_Replay->SetMeshColor(0,m_SelectColor_R,m_SelectColor_G,m_SelectColor_B,0);
	}
	else
	{
		Rotate.x= -D3DX_PI/2;
		Rotate.y= 0;
		Rotate.z= 0;
		Game_Over_Replay->SetMeshColor(0,1.f,1.f,1.f,0);
	}

	Game_Over_Replay->SetRotation(Rotate.x,Rotate.y,Rotate.z);
}
void CGame_Over::Game_OverBTT_Animation()
{
	D3DXVECTOR3 Rotate;
	if(	Game_Over_BTT->Get_Selected())
	{
		
		if(m_Rotate_Frame<=30)		
			Rotate.z =LinerInterpo(0.f,D3DX_PI/(6.f),float((float)m_Rotate_Frame/(float)30.f));		
		else if(m_Rotate_Frame<=50)		
			Rotate.z=	LinerInterpo(D3DX_PI/(6.f),0.f,float((float)(m_Rotate_Frame-30.f)/(float)20.f));		
		 else if(m_Rotate_Frame<=80)		
			Rotate.z = 	LinerInterpo(0,-(D3DX_PI/(6.f)),float((float)(m_Rotate_Frame-50.f)/(float)30.f));		
		else if(m_Rotate_Frame<=100)		
			Rotate.z =	LinerInterpo(-(D3DX_PI/(6.f)),0,float((float)(m_Rotate_Frame-80.f)/(float)20.f));		

		m_Rotate_Frame++;

		if(m_Rotate_Frame>100)		
			m_Rotate_Frame=0;

		Rotate.x= -D3DX_PI/2;
		Rotate.y= 0;	
		
		Game_Over_BTT->SetMeshColor(0,m_SelectColor_R,m_SelectColor_G,m_SelectColor_B,0);
	}
	else
	{
		Rotate.x= -D3DX_PI/2;
		Rotate.y= 0;
		Rotate.z= 0;
		Game_Over_BTT->SetMeshColor(0,1.f,1.f,1.f,0);
	}

	Game_Over_BTT->SetRotation(Rotate.x,Rotate.y,Rotate.z);

	
}
int CGame_Over::Game_Over_Move(bool Get_UP,bool Get_DOWN,bool Get_ENTER,float tick)
{
	m_tick_GO_Run +=tick;
	if(m_tick_GO_Run>Tick_Gb_run_minmum)
	{
		m_tick_GO_Run=0;
		if(!Game_OverTitle_Animation())
		{
			if(Get_UP)	
			{
				cCurserCount=(cCurserCount+1>=2)? 0 :cCurserCount+1;
				m_Rotate_Frame=0;
			}
			if(Get_DOWN)	
			{
				cCurserCount=(cCurserCount-1<0)? 1 :cCurserCount-1;
				m_Rotate_Frame=0;
			}

			//Game_Over_Title->Set_Selected(false);	
			Game_Over_Replay->Set_Selected(false);
			Game_Over_BTT->Set_Selected(false);	

			if(cCurserCount ==0)
				Game_Over_Replay->Set_Selected(true);
			else if(cCurserCount ==1)
				Game_Over_BTT->Set_Selected(true);

			//Game_OverTitle_Animation();
			

			/*Game_Over_Title->Move();
			Game_Over_Replay->Move();
			Game_Over_BTT->Move();*/

			if(Get_ENTER)
				return cCurserCount;

		}
		Game_OverReplay_Animation();
			Game_OverBTT_Animation();
	}
	return -1;	
}
void CGame_Over::Render()
{
		
	Game_Over_Title->Render();
	Game_Over_Replay->Render();
	Game_Over_BTT->Render();
}