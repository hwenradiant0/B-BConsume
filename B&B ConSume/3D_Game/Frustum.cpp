#include "Frustum.h"


CFrustum::CFrustum(void)
{
}


CFrustum::~CFrustum(void)
{
}


bool CFrustum::CalculateFrustumPlanes(D3DXMATRIXA16* mtViw, D3DXMATRIXA16* mtPrj)
{
	// Get combined matrix
	D3DXMATRIX matComb;
	D3DXMatrixMultiply(&matComb, mtViw, mtPrj);

	// Left plane
	m_pPlane[0].a = matComb._14 + matComb._11; 
	m_pPlane[0].b = matComb._24 + matComb._21; 
	m_pPlane[0].c = matComb._34 + matComb._31; 
	m_pPlane[0].d = matComb._44 + matComb._41;

	// Right plane 
	m_pPlane[1].a = matComb._14 - matComb._11; 
	m_pPlane[1].b = matComb._24 - matComb._21; 
	m_pPlane[1].c = matComb._34 - matComb._31; 
	m_pPlane[1].d = matComb._44 - matComb._41;

	// Top plane 
	m_pPlane[2].a = matComb._14 - matComb._12; 
	m_pPlane[2].b = matComb._24 - matComb._22; 
	m_pPlane[2].c = matComb._34 - matComb._32; 
	m_pPlane[2].d = matComb._44 - matComb._42;

	// Bottom plane 
	m_pPlane[3].a = matComb._14 + matComb._12; 
	m_pPlane[3].b = matComb._24 + matComb._22; 
	m_pPlane[3].c = matComb._34 + matComb._32; 
	m_pPlane[3].d = matComb._44 + matComb._42;	  

	// Near plane 
	m_pPlane[4].a = matComb._14 + matComb._13; 
	m_pPlane[4].b = matComb._24 + matComb._23; 
	m_pPlane[4].c = matComb._34 + matComb._33; 
	m_pPlane[4].d = matComb._44 + matComb._43;

	// Far plane 
	m_pPlane[5].a = matComb._14 - matComb._13; 
	m_pPlane[5].b = matComb._24 - matComb._23; 
	m_pPlane[5].c = matComb._34 - matComb._33; 
	m_pPlane[5].d = matComb._44 - matComb._43; 

	//plane 정규화
	for(int i=0;i<6;i++)
		D3DXPlaneNormalize(&m_pPlane[i], &m_pPlane[i]);

	return true;
}


void CFrustum::FrameMove(D3DXMATRIXA16* mtViw, D3DXMATRIXA16* mtPrj)
{
	CalculateFrustumPlanes(mtViw, mtPrj);
}


bool CFrustum::IsInCube(D3DXVECTOR3 &min, D3DXVECTOR3 &max)
{
	// 프러스텀 포함 체크
	for(int i=0 ; i<6 ; i++)
	{
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(min.x, min.y, min.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(max.x, min.y, min.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(min.x, max.y, min.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(min.x, min.y, max.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(min.x, max.y, max.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(max.x, min.y, max.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(max.x, max.y, min.z)) >= 0.0f)
			continue;
		if(D3DXPlaneDotCoord(&m_pPlane[i], &D3DXVECTOR3(max.x, max.y, max.z)) >= 0.0f)
			continue;

		return false;
	}
	return true;
}