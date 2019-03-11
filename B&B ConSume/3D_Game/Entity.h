#pragma once
#include "Mesh.h"
#include "Collision.h"
#include "Phisical.h"
class CEntity//�޽��� ���ϸ��̼� �� �׷����� �������� �޽������� ó���ϰ� ���⼱ ���� ������,�浹��
{

protected:
	CMesh			*cmObject;
	D3DXVECTOR3     m_vRotAngle;//ȸ�� ��
public:
	CEntity(void);
	~CEntity(void);
	D3DXVECTOR3			m_vPos;//���� ��ġ��
	CCollision*			m_Coll;
	CPhysicData*		m_PhyData;
	virtual void		Init(LPCSTR pFile,D3DXVECTOR3 loadPos,float Size, LPCSTR pCollType, CShader* Shader);//���� �ε��� �Ǹ� ��ȣ�� �Է��ϵ��� ����
	virtual bool		Move()=0;//ƽ���� ������ ����
	bool				Render();//��Ĺ� ����	
	CMesh				*GetpCMesh(){return cmObject;}
	void				SetPos(D3DXVECTOR3 Move);
	void				SetScale(D3DXVECTOR3 Move);
	D3DXVECTOR3			Get_Pos(){return m_vPos;}
	VOID				SetMeshColor(DWORD dwNumMaterial,float fR,float fG,float fB,float fA);//�޽��� ���� ����
	VOID				SetRotation(FLOAT fXrot,FLOAT fYrot,FLOAT fZrot);//xyz�� ȸ��
};