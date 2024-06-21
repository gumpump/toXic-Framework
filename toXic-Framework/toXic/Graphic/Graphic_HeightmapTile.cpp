#include "Graphic_HeightmapTile.hpp"

void CGraphic_HeightmapTile::Create(LPDIRECT3DDEVICE9 Device,
									int Width, int Length,
									int HeightmapWidth,
									int HeightmapHeight,
									int OffsetX, int OffsetY,
									float *Heightmap)
{
	m_D3D9Device = Device;

	m_VB = ZERO;
	m_IB = ZERO;

	m_Width = Width;
	m_Length = Length;

	int i = 0, j = 0, k = 0;

	int SizeVertices = m_Width * m_Length;
	int SizeIndices = (m_Width-1) * (m_Length-1) * 2 * 3;

	FAIL (m_D3D9Device->CreateVertexBuffer (SizeVertices * sizeof (TerrainVertex),
											ZERO, TERRAINVERTEX,
											D3DPOOL_DEFAULT,
											&m_VB,
											ZERO));

	FAIL (m_D3D9Device->CreateIndexBuffer (SizeIndices * 2,
										   ZERO,
										   D3DFMT_INDEX16,
										   D3DPOOL_DEFAULT,
										   &m_IB,
										   ZERO));

	TerrainVertex *Vertices = new TerrainVertex[SizeVertices];

	for (i = 0; i < m_Length; i++)
	{
		for (j = 0; j < m_Width; j++)
		{
			Vertices[i*m_Width+j].Pos.x = static_cast<float>(j);
			Vertices[i*m_Width+j].Pos.y = Heightmap[(i+OffsetY)*HeightmapWidth+j+OffsetX];
			Vertices[i*m_Width+j].Pos.z = static_cast<float>(m_Length - i);

			Vertices[i*m_Width+j].Normal.x = static_cast<float>(Heightmap[(OffsetY+i)*HeightmapWidth+(OffsetX + j)] - 128.0f) / 127.0f;
			Vertices[i*m_Width+j].Normal.y = static_cast<float>(Heightmap[(OffsetY+i)*HeightmapWidth+(OffsetX + j)] - 128.0f) / 127.0f;
			Vertices[i*m_Width+j].Normal.z = static_cast<float>(Heightmap[(OffsetY+i)*HeightmapWidth+(OffsetX + j)] - 128.0f) / 127.0f;

			Vertices[i*m_Width+j].Diffuse = D3DCOLOR_COLORVALUE (1.0f, 1.0f, 1.0f, 1.0f);

			Vertices[i*m_Width+j].tu = static_cast<float>(j+OffsetX) / HeightmapWidth;
			Vertices[i*m_Width+j].tv = static_cast<float>(i+OffsetY) / HeightmapHeight;

			Vertices[i*m_Width+j].tu2 = static_cast<float>(j) / m_Width;
			Vertices[i*m_Width+j].tv2 = static_cast<float>(i) / m_Length;
		}
	}

	unsigned short *Indices = new unsigned short[SizeIndices];

	k = 0;

	for (i = 0; i < m_Length-1; i++)
	{
		for (j = 0; j < m_Width-1; j++)
		{
			Indices[k++] = m_Width * (i + 1) + j;
			Indices[k++] = m_Width * i + j;
			Indices[k++] = m_Width * (i + 1) + j + 1;
			Indices[k++] = m_Width * i + j;
			Indices[k++] = m_Width * i + j + 1;
			Indices[k++] = m_Width * (i + 1) + j + 1;
		}
	}

	void *pVertices;

	FAIL (m_VB->Lock (ZERO,
					  SizeVertices * sizeof (TerrainVertex),
					  &pVertices,
					  ZERO));

	memcpy (pVertices,
			Vertices,
			SizeVertices * sizeof (TerrainVertex));

	FAIL (m_VB->Unlock ());

	void *pIndices;

	FAIL (m_IB->Lock (ZERO,
					  SizeIndices * sizeof (unsigned short),
					  &pIndices,
					  ZERO));

	memcpy (pIndices,
			Indices,
			SizeIndices * sizeof (unsigned short));

	FAIL (m_IB->Unlock ());

	delete[] Vertices;
	delete[] Indices;
}

void CGraphic_HeightmapTile::Render ()
{
	FAIL (m_D3D9Device->SetFVF (TERRAINVERTEX));

	FAIL (m_D3D9Device->SetStreamSource (ZERO,
										 m_VB,
										 ZERO,
										 sizeof (TerrainVertex)));
	FAIL (m_D3D9Device->SetIndices (m_IB));

	FAIL (m_D3D9Device->DrawIndexedPrimitive (D3DPT_TRIANGLELIST,
											  ZERO, ZERO,
											  m_Length * m_Width,
											  ZERO,
											  (m_Width-1)*(m_Length-1) * 2));
}

void CGraphic_HeightmapTile::Delete ()
{
	if (m_VB != ZERO)
	{
		m_VB->Release ();
		m_VB = ZERO;
	}

	if (m_IB != ZERO)
	{
		m_IB->Release ();
		m_IB = ZERO;
	}
}