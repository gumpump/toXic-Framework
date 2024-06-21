#ifndef GRAPHIC_ASSIMPMESH_IS_DEFINED
#define GRAPHIC_ASSIMPMESH_IS_DEFINED

#include "Graphic_Textures.hpp"
#include <string>
#include "Graphic_Mesh_Types.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment (lib, "lib64/assimp.lib")

class CGraphic_AssimpMesh
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		void Delete ();

		void LoadMeshFile (string File);
		void Render ();

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;
		LPDIRECT3DVERTEXBUFFER9	*m_Vertices;
		LPDIRECT3DINDEXBUFFER9	*m_Indizes;
		std::list<aiMesh*> m_Mesh;

		D3DXMATRIX m_WorldMat;
		D3DXMATRIX m_ScaleMat;
		D3DXMATRIX m_TransMat;
		D3DXMATRIX m_RotMat;
		D3DXMATRIX m_RotMatX;
		D3DXMATRIX m_RotMatY;
		D3DXMATRIX m_RotMatZ;
		D3DXMATRIX m_RotMatA;

		D3DXVECTOR3 m_Pos;
		D3DXVECTOR4 m_Rot;
		D3DXVECTOR3 m_Axis;
		D3DXVECTOR3 m_Scale;
};
#endif