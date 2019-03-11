#include "MenuMesh.h"


MenuMesh::MenuMesh(void)
{

}


MenuMesh::~MenuMesh(void)
{
	if(m_Coll != NULL)
		delete m_Coll;
}



void MenuMesh::menu_box_move()
{
	UINT iTime = timeGetTime() % 8000;
	FLOAT fAngle = iTime * ( D3DX_PI * 2.0f) / 2000.0f;

	cmObject->SetRotation(fAngle,fAngle,fAngle);

}


void MenuMesh::menu_Cylinder_move()
{
	cmObject->SetRotation(0,D3DX_PI/8,0);
}

void MenuMesh::keyboard_rot()
{

	cmObject->SetRotation(-D3DX_PI/2 , -D3DX_PI/2  , 0);

}
void MenuMesh::keyboard_rot_pluse()
{

	cmObject->SetRotation(-D3DX_PI/2-D3DX_PI/20.f , -D3DX_PI/2 , 0);

}

void MenuMesh::change_color()
{
	SetMeshColor(1,0,0,1,1);
}

void MenuMesh::old_color()
{
	SetMeshColor(1,0,0,0,1);

}

bool MenuMesh::Move()
{
	return 0;
}

void MenuMesh::SetTRMatrices(D3DXVECTOR3 vPos ,D3DXVECTOR3 Angle )
{
	/// 월드행렬
	D3DXMATRIXA16 matWorld;

	D3DXMATRIXA16 matSize;

	D3DXMATRIXA16 matRot;

	D3DXMATRIXA16 matRot_x;
	D3DXMATRIXA16 matRot_y;
	D3DXMATRIXA16 matRot_z;

	D3DXMATRIXA16 matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matSize);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matRot_x);
	D3DXMatrixIdentity(&matRot_y);
	D3DXMatrixIdentity(&matRot_z);
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matSize,2,1,1);

	D3DXMatrixRotationX( &matRot_x, Angle.x );
	D3DXMatrixRotationY( &matRot_y, Angle.y );
	D3DXMatrixRotationZ( &matRot_z, Angle.z );

	D3DXMatrixTranslation(&matTrans,vPos.x,vPos.y,vPos.z);

	matRot = matRot_x * matRot_y * matRot_z;

	matWorld=matSize*matTrans*matRot;

	Get_Device->SetTransform( D3DTS_WORLD, &matWorld );

	
	//버텍스 정보 트랜스 수정

}


void MenuMesh::keyboard_rot_Enter_Fix()
{
	cmObject->SetRotation(-D3DX_PI/2+D3DX_PI/20.f,-D3DX_PI/2+D3DX_PI/20.f , 0);
}