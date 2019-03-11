#pragma once
#include "Device.h"
#include "Shader.h"


class CMesh
{
	LPD3DXMESH              m_pMesh;
	D3DMATERIAL9*           m_pMeshMaterials; // 메시에서 사용할 재질
	LPDIRECT3DTEXTURE9*     m_pMeshTextures ; // 메시에서 사용할 텍스쳐
	DWORD                   m_dwNumMaterials;   // 메시에서 사용중인 재질의 개수


	LPCSTR			m_pchFilecourse;//소스파일 경로

	D3DXVECTOR3		m_vPos;//절대좌표상 위치
	D3DXVECTOR3     m_vRotAngle;//회전 축
	D3DXVECTOR3     m_vSize;
	D3DXVECTOR4		m_vColor;
	D3DXMATRIXA16	matRot;

	CShader			*m_pShader;
	

	D3DXMATRIXA16 m_matWorld;//원의 역행렬을 위한 것
		

	
	void FindMinMaxVertexpos(D3DXVECTOR3 m_vPos);//상자 한개용 함수. 확장 필요
public:
	CMesh(void);
	~CMesh(void);
	HRESULT InitGeometry_Total();//x파일,큐브,구 중 경로텍스트로 입력한 내용으로 메쉬값 설정
	LPDIRECT3DTEXTURE9 LoadTexturetwo(const char * filename);
	HRESULT InitGeometry_XFile();
	HRESULT InitGeometry_Cube();
	HRESULT InitGeometry_Sphere();
	HRESULT InitGeometry_Cylinder();

	void SetupMatrices();
	
	void PlayerSetupMatrices(D3DXMATRIXA16 *CamerMatrix);
	
	VOID Render();//일단 행렬 설정과 분리
	VOID Render(float energy);

	VOID SetPos(D3DXVECTOR3 ppos);//위치 변경

	VOID SetRotation(FLOAT fXrot,FLOAT fYrot,FLOAT fZrot);//xyz축 회전
	VOID SetSize(FLOAT fSize);//사이즈 변경
	VOID Init(LPCSTR pFile, CShader* Shader);
	VOID Set_Size_Detail(float Sx,float Sy,float Sz);
	VOID SetMaterial_DifAm(DWORD dwNumMaterial,float fR,float fG,float fB,float fA);//번호 재질의 주변,확산 색 값을 설정
	
	//VOID Animation(int Ani_Num,);// 키프레임 식으로
	VOID Cleanup();


	D3DXMATRIXA16 Get_matWorld(){return m_matWorld;}

	LPD3DXMESH Get_Mesh();
	
};
//LPSTR Plus_LPSTR_Word(LPSTR A,LPSTR B);//경로 수정을 위해 필요한 클래스 외 함수//메모리가 남는지 확인해 볼것



