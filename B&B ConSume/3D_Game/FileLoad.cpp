#include "FileLoad.h"


CFileLoad::CFileLoad(void)
{
	m_ix = 0;
	m_iy = 0;
	m_iz = 0;
	m_iMaterial = 0;

	

	Number = 0;
}

void CFileLoad::Stage_Read1(char* filename, Tile_Data* a)
{
	////파일 출력 (읽기)

	FILE *read;

	read = fopen( filename ,"r");
	
	for(int i = 0; i<Tile_Number1 ; i++)
	{
		if( read != false)
		{
			fscanf(read, "%f %f %f %d " , &m_ix,&m_iy,&m_iz, &m_iMaterial);
			Number ++;
			a[i].ix = m_ix;
			a[i].iy = m_iy;
			a[i].iz = m_iz;
			a[i].iMaterial = m_iMaterial;
		}
	}
	fclose(read);
}

void CFileLoad::Stage_Read2(char* filename, Tile_Data* a)
{
	////파일 출력 (읽기)

	FILE *read;

	read = fopen( filename ,"r");
	
	for(int i = 0; i<Tile_Number2 ; i++)
	{
		if( read != false)
		{
			fscanf(read, "%f %f %f %d " , &m_ix,&m_iy,&m_iz, &m_iMaterial);
			Number ++;
			a[i].ix = m_ix;
			a[i].iy = m_iy;
			a[i].iz = m_iz;
			a[i].iMaterial = m_iMaterial;
		}
	}
	fclose(read);
}

void CFileLoad::Stage_Read3(char* filename, Tile_Data* a)
{
	////파일 출력 (읽기)

	FILE *read;

	read = fopen( filename ,"r");
	
	for(int i = 0; i<Tile_Number3 ; i++)
	{
		if( read != false)
		{
			fscanf(read, "%f %f %f %d " , &m_ix,&m_iy,&m_iz, &m_iMaterial);
			Number ++;
			a[i].ix = m_ix;
			a[i].iy = m_iy;
			a[i].iz = m_iz;
			a[i].iMaterial = m_iMaterial;
		}
	}
	fclose(read);
}

void CFileLoad::Title_Read(char * filename , title_Data *a)
{
	FILE *read;
	read = fopen( filename ,"r");

	for(int i = 0; i<700 ; i++)
	{
		if( read != false)
		{
			fscanf(read, "%f %f %f %d " , &m_x,&m_y,&m_z, &m_Material);
			a[i].ix = m_x;
			a[i].iy = m_y;
			a[i].iz = m_z;
			a[i].iMaterial = m_Material;
		}
	}
	fclose(read);


}