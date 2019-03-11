#include "Collision.h"

void Plane::CaculateNormal(D3DXVECTOR3 m1,D3DXVECTOR3 m2)
{
	D3DXVECTOR3 v1 = m1 - centerPos ;
	D3DXVECTOR3 v2 = m2 - centerPos ;

	D3DXVec3Cross(&vfaceNormal,&v2,&v1);///정반대일 수도 있다.
	
}
//
CCollision::CCollision(void)
{
}


CCollision::~CCollision(void)
{
}


void CCollision::CreateMMB(D3DXVECTOR3 vMin , D3DXVECTOR3 vMax)
{
	m_CubeModel.centerPos	= (vMin + vMax)/2;
	m_CubeModel.rotateAngle = D3DXVECTOR3(0,0,0);
	m_CubeModel.scale		= D3DXVECTOR3(1,1,1);
	m_CubeModel.length		= vMax.x - vMin.x;
	m_CubeModel.depth		= vMax.z - vMin.z;
	m_CubeModel.heigth		= vMax.y - vMin.y;
	

	///////////////////앞 평면 값 입력/////////////////
	m_CubeModel.face[front].centerPos = (vMax+ D3DXVECTOR3(vMin.x,vMin.y,vMax.z))/2;
	m_CubeModel.face[front].CaculateNormal(D3DXVECTOR3(vMin.x,vMin.y,vMax.z),D3DXVECTOR3(vMax.x,vMin.y,vMax.z));	
	m_CubeModel.Degree_face[front] = m_CubeModel.face[Cube_Face::front].centerPos -m_CubeModel.centerPos;
	m_CubeModel.face[front].vfaceNormal =D3DXVECTOR3(0,0,1);
	///////////////////뒤 평면 값 입력/////////////////
	m_CubeModel.face[back].centerPos = (vMin+ D3DXVECTOR3(vMax.x,vMax.y,vMin.z))/2;
	m_CubeModel.face[back].CaculateNormal(vMin,D3DXVECTOR3(vMax.x,vMin.y,vMin.z));	
	m_CubeModel.Degree_face[back] = m_CubeModel.face[Cube_Face::back].centerPos -m_CubeModel.centerPos;
	m_CubeModel.face[back].vfaceNormal =D3DXVECTOR3(0,0,-1);
	///////////////////왼쪽 평면 값 입력/////////////////
	m_CubeModel.face[left].centerPos = (vMin+ D3DXVECTOR3(vMin.x,vMax.y,vMax.z))/2;
	m_CubeModel.face[left].CaculateNormal(vMin,D3DXVECTOR3(vMin.x,vMin.y,vMax.z));	
	m_CubeModel.Degree_face[left] = m_CubeModel.face[Cube_Face::left].centerPos -m_CubeModel.centerPos;
	m_CubeModel.face[left].vfaceNormal =D3DXVECTOR3(-1,0,0);
	///////////////////오른쪽 평면 값 입력/////////////////
	m_CubeModel.face[right].centerPos = (vMax+ D3DXVECTOR3(vMax.x,vMin.y,vMin.z))/2;
	m_CubeModel.face[right].CaculateNormal(D3DXVECTOR3(vMax.x,vMin.y,vMin.z),D3DXVECTOR3(vMax.x,vMin.y,vMax.z));	
	m_CubeModel.Degree_face[right] = m_CubeModel.face[Cube_Face::right].centerPos -m_CubeModel.centerPos;
	m_CubeModel.face[right].vfaceNormal =D3DXVECTOR3(1,0,0);
	///////////////////천장 평면 값 입력/////////////////
	m_CubeModel.face[top].centerPos = (vMax+ D3DXVECTOR3(vMin.x,vMax.y,vMin.z))/2;
	m_CubeModel.face[top].CaculateNormal(vMax,D3DXVECTOR3(vMin.x,vMax.y,vMax.z));	
	m_CubeModel.Degree_face[top] = m_CubeModel.face[Cube_Face::top].centerPos -m_CubeModel.centerPos;
	m_CubeModel.face[top].vfaceNormal =D3DXVECTOR3(0,1,0);
	///////////////////바닥 평면 값 입력/////////////////
	m_CubeModel.face[bottom].centerPos = (vMin+ D3DXVECTOR3(vMax.x,vMin.y,vMax.z))/2;
	m_CubeModel.face[bottom].CaculateNormal(vMin,D3DXVECTOR3(vMax.x,vMin.y,vMin.z));	
	m_CubeModel.Degree_face[bottom] = m_CubeModel.face[Cube_Face::bottom].centerPos -m_CubeModel.centerPos;
	m_CubeModel.face[bottom].vfaceNormal =D3DXVECTOR3(0,-1,0);
	
	
	
}
void CCollision::CreateSphere(D3DXVECTOR3 vCenter , float Rad)
{
	m_SpereModel.rad			= Rad;
	m_SpereModel.centerPos		= vCenter;
	m_SpereModel.rotateAngle	= D3DXVECTOR3(0,0,0);
	m_SpereModel.scale			= D3DXVECTOR3(1,1,1);
	
}
bool CCollision::CheckSp_B(D3DXVECTOR3 Pos,float Rad ,  Cube Box)
{
	//변화가 적용된 값 선언
	D3DXVECTOR3 Sp_Center = Pos;
	float Sp_Rad = Rad;//구의 크기는 축끼리 동일하므로

	D3DXVECTOR3 B_Center = Box.centerPos;
	float B_Depth = Box.depth*Box.scale.z;
	float B_Length = Box.length*Box.scale.x;
	float B_Height = Box.heigth*Box.scale.y;
	D3DXVECTOR3 Closest_BPoint;//박스 내에서 구와 가장 가까운 점
//일단 obb는 생각하지않고 aabb로 판단한다.
	if( Sp_Center.x<B_Center.x - B_Length/2.0f)
		Closest_BPoint.x = B_Center.x - B_Length/2.0f;
	else if(Sp_Center.x > B_Center.x + B_Length/2.0f)
		Closest_BPoint.x = B_Center.x + B_Length/2.0f;
	else
		Closest_BPoint.x = Sp_Center.x;

	if( Sp_Center.y<B_Center.y - B_Height/2.0f)
		Closest_BPoint.y = B_Center.y - B_Height/2.0f;
	else if(Sp_Center.y > B_Center.y + B_Height/2.0f)
		Closest_BPoint.y = B_Center.y + B_Height/2.0f;
	else
		Closest_BPoint.y = Sp_Center.y;

	if( Sp_Center.z<B_Center.z - B_Depth/2.0f)
		Closest_BPoint.z = B_Center.z - B_Depth/2.0f;
	else if(Sp_Center.z > B_Center.z + B_Depth/2.0f)
		Closest_BPoint.z = B_Center.z + B_Depth/2.0f;
	else
		Closest_BPoint.z = Sp_Center.z;

	D3DXVECTOR3 vPush = Sp_Center - Closest_BPoint;

	float fDistDist = D3DXVec3Dot(&vPush,&vPush);

	if(fDistDist>Sp_Rad*Sp_Rad)//비교값이 필요하므로 계산량이 많은 루트를 안쓰고 먼저 판단한다.
		return false;

	
	return true;
}

bool CCollision::CheckSp_B(Sphere Ball ,  Cube Box, D3DXVECTOR3*Value)
{
	//변화가 적용된 값 선언
	D3DXVECTOR3 Sp_Center = Ball.centerPos;
	float Sp_Rad = Ball.rad*Ball.scale.x;//구의 크기는 축끼리 동일하므로

	D3DXVECTOR3 B_Center = Box.centerPos;
	float B_Depth = Box.depth*Box.scale.z;
	float B_Length = Box.length*Box.scale.x;
	float B_Height = Box.heigth*Box.scale.y;
	D3DXVECTOR3 Closest_BPoint;//박스 내에서 구와 가장 가까운 점
//일단 obb는 생각하지않고 aabb로 판단한다.
	if( Sp_Center.x<B_Center.x - B_Length/2.0f)
		Closest_BPoint.x = B_Center.x - B_Length/2.0f;
	else if(Sp_Center.x > B_Center.x + B_Length/2.0f)
		Closest_BPoint.x = B_Center.x + B_Length/2.0f;
	else
		Closest_BPoint.x = Sp_Center.x;

	if( Sp_Center.y<B_Center.y - B_Height/2.0f)
		Closest_BPoint.y = B_Center.y - B_Height/2.0f;
	else if(Sp_Center.y > B_Center.y + B_Height/2.0f)
		Closest_BPoint.y = B_Center.y + B_Height/2.0f;
	else
		Closest_BPoint.y = Sp_Center.y;

	if( Sp_Center.z<B_Center.z - B_Depth/2.0f)
		Closest_BPoint.z = B_Center.z - B_Depth/2.0f;
	else if(Sp_Center.z > B_Center.z + B_Depth/2.0f)
		Closest_BPoint.z = B_Center.z + B_Depth/2.0f;
	else
		Closest_BPoint.z = Sp_Center.z;

	D3DXVECTOR3 vPush = Sp_Center - Closest_BPoint;

	float fDistDist = D3DXVec3Dot(&vPush,&vPush);

	if(fDistDist>Sp_Rad*Sp_Rad)//비교값이 필요하므로 계산량이 많은 루트를 안쓰고 먼저 판단한다.
		return false;

	float fPush;
	if(Closest_BPoint == Sp_Center)//만약 구의 중심이 박스 내에 있다면 저장된 충돌 교점을 이용해 계산해야한다.
	{
		//Test
		//Ball.collisionPoint = D3DXVECTOR3(0,108,60);
		
		//MessageBox(NULL,"내부 진입","충돌",MB_OK);
		vPush = Ball.collisionPoint - Ball.centerPos;
		fPush = sqrt(D3DXVec3Dot(&vPush,&vPush)) + Ball.rad;

		if(D3DXVec3Dot(&vPush,&vPush)>1.f)//여기 아님
		D3DXVec3Normalize(&vPush,&vPush);
		
	}
	else
	{
		fPush = Sp_Rad - sqrt(fDistDist);
		if(D3DXVec3Dot(&vPush,&vPush)>1.f)//여기 아님
		D3DXVec3Normalize(&vPush,&vPush);
		
	}

	Value->x = vPush.x *fPush;
	Value->y = vPush.y *fPush;
	Value->z = vPush.z *fPush;
	return true;
}


bool CCollision::CheckSp_B(Sphere Ball ,  Cube Box, D3DXVECTOR3*Value,D3DXVECTOR3*PlaneNormal)
{
	//변화가 적용된 값 선언
	D3DXVECTOR3 Sp_Center = Ball.centerPos;
	float Sp_Rad = Ball.rad*Ball.scale.x;//구의 크기는 축끼리 동일하므로

	D3DXVECTOR3 B_Center = Box.centerPos;
	float B_Depth = Box.depth*Box.scale.z;
	float B_Length = Box.length*Box.scale.x;
	float B_Height = Box.heigth*Box.scale.y;
	D3DXVECTOR3 Closest_BPoint;//박스 내에서 구와 가장 가까운 점
//일단 obb는 생각하지않고 aabb로 판단한다.
	if( Sp_Center.x<B_Center.x - B_Length/2.0f)
		Closest_BPoint.x = B_Center.x - B_Length/2.0f;
	else if(Sp_Center.x > B_Center.x + B_Length/2.0f)
		Closest_BPoint.x = B_Center.x + B_Length/2.0f;
	else
		Closest_BPoint.x = Sp_Center.x;

	if( Sp_Center.y<B_Center.y - B_Height/2.0f)
		Closest_BPoint.y = B_Center.y - B_Height/2.0f;
	else if(Sp_Center.y > B_Center.y + B_Height/2.0f)
		Closest_BPoint.y = B_Center.y + B_Height/2.0f;
	else
		Closest_BPoint.y = Sp_Center.y;

	if( Sp_Center.z<B_Center.z - B_Depth/2.0f)
		Closest_BPoint.z = B_Center.z - B_Depth/2.0f;
	else if(Sp_Center.z > B_Center.z + B_Depth/2.0f)
		Closest_BPoint.z = B_Center.z + B_Depth/2.0f;
	else
		Closest_BPoint.z = Sp_Center.z;

	D3DXVECTOR3 vPush = Sp_Center - Closest_BPoint;

	float fDistDist = D3DXVec3Dot(&vPush,&vPush);

	if(fDistDist>Sp_Rad*Sp_Rad)//비교값이 필요하므로 계산량이 많은 루트를 안쓰고 먼저 판단한다.
		return false;

	float fPush;
	if(Closest_BPoint == Sp_Center)//만약 구의 중심이 박스 내에 있다면 저장된 충돌 교점을 이용해 계산해야한다.
	{
		//Test
		//Ball.collisionPoint = D3DXVECTOR3(0,108,60);
		
		//MessageBox(NULL,"내부 진입","충돌",MB_OK);
		vPush = Ball.collisionPoint - Ball.centerPos;
		fPush = sqrt(D3DXVec3Dot(&vPush,&vPush)) + Ball.rad;

		D3DXVECTOR3 vecCenterToCenter = Ball.collisionPoint - Box.centerPos;

		D3DXVec3Normalize(&vecCenterToCenter,&vecCenterToCenter);
		(*PlaneNormal) = Find_IntersectPlane(Ball.collisionPoint+(100.f*vecCenterToCenter),-vecCenterToCenter,Box);//임의의 직선상의 박스바깥 점
	}
	else
	{
		fPush = Sp_Rad - sqrt(fDistDist);
		if(D3DXVec3Dot(&vPush,&vPush)>1.f)//여기 아님
		D3DXVec3Normalize(&vPush,&vPush);
		D3DXVECTOR3 vecCenterToCenter2 = Sp_Center - Box.centerPos;
		(*PlaneNormal) = Find_IntersectPlane(Sp_Center,-vecCenterToCenter2,Box);
		
	}

	Value->x = vPush.x *fPush;
	Value->y = vPush.y *fPush;
	Value->z = vPush.z *fPush;
	return true;
}


bool CCollision::CheckSp_Sp(Sphere Ball , Sphere Ball2,D3DXVECTOR3*Value)
{
	float Degree = D3DXVec3Dot(&Ball.centerPos,&Ball2.centerPos);
	float PushOut;
	if(Degree>((Ball.rad+Ball2.rad)*(Ball.rad+Ball2.rad)))
	return false;

	
	*Value = Ball.centerPos - Ball2.centerPos;
	PushOut = Ball.rad + Ball2.rad -sqrt(D3DXVec3Dot(Value,Value));
	D3DXVec3Normalize(Value,Value);
	*Value = (*Value) * PushOut;
	return true;
	
}
bool CCollision::AABBvec_B(Cube Box, D3DXVECTOR3 Point, float error )
{
	

	D3DXVECTOR3 B_Center = Box.centerPos;
	float B_Depth = Box.depth*Box.scale.z;
	float B_Length = Box.length*Box.scale.x;
	float B_Height = Box.heigth*Box.scale.y;
	D3DXVECTOR3 Closest_BPoint;//박스 내에서 구와 가장 가까운 점
//일단 obb는 생각하지않고 aabb로 판단한다.
	if( 
		Point.x		>=	B_Center.x -error - (B_Length/2.0f) && 
		Point.x		<=	B_Center.x +error  + (B_Length/2.0f) &&
		Point.y		>=	B_Center.y -error- (B_Height/2.0f) &&
		Point.y		<=	B_Center.y +error+ (B_Height/2.0f) &&
		Point.z		>=	B_Center.z -error- (B_Depth/2.0f) &&
		Point.z		<=	B_Center.z +error+ (B_Depth/2.0f)
		)
		return true;

	return false;
		
}
D3DXVECTOR3* CCollision::Find_Intersection_Plane_To_VanRay(D3DXVECTOR3 Point,D3DXVECTOR3 Dirvec,D3DXVECTOR3 Normal,float D)
{
	float Delta;
	if(D3DXVec3Dot(&Dirvec,&Dirvec)>1.f)//여기 아님
	D3DXVec3Normalize(&Dirvec,&Dirvec);
	if(D3DXVec3Dot(&Normal,&Normal)>1.f)//여기 아님
	D3DXVec3Normalize(&Normal,&Normal);

	float NV = D3DXVec3Dot(&Normal,&Dirvec);

	if(NV==0.f)
		return NULL;
	float NQ= D3DXVec3Dot(&Point,&Normal);

	Delta = -(NQ+D)/NV;
	if(Delta<0)
		return NULL;
	D3DXVECTOR3 Value=Point+(Dirvec*Delta);
	return &Value;
}
bool	CCollision::Find_Intersection_PlaneFromBox(Sphere Ball,Cube Box,D3DXVECTOR3 intersecPoint,int*FaceNum)
{
	D3DXVECTOR3 DirVec;
	float	D;
	D3DXVECTOR3 *InterSectionP;
	for(int fn=0;fn<6;fn++)
	{
		DirVec =intersecPoint- Ball.centerPos ;
		if(D3DXVec3Dot(&Box.face[0].vfaceNormal,&Box.face[0].vfaceNormal)>1.f)//여기 아님
		D3DXVec3Normalize(&Box.face[0].vfaceNormal,&Box.face[0].vfaceNormal);
		D = -D3DXVec3Dot(&Box.face[0].vfaceNormal,&Box.face[0].centerPos);
		InterSectionP = Find_Intersection_Plane_To_VanRay(Ball.centerPos,DirVec,Box.face[0].vfaceNormal,D);
		if(InterSectionP != NULL)
		{
			if(AABBvec_B(Box,intersecPoint,1.0f))
			{
				*FaceNum  = fn;
				return true;
			}
		}
	}
	return false;
}
void CCollision::ReviceSRT(D3DXVECTOR3 S,D3DXVECTOR3 R,D3DXVECTOR3 T)
{
	
	m_SpereModel.centerPos			=	T;	
	m_SpereModel.rotateAngle		=	R;
	m_SpereModel.scale				=	S;
	

	
	m_PlaneModel.centerPos			=	T;	
	m_PlaneModel.rotateAngle		=	R;
	m_PlaneModel.scale				=	S;

	m_CubeModel.centerPos			=	T;	
	m_CubeModel.rotateAngle			=	R;
	m_CubeModel.scale				=	S;
	

	for(int i=0;i<6;i++)
	{
		
		m_CubeModel.face[i].centerPos		= m_CubeModel.centerPos +m_CubeModel.Degree_face[i];
		m_CubeModel.face[i].rotateAngle		= R;
		m_CubeModel.face[i].scale			= S;
	
	}
}

D3DXVECTOR3 CCollision::Find_Intersection_Box(D3DXVECTOR3 Point,D3DXVECTOR3 Vector,Cube Box)
{
	D3DXVECTOR3 normalvec;
	float NV;
	float Distance=0;;
	float t;
	float d;
	for(int i=0;i<6;i++)
	{
		normalvec= Box.face[i].vfaceNormal;
		if(D3DXVec3Dot(&normalvec,&normalvec)>1.f)//여기 아님
		D3DXVec3Normalize(&normalvec,&normalvec);
		if(D3DXVec3Dot(&Vector,&Vector)>1.f)//여기 아님
		D3DXVec3Normalize(&Vector,&Vector);
		NV = D3DXVec3Dot(&Vector,&normalvec);
		if(NV !=0)//0이면 서로 평행
		{
			d = -D3DXVec3Dot(&Box.face[i].centerPos,&Box.face[i].vfaceNormal);
			t= - (D3DXVec3Dot(&Point,&normalvec) + d)/NV;
			D3DXVECTOR3 a =Point+(Vector*t);
			if(t>=0 && AABBvec_B(Box,Point+(Vector*t),0.05f))//음수는 대상이 아니다.  교점은 박스내에 있어야 한다.  
			{
				if(Distance==0 ||Distance>t )//디스턴스는 최소값만 받는다.
				{
				Distance = t;
				}
			}
		}

	
	}
	return Point+(Vector*Distance);
}
D3DXVECTOR3 CCollision::Find_IntersectPlane(D3DXVECTOR3 Point,D3DXVECTOR3 Vector,Cube Box)
{
	D3DXVECTOR3 normalvec;
	float NV;
	float Distance=600;//솔직히 이걸 넘고서 충돌이라 할수는 없을 것
	int Interscet_Point= -1;
	int cPoint=0;
	float t;
	float d;
	int aa;
	for(int i=0;i<6;i++)
	{
		normalvec= Box.face[i].vfaceNormal;
		if(D3DXVec3Dot(&normalvec,&normalvec)>1.f)//여기 아님
		D3DXVec3Normalize(&normalvec,&normalvec);
		if(D3DXVec3Dot(&Vector,&Vector)>1.f)//여기 아님
		D3DXVec3Normalize(&Vector,&Vector);
		NV = D3DXVec3Dot(&Vector,&normalvec);
		if(NV !=0)//0이면 서로 평행
		{
			d = -D3DXVec3Dot(&Box.face[i].centerPos,&Box.face[i].vfaceNormal);
			t= - (D3DXVec3Dot(&Point,&normalvec) + d)/NV;
			D3DXVECTOR3 a =Point+(Vector*t);
			if(t>0 && AABBvec_B(Box,Point+(Vector*t),0.05f))//음수는 대상이 아니다.  교점은 박스내에 있어야 한다.  
			{				
				if( Distance>=t )//디스턴스는 최소값만 받는다.
				{						
					if(Distance == t)				
 						aa = 5;

					Distance = t;
					Interscet_Point=i;
				
				}
			}
		}


	}
	if(Interscet_Point != -1)
	{
		return Box.face[Interscet_Point].vfaceNormal;
	}
	else 	
	{
		return D3DXVECTOR3(0,0,0);
	}

}
void CCollision::Set_CP(D3DXVECTOR3 CCP)
{
	m_SpereModel.collisionPoint = CCP;
	m_CubeModel.collisionPoint = CCP;
	m_PlaneModel.collisionPoint = CCP;
}


bool CCollision::AABB_B_B(Cube Box, Cube Box2)
{
	float Max1_x=Box.centerPos.x+(Box.length/2);
	float Min1_x=Box.centerPos.x-(Box.length/2);

	float Max2_x=Box2.centerPos.x+(Box2.length/2);
	float Min2_x=Box2.centerPos.x-(Box2.length/2);

	if(max(Min1_x,Min2_x) >min(Max1_x,Max2_x))
		return false;

	float Max1_y=Box.centerPos.y+(Box.heigth/2);
	float Min1_y=Box.centerPos.y-(Box.heigth/2);

	float Max2_y=Box2.centerPos.y+(Box2.heigth/2);
	float Min2_y=Box2.centerPos.y-(Box2.heigth/2);

	if(max(Min1_y,Min2_y) >min(Max1_y,Max2_y))
		return false;

	float Max1_z=Box.centerPos.z+(Box.depth/2);
	float Min1_z=Box.centerPos.z-(Box.depth/2);

	float Max2_z=Box2.centerPos.z+(Box2.depth/2);
	float Min2_z=Box2.centerPos.z-(Box2.depth/2);

	if(max(Min1_z,Min2_z) >min(Max1_z,Max2_z))
		return false;

	

	

	

	

	

	

	return true;
}