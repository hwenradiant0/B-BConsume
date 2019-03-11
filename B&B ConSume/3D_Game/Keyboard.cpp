#include "Keyboard.h"


KeyInput::KeyInput(void)
{
	m_bVk_Up	=false;
	m_bVk_Down	=false;
	m_bVk_Right	=false;
	m_bVk_Left	=false;
	m_bVk_W		=false;
	m_bVk_S		=false;
	m_bVk_A		=false;
	m_bVk_D		=false;
	m_bVk_R		=false;
	m_bVk_F		=false;
	m_bvk_Enter	=false;
	m_bvk_Space = false;

	m_Up_State =true;
	m_Down_State=false;



	m_bVk_Esc= false;
	m_Esc_State= false;
	for( int i = 0 ; i < 256 ; i++ )
		KeyState[i] = NULL;


}

KeyInput::~KeyInput(void)
{
}

void KeyInput::Key_input_Init()
{
	CDevice::GetInstance()->GetKeyboard()->Acquire();
}

void KeyInput::Key_False()
{
	Set_A(false);
	Set_D(false);
	Set_Down(false);
	Set_Enter(false);
	Set_Esc(false);
	Set_F(false);
	Set_Left(false);
	Set_R(false);
	Set_Right(false);
	Set_S(false);
	Set_Space(false);
	Set_UP(false);
	Set_W(false);
}

void KeyInput::key_State()
{
	CDevice::GetInstance()->GetKeyboard()->GetDeviceState(sizeof(KeyState),(LPVOID)KeyState);


}

bool KeyInput::Get_A()
{
	if(DIKEYDOWN(KeyState,DIK_A))
		m_bVk_A=true;
	else
		m_bVk_A=false;

	return m_bVk_A;
}

bool KeyInput::Get_D()
{

	if(DIKEYDOWN(KeyState,DIK_D))
		m_bVk_D=true;
	else
		m_bVk_D=false;
	
	return m_bVk_D;
}

bool KeyInput::Get_UP()
{
	if(GetAsyncKeyState(VK_UP)&0x8000 && m_Up_State == true)
	{
		m_bVk_Up=true;

		m_Up_State=false;
	}

	else if(GetAsyncKeyState(VK_UP)&0x8001)					// 눌려있을때
	{
		m_bVk_Up=false;
	}

	else if (!(GetAsyncKeyState(VK_UP)&0x8000))				// 뗐을때
	{
		m_bVk_Up=false;

		m_Up_State=true;
	}

	return m_bVk_Up;
}

bool KeyInput::Get_Down()
{
	if(GetAsyncKeyState(VK_DOWN)&0x8000 && m_Down_State == true)
	{
		m_bVk_Down=true;

		m_Down_State=false;
	}

	else if(GetAsyncKeyState(VK_DOWN)&0x8001)
	{
		m_bVk_Down=false;
	}

	else if (!(GetAsyncKeyState(VK_DOWN)&0x8000))
	{
		m_bVk_Down=false;

		m_Down_State=true;
	}

	return m_bVk_Down;
}

bool KeyInput::Get_Left()
{
	if(DIKEYDOWN(KeyState,DIK_LEFT))
		m_bVk_Left = true;
	else
		m_bVk_Left = false;

	return m_bVk_Left;
}

bool KeyInput::Get_Right()
{
	if(DIKEYDOWN(KeyState,DIK_RIGHT))
		m_bVk_Right=true;
	else 
		m_bVk_Right=false;

	return m_bVk_Right;
}

bool KeyInput::Get_F()
{
	if(DIKEYDOWN(KeyState,DIK_F))
		m_bVk_F=true;
	else
		m_bVk_F=false;

	return m_bVk_F;
}


bool KeyInput::Get_R()
{
	if(DIKEYDOWN(KeyState,DIK_R))
		m_bVk_R = true;
	else
		m_bVk_R = false;

	return m_bVk_R;
}


bool KeyInput::Get_S()
{
	if(DIKEYDOWN(KeyState,DIK_S))
		m_bVk_S=true;
	else
		m_bVk_S=false;

	return m_bVk_S;
}


bool KeyInput::Get_W()
{
	if(DIKEYDOWN(KeyState,DIK_W))
		m_bVk_W=true;
	else
		m_bVk_W=false;

	return m_bVk_W;
}

bool KeyInput::Get_Enter()
{
	if(DIKEYDOWN(KeyState,DIK_RETURN))
		m_bvk_Enter = true;
	else
		m_bvk_Enter = false;

	return m_bvk_Enter;
}

bool KeyInput::Get_Space()
{
	if(DIKEYDOWN(KeyState,DIK_SPACE))
		m_bvk_Space = true;
	else
		m_bvk_Space = false;

	return m_bvk_Space;
}


bool KeyInput::Get_Esc()
{
	

	if(DIKEYDOWN(KeyState,DIK_ESCAPE)&& m_Esc_State == false)
	{
		m_bVk_Esc=true;

		m_Esc_State=true;
	}
	else if(DIKEYDOWN(KeyState,DIK_ESCAPE))
	{
		m_bVk_Esc=true;
	}
	else
	{
		m_bVk_Esc=false;
		m_Esc_State=false;
	}

	return m_bVk_Esc;
}


bool KeyInput::Get_F8()
{
	if(GetAsyncKeyState(VK_F8)&0x8000 && m_bF8_State == true)
	{
		m_bVK_F8=true;

		m_bF8_State=false;
	}

	else if(GetAsyncKeyState(VK_F8)&0x8001)					// 눌려있을때
	{
		m_bVK_F8=false;
	}

	else if (!(GetAsyncKeyState(VK_F8)&0x8000))				// 뗐을때
	{
		m_bVK_F8=false;

		m_bF8_State=true;
	}

	return m_bVK_F8;
}


bool KeyInput::Get_F7()
{
	if(GetAsyncKeyState(VK_F7)&0x8000 && m_bF7_State == true)
	{
		m_bVK_F7=true;

		m_bF7_State=false;
	}

	else if(GetAsyncKeyState(VK_F7)&0x8001)					// 눌려있을때
	{
		m_bVK_F7=false;
	}

	else if (!(GetAsyncKeyState(VK_F7)&0x8000))				// 뗐을때
	{
		m_bVK_F7=false;

		m_bF7_State=true;
	}

	return m_bVK_F7;
}