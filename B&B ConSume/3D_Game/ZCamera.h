#pragma once
#include "Device.h"

/*
만든이 : 송병찬
내	용 : 카메라 클래스 헤더파일
수정일 : 2014.01.06
*/

class ZCamera
{
private:
	D3DXVECTOR3 m_vEye;		//카메라의 눈(카메라의 현재 위치)
	D3DXVECTOR3 m_vLookAt;	//카메라가 바라보는 방향(카메라의 시선 위치)
	D3DXVECTOR3 m_vUp;		//카메라의 상방벡터

	D3DXVECTOR3 m_vCameraBasis; //카메라시선의 단위방향벡터(m_vLookAt-m_vEye)
	D3DXVECTOR3 m_vCameraCross; //카메라의 오른쪽 측면 벡터(m_vUp,m_vCameraBasis 두벡터의 직각)

	D3DXMATRIXA16 m_matView;	//카메라 행렬
public:
	ZCamera(void);

	~ZCamera(void);

	//초기값 설정
	void Init(void);

	//카메라의 눈을 설정한다.
	void SetEye( D3DXVECTOR3 *pvEye ) { m_vEye = *pvEye; }

	//카메라의 눈의 값을 리턴한다.
	D3DXVECTOR3 GetEye() { return m_vEye; }

	//카메라의 시선값을 설정한다.
	void SetLookAt(D3DXVECTOR3 *pvLootAt) { m_vLookAt = *pvLootAt; }

	//카메라의 시선값을 리턴한다.
	D3DXVECTOR3 GetLookAt() { return m_vLookAt ; }

	//카메라의 상방벡터를 설정한다.
	void SetUp(D3DXVECTOR3 *pvUp) { m_vUp = *pvUp; }

	//카메라의 상방벡터를 리턴한다.
	D3DXVECTOR3 GetUp() { return m_vUp; }

	//카메라 행렬을 설정하고 리턴한다.
	void SetViewMatrix(D3DXVECTOR3 *pvEye, D3DXVECTOR3 *pvLookAt, D3DXVECTOR3 *pvUp);

	//카메라 행렬을 리턴한다.
	D3DXMATRIXA16 GetViewMatrix() { return m_matView; }

	//D3DXMatrixLookAtLH()와 동일한 기능을 하는 함수
	void ViewMatrix(D3DXMATRIX* pOut, D3DXVECTOR3* vcPos, D3DXVECTOR3* vcLook, D3DXVECTOR3* vcUp);

	//카메라 좌표계의 X축 방향으로 눈과 시선을 dist만큼 이동
	void MoveCameraX(float distance);

	//카메라 좌표계의 Y축 방향으로 눈과 시선을 dist만큼 이동
	void MoveCameraY(float distance);

	//카메라 좌표계의 Z축 방향으로 눈과 시선을 dist만큼 이동
	void MoveCameraZ(float distance);

	//카메라 눈의 X축을 기준으로 angle 만큼 회전
	void RotateEyeX(float angle);

	//카메라 눈의 Y축을 기준으로 angle 만큼 회전
	void RotateEyeY(float angle);

	//카메라 눈의 Z축을 기준으로 angle 만큼 회전
	void RotateEyeZ(float angle);

	//카메라가 보고있는 정점의 X축 기준으로 angle 만큼 회전
	void RotateLookAtX(float angle);

	//카메라가 보고있는 정점의 Y축 기준으로 angle 만큼 회전
	void RotateLookAtY(float angle);

	//카메라가 보고있는 정점의 Z축 기준으로 angle 만큼 회전
	void RotateLookAtZ(float angle);

	//월드좌표계의 X축 기준으로 angle 만큼 회전
	void RotateWorldX(float angle);

	//월드좌표계의 Y축 기준으로 angle 만큼 회전
	void RotateWorldY(float angle);

	//월드좌표계의 Z축 기준으로 angle 만큼 회전
	void RotateWorldZ(float angle);

	//카메라가 바라보는 정점을 월드 좌표계의 X축 기준으로 angle 만큼 회전
	void RotateWorldLookAtX(float angle);

	//카메라가 바라보는 정점을 월드 좌표계의 X축 기준으로 angle 만큼 회전
	void RotateWorldLookAtY(float angle);

	//카메라가 바라보는 정점을 월드 좌표계의 X축 기준으로 angle 만큼 회전
	void RotateWorldLookAtZ(float angle);

	// 월드좌표계의 *pv값의 위치로 이동한다.
	void MoveTo(D3DXVECTOR3 *pv);
};