#include "Shader.h"


CShader::CShader(void)
{
	brightness = 0;
}


CShader::~CShader(void)
{
	Cleanup();
}


bool CShader::LoadAssets(const char * Shaderfilename, const char * DiffuseMapfilename, const char * SpecularMapfilename)
{
	//셰이더로딩
	m_pBasicEffect = LoadShader(Shaderfilename);
	if ( !m_pBasicEffect )
	{
		return false;
	}
	// 텍스처 로딩
	DiffuseMap  = LoadTexture(DiffuseMapfilename);
	if ( !DiffuseMap )
	{
		return false;
	}
	SpecularMap = LoadTexture(SpecularMapfilename);
	if ( !SpecularMap )
	{
		return false;
	}
	return false;
	
}

LPD3DXEFFECT CShader::LoadShader(const char * filename )
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(Get_Device, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if(!ret && pError)
	{
		int size	= pError->GetBufferSize();
		void *ack	= pError->GetBufferPointer();

		if(ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete [] str;
		}
	}
	return ret;
}

LPDIRECT3DTEXTURE9 CShader::LoadTexture(const char * filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if ( FAILED(D3DXCreateTextureFromFile(Get_Device, filename, &ret)) )
	{
		OutputDebugString("텍스처 로딩 실패: ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	}

	return ret;

}

void CShader::SetVariable(D3DXVECTOR4 color, D3DXMATRIX Rotate)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	Get_Device->GetTransform(D3DTS_WORLD,&matWorld);

	D3DXMATRIXA16 matView;
	D3DXMatrixIdentity(&matView);

	Get_Device->GetTransform(D3DTS_VIEW,&matView);

	D3DXMATRIXA16 matProjection;
	D3DXMatrixIdentity(&matProjection);
	Get_Device->GetTransform(D3DTS_PROJECTION,&matProjection);

	D3DXMATRIXA16 mat_InverseView;
	D3DXMatrixInverse(&mat_InverseView, NULL, &matView);

	// 월드/뷰/투영행렬을 미리 곱한다
	D3DXMATRIXA16 matWorldView;
	D3DXMATRIXA16 matWorldViewProjection;
	D3DXMatrixMultiply(&matWorldView,&matWorld,&matView);
	D3DXMatrixMultiply(&matWorldViewProjection,&matWorldView,&matProjection);

	float SpecularPower = 0.01f;
	int temp = 0;

	if(brightness >= 500)
	{
		temp = brightness;
		brightness = brightness - (brightness - 500);
	}

	SpecularPower = ((500 - brightness))/100 + 0.01f;

	D3DXVECTOR4 v_Light[2];
	v_Light[0] = D3DXVECTOR4(m_PlayerPos.x, m_PlayerPos.y + 30, m_PlayerPos.z,0);
	v_Light[1] = D3DXVECTOR4(200, -500, 100, 0);

	D3DXVECTOR4 v_Camera;
	
	if(temp <= 500)
		v_Camera = D3DXVECTOR4(m_PlayerPos.x, m_PlayerPos.y + 30, m_PlayerPos.z,0);
	else
		v_Camera = D3DXVECTOR4(m_PlayerPos.x, m_PlayerPos.y + 30 + (temp - 500)/2, m_PlayerPos.z,0);

	m_pBasicEffect->SetMatrix("gWorldMatrix",&matWorld);
	m_pBasicEffect->SetMatrix("gViewMatrix",&matView);
	m_pBasicEffect->SetMatrix("gProjectionMatrix",&matProjection);
	m_pBasicEffect->SetMatrix("gWorldViewProjectionMatrix",&matWorldViewProjection);
	//m_pBasicEffect->SetMatrix("ObjectRotate",&Rotate);

	m_pBasicEffect->SetVectorArray("gWorldLightPosition",v_Light, 2);
	m_pBasicEffect->SetVector("gWorldCameraPosition",&v_Camera);
	m_pBasicEffect->SetVector("ObjectColor",&color);


	m_pBasicEffect->SetFloat("SpecularPower",SpecularPower);

	m_pBasicEffect->SetTexture("DiffuseMap_Tex",DiffuseMap);	
	m_pBasicEffect->SetTexture("SpecularMap_Tex",SpecularMap);
}

void CShader::Begin()
{
	m_pBasicEffect->Begin(0, 0);
	m_pBasicEffect->BeginPass(0);
}


void CShader::End()
{
	m_pBasicEffect->EndPass();
	m_pBasicEffect->End();
}

void CShader::Cleanup()
{
	if(m_pBasicEffect)
	{
		m_pBasicEffect->Release();
		m_pBasicEffect = NULL;
	}

	if(DiffuseMap)
	{
		DiffuseMap->Release();
		DiffuseMap = NULL;
	}

	if(SpecularMap)
	{
		SpecularMap->Release();
		SpecularMap = NULL;
	}
}

void CShader::SetCameraEyePos(D3DXVECTOR3 CameraEyePos,D3DXVECTOR3 PlayerPos)
{
	m_CameraEyePos = CameraEyePos;
	m_PlayerPos = PlayerPos;
}


void CShader::SetBrightness(float energy)
{
	brightness = energy;
}