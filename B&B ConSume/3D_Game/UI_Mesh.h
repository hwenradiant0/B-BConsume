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

	//�������� �̿��� �׸� Į��
	void ColorGreen(float Start, float End, float difference, float time)
	{
		Green = Start + (difference/time)*(End - Start);
	}

	//�������� �̿��� ��� Į��
	void ColorBlue(float Start, float End, float difference, float time)
	{
		Blue = Start + (difference/time)*(End - Start);
	}

	int	m_Loading_Num;
	CUI_Mesh(void);
	~CUI_Mesh(void);

	void Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);//���� �ε��� �Ǹ� ��ȣ�� �Է��ϵ��� ����
	bool Move();//ƽ���� ������ ����
	void Color_Change(int Loading_Num);
};