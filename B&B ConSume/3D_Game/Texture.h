#pragma once
#include "Device.h"

#define MAX_TEXTURE 8

class CTexture
{
protected:
	D3DXIMAGE_INFO		m_Img;
	LPDIRECT3DTEXTURE9	m_pTx;

	D3DXIMAGE_INFO		m_arr_Img[MAX_TEXTURE];
	LPDIRECT3DTEXTURE9	m_arr_pTx[MAX_TEXTURE];

public:
	CTexture();
	virtual ~CTexture();

	virtual INT		Create(char* sFile);
	virtual INT		Arry_Create(char* sFile[], int num);
	virtual void	Destroy();

public:
	LPDIRECT3DTEXTURE9	GetTexture();
	D3DXIMAGE_INFO		GetImageInfo();

	LPDIRECT3DTEXTURE9*	Arry_GetTexture();
	D3DXIMAGE_INFO*		Arry_GetImageInfo();
};