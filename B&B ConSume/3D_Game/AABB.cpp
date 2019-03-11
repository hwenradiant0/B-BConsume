#include "Device.h"
//완벽판이라고 붙인 이유는..제 나름대로 완벽하다는 뜻에서 붙였습니다..;;
//아! 그리고 저번 강좌때 약간 버그가 있는 버젼을 올려서 죄송합니다..꾸벅..
//
//	자 그럼 AABB에 대한 설명을 다시 한번 드리겠습니다. AABB는 축 정렬 경계박스입니다.
//	뭐..무지 어려운 말을 섞어 놓은 것 같지만..실제로 보면 별거 아닙니다. 한 오브젝트에
//	대해 x,y,z축에 각각 평행한 최소점과 최대점을 구하여 연결시킨 6면체를 사용한 충돌체크 방식입니다.
//	다시 한번 말하면 오브젝트의 모든 정점을 조사하여 각 정점들의 세 개의 선분(x,y,z)의 최대 최소값을 구해서 정육면체를 만든다는 것이죠 
//	그럼 그 정육면체에 부딪히면 충돌이 되는 거죠.. 울퉁불퉁한 물체에 AABB방식을 쓰면 충돌체크가 어색하게 되겠지만 집으나 정육면체에
//	가까운 물체에 AABB를 쓰면 사실적인 충돌체크가 될것입니다. 사실 저도 AABB에 깊숙히 들어가보질 못해서 설명은 이것으로 마치겠습니다.
//	AABB에 대해 더 알고 싶다면 책을 찾아보시길 권합니다.
//
//	저 위에 보면 모든 정점을 조사해서 세개의 선분(X,Y,Z)의 최대 최소값을 구해서 큰 정육면체를 만든다는게 있죠..
//	그런데 그렇게 하면 울퉁불퉁한 모양의 오브젝트나 울퉁불퉁한 오브젝트 아님.. 원 모양의 오브젝트는 충돌체크가 이상하게 된다는 단점이 있죠.. 
//	그래서 생각해낸 것이 폴리곤 단위로 정점을 조사해서 최대 값과 최소 값을 구해서 AABB를 만드는 거죠.. 그렇게 하면 어떠한 물체라도 완벽한
//	충돌체크가 가능하게 되는 거죠.. 음.. 잘 이해가 안되신다면 천천히 따라오면서 이해하세요
//
//	자 Directx SDK에 CD3DFile을 봅시다. CD3DFile은 아마 메시를 불러와서 랜더링 할 수 있게 해주는 것 같습니다.
//	그럼 이 CD3DFIle에 우선 CreateCollision이라는 함수를 만들어서 폴리곤에 AABB를 만들어서 충돌이 일어나게 해봅시다

	HRESULT CD3DMesh::CreateCollision( LPDIRECT3DDEVICE9 pd3dDevice )
{
	if( NULL == m_pSysMemMesh )
		return E_FAIL;

	LPD3DXMESH CloneMesh;
	//이 부분은 Create에서 메시의 정보가 들어있는(?) m_pSysMemMesh의 메쉬의 복사하는 것입니다. 
	//인자의 첫번째 D3DXMESH_SYSTEMMEM는 인덱스와 버텍스를 얻어온다는 것입니다. 두번째는 정점의 포맷입니다.
	
	if( SUCCEEDED(m_pSysMemMesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, D3DFVF_XYZ, pd3dDevice, &CloneMesh ) ) )
	{
		int FaceNum = CloneMesh->GetNumFaces();
		int VertexNum = CloneMesh->GetNumVertices();
		CollisionVertex* ColVer;
		if( SUCCEEDED(CloneMesh->LockVertexBuffer(D3DLOCK_READONLY,(VOID**)&ColVer) ) )//메시에 락을 걸어서 각 버텍스를 얻어옵니다.
		{
			WORD* index;
			if( SUCCEEDED(CloneMesh->LockIndexBuffer( D3DLOCK_READONLY,(VOID**)&index) ) )
			{
				m_CollisionData = new SCollisionData(FaceNum);
				int i;
				for( i = 0; i < FaceNum; i++ )
				{
					FindMinMaxVerPos( i, ColVer[index[i*3+0]].x, ColVer[index[i*3+0]].y, ColVer[index[i*3+0]].z,
						ColVer[index[i*3+1]].x, ColVer[index[i*3+1]].y, ColVer[index[i*3+1]].z,
						ColVer[index[i*3+2]].x, ColVer[index[i*3+2]].y, ColVer[index[i*3+2]].z ); //폴리곤 단위로 최소와 최대를 구합니다.
				}
			}
			CloneMesh->UnlockVertexBuffer();
		}
		CloneMesh->Release();
	}
	return S_OK;
}

//위의 코드를 다시 설명하자면 CloneMeshFVF를 통해 메시를 복사하고 복사한 메시에서 버텍스를 얻어옵니다.
//	그리고 FindMinMaxVerPos를 통해 각 폴리곤의 제일 큰 Pos와 제일 작은 Pos를 구해 AABB를 만듭니다.
	void CD3DMesh::FindMinMaxVerPos( int FaceNum, float Vertex1X, float Vertex1Y, float Vertex1Z,
	float Vertex2X, float Vertex2Y, float Vertex2Z,
	float Vertex3X, float Vertex3Y, float Vertex3Z )
{
	if( Vertex1X < Vertex2X )
	{
		if( Vertex1X < Vertex3X )
		{
			m_CollisionData->MinVertexPos[FaceNum].x = Vertex1X;
		}else
		{
			m_CollisionData->MinVertexPos[FaceNum].x = Vertex3X;
		}
	}else{
		if( Vertex2X < Vertex3X )
		{
			m_CollisionData->MinVertexPos[FaceNum].x = Vertex2X;
		}else
		{
			m_CollisionData->MinVertexPos[FaceNum].x = Vertex3X;
		}
	}

	if( Vertex1Y < Vertex2Y )
	{
		if( Vertex1Y < Vertex3Y )
		{
			m_CollisionData->MinVertexPos[FaceNum].y = Vertex1Y;
		}else
		{
			m_CollisionData->MinVertexPos[FaceNum].y = Vertex3Y;
		}
	}else{
		if( Vertex2Y < Vertex3Y )
		{
			m_CollisionData->MinVertexPos[FaceNum].y = Vertex2Y;
		}else
		{
			m_CollisionData->MinVertexPos[FaceNum].y = Vertex3Y;
		}
	}

	if( Vertex1Z < Vertex2Z )
	{
		if( Vertex1Z < Vertex3Z )
		{
			m_CollisionData->MinVertexPos[FaceNum].z = Vertex1Z;
		}else
		{
			m_CollisionData->MinVertexPos[FaceNum].z = Vertex3Z;
		}
	}else{
		if( Vertex2Z < Vertex3Z )
		{
			m_CollisionData->MinVertexPos[FaceNum].z = Vertex2Z;
		}else
		{
			m_CollisionData->MinVertexPos[FaceNum].z = Vertex3Z;
		}
	}



	if( Vertex1X > Vertex2X )
	{
		if( Vertex1X > Vertex3X )
		{
			m_CollisionData->MaxVertexPos[FaceNum].x = Vertex1X;
		}else
		{
			m_CollisionData->MaxVertexPos[FaceNum].x = Vertex3X;
		}
	}else{
		if( Vertex2X > Vertex3X )
		{
			m_CollisionData->MaxVertexPos[FaceNum].x = Vertex2X;
		}else
		{
			m_CollisionData->MaxVertexPos[FaceNum].x = Vertex3X;
		}
	}

	if( Vertex1Y > Vertex2Y )
	{
		if( Vertex1Y > Vertex3Y )
		{
			m_CollisionData->MaxVertexPos[FaceNum].y = Vertex1Y;
		}else
		{
			m_CollisionData->MaxVertexPos[FaceNum].y = Vertex3Y;
		}
	}else{
		if( Vertex2Y > Vertex3Y )
		{
			m_CollisionData->MaxVertexPos[FaceNum].y = Vertex2Y;
		}else
		{
			m_CollisionData->MaxVertexPos[FaceNum].y = Vertex3Y;
		}
	}

	if( Vertex1Z > Vertex2Z )
	{
		if( Vertex1Z > Vertex3Z )
		{
			m_CollisionData->MaxVertexPos[FaceNum].z = Vertex1Z;
		}else
		{
			m_CollisionData->MaxVertexPos[FaceNum].z = Vertex3Z;
		}
	}else{
		if( Vertex2Z > Vertex3Z )
		{
			m_CollisionData->MaxVertexPos[FaceNum].z = Vertex2Z;
		}else
		{
			m_CollisionData->MaxVertexPos[FaceNum].z = Vertex3Z;
		}
	}
}
//위의 코드는 별다른 설명을 드리지 않겠습니다.
//	이제 최소의 폴리곤의 최대, 최소Pos를 얻었습니다.
//	그런데 만약 이 오브젝트가 Translation이나 Scaling, Rotation을 한다면 폴리곤의 최대, 최소Pos는 당연히 바뀌겠지요..
//	그러면 최소의 폴리곤의 최대, 최소Pos를 다시 얻어와야 겠지요.. 이것은 D3DXVec3TransformCoord를 통해 해결할수 있습니다.
//	그럼 Translation, Scaling, Rotation를 한 폴리곤의 최소 Pos를 구하는 함수를 보여드리겠습니다.



	D3DXVECTOR3 CD3DMesh::GetMinCollisionPos( int FaceNum, D3DXVECTOR3& Pos, D3DXVECTOR3& Scale, D3DXVECTOR3& Rotate )
{
	D3DXVECTOR3 ReturnPos;
	D3DXVECTOR3 MinCollsionPos;

	D3DXMATRIX matTrans, matScale, matRotate, matWorld;
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixScaling( &matScale, Scale.x, Scale.y ,Scale.z );

	D3DXMatrixRotationYawPitchRoll( &matRotate, Rotate.y, Rotate.x, Rotate.z );

	D3DXMatrixMultiply( &matWorld, &matScale, &matRotate );
	D3DXMatrixTranslation( &matTrans, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply( &matWorld, &matWorld,  &matTrans );

	MinCollsionPos.x = m_CollisionData->MinVertexPos[FaceNum].x;
	MinCollsionPos.y = m_CollisionData->MinVertexPos[FaceNum].y;
	MinCollsionPos.z = m_CollisionData->MinVertexPos[FaceNum].z;

	D3DXVec3TransformCoord( &ReturnPos, &MinCollsionPos, &matWorld );

	return ReturnPos;
}

//이렇게 하면 각 폴리곤의 최대, 최소 Pos를 구했습니다.
	//이젠 이걸 가지고 충돌체크를 하면 3D충돌체크는 모두 끝이 나지요..ㅎㅎ


	bool CQuadTree::CollisionCheck( D3DXVECTOR3 Pos )
{
	BYTE  i, j;
	int k;
	bool bYCollisionCheck = TRUE;

	for( i = 0; i < MAXMESHKINDCNT ; i++ )
	{
		bYCollisionCheck = TRUE;
		for( j = 0; j < m_MeshDataList[i].MeshCount; j++ )
		{
			for( k = 0; k < m_MeshDataList[i].FaceNum[j]; k++ )
			{
				if( bYCollisionCheck )
				{
					if( Pos.x > m_MeshDataList[i].MinCollisionPos[j][k].x &&
						Pos.y + 1.0f > m_MeshDataList[i].MinCollisionPos[j][k].y &&
						Pos.z > m_MeshDataList[i].MinCollisionPos[j][k].z &&
						Pos.x < m_MeshDataList[i].MaxCollisionPos[j][k].x &&
						Pos.y < m_MeshDataList[i].MaxCollisionPos[j][k].y &&
						Pos.z < m_MeshDataList[i].MaxCollisionPos[j][k].z )
						return FALSE;
				}
			}


		}
	}
	return TRUE;
}
//위의 코드는 바로 충돌체크를 하는 부분입니다. Pos가 각 폴리곤의 최소 Pos보다 크고 최대 Pos안에 있으면
//	FALSE를 리턴해 충돌이 일어났다는 걸 알려주죠.. 
//	이렇게 하면 충돌체크가 되는 것이죠.. 만약에 충돌체크가 이상하게 일어난다면 AABB를 그려보세요 
//	그러면 뭐가 문제인지 금방 알게 될겁니다.. 그럼 전 이만~