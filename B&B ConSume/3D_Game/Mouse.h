#pragma once
#include "Device.h"

class MouseInput
{
	DIMOUSESTATE			MouseState; // 마우스 상태 객체
	D3DXVECTOR3				mouse_move;	// 마우스 위치
	BOOL					Left_button;
	BOOL					Right_button;
	BOOL					Middle_button;
	float					Moust_Wheel;

public:
	MouseInput(void);
	~MouseInput(void);



	void Init();
	void mouse_state();
	void Clean();

	int Get_mouse_x();
	int	Get_mouse_y();
	BOOL Get_Left_button();
	BOOL Get_Right_button();
	BOOL Get_Middle_button();
	int Get_Wheel();
	void Set_Wheel(int x){Moust_Wheel=x;};

};

