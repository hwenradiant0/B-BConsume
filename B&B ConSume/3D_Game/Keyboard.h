#pragma once
#include "Device.h"
class KeyInput
{

private:
	bool				m_bVk_Up;
	bool				m_bVk_Up_press;
	bool				m_bVk_Down;
	bool				m_bVk_Right;
	bool				m_bVk_Left;
	bool				m_bVk_W;
	bool				m_bVk_S;
	bool				m_bVk_A;
	bool				m_bVk_D;
	bool				m_bVk_R;
	bool				m_bVk_F;
	bool				m_bvk_Enter;
	bool				m_bvk_Space;

	bool				m_Up_State;		// True일때 키입력을 받는다. False일때 키입력을 받지 않는다
	bool				m_Down_State;	// True일때 키입력을 받는다. False일때 키입력을 받지 않는다
	bool				m_bVk_Esc;
	bool				m_Esc_State;

	bool				m_bVK_F8;
	bool				m_bF8_State;
	bool				m_bVK_F7;
	bool				m_bF7_State;

	BYTE KeyState[256];	

public:
	KeyInput(void);
	~KeyInput(void);


	bool Get_UP();
	void Set_UP(bool Up){m_bVk_Up=Up;};
	void UP_press();
	bool Get_Down();
	void Set_Down(bool Down){m_bVk_Down=Down;};
	bool Get_Right();
	void Set_Right(bool Right){m_bVk_Right=Right;};
	bool Get_Left();
	void Set_Left(bool Left){m_bVk_Left=Left;};
	bool Get_W();
	void Set_W(bool W){m_bVk_W=W;};
	bool Get_S();
	void Set_S(bool S){m_bVk_S=S;};
	bool Get_A();
	void Set_A(bool A){m_bVk_A=A;};
	bool Get_D();
	void Set_D(bool D){m_bVk_D=D;};
	bool Get_R();
	void Set_R(bool R){m_bVk_R=R;};
	bool Get_F();
	void Set_F(bool F){m_bVk_F=F;};
	bool Get_Space();
	void Set_Space(bool Space){m_bvk_Space=Space;};
	bool Get_Enter();
	void Set_Enter(bool Enter){m_bvk_Enter=Enter;};
	bool Get_Esc();
	void Set_Esc(bool ESC){m_bVk_Esc=ESC;};
	bool Get_F8();
	void Set_F8(bool F8){m_bVK_F8=F8;};
	bool Get_F7();
	void Set_F7(bool F7){m_bVK_F7=F7;};

	void Key_False();

	void Key_input_Init();
	void key_State();
	BYTE Get_Key_state();


};

