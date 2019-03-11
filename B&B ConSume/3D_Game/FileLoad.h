#pragma once
#include <fstream>
#include "Define.h"
#include "ZFLog.h"

struct Tile_Data
{
	float ix;
	float iy;
	float iz;
	int iMaterial;
};

struct title_Data
{
	float ix;
	float iy;
	float iz;
	int iMaterial;
	
};


class CFileLoad
{
public:

	float m_ix;
	float m_iy;
	float m_iz;
	int m_iMaterial;
	int m_iHardness;

	float m_x;
	float m_y;
	float m_z;
	int m_Material;

	int Number;

	CFileLoad(void);
	

	void Stage_Read1(char* filename, Tile_Data* a);
	void Stage_Read2(char* filename, Tile_Data* a);
	void Stage_Read3(char* filename, Tile_Data* a);

	void Title_Read(char * filename , title_Data *a);
	int Get_x();


};
