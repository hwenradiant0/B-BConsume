#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#include <list>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma warning( default : 4996 )

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Dsound.lib ")
#pragma comment(lib, "dinput8.lib ")
#pragma comment(lib, "dxguid.lib")

#define Game_Title  "B&B ConSume"

//Ű ����
#define VK_A 0x41
#define VK_D 0x44
#define VK_S 0x53
#define VK_W 0x57
#define VK_R 

#define VK_F 0x46

#define TextureFileFolder  "Texture/"

#define Tick_Gb_run_minmum 0.001 //���Ӻ��̽� ƽ �ּҰ�


#define Gravity 9.8/40//�׶��Ƽ ��,���� ����½� �ɼǰ����� �޾ƿ��� ����
#define AirFric	0.025//���� �������#define Window_Height 600


#define Window_Width  3000//SM_CXSCREEN �� �ٲٴ°� ������ �� ���� ������� X����
#define Window_Height 3000//SM_CYSCREEN �� �ٲٴ°� ������ �� ���� ������� Y����

#define Ball_Radius   10
#define Ball_Slices   8
#define Ball_Stacks   8

#define Tile_Size			20

#define Max_Velocity_X		4

#define Max_Velocity_Y		6

#define Max_Velocity_Z		4

#define Command_Cube		"The Cube"
#define Command_Sphere		"The Sphere"
#define Command_Cylinder	"The Cylinder"
//�ʸ��� 1600���� �ִ�ġ�� ��������

#define Tile_Number1 1074 //��������
#define Tile_Number2 1286 //��������2
#define Tile_Number3 983 //��������3
#define Coll_TYPE_Sphere "COLL_TYPE_Sp"
#define Coll_TYPE_MMB    "COLL_TYPE_MMB"
#define MAX_SKY_TEX		6


#ifndef DSBCAPS_CTRLDEFAULT  //6.0���� ���� ���������Ƿ� define���� 
#define DSBCAPS_CTRLDEFAULT  (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME)
#endif

#define DIKEYDOWN(data, n)    (data[n] & 0x80)	//Ű���� �����Ƽ� ������
#define KEYDOWN(data, n)	  (data[n] & 0x80)

//�Է°��� dB(decibel)�� �ٲ��ִ� ��ũ�� �Լ�
#define DSVOLUME_TO_DB(volume)   ((DWORD)(-30*(100-volume))) 
#define DEBUG_FLOAT_MIN   0.1f


#define Player_Speed							0.2//�̺�Ʈ ó�� �����
#define Height_To_Fallen						10000.0f


#define Consume_Energy							-10		//��Ÿ�ϰ� ������ ����Ǵ� ������
#define Charge_Energy							20			//��Ÿ�ϰ� ������ �����Ǵ� ������
#define Empty_Energy							0			//�������� �� ����������
#define Spontaneous_Loss_Energy					-0.2			//�ڿ������� �Ҹ�Ǵ� ������
#define Move_Consume_Energy						-0.5			//�����϶� �Ҹ�Ǵ� ������
#define Time_Tile_Consume_Energy				-5		//Ÿ��Ÿ�ϰ� ������ Ÿ��Ÿ���� �������� ������
#define Tile_Move_Distance						1			//Ÿ���� �ѹ� �����϶��� �Ÿ�