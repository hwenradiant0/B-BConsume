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

//키 정보
#define VK_A 0x41
#define VK_D 0x44
#define VK_S 0x53
#define VK_W 0x57
#define VK_R 

#define VK_F 0x46

#define TextureFileFolder  "Texture/"

#define Tick_Gb_run_minmum 0.001 //게임베이스 틱 최소값


#define Gravity 9.8/40//그라비티 값,파일 입출력시 옵션값으로 받아오게 수정
#define AirFric	0.025//공기 마찰계수#define Window_Height 600


#define Window_Width  3000//SM_CXSCREEN 로 바꾸는게 좋을듯 함 현재 모니터의 X길이
#define Window_Height 3000//SM_CYSCREEN 로 바꾸는게 좋을듯 함 현재 모니터의 Y길이

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
//맵마다 1600개를 최대치로 생각하자

#define Tile_Number1 1074 //스테이지
#define Tile_Number2 1286 //스테이지2
#define Tile_Number3 983 //스테이지3
#define Coll_TYPE_Sphere "COLL_TYPE_Sp"
#define Coll_TYPE_MMB    "COLL_TYPE_MMB"
#define MAX_SKY_TEX		6


#ifndef DSBCAPS_CTRLDEFAULT  //6.0이후 부터 없어졌으므로 define해줌 
#define DSBCAPS_CTRLDEFAULT  (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME)
#endif

#define DIKEYDOWN(data, n)    (data[n] & 0x80)	//키보드 귀찮아서 정의함
#define KEYDOWN(data, n)	  (data[n] & 0x80)

//입력값을 dB(decibel)로 바꿔주는 매크로 함수
#define DSVOLUME_TO_DB(volume)   ((DWORD)(-30*(100-volume))) 
#define DEBUG_FLOAT_MIN   0.1f


#define Player_Speed							0.2//이벤트 처리 연산용
#define Height_To_Fallen						10000.0f


#define Consume_Energy							-10		//물타일과 만날때 흡수되는 에너지
#define Charge_Energy							20			//불타일과 만날때 충전되는 에너지
#define Empty_Energy							0			//에너지가 다 떨어졌을때
#define Spontaneous_Loss_Energy					-0.2			//자연적으로 소모되는 에너지
#define Move_Consume_Energy						-0.5			//움직일때 소모되는 에너지
#define Time_Tile_Consume_Energy				-5		//타임타일과 만날때 타임타일의 떨어지는 에너지
#define Tile_Move_Distance						1			//타일이 한번 움직일때의 거리