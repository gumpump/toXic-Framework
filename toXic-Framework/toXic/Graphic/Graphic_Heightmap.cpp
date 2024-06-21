#include "Graphic_Heightmap.hpp"

bool CGraphic_Heightmap::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	m_Width = 0;
	m_Length = 0;

	m_Tiles = ZERO;

	m_TerrainTexture = ZERO;
	m_TerrainDetail = ZERO;

	return true;
}

void CGraphic_Heightmap::Delete ()
{
	if (m_TerrainTexture != ZERO)
	{
		m_TerrainTexture->Release ();
		m_TerrainTexture = ZERO;
	}

	if (m_TerrainDetail != ZERO)
	{
		m_TerrainDetail->Release ();
		m_TerrainDetail = ZERO;
	}

	if (m_Tiles != ZERO)
	{
		for (int i = 0; i < m_TPC; i++)
		{
			m_Tiles[i]->Delete ();
			delete [] m_Tiles[i];
		}

		delete [] m_Tiles;
	}

	delete[] m_Heightmap;
}

void CGraphic_Heightmap::Create ()
{
	int i = 0, j = 0;

	LPDIRECT3DSURFACE9 Surface = ZERO;

	D3DXIMAGE_INFO ImgInfo;

	FAIL (D3DXGetImageInfoFromFileA (m_Filename, &ImgInfo));

	m_Width = ImgInfo.Width;
	m_Length = ImgInfo.Height;

	FAIL (m_D3D9Device->CreateOffscreenPlainSurface (m_Width,
													 m_Length,
													 D3DFMT_L8,
													 D3DPOOL_SCRATCH,
													 &Surface, ZERO));

	FAIL (D3DXLoadSurfaceFromFileA (Surface,
								    ZERO, ZERO,
								    m_Filename,
								    ZERO,
								    D3DX_DEFAULT,
								    ZERO, ZERO));

	int SizeVertices = m_Width * m_Length;
	int SizeIndices = (m_Width-1)*(m_Length-1)*2*3;

	D3DLOCKED_RECT LockedRect;

	FAIL (Surface->LockRect (&LockedRect, ZERO, ZERO));

	BYTE *Heights = (BYTE*) LockedRect.pBits;

	int Pitch = LockedRect.Pitch;

	m_Heightmap = new float[m_Width * m_Length];

	for (i = 0; i < m_Length; i++)
	{
		for (j = 0; j < m_Width; j++)
		{
			m_Heightmap[i*m_Width+j] = static_cast<float>(Heights[i*Pitch+j]) / 10.0f;
		}
	}

	FAIL (Surface->UnlockRect ());
	Surface->Release ();

	m_Tiles = new CGraphic_HeightmapTile*[m_TPC];

	for (i = 0; i < m_TPC; i++)
	{
		m_Tiles[i] = new CGraphic_HeightmapTile[m_TPR];
	}

	int TileWidth = 0;
	int TileLength = 0;

	for (i = 0; i < m_TPC; i++)
	{
		if (i == m_TPC-1)
		{
			TileLength = m_Length / m_TPC;
		}

		else
		{
			TileLength = m_Length / m_TPC + 1;
		}

		for (j = 0; j < m_TPR; j++)
		{
			if (j == m_TPR-1)
			{
				TileWidth = m_Width / m_TPR;
			}

			else
			{
				TileWidth = m_Width / m_TPR + 1;
			}

			m_Tiles[i][j].Create (m_D3D9Device,
								  TileWidth,
								  TileLength,
								  m_Width,
								  m_Length,
								  j * m_Width / m_TPR,
								  i * m_Length / m_TPC,
								  m_Heightmap);
		}
	}

	if (FAILED (D3DXCreateTextureFromFileA (m_D3D9Device,
										    m_Texturename,
										    &m_TerrainTexture)))
	{
		MessageBox (ZERO,
					L"Fehler beim Laden der Terrain-Textur",
					L"Fehler",
					MB_OK);
	}

	if (FAILED (D3DXCreateTextureFromFileA (m_D3D9Device,
										    m_Detailname,
										    &m_TerrainDetail)))
	{
		MessageBox (ZERO,
					L"Fehler beim Laden der Terrain-Textur",
					L"Fehler",
					MB_OK);
	}
}

void CGraphic_Heightmap::SetFilename (LPCSTR Filename)
{
	m_Filename = Filename;
}

void CGraphic_Heightmap::SetTexturename (LPCSTR Filename)
{
	m_Texturename = Filename;
}

void CGraphic_Heightmap::SetDetailname (LPCSTR Filename)
{
	m_Detailname = Filename;
}

void CGraphic_Heightmap::SetCamPos (D3DXVECTOR3 Pos)
{
	m_CamPos = Pos;
}

void CGraphic_Heightmap::SetCamLA (D3DXVECTOR3 LA)
{
	m_CamLA = LA;
}

void CGraphic_Heightmap::SetTilesPerColumn (int TPC)
{
	m_TPC = TPC;
}

void CGraphic_Heightmap::SetTilesPerRow (int TPR)
{
	m_TPR = TPR;
}

float CGraphic_Heightmap::AdjustHeight (D3DXVECTOR3 Pos)
{
	int X = static_cast<int>(Pos.x);
	int Z = static_cast<int>(Pos.z);

	if (Z < 0 || Z >= m_Length - 1)
	{
		Z = 0;
	}

	else if (X < 0 || X >= m_Width - 1)
	{
		X = 0;
	}

	else
	{
		D3DXVECTOR2 A		(static_cast<float>(X + 1), static_cast<float>(Z));
		D3DXVECTOR2 B		(static_cast<float>(X),		static_cast<float>(Z + 1));
		D3DXVECTOR2 Point	(static_cast<float>(X),		static_cast<float>(Z));

		int r = PointLine (A, B, Point);

		float P1;
		float P2;
		float P3;

		if (r > 0)
		{
			P1 = m_Heightmap[TERRAIN_INDEX (X, Z + 1, m_Length)];
			P2 = m_Heightmap[TERRAIN_INDEX (X, Z, m_Length)];
			P3 = m_Heightmap[TERRAIN_INDEX (X + 1, Z, m_Length)];
		}

		else
		{
			P1 = m_Heightmap[TERRAIN_INDEX (X, Z + 1, m_Length)];
			P2 = m_Heightmap[TERRAIN_INDEX (X + 1, Z + 1, m_Length)];
			P3 = m_Heightmap[TERRAIN_INDEX (X + 1, Z, m_Length)];
		}

		D3DXVECTOR3 Triangle1 (static_cast<float>(X), P1, static_cast<float>(Z + 1));
		D3DXVECTOR3 Triangle2 (static_cast<float>(X), P2, static_cast<float>(Z));
		D3DXVECTOR3 Triangle3 (static_cast<float>(X + 1), P3, static_cast<float>(Z));

		D3DXVECTOR3 v1 = Triangle2 + Triangle3;
		D3DXVECTOR3 v2 = Triangle1 + Triangle2;

		D3DXVECTOR3 Normal;

		D3DXVec3Cross (&Normal, &v1, &v2);

		D3DXPLANE Plane (Normal.x, Normal.y, Normal.z, 0.0f);

		D3DXVECTOR3 Out;
		D3DXVECTOR3 v3 (Pos.x, 1000.0f, Pos.z);
		D3DXVECTOR3 v4 (Pos.x, -1000.0f, Pos.z);

		D3DXPlaneIntersectLine (&Out, &Plane, &v3, &v4);

		return ((Out.y + 1.8f + Pos.y) / 2);
	}

	return Pos.y;
}

int CGraphic_Heightmap::Render ()
{
	int TilesRendered = 0;

	D3DXMATRIX TransMatrix;

	FAIL (m_D3D9Device->SetTexture (0, m_TerrainTexture));
	FAIL (m_D3D9Device->SetTexture (1, m_TerrainDetail));

	FAIL (m_D3D9Device->SetTextureStageState (0, D3DTSS_COLOROP, D3DTOP_MODULATE));
	FAIL (m_D3D9Device->SetTextureStageState (0, D3DTSS_COLORARG1, D3DTA_TEXTURE));
	FAIL (m_D3D9Device->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE));
    FAIL (m_D3D9Device->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT));
    FAIL (m_D3D9Device->SetTextureStageState(1, D3DTSS_COLOROP,   D3DTOP_MODULATE));

	FAIL (m_D3D9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
    FAIL (m_D3D9Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	FAIL (m_D3D9Device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
    FAIL (m_D3D9Device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));

	int i = 0;

	int TileWidth = m_Width / m_TPR;
	int TileLength = m_Length / m_TPC;

	for (i = 0; i < m_TPC-1; i++)
	{
		for (int j = 0; j < m_TPR; j++)
		{
			D3DXMatrixTranslation (&TransMatrix,
								   static_cast<float>(j*TileWidth),
								   0.0f,
								   static_cast<float>(m_Length - (i * TileLength) - TileLength));

			FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &TransMatrix));

			D3DXVECTOR3 vTile1 (static_cast<float>(j*TileWidth),
								0.0f,
								static_cast<float>(m_Length - (i * TileLength)));
			D3DXVECTOR3 vTile2 (vTile1.x + TileWidth, 0.0f, vTile1.z);
			D3DXVECTOR3 vTile3 (vTile1.x, 0.0f, vTile1.z - TileLength);
			D3DXVECTOR3 vTile4 (vTile1.x + TileWidth, 0.0f, vTile1.z - TileLength);

			if (IsVisible (&m_CamPos, &m_CamLA, &vTile1) ||
				IsVisible (&m_CamPos, &m_CamLA, &vTile2) ||
				IsVisible (&m_CamPos, &m_CamLA, &vTile3) ||
				IsVisible (&m_CamPos, &m_CamLA, &vTile4))
			{
				TilesRendered++;

				m_Tiles[i][j].Render ();
			}
		}
	}

	for (int j = 0; j < m_TPR; j++)
	{
		D3DXMatrixTranslation (&TransMatrix,
							   static_cast<float>(j*m_Width/m_TPR),
							   0.0f,
							   static_cast<float>(m_Length - (i * m_Length/m_TPC) + 1) - TileLength);

		FAIL (m_D3D9Device->SetTransform (D3DTS_WORLD, &TransMatrix));

		D3DXVECTOR3 vTile1 (static_cast<float>(j*TileWidth),
							0.0f,
							static_cast<float>(m_Length - (i * m_Length/m_TPC) + 1) - TileLength);

		D3DXVECTOR3 vTile2 (vTile1.x + TileWidth, 0.0f, vTile1.z);
		D3DXVECTOR3 vTile3 (vTile1.x, 0.0f, vTile1.z - TileLength);
		D3DXVECTOR3 vTile4 (vTile1.x + TileWidth, 0.0f, vTile1.z - TileLength);

		if (IsVisible (&m_CamPos, &m_CamLA, &vTile1) ||
			IsVisible (&m_CamPos, &m_CamLA, &vTile2) ||
			IsVisible (&m_CamPos, &m_CamLA, &vTile3) ||
			IsVisible (&m_CamPos, &m_CamLA, &vTile4))
		{
			TilesRendered++;

			m_Tiles[i][j].Render ();
		}
	}

	FAIL (m_D3D9Device->SetTexture (0, ZERO));
	FAIL (m_D3D9Device->SetTexture (1, ZERO));

	return TilesRendered;
}

BOOL CGraphic_Heightmap::IsVisible (D3DXVECTOR3 *Pos,
									D3DXVECTOR3 *LA,
									D3DXVECTOR3 *Tile)
{
	D3DXVECTOR2 vLookAt2D,
				vFrustumLeft,
				vFrustumRight,
				vPos2D,
				vTile2D;

	vLookAt2D.x = LA->x;
	vLookAt2D.y = LA->z;

	vPos2D.x = Pos->x;
	vPos2D.y = Pos->z;

	vTile2D.x = Tile->x;
	vTile2D.y = Tile->z;

	vFrustumLeft = vLookAt2D;
	vFrustumRight = vLookAt2D;

	RotateVector (&vFrustumLeft, -45.0f * D3DX_PI / 180.0f, vPos2D);
	RotateVector (&vFrustumRight, 45.0f * D3DX_PI / 180.0f, vPos2D);

	int r1 = PointLine (vPos2D, vFrustumLeft, vTile2D);
	int r2 = PointLine (vPos2D, vFrustumRight, vTile2D);

	if (r1 <= 0 && r2 >= 0)
	{
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}

int CGraphic_Heightmap::PointLine (D3DXVECTOR2 A,
								   D3DXVECTOR2 B,
								   D3DXVECTOR2 P)
{
	D3DXVECTOR2 v1 = B - A;
	D3DXVECTOR2 v2 = P - A;

	return static_cast<int>(v1.x * v2.y - v1.y * v2.x);
}

void CGraphic_Heightmap::RotateVector (D3DXVECTOR2 *pV,
									   float Angle,
									   D3DXVECTOR2 Origin)
{
	float c = cosf (Angle);
	float s = sinf (Angle);

	float x = pV->x - Origin.x;
	float y = pV->y - Origin.y;

	float x1 =  c * x + s * y;
	float y1 = -s * x + c * y;

	pV->x = x1 + Origin.x;
	pV->y = y1 + Origin.y;
}