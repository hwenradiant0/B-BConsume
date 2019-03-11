#pragma once
#include "Device.h"


class CFrustum
{
private:
	D3DXVECTOR3			m_vVtx[8];	/// ���������� ������ ���� 8��
	D3DXVECTOR3			m_vPos;		/// ���� ī�޶��� ������ǥ
	D3DXPLANE			m_pPlane[6];	/// ���������� �����ϴ� 6���� ���

public:
	CFrustum(void);
	~CFrustum(void);

	bool CalculateFrustumPlanes(D3DXMATRIXA16* mtViw, D3DXMATRIXA16* mtPrj);
	void FrameMove(D3DXMATRIXA16* mtViw, D3DXMATRIXA16* mtPrj);
	bool IsInCube(D3DXVECTOR3 &min, D3DXVECTOR3 &max);

};

