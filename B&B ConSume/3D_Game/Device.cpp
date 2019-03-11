#include "Device.h"


CDevice::CDevice(void)
{
	g_pD3D			= NULL;
	g_pd3dDevice	= NULL;
	g_lpDS			= NULL;  //다이렉트 사운드

	lpDI			= NULL;	// 다이렉트 인풋 객체
	lpDIKeyboard	= NULL;	//키보드임
	lpDIMouse		= NULL;	//마우스임
}


CDevice::~CDevice(void)
{
}
LPDIRECT3DDEVICE9 CDevice::Get_g_pd3dDevice(){return g_pd3dDevice;}
HRESULT CDevice::InitD3D( HWND hWnd , HINSTANCE hInst)
{
    /// 디바이스를 생성하기위한 D3D객체 생성
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;                /// 디바이스 생성을 위한 구조체
	ZeroMemory( &d3dpp, sizeof(d3dpp) );        /// 반드시 ZeroMemory()함수로 미리 구조체를 깨끗이 지워야 한다.
	d3dpp.Windowed					= TRUE; //FALSE;                      /// 창모드로 생성
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;   /// 가장 효율적인 SWAP효과
	/*d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;    /// 현재 바탕화면 모드에 맞춰서 후면버퍼를 생성*/
	d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp.hDeviceWindow				= hWnd;
	d3dpp.BackBufferWidth			= GetSystemMetrics(SM_CXSCREEN);
	d3dpp.BackBufferHeight			= GetSystemMetrics(SM_CYSCREEN);
	d3dpp.EnableAutoDepthStencil	= TRUE;//Direct3D가 자동으로 깊이/스텐실 버퍼를 만들고 관리하기를 원한다면 true... 
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;//깊이/스탠실 버퍼의 포맷


    /// 디바이스를 다음과 같은 설정으로 생성한다.
	/// 1. 디폴트 비디오카드를 사용(대부분은 비디오카드가 1개 이다.)
	/// 2. HAL디바이스를 생성한다.(HW가속장치를 사용하겠다는 의미)
	/// 3. 정점처리는 모든 카드에서 지원하는 SW처리로 생성한다.(HW로 생성할경우 더욱 높은 성능을 낸다.)
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	/// 디바이스 상태정보를 처리할경우 여기에서 한다.
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,TRUE);//zbuffer is ON

	/// Z버퍼기능을 켠다.
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );	
	/// 주변광원값을 최대밝기로
	g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	

	///알파값
	/*g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088); */
	
	//다이렉트 사운드 개체 생성 
	if( DirectSoundCreate8(NULL, &g_lpDS, NULL) == DS_OK )
		if( g_lpDS->SetCooperativeLevel( hWnd, DSSCL_NORMAL ) != DS_OK )
			;



	//다이렉트 인풋(마우스)
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&lpDI, NULL)))
		return E_FAIL;
	//선언한 객체를 통해 디바이스를 생성한다.
	if(FAILED(lpDI->CreateDevice(GUID_SysMouse, &lpDIMouse, NULL)))
		return E_FAIL;
	//창모드일때는  DISCL_NONEXCLUSIVE | DISCL_BACKGROUND  를 사용합니다.
	//SetCooperativeLevel의 2번재 인자값 
	//		DISCL_EXCLUSIVE		//마우스를 안보이게 해줌
	//		DISCL_NONEXCLUSIVE	//<-- 넌 누구니?
	//		DISCL_FOREGROUND	// 응용프로그램이 사용중일때만 입력받도록 함
	//		DISCL_BACKGROUND	//<-- 넌 누구니?
	//		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND // <--창모드일때는 이거를 씀
	if(FAILED(lpDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		return E_FAIL;
	if(FAILED(lpDIMouse->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;


	if( FAILED(lpDI->CreateDevice(GUID_SysKeyboard, &lpDIKeyboard, NULL)) )
		return E_FAIL;
	if( FAILED(lpDIKeyboard->SetDataFormat(&c_dfDIKeyboard)) )
		return E_FAIL;
	if( FAILED(lpDIKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE|DISCL_BACKGROUND)) )
		return E_FAIL;



	return S_OK;
}


/**-----------------------------------------------------------------------------
 * 초기화된 객체들을 소거한다.
 *------------------------------------------------------------------------------
 */
void CDevice::Cleanup()
{
    if( g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL)
        g_pD3D->Release();



}

