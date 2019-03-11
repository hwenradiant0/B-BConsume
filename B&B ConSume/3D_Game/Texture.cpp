#include "Texture.h"


CTexture::CTexture()
{
	m_pTx	= NULL;
	memset(&m_Img, 0, sizeof m_Img);
}

CTexture::~CTexture()
{
	Destroy();
}


void CTexture::Destroy()
{
	if(m_pTx)
	{
		m_pTx->Release();
		m_pTx= NULL;
	}
}


INT CTexture::Create(char* sFile)
{
	DWORD	dColorKey	= NULL;

	if(FAILED(D3DXCreateTextureFromFileEx(
		Get_Device
		, sFile
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, dColorKey
		, &m_Img
		, NULL
		, &m_pTx
		)) )
	{
		m_pTx = NULL;
		MessageBox( GetActiveWindow()
					, "Create Texture Failed"
					, "Err"
					, MB_ICONEXCLAMATION
					);
		return -1;
	}

	return 0;
}


INT CTexture::Arry_Create(char* sFile[], int num)
{
	DWORD	dColorKey	= NULL;

	for(int i=0 ; i<num ; ++i)
	{
		if(FAILED(D3DXCreateTextureFromFileEx(
			Get_Device
			, sFile[i]
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_NONE
			, D3DX_FILTER_NONE
			, dColorKey
			, &m_Img
			, NULL
			, &m_arr_pTx[i]
			)) )
		{
			m_arr_pTx[i] = NULL;
			MessageBox( GetActiveWindow()
						, "Create Texture Failed"
						, "Err"
						, MB_ICONEXCLAMATION
						);
			return -1;
		}
	}

	return 0;
}


LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return m_pTx;
}


D3DXIMAGE_INFO CTexture::GetImageInfo()
{
	return m_Img;
}


LPDIRECT3DTEXTURE9* CTexture::Arry_GetTexture()
{
	return m_arr_pTx;
}


D3DXIMAGE_INFO* CTexture::Arry_GetImageInfo()
{
	return m_arr_Img;
}