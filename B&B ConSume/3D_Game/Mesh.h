#pragma once
#include "Device.h"
#include "Shader.h"


class CMesh
{
	LPD3DXMESH              m_pMesh;
	D3DMATERIAL9*           m_pMeshMaterials; // �޽ÿ��� ����� ����
	LPDIRECT3DTEXTURE9*     m_pMeshTextures ; // �޽ÿ��� ����� �ؽ���
	DWORD                   m_dwNumMaterials;   // �޽ÿ��� ������� ������ ����


	LPCSTR			m_pchFilecourse;//�ҽ����� ���

	D3DXVECTOR3		m_vPos;//������ǥ�� ��ġ
	D3DXVECTOR3     m_vRotAngle;//ȸ�� ��
	D3DXVECTOR3     m_vSize;
	D3DXVECTOR4		m_vColor;
	D3DXMATRIXA16	matRot;

	CShader			*m_pShader;
	

	D3DXMATRIXA16 m_matWorld;//���� ������� ���� ��
		

	
	void FindMinMaxVertexpos(D3DXVECTOR3 m_vPos);//���� �Ѱ��� �Լ�. Ȯ�� �ʿ�
public:
	CMesh(void);
	~CMesh(void);
	HRESULT InitGeometry_Total();//x����,ť��,�� �� ����ؽ�Ʈ�� �Է��� �������� �޽��� ����
	LPDIRECT3DTEXTURE9 LoadTexturetwo(const char * filename);
	HRESULT InitGeometry_XFile();
	HRESULT InitGeometry_Cube();
	HRESULT InitGeometry_Sphere();
	HRESULT InitGeometry_Cylinder();

	void SetupMatrices();
	
	void PlayerSetupMatrices(D3DXMATRIXA16 *CamerMatrix);
	
	VOID Render();//�ϴ� ��� ������ �и�
	VOID Render(float energy);

	VOID SetPos(D3DXVECTOR3 ppos);//��ġ ����

	VOID SetRotation(FLOAT fXrot,FLOAT fYrot,FLOAT fZrot);//xyz�� ȸ��
	VOID SetSize(FLOAT fSize);//������ ����
	VOID Init(LPCSTR pFile, CShader* Shader);
	VOID Set_Size_Detail(float Sx,float Sy,float Sz);
	VOID SetMaterial_DifAm(DWORD dwNumMaterial,float fR,float fG,float fB,float fA);//��ȣ ������ �ֺ�,Ȯ�� �� ���� ����
	
	//VOID Animation(int Ani_Num,);// Ű������ ������
	VOID Cleanup();


	D3DXMATRIXA16 Get_matWorld(){return m_matWorld;}

	LPD3DXMESH Get_Mesh();
	
};
//LPSTR Plus_LPSTR_Word(LPSTR A,LPSTR B);//��� ������ ���� �ʿ��� Ŭ���� �� �Լ�//�޸𸮰� ������ Ȯ���� ����



