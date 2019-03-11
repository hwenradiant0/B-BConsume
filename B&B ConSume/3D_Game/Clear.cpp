#include "Clear.h"
CClear_Mesh::CClear_Mesh()
{

}
CClear_Mesh::~CClear_Mesh()
{

}
bool CClear_Mesh::Move()
{
	return 0;

}
void CClear_Mesh::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//파일 로딩만 되면 번호만 입력하도록 변경
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
	
	Radian_Y=0.0f;

}




////////////////////////////////////////////////////////////////
//클리어 시스템
///////////////////////////////////////////////////////////////////

CClear_System::CClear_System(void)
{
}


CClear_System::~CClear_System(void)
{
	Clean_Up();
}
void CClear_System::Clean_Up()
{
	if(Clear_Title !=NULL)
	{
		delete Clear_Title;
		Clear_Title=NULL;
	}

	if(Clear_Next !=NULL)
	{
		delete Clear_Next;
		Clear_Next=NULL;
	}
	if(m_Shader !=NULL)
	{
		delete m_Shader;
		m_Shader=NULL;
	}
	if(sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
}


void CClear_System::Clear_Init(D3DXVECTOR3 TitlePos,D3DXVECTOR3 NextPos)
{
	sound=new Sound();
	sound->LoadWave("Sound/SE/001-Victory01.wav", &g_lpDSBG[0]);//메인화면 BGM
	sound->Play(g_lpDSBG[0], false);

	Clear_Title = new CClear_Mesh();
	Clear_Next = new CClear_Mesh();

	m_Shader = new CShader();
	m_Shader->LoadAssets("Data/BallBoxConSume.fx","Texture/NONE.jpg","Texture/NONE.jpg");

	Clear_Title->Init("xFile/Clear.x",TitlePos,14.0f,Coll_TYPE_MMB,m_Shader);
	Clear_Title->m_PhyData=NULL;
	Clear_Title->SetMeshColor(0,1.0f,0.f,0.f,1.0f);

	Clear_Next->Init("xFile/BackToTitle.x",NextPos,12.0f,Coll_TYPE_MMB,m_Shader);
	Clear_Next->m_PhyData=NULL;
	Clear_Next->SetMeshColor(0,0.f,0.f,1.5f,1.0f);
	

	 m_Max_Frame=80;
	 Now_Frame=0;
	 m_tick_Clear_Run=0;
	 Next_Y_Angle=0;
	 Default_X_Angle = -D3DX_PI/2.0f;
}
float	CClear_System::LinerInterpo(float v0,float v1,float FrameperMax)
{
	return (v0*(1-FrameperMax) + v1*FrameperMax);
}
	
bool CClear_System::ClearTitle_Animation()
{
	if(Now_Frame<=m_Max_Frame)
	{
		D3DXVECTOR3 Angle;
		Angle.x  = Default_X_Angle;
		Angle.y=0;
		Angle.z = LinerInterpo(0.0f,2*D3DX_PI,float((float)Now_Frame/(float)m_Max_Frame));

		Clear_Title->SetRotation(Angle.x,Angle.y,Angle.z);
		Now_Frame++;
		return true;
	}
	return false;
}

void CClear_System::ClearNext_Animation()
{
	Next_Y_Angle += D3DX_PI/60;
	if(Next_Y_Angle>=2*D3DX_PI)
		Next_Y_Angle=0;

	Clear_Next->SetRotation(Default_X_Angle,Next_Y_Angle,0);
	
}
bool CClear_System::Clear_Move(bool Enter,float tick)
{
	
	m_tick_Clear_Run+=tick;
	if(m_tick_Clear_Run>Tick_Gb_run_minmum)
	{
		m_tick_Clear_Run=0;
		
		
		if(ClearTitle_Animation()==false)//애니메이션 끝나면 키입력 받기 시작
		{
			ClearNext_Animation();
			if(Enter)
				return false;





		}
		
	}
	return true;

}//펄스면 클리어 화면 나가기(아마 타이틀로 갈거 같음)
void CClear_System::Render()
{
		
	Clear_Title->Render();
	Clear_Next->Render();
}


void CClear_System::Volume(int num)
{
	sound->SetVolume(g_lpDSBG[0], num);
}