#include "Define.h"

#ifndef _DEVICE_H//������ ���� ����
#define _DEVICE_H
class CDevice
{
	LPDIRECT3D9             g_pD3D    ; /// D3D ����̽��� ������ D3D��ü����
	LPDIRECT3DDEVICE9       g_pd3dDevice ; /// �������� ���� D3D����̽�
	LPDIRECTSOUND8			g_lpDS;  //���̷�Ʈ ���尳ü

	LPDIRECTINPUT8			lpDI;				//���̷�Ʈ ��ǲ ��ü
	LPDIRECTINPUTDEVICE8	lpDIKeyboard;		//���̷�Ʈ Ű����
	LPDIRECTINPUTDEVICE8	lpDIMouse;			//���̷�Ʈ ���콺
		

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