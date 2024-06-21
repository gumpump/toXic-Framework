#ifndef GRAPHIC_SKYBOX_IS_DEFINED
#define GRAPHIC_SKYBOX_IS_DEFINED

#include "Graphic_Textures.hpp"
#include "Graphic_Skybox_Types.hpp"

class CGraphic_Skybox
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		bool InitTextures (CGraphic_Textures *TexMng);
		void Delete ();

		void SetTexture (LPCSTR Filename, tX_SIDE Side);
		void SetPos (D3DVECTOR Pos);
		void SetPos (float X, float Y, float Z);

		void Create ();
		
		void Render ();

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;

		LPDIRECT3DVERTEXBUFFER9 m_Buffer;
		CGraphic_Textures *m_TexMng;

		LPCSTR m_TexNames[6];

		D3DVECTOR m_Pos;

		float m_Dx;
		float m_Dy;
		float m_Dz;
};
#endif