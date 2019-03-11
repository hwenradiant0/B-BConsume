#include "Device.h"
//�Ϻ����̶�� ���� ������..�� ������� �Ϻ��ϴٴ� �濡�� �ٿ����ϴ�..;;
//��! �׸��� ���� ���¶� �ణ ���װ� �ִ� ������ �÷��� �˼��մϴ�..�ٹ�..
//
//	�� �׷� AABB�� ���� ������ �ٽ� �ѹ� �帮�ڽ��ϴ�. AABB�� �� ���� ���ڽ��Դϴ�.
//	��..���� ����� ���� ���� ���� �� ������..������ ���� ���� �ƴմϴ�. �� ������Ʈ��
//	���� x,y,z�࿡ ���� ������ �ּ����� �ִ����� ���Ͽ� �����Ų 6��ü�� ����� �浹üũ ����Դϴ�.
//	�ٽ� �ѹ� ���ϸ� ������Ʈ�� ��� ������ �����Ͽ� �� �������� �� ���� ����(x,y,z)�� �ִ� �ּҰ��� ���ؼ� ������ü�� ����ٴ� ������ 
//	�׷� �� ������ü�� �ε����� �浹�� �Ǵ� ����.. ���������� ��ü�� AABB����� ���� �浹üũ�� ����ϰ� �ǰ����� ������ ������ü��
//	����� ��ü�� AABB�� ���� ������� �浹üũ�� �ɰ��Դϴ�. ��� ���� AABB�� ����� ������ ���ؼ� ������ �̰����� ��ġ�ڽ��ϴ�.
//	AABB�� ���� �� �˰� �ʹٸ� å�� ã�ƺ��ñ� ���մϴ�.
//
//	�� ���� ���� ��� ������ �����ؼ� ������ ����(X,Y,Z)�� �ִ� �ּҰ��� ���ؼ� ū ������ü�� ����ٴ°� ����..
//	�׷��� �׷��� �ϸ� ���������� ����� ������Ʈ�� ���������� ������Ʈ �ƴ�.. �� ����� ������Ʈ�� �浹üũ�� �̻��ϰ� �ȴٴ� ������ ����.. 
//	�׷��� �����س� ���� ������ ������ ������ �����ؼ� �ִ� ���� �ּ� ���� ���ؼ� AABB�� ����� ����.. �׷��� �ϸ� ��� ��ü�� �Ϻ���
//	�浹üũ�� �����ϰ� �Ǵ� ����.. ��.. �� ���ذ� �ȵǽŴٸ� õõ�� ������鼭 �����ϼ���
//
//	�� Directx SDK�� CD3DFile�� ���ô�. CD3DFile�� �Ƹ� �޽ø� �ҷ��ͼ� ������ �� �� �ְ� ���ִ� �� �����ϴ�.
//	�׷� �� CD3DFIle�� �켱 CreateCollision�̶�� �Լ��� ���� �����￡ AABB�� ���� �浹�� �Ͼ�� �غ��ô�

	HRESULT CD3DMesh::CreateCollision( LPDIRECT3DDEVICE9 pd3dDevice )
{
	if( NULL == m_pSysMemMesh )
		return E_FAIL;

	LPD3DXMESH CloneMesh;
	//�� �κ��� Create���� �޽��� ������ ����ִ�(?) m_pSysMemMesh�� �޽��� �����ϴ� ���Դϴ�. 
	//������ ù��° D3DXMESH_SYSTEMMEM�� �ε����� ���ؽ��� ���´ٴ� ���Դϴ�. �ι�°�� ������ �����Դϴ�.
	
	if( SUCCEEDED(m_pSysMemMesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, D3DFVF_XYZ, pd3dDevice, &CloneMesh ) ) )
	{
		int FaceNum = CloneMesh->GetNumFaces();
		int VertexNum = CloneMesh->GetNumVertices();
		CollisionVertex* ColVer;
		if( SUCCEEDED(CloneMesh->LockVertexBuffer(D3DLOCK_READONLY,(VOID**)&ColVer) ) )//�޽ÿ� ���� �ɾ �� ���ؽ��� ���ɴϴ�.
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
						ColVer[index[i*3+2]].x, ColVer[index[i*3+2]].y, ColVer[index[i*3+2]].z ); //������ ������ �ּҿ� �ִ븦 ���մϴ�.
				}
			}
			CloneMesh->UnlockVertexBuffer();
		}
		CloneMesh->Release();
	}
	return S_OK;
}

//���� �ڵ带 �ٽ� �������ڸ� CloneMeshFVF�� ���� �޽ø� �����ϰ� ������ �޽ÿ��� ���ؽ��� ���ɴϴ�.
//	�׸��� FindMinMaxVerPos�� ���� �� �������� ���� ū Pos�� ���� ���� Pos�� ���� AABB�� ����ϴ�.
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
//���� �ڵ�� ���ٸ� ������ �帮�� �ʰڽ��ϴ�.
//	���� �ּ��� �������� �ִ�, �ּ�Pos�� ������ϴ�.
//	�׷��� ���� �� ������Ʈ�� Translation�̳� Scaling, Rotation�� �Ѵٸ� �������� �ִ�, �ּ�Pos�� �翬�� �ٲ������..
//	�׷��� �ּ��� �������� �ִ�, �ּ�Pos�� �ٽ� ���;� ������.. �̰��� D3DXVec3TransformCoord�� ���� �ذ��Ҽ� �ֽ��ϴ�.
//	�׷� Translation, Scaling, Rotation�� �� �������� �ּ� Pos�� ���ϴ� �Լ��� �����帮�ڽ��ϴ�.



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

//�̷��� �ϸ� �� �������� �ִ�, �ּ� Pos�� ���߽��ϴ�.
	//���� �̰� ������ �浹üũ�� �ϸ� 3D�浹üũ�� ��� ���� ������..����


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
//���� �ڵ�� �ٷ� �浹üũ�� �ϴ� �κ��Դϴ�. Pos�� �� �������� �ּ� Pos���� ũ�� �ִ� Pos�ȿ� ������
//	FALSE�� ������ �浹�� �Ͼ�ٴ� �� �˷�����.. 
//	�̷��� �ϸ� �浹üũ�� �Ǵ� ������.. ���࿡ �浹üũ�� �̻��ϰ� �Ͼ�ٸ� AABB�� �׷������� 
//	�׷��� ���� �������� �ݹ� �˰� �ɰ̴ϴ�.. �׷� �� �̸�~