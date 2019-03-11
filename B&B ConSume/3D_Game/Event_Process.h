#pragma once
#include "Tile.h"
#include "Player.h"
#include "Sound.h"

class CEvent_Process
{
protected:
	D3DXVECTOR3 m_Pos;
	int m_Stack;
	bool m_Tile_Switch;
	Sound				*sound;
	LPDIRECTSOUNDBUFFER   g_lpDSBG[1];
	int					volume;

public:
	void Event_Cheaking(CTile *Tile, CPlayer *Player);
	void Set_Pos(D3DXVECTOR3 Pos);
	D3DXVECTOR3 Get_Pos();
	bool Get_Tile_Switch();
	void Set_Tile_Switch(bool m_Tile_Switch);

	void Volume(int num);

	CEvent_Process(void);
	~CEvent_Process(void);
};