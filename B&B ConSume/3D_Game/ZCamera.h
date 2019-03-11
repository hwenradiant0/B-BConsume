#pragma once
#include "Device.h"

/*
������ : �ۺ���
��	�� : ī�޶� Ŭ���� �������
������ : 2014.01.06
*/

class ZCamera
{
private:
	D3DXVECTOR3 m_vEye;		//ī�޶��� ��(ī�޶��� ���� ��ġ)
	D3DXVECTOR3 m_vLookAt;	//ī�޶� �ٶ󺸴� ����(ī�޶��� �ü� ��ġ)
	D3DXVECTOR3 m_vUp;		//ī�޶��� ��溤��

	D3DXVECTOR3 m_vCameraBasis; //ī�޶�ü��� �������⺤��(m_vLookAt-m_vEye)
	D3DXVECTOR3 m_vCameraCross; //ī�޶��� ������ ���� ����(m_vUp,m_vCameraBasis �κ����� ����)

	D3DXMATRIXA16 m_matView;	//ī�޶� ���
public:
	ZCamera(void);

	~ZCamera(void);

	//�ʱⰪ ����
	void Init(void);

	//ī�޶��� ���� �����Ѵ�.
	void SetEye( D3DXVECTOR3 *pvEye ) { m_vEye = *pvEye; }

	//ī�޶��� ���� ���� �����Ѵ�.
	D3DXVECTOR3 GetEye() { return m_vEye; }

	//ī�޶��� �ü����� �����Ѵ�.
	void SetLookAt(D3DXVECTOR3 *pvLootAt) { m_vLookAt = *pvLootAt; }

	//ī�޶��� �ü����� �����Ѵ�.
	D3DXVECTOR3 GetLookAt() { return m_vLookAt ; }

	//ī�޶��� ��溤�͸� �����Ѵ�.
	void SetUp(D3DXVECTOR3 *pvUp) { m_vUp = *pvUp; }

	//ī�޶��� ��溤�͸� �����Ѵ�.
	D3DXVECTOR3 GetUp() { return m_vUp; }

	//ī�޶� ����� �����ϰ� �����Ѵ�.
	void SetViewMatrix(D3DXVECTOR3 *pvEye, D3DXVECTOR3 *pvLookAt, D3DXVECTOR3 *pvUp);

	//ī�޶� ����� �����Ѵ�.
	D3DXMATRIXA16 GetViewMatrix() { return m_matView; }

	//D3DXMatrixLookAtLH()�� ������ ����� �ϴ� �Լ�
	void ViewMatrix(D3DXMATRIX* pOut, D3DXVECTOR3* vcPos, D3DXVECTOR3* vcLook, D3DXVECTOR3* vcUp);

	//ī�޶� ��ǥ���� X�� �������� ���� �ü��� dist��ŭ �̵�
	void MoveCameraX(float distance);

	//ī�޶� ��ǥ���� Y�� �������� ���� �ü��� dist��ŭ �̵�
	void MoveCameraY(float distance);

	//ī�޶� ��ǥ���� Z�� �������� ���� �ü��� dist��ŭ �̵�
	void MoveCameraZ(float distance);

	//ī�޶� ���� X���� �������� angle ��ŭ ȸ��
	void RotateEyeX(float angle);

	//ī�޶� ���� Y���� �������� angle ��ŭ ȸ��
	void RotateEyeY(float angle);

	//ī�޶� ���� Z���� �������� angle ��ŭ ȸ��
	void RotateEyeZ(float angle);

	//ī�޶� �����ִ� ������ X�� �������� angle ��ŭ ȸ��
	void RotateLookAtX(float angle);

	//ī�޶� �����ִ� ������ Y�� �������� angle ��ŭ ȸ��
	void RotateLookAtY(float angle);

	//ī�޶� �����ִ� ������ Z�� �������� angle ��ŭ ȸ��
	void RotateLookAtZ(float angle);

	//������ǥ���� X�� �������� angle ��ŭ ȸ��
	void RotateWorldX(float angle);

	//������ǥ���� Y�� �������� angle ��ŭ ȸ��
	void RotateWorldY(float angle);

	//������ǥ���� Z�� �������� angle ��ŭ ȸ��
	void RotateWorldZ(float angle);

	//ī�޶� �ٶ󺸴� ������ ���� ��ǥ���� X�� �������� angle ��ŭ ȸ��
	void RotateWorldLookAtX(float angle);

	//ī�޶� �ٶ󺸴� ������ ���� ��ǥ���� X�� �������� angle ��ŭ ȸ��
	void RotateWorldLookAtY(float angle);

	//ī�޶� �ٶ󺸴� ������ ���� ��ǥ���� X�� �������� angle ��ŭ ȸ��
	void RotateWorldLookAtZ(float angle);

	// ������ǥ���� *pv���� ��ġ�� �̵��Ѵ�.
	void MoveTo(D3DXVECTOR3 *pv);
};