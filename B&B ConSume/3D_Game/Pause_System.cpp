#include "Pause_System.h"



CPause_Mesh::CPause_Mesh()
{
}
CPause_Mesh::~CPause_Mesh()
{
}
bool CPause_Mesh::Move()
{
	if(bSelected)
	{
		Radian_Y=	Radian_Y+(D3DX_PI/80.0f);
		SetMeshColor(0,SelectedColor.r,SelectedColor.g,SelectedColor.b,SelectedColor.a);		
		SetRotation(-D3DX_PI/2,Radian_Y,0.0f);
	}
	else
	{
		Radian_Y=0;
		SetMeshColor(0,DefaultColor.r,DefaultColor.g,DefaultColor.b,DefaultColor.a);
		SetRotation(-D3DX_PI/2.0f,Radian_Y,0.0f);
	}

	return 0;
}

void CPause_Mesh::Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader)//파일 로딩만 되면 번호만 입력하도록 변경
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
	bSelected = false;
	Radian_Y=0.0f;

}
void CPause_Mesh::Is_Selected(bool Ans)
{
	bSelected = Ans;
}
void CPause_Mesh::Set_DefaultColor(float R,float G,float B,float A )
{
	DefaultColor.r = R;
	DefaultColor.b = B;
	DefaultColor.g = G;
	DefaultColor.a = A;
}

void CPause_Mesh::Set_SelectedColor(float R,float G,float B,float A )
{
	SelectedColor.r = R;
	SelectedColor.b = B;
	SelectedColor.g = G;
	SelectedColor.a = A;
}



//////////////////////////////////////////////////////////////////////////////
///일시정지 시스템/////////////////////////
//////////////////////////////////////////////////////////////////////////////
CPause_System::CPause_System(void)
{
}


CPause_System::~CPause_System(void)
{
	 if(PauMesh_Continue !=NULL)
	 {
		 delete PauMesh_Continue;
		 PauMesh_Continue = NULL;
	 }
	 if(PauMesh_BtoT !=NULL)
	 {
		 delete PauMesh_BtoT;
		 PauMesh_BtoT = NULL;
	 }
	 if(PauMesh_Pause !=NULL)
	 {
		 delete PauMesh_Pause;
		 PauMesh_Pause = NULL;
	 }
	 if(m_Shader !=NULL)
	 {	 
		 delete m_Shader;
		 m_Shader = NULL;
	 }

}


void CPause_System::Pause_init()
{
	cCurserCount=0;//현재 커서의 위치

	m_Shader = new CShader();
	m_Shader->LoadAssets("Data/BallBoxConSume.fx","Texture/NONE.jpg","Texture/NONE.jpg");
	float Scale = (float)(Window_Width*Window_Height)/640000;

	PauMesh_Continue = new CPause_Mesh();
	PauMesh_Continue->Init("xFile/Continue.x",D3DXVECTOR3(Window_Width*0.7f,Window_Height*0.2f,-0.f),Scale*0.7f,Coll_TYPE_MMB,m_Shader);
	PauMesh_Continue->m_PhyData=NULL;
	PauMesh_Continue->SetMeshColor(0,0.5f,0.5,0.5f,1.0f);
	PauMesh_Continue->Set_DefaultColor(0.5f,0.5,0.5f,1.0f);
	PauMesh_Continue->Set_SelectedColor(1.f,0.0,0.0f,1.0f);

	PauMesh_BtoT = new CPause_Mesh();
	PauMesh_BtoT->Init("xFile/BackToTitle.x",D3DXVECTOR3(Window_Width*0.7f,Window_Height*0.1f,-0.f),Scale*0.7f,Coll_TYPE_MMB,m_Shader);
	PauMesh_BtoT->m_PhyData=NULL;
	PauMesh_BtoT->SetMeshColor(0,0.5f,0.5,0.5f,1.0f);
	PauMesh_BtoT->Set_DefaultColor(0.5f,0.5,0.5f,1.0f);
	PauMesh_BtoT->Set_SelectedColor(1.f,0.0,0.0f,1.0f);

	PauMesh_Pause = new CPause_Mesh();
	PauMesh_Pause->Init("xFile/Pause.x",D3DXVECTOR3(Window_Width*0.5f,Window_Height*0.8f,-0.f),Scale*1.2f,Coll_TYPE_MMB,m_Shader);
	PauMesh_Pause->m_PhyData=NULL;
	PauMesh_Pause->SetMeshColor(0,0.78f,0.37f,0.5f,1.0f);	
	PauMesh_Pause->Set_DefaultColor(1.0f,0.5f,0.0f,1.0f);
	PauMesh_Pause->Set_SelectedColor(0.78f,0.37f,0.5f,1.0f);

	//delete Shader;
	PauMesh_BtoT->Is_Selected(false);
	PauMesh_Pause->Is_Selected(false);
	PauMesh_Continue->Is_Selected(false);

	







}
int CPause_System::Pause_Move(bool Get_UP,bool Get_DOWN,bool Get_ENTER)
{
	if(Get_UP)	
		cCurserCount=(cCurserCount+1>=2)? 0 :cCurserCount+1;
	if(Get_DOWN)	
		cCurserCount=(cCurserCount-1<0)? 1 :cCurserCount-1;

	PauMesh_BtoT->Is_Selected(false);	
	PauMesh_Continue->Is_Selected(false);

	if(cCurserCount ==0)
		PauMesh_Continue->Is_Selected(true);
	else
		PauMesh_BtoT->Is_Selected(true);



	if(Get_ENTER)
		return cCurserCount;
	PauMesh_BtoT->Move();
	PauMesh_Continue->Move();
	PauMesh_Pause->Move();

	return -1;	
}
void CPause_System::PickUp_Scene()
{
}
void CPause_System::Clear_Up()
{
	if(PauMesh_BtoT!=NULL)
		delete PauMesh_BtoT;

	if(PauMesh_Pause!=NULL)
		delete PauMesh_Pause;

	if(PauMesh_Continue!=NULL)
		delete PauMesh_Continue;
}
void CPause_System::Pause_Render()
{

	PauMesh_BtoT->Render();
	PauMesh_Continue->Render();
	PauMesh_Pause->Render();
}