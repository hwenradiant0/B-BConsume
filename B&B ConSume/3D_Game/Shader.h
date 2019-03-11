#pragma once
#include "Device.h"


class CShader
{
private:
	LPD3DXEFFECT	m_pBasicEffect;//셰이더선언
	//텍스처 선언
	LPDIRECT3DTEXTURE9 DiffuseMap;
	LPDIRECT3DTEXTURE9 SpecularMap;
	//LPDIRECT3DTEXTURE9 NormalMap;

	//카메라눈의 위치
	D3DXVECTOR3 m_CameraEyePos;
	D3DXVECTOR3 m_PlayerPos;

	float brightness;

public:
	CShader(void);
	~CShader(void);

	bool LoadAssets(const char * filename,const char * DiffuseMapfilename, const char * SpecularMapfilename);
	LPD3DXEFFECT LoadShader(const char * Shaderfilename);
	LPDIRECT3DTEXTURE9 LoadTexture(const char * filename);
	void SetBrightness(float energy);
	void SetVariable(D3DXVECTOR4 color, D3DXMATRIX Rotate);
	void Begin();
	void End();
	void Cleanup();
	void SetCameraEyePos(D3DXVECTOR3 CameraEyePos,D3DXVECTOR3 PlayerPos);
};

