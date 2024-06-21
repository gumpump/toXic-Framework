#ifndef TESTGROUND_IS_DEFINED
#define TESTGROUND_IS_DEFINED

#include "toXic/Graphic/Graphic_Textures.hpp"

#define GROUNDVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct GroundVertex
{
	float x, y, z;
	D3DCOLOR Color;
	float tu, tv;
};

class CTestGround
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		bool InitTextures (CGraphic_Textures *TexMng);
		void Create ();
		void Delete ();

		void SetSize (float Value);
		void SetTex (LPCSTR Path);

		void Render ();

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;
		CGraphic_Textures *m_TexMng;
		LPDIRECT3DVERTEXBUFFER9 m_VBuffer;

		float m_Size;
		LPCSTR m_Path;
		GroundVertex m_Vertices[6];
};
#endif