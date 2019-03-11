#pragma once
#include "Device.h"


class CFrustum
{
private:
	D3DXVECTOR3			m_vVtx[8];	/// 프러스텀을 구성할 정점 8개
	D3DXVECTOR3			m_vPos;		/// 현재 카메라의 월드좌표
	D3DXPLANE			m_pPlane[6];	/// 프러스텀을 구성하는 6개의 평면

public:
	CFrustum(void);
	~CFrustum(void);

	bool CalculateFrustumPlanes(D3DXMATRIXA16* mtViw, D3DXMATRIXA16* mtPrj);
	void FrameMove(D3DXMATRIXA16* mtViw, D3DXMATRIXA16* mtPrj);
	bool IsInCube(D3DXVECTOR3 &min, D3DXVECTOR3 &max);

};

