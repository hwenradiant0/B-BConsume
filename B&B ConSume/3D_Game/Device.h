#include "Define.h"

#ifndef _DEVICE_H//재정의 오류 막기
#define _DEVICE_H
class CDevice
{
	LPDIRECT3D9             g_pD3D    ; /// D3D 디바이스를 생성할 D3D객체변수
	LPDIRECT3DDEVICE9       g_pd3dDevice ; /// 렌더링에 사용될 D3D디바이스
	LPDIRECTSOUND8			g_lpDS;  //다이렉트 사운드개체

	LPDIRECTINPUT8			lpDI;				//다이렉트 인풋 객체
	LPDIRECTINPUTDEVICE8	lpDIKeyboard;		//다이렉트 키보드
	LPDIRECTINPUTDEVICE8	lpDIMouse;			//다이렉트 마우스
		

public:
	CDevice();
	~CDevice();
	static CDevice* GetInstance()
	{
		static CDevice s_Instance;
		return &s_Instance;
	}
	LPDIRECT3DDEVICE9 Get_g_pd3dDevice();
	LPDIRECTSOUND8	  GetDXSound() { return g_lpDS; };
	LPDIRECTINPUTDEVICE8	GetMouse(){return lpDIMouse;};
	LPDIRECTINPUTDEVICE8	GetKeyboard(){return lpDIKeyboard;};

	HRESULT InitD3D( HWND hWnd , HINSTANCE hInst);
	void Cleanup();
};

#define Get_Device  CDevice::GetInstance()->Get_g_pd3dDevice()

#endif