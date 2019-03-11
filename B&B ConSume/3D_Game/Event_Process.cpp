#include "Event_Process.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>

using namespace std;

CEvent_Process::CEvent_Process(void)
{
	m_Stack=5;
	m_Tile_Switch=false;
	sound=new Sound();
	sound->LoadWave("Sound/SE/Tile/Fire_SE.wav", &g_lpDSBG[0]);
}

CEvent_Process::~CEvent_Process(void)
{
	delete sound;
	sound = NULL;
}

void CEvent_Process::Volume(int num)
{
	volume = num;
}

D3DXVECTOR3 CEvent_Process::Get_Pos()
{
	return m_Pos;
}


void CEvent_Process::Set_Pos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

void CEvent_Process::Set_Tile_Switch(bool Tile_Switch)
{
	m_Tile_Switch=Tile_Switch;
}

bool CEvent_Process::Get_Tile_Switch()
{
	return m_Tile_Switch;
}

void CEvent_Process::Event_Cheaking(CTile *Tile, CPlayer *Player)
{
	sound->SetVolume(g_lpDSBG[0], volume);

	switch(Tile->Get_Material())
	{
	case 1:				// ö
		break;
	case 2:				// ��
		//���� ������
		if(Tile->Get_Tile_Energy()>0)
		{
			Player->Set_Player_Energy(Player->Get_Player_Energy()+Consume_Energy);
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy()+Consume_Energy);
		}
		else//Get_Tile_Energy�� 0���� ������+
		{
			Player->Set_Player_Energy(Player->Get_Player_Energy());
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy());
		}
		break;
	case 3:				// ��
		Tile->SetMeshColor(0,Tile->Get_Tile_Energy()/100.f,0.0f,0.0f,1.0f);
		if(Tile->Get_Tile_Energy() ==100)
		{
			sound->Stop(g_lpDSBG[0]);
			sound->Play(g_lpDSBG[0], FALSE);
		}
		if(Tile->Get_Tile_Energy()>0)
		{
			Player->Set_Player_Energy(Player->Get_Player_Energy()+Charge_Energy);
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy()-Charge_Energy);
		}
		else
		{
			Player->Set_Player_Energy(Player->Get_Player_Energy());
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy());
		}
		break;
	case 4:				// �ٶ�
		break;
	case 5:				// ����
		Tile->Set_Material(0);
		break;
	case 6:				//��Ƽ����
		//�ٸ� Ÿ���� ������ �ʿ��ϹǷ� �浹 �Լ����� ó��
		break;
	case 7:				// Ÿ��Ÿ��!
		if(Tile->Get_Tile_Energy()<=0)
		{
			Tile->Set_Material(-1);
		}
		else
		{
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy()+Time_Tile_Consume_Energy);
		}
		break;
	case 8:				//����!
	/*	MessageBox(NULL,"Ŭ����.","Clear",NULL);
		exit(1);*/
		break;
	case 9:				//������Ÿ��!
		Tile->Set_Material(-2);
		break;
	case 10:			//Move_WindTile!
		break;
	case 11:			//Move_Tile!
		break;
	case 12:			//UpDown_Tile!
		m_Tile_Switch = true;
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16: //UpDownIron_Tile
		break;
	case 17:
		break;
	default:
		break;
	}
}