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
	case 1:				// 철
		break;
	case 2:				// 물
		//값을 가져옴
		if(Tile->Get_Tile_Energy()>0)
		{
			Player->Set_Player_Energy(Player->Get_Player_Energy()+Consume_Energy);
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy()+Consume_Energy);
		}
		else//Get_Tile_Energy가 0보다 작을때+
		{
			Player->Set_Player_Energy(Player->Get_Player_Energy());
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy());
		}
		break;
	case 3:				// 불
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
	case 4:				// 바람
		break;
	case 5:				// 나무
		Tile->Set_Material(0);
		break;
	case 6:				//스티로폼
		//다른 타일의 정보도 필요하므로 충돌 함수에서 처리
		break;
	case 7:				// 타임타일!
		if(Tile->Get_Tile_Energy()<=0)
		{
			Tile->Set_Material(-1);
		}
		else
		{
			Tile->Set_Tile_Energy(Tile->Get_Tile_Energy()+Time_Tile_Consume_Energy);
		}
		break;
	case 8:				//도착!
	/*	MessageBox(NULL,"클리어.","Clear",NULL);
		exit(1);*/
		break;
	case 9:				//원윈드타일!
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