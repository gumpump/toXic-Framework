#ifndef GRAPHIC_PROGRESSIVEMESH_IS_DEFINED
#define GRAPHIC_PROGRESSIVEMESH_IS_DEFINED

#include "Graphic_Textures.hpp"
#include <string>

using namespace std;

class CGraphic_ProgressiveMesh
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		bool InitTextures (CGraphic_Textures *TexMng);
		void Delete ();

		void SetPos (D3DVECTOR Pos);
		void SetPos (float X, float Y, float Z);

		void SetPath (LPCSTR Path);
		void LoadXFile (LPCWSTR File);
		void Render (DWORD NumberOfFaces);

		DWORD GetMaxFaces () {return m_PMesh->GetMaxFaces ();}

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;

		unsigned long m_NumMaterials;
		D3DMATERIAL9 *m_MeshMaterials;
		LPDIRECT3DTEXTURE9 *m_MeshTextures;
		CGraphic_Textures  *m_TexMng;
		LPCSTR			   m_Path;
		string			   *m_StrDir;
		D3DXMATRIX m_WorldMat;
		D3DXMATRIX m_TransMat;
		D3DXVECTOR3 m_Pos;

		LPD3DXPMESH m_PMesh;
};
#endif