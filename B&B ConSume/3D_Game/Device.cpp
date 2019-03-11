#include "Device.h"


CDevice::CDevice(void)
{
	g_pD3D			= NULL;
	g_pd3dDevice	= NULL;
	g_lpDS			= NULL;  //���̷�Ʈ ����

	lpDI			= NULL;	// ���̷�Ʈ ��ǲ ��ü
	lpDIKeyboard	= NULL;	//Ű������
	lpDIMouse		= NULL;	//���콺��
}


CDevice::~CDevice(void)
{
}
LPDIRECT3DDEVICE9 CDevice::Get_g_pd3dDevice(){return g_pd3dDevice;}
HRESULT CDevice::InitD3D( HWND hWnd , HINSTANCE hInst)
{
    /// ����̽��� �����ϱ����� D3D��ü ����
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;                /// ����̽� ������ ���� ����ü
	ZeroMemory( &d3dpp, sizeof(d3dpp) );        /// �ݵ�� ZeroMemory()�Լ��� �̸� ����ü�� ������ ������ �Ѵ�.
	d3dpp.Windowed					= TRUE; //FALSE;                      /// â���� ����
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;   /// ���� ȿ������ SWAPȿ��
	/*d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;    /// ���� ����ȭ�� ��忡 ���缭 �ĸ���۸� ����*/
	d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp.hDeviceWindow				= hWnd;
	d3dpp.BackBufferWidth			= GetSystemMetrics(SM_CXSCREEN);
	d3dpp.BackBufferHeight			= GetSystemMetrics(SM_CYSCREEN);
	d3dpp.EnableAutoDepthStencil	= TRUE;//Direct3D�� �ڵ����� ����/���ٽ� ���۸� ����� �����ϱ⸦ ���Ѵٸ� true... 
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;//����/���Ľ� ������ ����


    /// ����̽��� ������ ���� �������� �����Ѵ�.
	/// 1. ����Ʈ ����ī�带 ���(��κ��� ����ī�尡 1�� �̴�.)
	/// 2. HAL����̽��� �����Ѵ�.(HW������ġ�� ����ϰڴٴ� �ǹ�)
	/// 3. ����ó���� ��� ī�忡�� �����ϴ� SWó���� �����Ѵ�.(HW�� �����Ұ�� ���� ���� ������ ����.)
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	/// ����̽� ���������� ó���Ұ�� ���⿡�� �Ѵ�.
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,TRUE);//zbuffer is ON

	/// Z���۱���� �Ҵ�.
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );	
	/// �ֺ��������� �ִ����
	g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	

	///���İ�
	/*g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088); */
	
	//���̷�Ʈ ���� ��ü ���� 
	if( DirectSoundCreate8(NULL, &g_lpDS, NULL) == DS_OK )
		if( g_lpDS->SetCooperativeLevel( hWnd, DSSCL_NORMAL ) != DS_OK )
			;



	//���̷�Ʈ ��ǲ(���콺)
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&lpDI, NULL)))
		return E_FAIL;
	//������ ��ü�� ���� ����̽��� �����Ѵ�.
	if(FAILED(lpDI->CreateDevice(GUID_SysMouse, &lpDIMouse, NULL)))
		return E_FAIL;
	//â����϶���  DISCL_NONEXCLUSIVE | DISCL_BACKGROUND  �� ����մϴ�.
	//SetCooperativeLevel�� 2���� ���ڰ� 
	//		DISCL_EXCLUSIVE		//���콺�� �Ⱥ��̰� ����
	//		DISCL_NONEXCLUSIVE	//<-- �� ������?
	//		DISCL_FOREGROUND	// �������α׷��� ������϶��� �Է¹޵��� ��
	//		DISCL_BACKGROUND	//<-- �� ������?
	//		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND // <--â����϶��� �̰Ÿ� ��
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
 * �ʱ�ȭ�� ��ü���� �Ұ��Ѵ�.
 *------------------------------------------------------------------------------
 */
void CDevice::Cleanup()
{
    if( g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL)
        g_pD3D->Release();



}

