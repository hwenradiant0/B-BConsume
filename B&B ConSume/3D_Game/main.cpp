#include "GameBase.h"

#include<WinUser.h>
#include "resource.h"
CGameBase Game;//���� ���̽� ����
FLOAT g_Tick=0;

#define WM_MOUSEWHEEL 0x020A//���콺 �� �̺�Ʈ �޼��� �̸�

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	//case WM_KEYDOWN : 
	//	switch( wParam )
	//	{
	//	case VK_ESCAPE :
	//		PostMessage( hWnd, WM_DESTROY, 0, 0L );
	//		break;
	//	}
	//	break;
	case WM_MOUSEWHEEL:
	//	//((short)HIWORD(wParam)<0)? Game.m_fCamera_Eye_Postion_Y = Game.m_fCamera_Eye_Postion_Y - 10
	//	//	: Game.m_fCamera_Eye_Postion_Y = Game.m_fCamera_Eye_Postion_Y + 10;
		((short)HIWORD(wParam)<0)? Game.Camera->SetEye(&(Game.Camera->GetEye()+D3DXVECTOR3(0,-10,0)))
			: Game.Camera->SetEye(&(Game.Camera->GetEye()+D3DXVECTOR3(0,10,0)));
		break;
	case WM_ACTIVATE:
		if(LOWORD(wParam)==WA_INACTIVE)//��Ȱ��ȭ�϶�
		{
			Game.Set_Key_State(false);
		}
		else//Ȱ��ȭ�϶�
		{
			Game.Set_Key_State(true);
	
		}
		break;
	case WM_DESTROY:
		CDevice::GetInstance()->Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

/**-----------------------------------------------------------------------------
* ���α׷� ������
*------------------------------------------------------------------------------
*/
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{


	/// ������ Ŭ���� ���
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL };
	wc.hIcon=LoadIcon(hInst,MAKEINTRESOURCE(ID_BICon));
	RegisterClassEx( &wc );

	
	/// ������ ����
	HWND hWnd = CreateWindow( "D3D Tutorial",Game_Title,
		WS_OVERLAPPEDWINDOW // WS_EX_TOPMOST | WS_POPUP
		, 0, 0, GetSystemMetrics(SM_CXSCREEN),  GetSystemMetrics(SM_CYSCREEN),
		GetDesktopWindow(), NULL, wc.hInstance, NULL );

	/// Direct3D �ʱ�ȭ
	if( SUCCEEDED( CDevice::GetInstance()->InitD3D( hWnd , hInst ) ) )
	{
		Game.GB_Init();
		/// ������ ���
		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );

		/// �޽��� ����
		MSG msg;
		ZeroMemory( &msg, sizeof(msg) );
		while( msg.message!=WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				float time=GetTickCount();
				Game.GB_Run(g_Tick);
				g_Tick=(float)(GetTickCount()-time)/1000;
			}

		}
	}
	
	SetFocus(hWnd);
	UnregisterClass( "D3D Tutorial", wc.hInstance );
	return 0;
}