#pragma once
#include "Entity.h"

class CUI_Mesh :
	public CEntity
{
public:
	float Red;
	float Green;
	float Blue;

	void ColorRed(float Start, float End, float difference, float time)
	{
		Red = Start + (difference/time)*(End - Start);
	}

	//보간법을 이용한 그린 칼라
	void ColorGreen(float Start, float End, float difference, float time)
	{
		Green = Start + (difference/time)*(End - Start);
	}

	//보간법을 이용한 블루 칼라
	void ColorBlue(float Start, float End, float difference, float time)
	{
		Blue = Start + (difference/time)*(End - Start);
	}

	int	m_Loading_Num;
	CUI_Mesh(void);
	~CUI_Mesh(void);

	void Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);//파일 로딩만 되면 번호만 입력하도록 변경
	bool Move();//틱값을 넣을지 말지
	void Color_Change(int Loading_Num);
};