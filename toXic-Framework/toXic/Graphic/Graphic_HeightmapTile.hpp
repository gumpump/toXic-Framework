#ifndef GRAPHIC_HEIGHTMAPTILE_IS_DEFINED
#define GRAPHIC_HEIGHTMAPTILE_IS_DEFINED

#include "Graphic_Window.hpp"
#include "Graphic_Heightmap_Types.hpp"

class CGraphic_HeightmapTile
{
	public:
		void Create (LPDIRECT3DDEVICE9 Device,
					 int Width,
					 int Length,
					 int HeightmapWidth,
					 int HeightmapHeight,
					 int OffsetX,
					 int OffsetY,
					 float *Heightmap);

		void Render ();

		void Delete ();

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;

		int m_Width;
		int m_Length;

		LPDIRECT3DVERTEXBUFFER9 m_VB;
		LPDIRECT3DINDEXBUFFER9	m_IB;
};
#endif