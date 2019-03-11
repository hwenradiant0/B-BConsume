#include "Hp_Bar.h"
CHPB_Mesh::CHPB_Mesh()
{

}
CHPB_Mesh::~CHPB_Mesh()
{

}
bool CHPB_Mesh::Move()
{
	return 0;

}
void CHPB_Mesh::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//파일 로딩만 되면 번호만 입력하도록 변경
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

CHp_Bar_System::CHp_Bar_System(void)
{
}


CHp_Bar_System::~CHp_Bar_System(void)
{
	Clean_Up();
}
void CHp_Bar_System::Clean_Up()
{
	if(m_Gage !=NULL)
	{
		delete m_Gage;
		m_Gage=NULL;
	}

	if(m_Bar[0] !=NULL)
	{
		for(int i=0;i<8;i++)
		{
		delete m_Bar[i];		
		m_Bar[i] =NULL;
		}
	}
	if(m_Gage_Shader !=NULL)
	{
		delete m_Gage_Shader;
		m_Gage_Shader=NULL;
	}

	if(m_Bar_Shader !=NULL)
	{
		delete m_Bar_Shader;
		m_Bar_Shader=NULL;
	}

	

}


void CHp_Bar_System::HP_Sys_Init(D3DXVECTOR3 SetPos,float max_Energy)
{
	float R,G,B;
	D3DXVECTOR3 Bar_Pos;
	m_Gage = new CHPB_Mesh();
	

	
	m_Gage_Shader= new CShader();
	m_Gage_Shader->LoadAssets("Data/TextureMapping.fx","Texture/Shader/New/Water_DM.jpg","Texture/Shader/New/Water_DM.jpg");
	m_Bar_Shader= new CShader();
	m_Bar_Shader->LoadAssets("Data/TextureMapping(Color).fx","Texture/DaBoTop.jpg","Texture/Shader/Water_SM.jpg");
	Default_Scale=10.f;

	m_Gage->Init("xFile/Hp_GageNemo.x",SetPos,Default_Scale,Coll_TYPE_MMB,m_Gage_Shader);
	m_Gage->m_PhyData=NULL;
	m_Gage->SetMeshColor(0,0.6f,0.6f,0.6f,1.0f);
	
	for(int i=0;i<8;i++)
	{
		Bar_Pos=SetPos;
		Bar_Pos.y= SetPos.y + Default_Scale*(((i-4)*20) + 10);
		
		m_Bar[i] = new CHPB_Mesh();
		m_Bar[i]->Init("xFile/Small_Nemo_Bar.x",Bar_Pos,Default_Scale,Coll_TYPE_MMB,m_Bar_Shader);
		m_Bar[i]->m_PhyData=NULL;
		Presen_Energy =125*(i+1);
		Planet_tempeture_Algorithm(&R,&G,&B);
		m_Bar[i]->SetMeshColor(0,R,G,B,1.0f);
		Bar_Default_Pos[i] = Bar_Pos;
	}

	Default_Pos = SetPos;

	 m_Max_Frame=80;
	 Now_Frame=0;
	// m_tick_Clear_Run=0;
	 Next_Y_Angle=0;
	 Default_X_Angle = -D3DX_PI/2.0f;

	 Presen_Energy=0;
	 Max_Energy= max_Energy;
}
float	CHp_Bar_System::LinerInterpo(float v0,float v1,float FrameperMax)
{
	return (v0*(1-FrameperMax) + v1*FrameperMax);
	
}
	
bool CHp_Bar_System::HP_SysGage_Animation()
{
	return 0;
}
void CHp_Bar_System::Planet_tempeture_Algorithm(float *r,float *g , float *b)
{
	float R=0,G=0,B=0;
	float Color_Rate;
	if(Presen_Energy<=0)
	{
		Presen_Energy = 0;
	}
	else if(Presen_Energy>0 && Presen_Energy<=200) //검은색(0,0,0) ~ 빨강색(255,0,0) == 검은색(0,0,0) ~ 빨강색(1,0,0)
	{
		Color_Rate = Presen_Energy;
		R = LinerInterpo(0,1,Color_Rate/200);
		G = LinerInterpo(0,0,Color_Rate/200);
		B = LinerInterpo(0,0,Color_Rate/200);
	}
	else if(Presen_Energy>200 && Presen_Energy<=400) //빨강색(255,0,0) ~ 주황색(255,130,0) == 빨강색(1,0,0) ~ 주황색(1,0.5,0)
	{
		Color_Rate = Presen_Energy-200;
		R = LinerInterpo(1,1,Color_Rate/200);
		G = LinerInterpo(0,0.5,Color_Rate/200);
		B = LinerInterpo(0,0,Color_Rate/200);
	}
	else if(Presen_Energy>400 && Presen_Energy<=600) //주황색(255,127.5,0) ~ 노란색(255,255,0) == 주황색(1,0.5,0) ~ 노란색(1,1,0)
	{
		Color_Rate = Presen_Energy-400;
		R = LinerInterpo(1,1,Color_Rate/200);
		G = LinerInterpo(0.5,1,Color_Rate/200);
		B = LinerInterpo(0,0,Color_Rate/200);
	}
	else if(Presen_Energy>600 && Presen_Energy<=800) //노란색(255,255,0) ~ 하얀색(255,255,255) == 노란색(1,1,0) ~ 하얀색(1,1,1)
	{
		Color_Rate = Presen_Energy - 600;
		R = LinerInterpo(1,0.77,Color_Rate/200);
		G = LinerInterpo(1,0.77,Color_Rate/200);
		B = LinerInterpo(0,0.77,Color_Rate/200);
	}
	else if(Presen_Energy>800 && Presen_Energy<=1000) //하얀색(255,255,255) ~ 파랑색(0,0,255) == 하얀색(1,1,1) ~ 파랑색(0,0,1)
	{
		Color_Rate = Presen_Energy -800;
		R = LinerInterpo(0.77,0,Color_Rate/200);
		G = LinerInterpo(0.77,0,Color_Rate/200);
		B = LinerInterpo(0.77,1,Color_Rate/200);
	}
	else if(Presen_Energy>1000)
	{
		Presen_Energy = 1000;
	}
	*r = R;
	*g = G;
	*b = B;
}

void CHp_Bar_System::HP_SysBar_Animation()
{
	//float Now_Hp = Default_Scale*(float)((float)Presen_Energy/ (float)Max_Energy);

	//m_Bar->SetScale(D3DXVECTOR3(Now_Hp,Default_Scale,Default_Scale));

	//float Now_Pos = Default_Pos.x-50*(Default_Scale-1) +(LinerInterpo(-50,0,Now_Hp));
	//m_Bar->SetPos(D3DXVECTOR3(Now_Pos,Default_Pos.y,Default_Pos.z));
	float Now_Hp;
	float Now_Pos;
	Next_Y_Angle+=D3DX_PI/60;
	for(int i=0;i<8;i++)
	{
		if(Presen_Energy>=(i+1)*125)
		{
			Now_Hp=1;
		}
		else if(Presen_Energy<=(i)*125)
		{
			Now_Hp=0;
		}
		else
		{
			Now_Hp = (float)(Presen_Energy-(i*125)) / (float)125;			
		}
		m_Bar[i]->SetScale(D3DXVECTOR3(Default_Scale,Default_Scale*Now_Hp,Default_Scale));

		Now_Pos = Bar_Default_Pos[i].y +Default_Scale*(LinerInterpo(-10,0,Now_Hp));//-10*(Default_Scale-1)
		m_Bar[i]->SetPos(D3DXVECTOR3(Bar_Default_Pos[i].x,Now_Pos,Bar_Default_Pos[i].z));
		


		
		m_Bar[i]->SetRotation(0.f,Next_Y_Angle,0.f);
	}


}
bool CHp_Bar_System::HP_Sys_Move(float Energy,float tick)
{
	Presen_Energy  =	Energy;
	HP_SysBar_Animation();
	HP_SysGage_Animation();

	return true;

}//펄스면 클리어 화면 나가기(아마 타이틀로 갈거 같음)



void	CHp_Bar_System::SettingCameraEyePos(D3DXVECTOR3 EyePos,D3DXVECTOR3 PlayerPos)
{
	m_Gage_Shader->SetCameraEyePos(EyePos,PlayerPos);
	m_Bar_Shader->SetCameraEyePos(EyePos,PlayerPos);
}
void CHp_Bar_System::Render()
{
		
	m_Gage->Render();
	for(int i=0;i<8;i++)
	m_Bar[i]->Render();
}