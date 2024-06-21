#include "Graphic_AssimpMesh.hpp"

bool CGraphic_AssimpMesh::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	m_Mesh.clear();

	m_Scale.x = 2.0f;
	m_Scale.y = 2.0f;
	m_Scale.z = 2.0f;

	m_Rot.x = 0.0f;
	m_Rot.y = 0.0f;
	m_Rot.z = 0.0f;
	m_Rot.w = 0.0f;

	m_Pos.x = 100.0f;
	m_Pos.y = 20.0f;
	m_Pos.z = 100.0f;
	
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

void CGraphic_AssimpMesh::Delete ()
{
	m_D3D9Device = ZERO;

	for (int i = 0; i < m_Mesh.size(); i++)
	{
		m_Vertices[i]->Release();
		m_Vertices[i] = 0;

		m_Indizes[i]->Release();
		m_Indizes[i] = 0;
	}
}

void CGraphic_AssimpMesh::LoadMeshFile (string File)
{
	Assimp::Importer Import;

	const aiScene *Scene = Import.ReadFile (File,
											aiProcess_CalcTangentSpace |
											aiProcess_Triangulate |
											aiProcess_JoinIdenticalVertices |
											aiProcess_SortByPType);

	if (!Scene)
	{
		MessageBox (ZERO,
					L"Mesh konnte nicht geladen werden (Assimp hat versagt)",
					L"Fataler Fehler",
					ZERO);
	}

	if (Scene->HasMeshes() == true)
	{
		for (int i = 0; i < Scene->mNumMeshes; i++)
		{
			m_Mesh.push_back(Scene->mMeshes[i]);
		}

		m_Vertices = new LPDIRECT3DVERTEXBUFFER9[Scene->mNumMeshes];
		m_Indizes = new LPDIRECT3DINDEXBUFFER9[Scene->mNumMeshes];
		
		int a = 0;

		for (std::list<aiMesh*>::iterator j = m_Mesh.begin(); j != m_Mesh.end(); j++)
		{
			//VERTEX-BUFFER-SHIT
			//
			//

			FAIL(m_D3D9Device->CreateVertexBuffer((*j)->mNumVertices * sizeof(Assimp_Mesh_Vertex),
				ZERO,
				ASSIMP_MESH_VERTEX,
				D3DPOOL_DEFAULT,
				&m_Vertices[a],
				ZERO));

			// INDEX-BUFFER-SHIT
			//
			//

			// 32-Bit

			if ((*j)->mNumFaces * 3 >= 65536)
			{
				FAIL(m_D3D9Device->CreateIndexBuffer(4 * (*j)->mNumFaces * 3,
													 ZERO,
													 D3DFMT_INDEX32,
													 D3DPOOL_DEFAULT,
													 &m_Indizes[a],
													 ZERO));

				unsigned int *TempData;

				FAIL(m_Indizes[a]->Lock(ZERO, ZERO, (void**)&TempData, ZERO));

				for (int k = 0; k < (*j)->mNumFaces; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						*TempData++ = (*j)->mFaces[k].mIndices[l];
					}
				}
			}

			// 16-Bit
			else
			{
				FAIL(m_D3D9Device->CreateIndexBuffer(4 * (*j)->mNumFaces * 3,
					ZERO,
					D3DFMT_INDEX16,
					D3DPOOL_DEFAULT,
					&m_Indizes[a],
					ZERO));

				uint16_t *TempData;

				FAIL(m_Indizes[a]->Lock(ZERO, ZERO, (void**)&TempData, ZERO));

				for (int k = 0; k < (*j)->mNumFaces; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						*TempData++ = (uint16_t)(*j)->mFaces[k].mIndices[l];
					}
				}
			}

			FAIL(m_Indizes[a]->Unlock());

			// VERTEX-BUFFER-SHIT AGAIN!
			//
			//

			Assimp_Mesh_Vertex *TempVertexData;

			FAIL(m_Vertices[a]->Lock(ZERO, ZERO, (void**)&TempVertexData, ZERO));

			for (int m = 0; m < (*j)->mNumVertices; m++)
			{
				TempVertexData->Pos.x = (*j)->mVertices[m].x;
				TempVertexData->Pos.y = (*j)->mVertices[m].y;
				TempVertexData->Pos.z = (*j)->mVertices[m].z;

				if ((*j)->HasNormals() == true)
				{
					TempVertexData->Normal.x = (*j)->mNormals[m].x;
					TempVertexData->Normal.y = (*j)->mNormals[m].y;
					TempVertexData->Normal.z = (*j)->mNormals[m].z;
				}

				TempVertexData->Diffuse = D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF);

				if ((*j)->HasTextureCoords(0) == true)
				{
					TempVertexData->tx = (*j)->mTextureCoords[0][m].x;
					TempVertexData->ty = (*j)->mTextureCoords[0][m].y;
				}
			}

			FAIL(m_Vertices[a]->Unlock());

			a++;
		}
	}

	else
	{
		MessageBox(ZERO,
			L"Szene enthält keine Meshes",
			L"Fataler Fehler",
			ZERO);
	}
	
}

void CGraphic_AssimpMesh::Render ()
{
	D3DXMatrixIdentity (&m_WorldMat);
	D3DXMatrixIdentity (&m_ScaleMat);
	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_RotMat);
	D3DXMatrixIdentity (&m_RotMatX);
	D3DXMatrixIdentity (&m_RotMatY);
	D3DXMatrixIdentity (&m_RotMatZ);
	D3DXMatrixIdentity (&m_RotMatA);

	D3DXMatrixScaling		(&m_ScaleMat, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationX		(&m_RotMatX, m_Rot.x);
	D3DXMatrixRotationY		(&m_RotMatY, m_Rot.y);
	D3DXMatrixRotationZ		(&m_RotMatZ, m_Rot.z);
	D3DXMatrixRotationAxis	(&m_RotMatA, &m_Axis, m_Rot.w);
	D3DXMatrixMultiply		(&m_WorldMat, &m_WorldMat, &m_ScaleMat);
	D3DXMatrixMultiply		(&m_RotMat, &m_RotMat, &m_RotMatX);
	D3DXMatrixMultiply		(&m_RotMat, &m_RotMat, &m_RotMatY);
	D3DXMatrixMultiply		(&m_RotMat, &m_RotMat, &m_RotMatZ);
	D3DXMatrixMultiply		(&m_RotMat, &m_RotMat, &m_RotMatA);
	D3DXMatrixMultiply		(&m_WorldMat, &m_WorldMat, &m_RotMat);
	D3DXMatrixTranslation	(&m_TransMat, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply		(&m_WorldMat, &m_WorldMat, &m_TransMat);

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &m_WorldMat));

	FAIL (m_D3D9Device->SetFVF (ASSIMP_MESH_VERTEX));

	int a = 0;

	for (std::list<aiMesh*>::iterator k = m_Mesh.begin(); k != m_Mesh.end(); k++)
	{
		FAIL(m_D3D9Device->SetStreamSource(0, m_Vertices[a], 0, sizeof(Assimp_Mesh_Vertex)));
		FAIL(m_D3D9Device->SetIndices(m_Indizes[a]));

		FAIL(m_D3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0,
			0,
			(*k)->mNumVertices,
			0,
			(*k)->mNumFaces));

		a++;
	}

	D3DXMatrixIdentity (&m_WorldMat);
	D3DXMatrixIdentity (&m_ScaleMat);
	D3DXMatrixIdentity (&m_TransMat);
	D3DXMatrixIdentity (&m_RotMat);
	D3DXMatrixIdentity (&m_RotMatX);
	D3DXMatrixIdentity (&m_RotMatY);
	D3DXMatrixIdentity (&m_RotMatZ);
	D3DXMatrixIdentity (&m_RotMatA);

	D3DXMatrixScaling(&m_ScaleMat, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationX(&m_RotMatX, m_Rot.x);
	D3DXMatrixRotationY(&m_RotMatY, m_Rot.y);
	D3DXMatrixRotationZ(&m_RotMatZ, m_Rot.z);
	D3DXMatrixRotationAxis(&m_RotMatA, &m_Axis, m_Rot.w);
	D3DXMatrixMultiply(&m_WorldMat, &m_WorldMat, &m_ScaleMat);
	D3DXMatrixMultiply(&m_RotMat, &m_RotMat, &m_RotMatX);
	D3DXMatrixMultiply(&m_RotMat, &m_RotMat, &m_RotMatY);
	D3DXMatrixMultiply(&m_RotMat, &m_RotMat, &m_RotMatZ);
	D3DXMatrixMultiply(&m_RotMat, &m_RotMat, &m_RotMatA);
	D3DXMatrixMultiply(&m_WorldMat, &m_WorldMat, &m_RotMat);
	D3DXMatrixTranslation(&m_TransMat, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_WorldMat, &m_WorldMat, &m_TransMat);

	FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &m_WorldMat));
}