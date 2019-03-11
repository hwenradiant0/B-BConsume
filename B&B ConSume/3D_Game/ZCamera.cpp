#include "ZCamera.h"
/*
D3DXMatrixIdentity(D3DXVECTOR3 *pOut)
=>���ڰ��� ������ķ� �ʱ�ȭ�Ѵ�.

D3DXVec3Normalize(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV)
=>������ ����ȭ�� ���͸� �����ش�.(������ ���, ó���� �⺻�̵Ǵ� ����)

D3DXVec3Cross(D3DXVECTOR3 *pOut,CONST D3DXVECTOR3 *pV1,CONST D3DXVECTOR3 *pV2)
=>�ΰ��� �ǿ����ڸ� �޾Ƽ� �� �ο����ڿ� ���ÿ� ������ �̷�� ���͸� �����Ѵ�.
(�� ������ ������ ���Ѵ�)

D3DXVec3Dot(CONST D3DXVECTOR3 *pV1,CONST D3DXVECTOR3 *pV2)
=>������ �� ���� ���Ѵ�.

D3DXToRadian(����)
=>������ ���̾����� �ٲ۴�.

D3DXMATRIX* WINAPI D3DXMatrixRotationAxis( D3DXMATRIX *pOut, CONST D3DXVECTOR3 *pV, FLOAT Angle )
=>D3DXVECTOR3 *pV�� �߽� FLOAT Angle��ŭ ���� D3DXMATRIX *pOut�� ����� �ִ� �Լ�
//������ ���͹���(��)�� �������� ȸ�����(�ð����)�� �����Ѵ�.
//������ �μ� FLOAT angle�� �����̴�.
//D3DXVec3TransformCoord(���,��ȯ�� ����Ʈ,��ȯ���)

D3DXVec3TransformCoord(D3DXVECTOR3 *pOut, const D3DXVECTOR *pV, D3DXMATRIX *pM)
=>D3DXVECTOR3 *pOut�� const D3DXVECTOR *pV�� D3DXMATRIX *pM�� ���Ͽ� �ִ´�.
���⼭ *pV�� 3���� �����̰� *pM�� 4���� ��������� ���� ������ �����ϰ� ���ִ°� D3DXVec3TransformCoord�Լ��̴�.
*/

ZCamera::ZCamera(void)
{
	Init();
}


ZCamera::~ZCamera(void)
{

}


void ZCamera::Init(void)
{
	m_vEye		 = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_vLookAt	 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vUp		 = D3DXVECTOR3(0.0f,1.0f,0.0f);

	D3DXMatrixIdentity( &m_matView );
	SetViewMatrix( &m_vEye, &m_vLookAt, &m_vUp );	
}

void ZCamera::SetViewMatrix(D3DXVECTOR3 *pvEye, D3DXVECTOR3 *pvLookAt, D3DXVECTOR3 *pvUp)
{
	m_vEye		= *pvEye;
	m_vLookAt	= *pvLookAt;
	m_vUp		= *pvUp;

	//�޼���ǥ��� ����
	D3DXVec3Normalize(&m_vCameraBasis, &(m_vLookAt-m_vEye));
	D3DXVec3Cross(&m_vCameraCross,&m_vUp,&m_vCameraBasis);

	D3DXMatrixLookAtLH(&m_matView,&m_vEye,&m_vLookAt,&m_vUp);
	//ViewMatrix(&m_matView,&m_vEye,&m_vLookAt,&m_vUp);
}


void ZCamera::ViewMatrix(D3DXMATRIX* pOut, D3DXVECTOR3* vcPos, D3DXVECTOR3* vcLook, D3DXVECTOR3* vcUp)
{
	D3DXVECTOR3 zAx;
	D3DXVECTOR3 xAx;
	D3DXVECTOR3 yAx;

	zAx = *vcLook - *vcPos;
	D3DXVec3Normalize(&zAx, &zAx);

	D3DXVec3Cross(&xAx, vcUp, &zAx);
	D3DXVec3Normalize(&xAx, &xAx);

	D3DXVec3Cross(&yAx, &zAx, &xAx);

	*pOut = D3DXMATRIX(
		xAx.x,						yAx.x,						zAx.x,					0,
		xAx.y,						yAx.y,						zAx.y,					0,
		xAx.z,						yAx.z,						zAx.z,					0,
		-D3DXVec3Dot(&xAx, vcPos),	-D3DXVec3Dot(&yAx, vcPos),	-D3DXVec3Dot(&zAx, vcPos), 1
		);
}



void ZCamera::MoveCameraX(float distance)
{
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove,&m_vCameraCross);

	vMove = vMove * distance;
	m_vEye += vMove;
	m_vLookAt += vMove;

	SetViewMatrix(&m_vEye,&m_vLookAt,&m_vUp);
}


void ZCamera::MoveCameraY(float distance)
{
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove,&m_vUp);

	vMove = vMove * distance;
	m_vEye += vMove;
	m_vLookAt += vMove;

	SetViewMatrix(&m_vEye,&m_vLookAt,&m_vUp);
}


void ZCamera::MoveCameraZ(float distance)
{
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove,&m_vCameraBasis);

	vMove = vMove * distance;
	m_vEye += vMove;
	m_vLookAt += vMove;

	SetViewMatrix(&m_vEye,&m_vLookAt,&m_vUp);
}

//ȸ���� ���ذ� �� �ʿ�
void ZCamera::RotateEyeX(float angle)
{
	//D3DXMATRIXA16 matRotate;
	//D3DXMatrixRotationAxis(&matRotate,&m_vCameraCross,angle);

	//D3DXVECTOR3 vNewLookAt;
	//D3DXVec3TransformCoord(&vNewLookAt,&m_vCameraBasis,&matRotate);

	//vNewLookAt += m_vEye;

	//SetViewMatrix(&m_vEye,&vNewLookAt,&m_vUp);

	FLOAT	fPitch;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtX;

	fPitch	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vLookAt-m_vEye;

	D3DXMatrixRotationAxis(&rtX, &vcX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vLookAt	= vcZ + m_vEye;
	m_vUp		= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateEyeY(float angle)
{
	//D3DXMATRIXA16 matRotate;
	//D3DXMatrixRotationAxis(&matRotate,&m_vUp,angle);

	//D3DXVECTOR3 vNewLookAt;
	//D3DXVec3TransformCoord(&vNewLookAt,&m_vCameraBasis,&matRotate);

	//vNewLookAt += m_vEye;

	//SetViewMatrix(&m_vEye,&vNewLookAt,&m_vUp);

	float fYaw;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtY;

	fYaw	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vLookAt-m_vEye;

	D3DXMatrixRotationAxis(&rtY, &vcY, fYaw);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vLookAt	= vcZ + m_vEye;
	m_vUp		= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateEyeZ(float angle)
{
	float fRoll;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtZ;


	fRoll	= D3DXToRadian(angle);


	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vLookAt-m_vEye;

	D3DXMatrixRotationAxis(&rtZ, &vcZ, fRoll);
	D3DXVec3TransformCoord(&vcX, &vcX, &rtZ);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtZ);

	m_vLookAt	= vcZ + m_vEye;
	m_vUp		= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateLookAtX(float angle)
{
	FLOAT	fPitch;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtX;

	fPitch	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vEye-m_vLookAt;

	D3DXMatrixRotationAxis(&rtX, &vcX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vEye	= vcZ + m_vLookAt;
	m_vUp	= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateLookAtY(float angle)
{
	float fYaw;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtY;

	fYaw	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vEye-m_vLookAt;

	D3DXMatrixRotationAxis(&rtY, &vcY, fYaw);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vEye	= vcZ + m_vLookAt;
	m_vUp	= vcY;
	
	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateLookAtZ(float angle)
{
	float fRoll;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtZ;

	fRoll	= D3DXToRadian(angle);


	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vEye-m_vLookAt;

	D3DXMatrixRotationAxis(&rtZ, &vcZ, fRoll);
	D3DXVec3TransformCoord(&vcX, &vcX, &rtZ);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtZ);

	m_vEye	= vcZ + m_vLookAt;
	m_vUp	= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateWorldX(float angle)
{
	FLOAT	fPitch;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtX;

	fPitch	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vLookAt-m_vEye;

	D3DXMatrixRotationX(&rtX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vLookAt	= vcZ + m_vEye;
	m_vUp		= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateWorldY(float angle)
{
	float fYaw;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtY;

	fYaw	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vLookAt-m_vEye;

	D3DXMatrixRotationY(&rtY, fYaw);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vLookAt	= vcZ + m_vEye;
	m_vUp		= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateWorldZ(float angle)
{
	float fRoll;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtZ;

	fRoll	= D3DXToRadian(angle);


	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vLookAt-m_vEye;

	D3DXMatrixRotationZ(&rtZ, fRoll);
	D3DXVec3TransformCoord(&vcX, &vcX, &rtZ);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtZ);

	m_vLookAt	= vcZ + m_vEye;
	m_vUp		= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateWorldLookAtX(float angle)
{
	FLOAT	fPitch;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtX;

	fPitch	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vEye-m_vLookAt;

	D3DXMatrixRotationX(&rtX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vEye	= vcZ + m_vLookAt;
	m_vUp	= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateWorldLookAtY(float angle)
{
	float fYaw;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtY;

	fYaw	= D3DXToRadian(angle);

	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vEye-m_vLookAt;

	D3DXMatrixRotationY(&rtY, fYaw);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vEye	= vcZ + m_vLookAt;
	m_vUp	= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}


void ZCamera::RotateWorldLookAtZ(float angle)
{
	float fRoll;

	D3DXVECTOR3 vcX;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcZ;

	D3DXMATRIX rtZ;

	fRoll	= D3DXToRadian(angle);


	vcX	= D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	vcY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	vcZ = m_vEye-m_vLookAt;

	D3DXMatrixRotationZ(&rtZ, fRoll);
	D3DXVec3TransformCoord(&vcX, &vcX, &rtZ);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtZ);

	m_vEye	= vcZ + m_vLookAt;
	m_vUp	= vcY;

	SetViewMatrix(&m_vEye, &m_vLookAt, &m_vUp);
}

void ZCamera::MoveTo(D3DXVECTOR3 *pv)
{
	D3DXVECTOR3	dv = *pv - m_vEye;
	m_vEye = *pv;
	m_vLookAt += dv;
	SetViewMatrix( &m_vEye, &m_vLookAt, &m_vUp );
}