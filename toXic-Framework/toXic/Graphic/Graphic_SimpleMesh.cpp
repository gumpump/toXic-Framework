#include "Graphic_SimpleMesh.hpp"

bool CGraphic_SimpleMesh::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	m_NumMaterials = ZERO;
	m_MeshMaterials = ZERO;
	m_Mesh = ZERO;

	m_Scale.x = 0.0f;
	m_Scale.y = 0.0f;
	m_Scale.z = 0.0f;

	m_Rot.x = 0.0f;
	m_Rot.y = 0.0f;
	m_Rot.z = 0.0f;
	m_Rot.w = 0.0f;

	m_Pos.x = 0.0f;
	m_Pos.y = 0.0f;
	m_Pos.z = 0.0f;
	
	m_Axis.x = 0.0f;
	m_Axis.y = 0.0f;
	m_Axis.z = 0.0f;

	D3DXMatrixIdentity (&m_WorldMat);
	D3DXMatrixIdentity (&m_ScaleMat);
	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_RotMat);
	D3DXMatrixIdentity (&m_RotMatX);
	D3DXMatrixIdentity (&m_RotMatY);
	D3DXMatrixIdentity (&m_RotMatZ);
	D3DXMatrixIdentity (&m_RotMatA);
	
	return true;
}

bool CGraphic_SimpleMesh::InitTextures (CGraphic_Textures *TexMng)
{
	if (TexMng != ZERO)
	{
		m_TexMng = TexMng;
	}

	else
	{
		return false;
	}

	return true;
}

void CGraphic_SimpleMesh::Delete ()
{
	m_D3D9Device = ZERO;

	if (m_Mesh != ZERO)
	{
		m_Mesh->Release ();
		m_Mesh = ZERO;
	}

	m_TexMng->DeleteTextureByPath (m_Path);

	m_TexMng = ZERO;
}

void CGraphic_SimpleMesh::SetPos (D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

void CGraphic_SimpleMesh::SetPos (float x, float y, float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

void CGraphic_SimpleMesh::SetRotX (float X)
{
	m_Rot.x = D3DXToRadian (X);
}

void CGraphic_SimpleMesh::SetRotY (float Y)
{
	m_Rot.y = D3DXToRadian (Y);
}

void CGraphic_SimpleMesh::SetRotZ (float Z)
{
	m_Rot.z = D3DXToRadian (Z);
}

void CGraphic_SimpleMesh::SetRotA (float A, D3DXVECTOR3 Axis)
{
	m_Rot.w = D3DXToRadian (A);
	m_Axis = Axis;
}

void CGraphic_SimpleMesh::SetRotXR (float X)
{
	m_Rot.x = X;
}

void CGraphic_SimpleMesh::SetRotYR (float Y)
{
	m_Rot.y = Y;
}

void CGraphic_SimpleMesh::SetRotZR (float Z)
{
	m_Rot.z = Z;
}

void CGraphic_SimpleMesh::SetRotAR (float A, D3DXVECTOR3 Axis)
{
	m_Rot.w = A;
	m_Axis = Axis;
}

void CGraphic_SimpleMesh::SetScaleX (float X)
{
	m_Scale.x = X;
}

void CGraphic_SimpleMesh::SetScaleY (float Y)
{
	m_Scale.y = Y;
}

void CGraphic_SimpleMesh::SetScaleZ (float Z)
{
	m_Scale.z = Z;
}

void CGraphic_SimpleMesh::SetScale (D3DXVECTOR3 Scale)
{
	m_Scale = Scale;
}

void CGraphic_SimpleMesh::SetScale (float X, float Y, float Z)
{
	m_Scale.x = X;
	m_Scale.y = Y;
	m_Scale.z = Z;
}

void CGraphic_SimpleMesh::SetPath (LPCSTR Path)
{
	m_Path = Path;
}

void CGraphic_SimpleMesh::LoadXFile (LPCSTR File)
{
	LPD3DXBUFFER lpMaterialBuffer = ZERO;

	FAIL (D3DXLoadMeshFromXA (File, 
							  D3DXMESH_MANAGED, 
							  m_D3D9Device, 
							  ZERO, 
							  &lpMaterialBuffer, 
							  ZERO, 
							  &m_NumMaterials, 
							  &m_Mesh));

	D3DXMATERIAL* lpMaterials = (D3DXMATERIAL*)lpMaterialBuffer->GetBufferPointer();

	m_MeshMaterials = new D3DMATERIAL9[m_NumMaterials];
	m_MeshTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];


	// Materialien und Texturen kopieren
	for (int i = 0; i < m_NumMaterials; i++)
	{
		m_MeshMaterials[i] = lpMaterials[i].MatD3D;
		m_MeshMaterials[i].Ambient = m_MeshMaterials[i].Diffuse;

		if (lpMaterials[i].pTextureFilename != ZERO)
		{
			m_StrDir = new string (m_Path);
			m_StrDir->append (lpMaterials[i].pTextureFilename);
			m_MeshTextures[i] = (m_TexMng->Add (m_StrDir->c_str ()))->Texture;
			delete m_StrDir;
		}

		else
		{
			m_MeshTextures[i] = ZERO;
		}
	}

	if (!(m_Mesh->GetFVF () & D3DFVF_NORMAL))
	{
		LPD3DXMESH TempMesh;

		FAIL (m_Mesh->CloneMeshFVF ((m_Mesh->GetOptions () & D3DXMESH_32BIT) | D3DXMESH_MANAGED,
									m_Mesh->GetFVF () | D3DFVF_NORMAL,
									m_D3D9Device,
									&TempMesh));
		FAIL (D3DXComputeNormals (TempMesh, ZERO));

		m_Mesh->Release ();
		m_Mesh = TempMesh;
	}
}

void CGraphic_SimpleMesh::Render ()
{
	D3DXMatrixIdentity (&m_WorldMat);
	D3DXMatrixIdentity (&m_ScaleMat);
	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_RotMat);
	D3DXMatrixIdentity (&m_RotMatX);
	D3DXMatrixIdentity (&m_RotMatY);
	D3DXMatrixIdentity (&m_RotMatZ);
	D3DXMatrixIdentity (&m_RotMatA);

	D3DXMatrixScaling (&m_ScaleMat, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationX (&m_RotMatX, m_Rot.x);
	D3DXMatrixRotationY (&m_RotMatY, m_Rot.y);
	D3DXMatrixRotationZ (&m_RotMatZ, m_Rot.z);
	D3DXMatrixRotationAxis (&m_RotMatA, &m_Axis, m_Rot.w);
	D3DXMatrixMultiply (&m_WorldMat, &m_WorldMat, &m_ScaleMat);
	D3DXMatrixMultiply (&m_RotMat, &m_RotMat, &m_RotMatX);
	D3DXMatrixMultiply (&m_RotMat, &m_RotMat, &m_RotMatY);
	D3DXMatrixMultiply (&m_RotMat, &m_RotMat, &m_RotMatZ);
	D3DXMatrixMultiply (&m_RotMat, &m_RotMat, &m_RotMatA);
	D3DXMatrixMultiply (&m_WorldMat, &m_WorldMat, &m_RotMat);
	D3DXMatrixTranslation (&m_TransMat, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply (&m_WorldMat, &m_WorldMat, &m_TransMat);
	

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &m_WorldMat));

	// durch alle Materialien laufen
	for(int i = 0; i < m_NumMaterials; i++)
	{
		// Material setzen
		FAIL (m_D3D9Device->SetMaterial(&m_MeshMaterials[i]));

		if (m_MeshTextures[i] != ZERO)
		{
			FAIL (m_D3D9Device->SetTexture (0, m_MeshTextures[i]));
		}

		else
		{
			FAIL (m_D3D9Device->SetTexture (0, ZERO));
		}

		// Mesh rendern
		FAIL (m_Mesh->DrawSubset(i));
	}

	D3DXMatrixIdentity (&m_WorldMat);
	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_RotMat);
	D3DXMatrixIdentity (&m_RotMatX);
	D3DXMatrixIdentity (&m_RotMatY);
	D3DXMatrixIdentity (&m_RotMatZ);
	D3DXMatrixIdentity (&m_RotMatA);

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &m_WorldMat));
}