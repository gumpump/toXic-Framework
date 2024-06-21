#include "Graphic_ProgressiveMesh.hpp"

bool CGraphic_ProgressiveMesh::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	return true;
}

bool CGraphic_ProgressiveMesh::InitTextures (CGraphic_Textures *TexMng)
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

void CGraphic_ProgressiveMesh::Delete ()
{
	m_D3D9Device = ZERO;

	if (m_PMesh != ZERO)
	{
		m_PMesh->Release ();
		m_PMesh = ZERO;
	}

	m_TexMng->DeleteTextureByPath (m_Path);

	m_TexMng = ZERO;
}

void CGraphic_ProgressiveMesh::SetPos (D3DVECTOR Pos)
{
	m_Pos = Pos;
}

void CGraphic_ProgressiveMesh::SetPos (float X, float Y, float Z)
{
	m_Pos.x = X;
	m_Pos.y = Y;
	m_Pos.z = Z;
}

void CGraphic_ProgressiveMesh::SetPath (LPCSTR Path)
{
	m_Path = Path;
}

void CGraphic_ProgressiveMesh::LoadXFile (LPCWSTR File)
{
	LPD3DXMESH lpMesh = ZERO;

    LPD3DXBUFFER lpMaterialBuffer;

    D3DXLoadMeshFromX(File, 
                      D3DXMESH_MANAGED, 
                      m_D3D9Device, 
                      ZERO, 
                      &lpMaterialBuffer, 
                      ZERO,
                      &m_NumMaterials, 
                      &lpMesh);

	D3DXMATERIAL* lpMaterials = (D3DXMATERIAL*)lpMaterialBuffer->GetBufferPointer();

	m_MeshMaterials = new D3DMATERIAL9[m_NumMaterials];
	m_MeshTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];

	for(DWORD i=0;i<m_NumMaterials;i++)
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

	LPD3DXBUFFER pBuffer = ZERO;
    LPD3DXMESH pMeshTemp = ZERO;

	int nNumFaces = lpMesh->GetNumFaces();

	DWORD *pAdjacency1 = new DWORD[nNumFaces * 3];
    DWORD *pAdjacency2 = new DWORD[nNumFaces * 3];

	lpMesh->GenerateAdjacency(0.0f, pAdjacency1);

	D3DXCleanMesh(D3DXCLEAN_SIMPLIFICATION, lpMesh, pAdjacency1, &pMeshTemp, pAdjacency2, &pBuffer);

	D3DXValidMesh(pMeshTemp, pAdjacency2, &pBuffer);

	lpMesh->Release();
    lpMesh = pMeshTemp;

	D3DXGeneratePMesh(lpMesh, pAdjacency2, ZERO, ZERO, 300, D3DXMESHSIMP_FACE, &m_PMesh);

	delete[] pAdjacency1;
    delete[] pAdjacency2;

	lpMesh->Release();
}

void CGraphic_ProgressiveMesh::Render (DWORD NumberOfFaces)
{
	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_WorldMat);

	D3DXMatrixTranslation (&m_TransMat, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply (&m_WorldMat, &m_WorldMat, &m_TransMat);

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &m_WorldMat));

    for(DWORD i=0;i<m_NumMaterials;i++)
    {
		FAIL (m_D3D9Device->SetMaterial(&m_MeshMaterials[i]));

		if (m_MeshTextures[i] != ZERO)
		{
			FAIL (m_D3D9Device->SetTexture (0, m_MeshTextures[i]));
		}

		else
		{
			FAIL (m_D3D9Device->SetTexture (0, ZERO));
		}

		FAIL (m_PMesh->SetNumFaces(NumberOfFaces));

		FAIL (m_PMesh->DrawSubset(i));
    }

	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_WorldMat );

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &m_WorldMat));
}