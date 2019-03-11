#pragma once
#include "entity.h"
#include <stdlib.h>
#include <time.h>

class MenuMesh :
	public CEntity
{
public:
	MenuMesh(void);
	~MenuMesh(void);



	bool Move();
	void menu_box_move();
	void menu_Cylinder_move();
	void keyboard_rot();
	void change_color();
	void old_color();

	void SetTRMatrices(D3DXVECTOR3	vPos , D3DXVECTOR3 Angle);
	void keyboard_rot_pluse();
	void keyboard_rot_Enter_Fix();
};

