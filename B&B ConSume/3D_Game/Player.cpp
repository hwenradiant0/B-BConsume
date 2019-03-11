#include "Player.h"


CPlayer::CPlayer(void)
{
	m_bInput_SPACE		= false;
	m_bInput_W			= false;
	m_bInput_S			= false;
	m_bInput_D			= false;
	m_bInput_A			= false;

	m_icJump			= 0;
	m_bJump_State		= true;

	Red					= 0;
	Green				= 0;
	Blue				= 0;

	m_Player_Energy = 200;

	Moving_Direction =D3DXVECTOR3(1,0,0);

	Transe_Scale = D3DXVECTOR3(1,1,1);

	CollisionCheck = false;
	count = 0;
	rise = false;

}


CPlayer::~CPlayer(void)
{
	if(m_Coll != NULL)
		delete m_Coll;
}

bool CPlayer::Move()
{

	CPhisical::GetInstance()->PressGravity(m_PhyData);
	CPhisical::GetInstance()->PhysicActing(m_PhyData);


	return 0;
}

void CPlayer::PlayerMove(D3DXMATRIXA16 *CamerMatrix)
{
	D3DXVECTOR3 Forward(CamerMatrix->_13,0,CamerMatrix->_33);//���� ��ǥ���� z�����
	if(D3DXVec3Dot(&Forward,&Forward)>1.f)//���� �ƴ�
		D3DXVec3Normalize(&Forward,&Forward);

	D3DXVECTOR3 Sideward(CamerMatrix->_11,0,CamerMatrix->_31); //���� ��ǥ���� x�� ����
	if(D3DXVec3Dot(&Sideward,&Sideward)>1.f)//���� �ƴ�
		D3DXVec3Normalize(&Sideward,&Sideward);

	D3DXVECTOR3 Upward(0,1,0);//ī�޶��� y����� => ���� ��ǥ��� �ٲپ���ҰŰ���
	if(D3DXVec3Dot(&Upward,&Upward)>1.f)//���� �ƴ�
		D3DXVec3Normalize(&Upward,&Upward);

	FLOAT SpeedSpeed = D3DXVec3Dot(&m_PhyData->GetLinerVelocity(),&m_PhyData->GetLinerVelocity());

	if(CollisionCheck  && m_Player_Energy > 0 && SpeedSpeed < 10) //�浹üũ���Ͽ� �÷��̾��� ������ ���θ� �����ϰ� �ӵ��� �����Ѵ�. �������� 0�̻��϶��� �����ϰ��� �����ǰ��� ���Ѵ�.
	{
		//this->cmObject->SetRotation(RotateXSpeed, RotateYSpeed, RotateZSpeed);
		if(GetAsyncKeyState(VK_W)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Forward*Player_Speed);
			//RotateXSpeed = RotateXSpeed + m_PhyData->GetLinerVelocity().x/10;
		}
		if(GetAsyncKeyState(VK_S)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Forward*-Player_Speed);
			//RotateXSpeed = RotateXSpeed - m_PhyData->GetLinerVelocity().x/10;
		}
		if(GetAsyncKeyState(VK_A)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Sideward*-Player_Speed);
			//RotateZSpeed = RotateZSpeed + 0.1;
		}
		if(GetAsyncKeyState(VK_D)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Sideward*Player_Speed);
			//RotateZSpeed = RotateZSpeed - 0.1;
		}
	}

	else if(m_Player_Energy > 0)
	{
		if(GetAsyncKeyState(VK_W)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Forward*Player_Speed/2);
			//RotateXSpeed = RotateXSpeed + m_PhyData->GetLinerVelocity().x/10;
		}
		if(GetAsyncKeyState(VK_S)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Forward*-Player_Speed/2);
			//RotateXSpeed = RotateXSpeed - m_PhyData->GetLinerVelocity().x/10;
		}
		if(GetAsyncKeyState(VK_A)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Sideward*-Player_Speed/2);
			//RotateZSpeed = RotateZSpeed + 0.1;
		}
		if(GetAsyncKeyState(VK_D)&0x8000)
		{
			m_Player_Energy=m_Player_Energy+Move_Consume_Energy;
			m_PhyData->AddForce( Sideward*Player_Speed/2);
			//RotateZSpeed = RotateZSpeed - 0.1;
		}
	}

////���� �ȸ���
	//if((GetAsyncKeyState(VK_SPACE)&0x8000) && m_bJump_State == true )	//SPACE�� �������� ����		
	//{
	//	m_bInput_SPACE	= true;
	//	m_bJump_State	= false;
	//	m_bScale_Change = true;
	//}

	//if(GetAsyncKeyState(VK_SPACE)&0x80001)	//SPACE�� ���������� ����(������ �ѹ��� �ϱ����ؼ�)
	//{
	//	m_bInput_SPACE	= true;
	//}

	//else if(!(GetAsyncKeyState(VK_SPACE)&0x8000))	//SPACE���� ������ ����
	//{
	//	m_bInput_SPACE	= false;
	//	m_bJump_State = true;
	//}

	//��������
	if((GetAsyncKeyState(VK_SPACE)&0x8000) && m_bJump_State == true && CollisionCheck)	//SPACE�� �������� ����		
	{
		m_bInput_SPACE	= true;
		m_bJump_State	= false;
		m_bScale_Change = true;
	}
	if(GetAsyncKeyState(VK_SPACE)&0x80001)	//SPACE�� ���������� ����(������ �ѹ��� �ϱ����ؼ�)
	{
		m_bInput_SPACE	= false;
	}
	else if(!(GetAsyncKeyState(VK_SPACE)&0x8000))	//SPACE���� ������ ����
	{
		m_bInput_SPACE	= false;
		m_bJump_State = true;
	}

	if(Transe_Scale.y < 0.5f && m_Player_Energy > 0)
	{
		m_PhyData->AddForce(Upward*Player_Speed*500);
		if(GetAsyncKeyState(VK_SPACE)&0x80001)	//SPACE�� ���������� ����(������ �ѹ��� �ϱ����ؼ�)
		{
			m_bInput_SPACE	= false;
		}
		else if(!(GetAsyncKeyState(VK_SPACE)&0x8000))	//SPACE���� ������ ����
		{
			m_bInput_SPACE	= false;
			m_bJump_State = true;
		}
	}



	float Sp = (D3DXVec3Dot(&Moving_Direction,&Moving_Direction)/1600)*36;

	D3DXVECTOR3 tester = m_PhyData->GetLinerVelocity();
	tester.y =0;
	if(abs(D3DXVec3Dot(&tester,&tester))>=0.001f)
	{
		Moving_Direction = tester;

	}

	Moving_DirAngle-= Sp;
	if(Moving_DirAngle>D3DX_PI*2 || Moving_DirAngle<-D3DX_PI*2)
		Moving_DirAngle=0;


	}
VOID CPlayer::Direction_RotatigSetupMatrices(D3DXMATRIXA16 *CamerMatrix)
{

	D3DXMATRIXA16 matWorld;

	D3DXMATRIXA16 matSize;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matRot_x;
	D3DXMATRIXA16 matRot_y;
	D3DXMATRIXA16 matRot_z;

	D3DXMATRIXA16 matTrans;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixIdentity(&matSize);

	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matRot_x);
	D3DXMatrixIdentity(&matRot_y);
	D3DXMatrixIdentity(&matRot_z);

	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matSize,1.0f,1.0f,1.0f);


	if(m_bScale_Change == true && m_Player_Energy > 0)
	{
		if(count == 1)
		{
			Transe_Scale.x += 0.15f;
			Transe_Scale.y -= 0.15f;
			Transe_Scale.z += 0.15f;
			if(Transe_Scale.y < 1.0f)
			{
				m_bScale_Change = false;
				count = 0;
				Transe_Scale = D3DXVECTOR3(1,1,1);
			}
		}
		else if(rise == false)
		{
			Transe_Scale.x += 0.15f;
			Transe_Scale.y -= 0.15f;
			Transe_Scale.z += 0.15f;
			if(Transe_Scale.y < 0.5f)
				rise = true;
		}
		else
		{
			Transe_Scale.x -= 0.15f;
			Transe_Scale.y += 0.15f;
			Transe_Scale.z -= 0.15f;
			if(Transe_Scale.y > 1.5f)
			{
				rise = false;
				count++;
			}
		}

		D3DXMatrixScaling( &matSize, Transe_Scale.x, Transe_Scale.y, Transe_Scale.z );
	}

	else if(m_Player_Energy <= 0)
	{
		Transe_Scale.x -= 0.02f;
		Transe_Scale.y -= 0.02f;
		Transe_Scale.z -= 0.02f;

		if(Transe_Scale.y < 0.1f)
		{
			Transe_Scale = D3DXVECTOR3(0.1f,0.1f,0.1f);
		}

		D3DXMatrixScaling( &matSize, Transe_Scale.x, Transe_Scale.y, Transe_Scale.z );
	}

	//D3DXMatrixRotationYawPitchRoll( CamerMatrix, m_vRotAngle.x, m_vRotAngle.y, m_vRotAngle.z );
	D3DXVECTOR3 RotateAxis;
	D3DXVec3Cross(&RotateAxis,&Moving_Direction,&D3DXVECTOR3(0,1,0));
	D3DXVec3Normalize(&RotateAxis,&RotateAxis);
	//if(TestAxis.x!=0 || TestAxis.z!=0 )
	D3DXMatrixRotationAxis(&matRot_x,&RotateAxis ,Moving_DirAngle);


	D3DXMatrixTranslation(&matTrans,m_vPos.x,m_vPos.y,m_vPos.z);
	matRot = matRot_x;
	matWorld=matRot*matSize*matTrans;

	Get_Device->SetTransform( D3DTS_WORLD, &matWorld );
}
bool CPlayer::PlayerRender(D3DXMATRIXA16 *CamerMatrix)
{
	Direction_RotatigSetupMatrices(CamerMatrix);
	cmObject->Render(m_Player_Energy);
	return 0;
}

void CPlayer::ColorUpdate()
{

	if(m_Player_Energy<=0)
	{
		m_Player_Energy = 0;	}
	else if(m_Player_Energy>0 && m_Player_Energy<=200) //������(0,0,0) ~ ������(255,0,0) == ������(0,0,0) ~ ������(1,0,0)
	{
		ColorRed(0,1,m_Player_Energy,200);
		ColorGreen(0,0,m_Player_Energy,200);
		ColorBlue(0,0,m_Player_Energy,200);
	}
	else if(m_Player_Energy>200 && m_Player_Energy<=400) //������(255,0,0) ~ ��Ȳ��(255,130,0) == ������(1,0,0) ~ ��Ȳ��(1,0.5,0)
	{
		ColorRed(1,1,m_Player_Energy-200,200);
		ColorGreen(0,0.5,m_Player_Energy-200,200);
		ColorBlue(0,0,m_Player_Energy-200,200);
	}
	else if(m_Player_Energy>400 && m_Player_Energy<=600) //��Ȳ��(255,127.5,0) ~ �����(255,255,0) == ��Ȳ��(1,0.5,0) ~ �����(1,1,0)
	{
		ColorRed(1,1,m_Player_Energy-400,200);
		ColorGreen(0.5,1,m_Player_Energy-400,200);
		ColorBlue(0,0,m_Player_Energy-400,200);
	}
	else if(m_Player_Energy>600 && m_Player_Energy<=800) //�����(255,255,0) ~ �Ͼ��(255,255,255) == �����(1,1,0) ~ �Ͼ��(1,1,1)
	{
		ColorRed(1,0.77,m_Player_Energy-600,200);
		ColorGreen(1,0.77,m_Player_Energy-600,200);
		ColorBlue(0,0.77,m_Player_Energy-600,200);
	}
	else if(m_Player_Energy>800 && m_Player_Energy<=1000) //�Ͼ��(255,255,255) ~ �Ķ���(0,0,255) == �Ͼ��(1,1,1) ~ �Ķ���(0,0,1)
	{
		ColorRed(0.77,0,m_Player_Energy-800,200);
		ColorGreen(0.77,0,m_Player_Energy-800,200);
		ColorBlue(0.77,1,m_Player_Energy-800,200);
	}
	else if(m_Player_Energy>1000)
	{
		m_Player_Energy = 1000;
	}
}

void CPlayer::Set_Player_Energy(float now_Player_Energy)
{
	m_Player_Energy = now_Player_Energy;
}

float CPlayer::Get_Player_Energy()
{
	return m_Player_Energy;
}


float CPlayer::GetTS()
{
	return Transe_Scale.y;
}