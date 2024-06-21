#ifndef GRAPHIC_SKYBOX_TYPES_IS_DEFINED
#define GRAPHIC_SKYBOX_TYPES_IS_DEFINED

enum tX_Skybox_Sides
{
	SKY_FRONT = 0,
	SKY_BACK = 1,
	SKY_LEFT = 2,
	SKY_RIGHT = 3,
	SKY_UP = 4,
	SKY_DOWN = 5
};

struct tX_SkyboxVertex
{
	D3DXVECTOR3 Coords;
	FLOAT tu, tv;
};

#define tX_SIDE			 tX_Skybox_Sides
#define SKYBOX_VERTEX	 (D3DFVF_XYZ|D3DFVF_TEX1)
#endif