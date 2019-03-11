#include "Mouse.h"


MouseInput::MouseInput(void)
{

	Left_button		= FALSE;
	Right_button	= FALSE;

}

MouseInput::~MouseInput()
{



}


void MouseInput::Init()
{
	CDevice::GetInstance()->GetMouse()->Acquire();
	Moust_Wheel=0;

}

void MouseInput::mouse_state()
{
	//마우스 상태 얻어오기
	CDevice::GetInstance()->GetMouse()->GetDeviceState( sizeof(DIMOUSESTATE),&MouseState );

	// 마우스를 윈도우의 중앙으로 초기화
	SetCursor( NULL );	// 마우스를 나타나지 않게 않다.

	//좌표 넘기기
	mouse_move.x = MouseState.lX;
	mouse_move.y = MouseState.lY;
	
	//눌렸지 보기
	if(MouseState.rgbButtons[0] & 0x80)
		Left_button = TRUE;
	else
		Left_button = FALSE;

	if(MouseState.rgbButtons[1] & 0x80)
		Right_button = TRUE;
	else
		Right_button = FALSE;

	if(MouseState.lZ>0 )
	{
		Moust_Wheel =Moust_Wheel+1;
		Middle_button=true;
	}
	else if( MouseState.lZ<0)
	{
		Moust_Wheel=Moust_Wheel-1;
		Middle_button=true;
	}
	else
Middle_button=false;


}
int MouseInput::Get_Wheel()
{ 	
	return Moust_Wheel;

}

int MouseInput::Get_mouse_x()
{
	return mouse_move.x;
}
int	MouseInput::Get_mouse_y()
{
	return mouse_move.y;
}

BOOL MouseInput::Get_Left_button()
{
	return Left_button;
}

BOOL MouseInput::Get_Right_button()
{
	return Right_button;
}
BOOL MouseInput::Get_Middle_button()
{
	return Middle_button;
}



void MouseInput::Clean()
{

	CDevice::GetInstance()->GetMouse()->Unacquire();

}