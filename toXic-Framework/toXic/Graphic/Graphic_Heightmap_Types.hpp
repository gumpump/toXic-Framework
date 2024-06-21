#ifndef GRAPHIC_HEIGHTMAP_TYPES_IS_DEFINED
#define GRAPHIC_HEIGHTMAP_TYPES_IS_DEFINED
//((x)+(((z)*(v)-v)))
#define TERRAIN_INDEX(x,z,v) ((x*v)+z)
#define TERRAINVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2)

struct TerrainVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	DWORD Diffuse;
	float tu, tv;
	float tu2, tv2;
};
#endif