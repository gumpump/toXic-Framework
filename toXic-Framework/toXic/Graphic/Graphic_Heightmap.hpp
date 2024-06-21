#ifndef GRAPHIC_HEIGHTMAP_IS_DEFINED
#define GRAPHIC_HEIGHTMAP_IS_DEFINED

#include "Graphic_HeightmapTile.hpp"

class CGraphic_Heightmap
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		void Delete ();

		void Create ();

		void SetFilename		(LPCSTR Filename);
		void SetTexturename		(LPCSTR Filename);
		void SetDetailname		(LPCSTR Filename);
		void SetCamPos			(D3DXVECTOR3 Pos);
		void SetCamLA			(D3DXVECTOR3 LA);
		void SetTilesPerColumn	(int TPC);
		void SetTilesPerRow		(int TPR);

		float AdjustHeight (D3DXVECTOR3 Pos);
		int Render		 ();

		int GetWidth () {return m_Width;}
		int GetHeight () {return m_Length;}

	private:
		LPDIRECT3DDEVICE9  m_D3D9Device;
		LPDIRECT3DTEXTURE9 m_TerrainTexture;
		LPDIRECT3DTEXTURE9 m_TerrainDetail;

		CGraphic_HeightmapTile **m_Tiles;

		float *m_Heightmap;

		LPCSTR m_Filename;
		LPCSTR m_Texturename;
		LPCSTR m_Detailname;

		int m_Width;
		int m_Length;

		int m_TPC;
		int m_TPR;

		D3DXVECTOR3 m_CamPos;
		D3DXVECTOR3 m_CamLA;

		BOOL IsVisible (D3DXVECTOR3 *Pos,
						D3DXVECTOR3 *LA,
						D3DXVECTOR3 *Tile);

		int PointLine (D3DXVECTOR2 A,
					   D3DXVECTOR2 B,
					   D3DXVECTOR2 P);

		void RotateVector (D3DXVECTOR2 *pV,
						   float Angle,
						   D3DXVECTOR2 Origin);
};
#endif