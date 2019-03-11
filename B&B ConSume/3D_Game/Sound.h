#pragma once
#include "Device.h"


class Sound
{

	BOOL            g_bPlay;

public:
	Sound();

	BOOL CreateDirectSound(HWND hWnd);
	BOOL LoadWave(LPSTR lpFileName, LPDIRECTSOUNDBUFFER* lpDSBuffer);
	BOOL SetVolume(LPDIRECTSOUNDBUFFER lpDSBuffer, LONG lVolume);
	BOOL SetPan(LPDIRECTSOUNDBUFFER lpDSBuffer, LONG lPan);

	void DeleteDirectSound();
	void Play(LPDIRECTSOUNDBUFFER lpDSBuffer, BOOL Loop);
	void Stop(LPDIRECTSOUNDBUFFER lpDSBuffer);




};

