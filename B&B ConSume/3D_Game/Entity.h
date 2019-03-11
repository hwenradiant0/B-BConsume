#pragma once
#include "Mesh.h"
#include "Collision.h"
#include "Phisical.h"
class CEntity//메쉬의 에니메이션 등 그래픽의 움직임은 메쉬선에서 처리하고 여기선 단지 움직임,충돌만
{

protected:
	CMesh			*cmObject;
	D3DXVECTOR3     m_vRotAngle;//회전 축
public:
	CEntity(void);
	~CEntity(void);
	D3DXVECTOR3			m_vPos;//유닛 위치값
	CCollision*			m_Coll;
	CPhysicData*		m_PhyData;
	virtual void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);//파일 로딩만 되면 번호만 입력하도록 변경
	virtual bool		Move()=0;//틱값을 넣을지 말지
	bool				Render();//행렬및 렌더	
	CMesh				*GetpCMesh(){return cmObject;}
	void				SetPos(D3DXVECTOR3 Move);
	void				SetScale(D3DXVECTOR3 Move);
	D3DXVECTOR3			Get_Pos(){return m_vPos;}
	VOID				SetMeshColor(DWORD dwNumMaterial,float fR,float fG,float fB,float fA);//메쉬의 색을 설정
	VOID				SetRotation(FLOAT fXrot,FLOAT fYrot,FLOAT fZrot);//xyz축 회전
};