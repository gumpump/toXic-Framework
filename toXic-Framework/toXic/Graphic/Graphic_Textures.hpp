#ifndef GRAPHIC_TEXTURES_IS_DEFINED
#define GRAPHIC_TEXTURES_IS_DEFINED

#include "Graphic_Window.hpp"
#include <list>

using namespace std;

struct tX_Texture_Data
{
	LPCSTR Filename;
	LPCSTR Path;
	LPDIRECT3DTEXTURE9 Texture;
};

#define tX_TEX tX_Texture_Data

class CGraphic_Textures
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		void Delete ();

		tX_TEX *Add (LPCSTR File);
		void DeleteTexture ();
		void DeleteTexture (LPCSTR File);
		void DeleteTextureByPath (LPCSTR Path);

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;

		list<tX_TEX*> m_Textures;

		tX_TEX *Tex;

		int Count;
};
#endif