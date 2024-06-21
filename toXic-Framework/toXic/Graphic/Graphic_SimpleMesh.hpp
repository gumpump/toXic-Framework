#ifndef GRAPHIC_SIMPLEMESH_IS_DEFINED
#define GRAPHIC_SIMPLEMESH_IS_DEFINED

#include "Graphic_Textures.hpp"
#include <string>
#include "Graphic_Mesh_Types.hpp"

using namespace std;

// NUR MAL SO ALS ANMERKUNG!!!
// TEXTUREN KÖNNEN JETZT GELADEN WERDEN!!!
// ES LAG DARAN, DASS DIE TEXTUREN IM
// EXE-VERZEICHNIS GESUCHT WURDEN

// Nur mal so als weitere Anmerkung:
// Ich arbeite gerade an dem Textur-Bug,
// der allen Texturen die gleiche
// Speicheradresse übergibt.

// Nur mal so als Anmerkung,
// nachdem ich diesen Code
// ca. 2 Jahre nicht zu Gesicht
// bekam:
// I have no idea, what I'm doing

class CGraphic_SimpleMesh
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		bool InitTextures (CGraphic_Textures *TexMng);
		void Delete ();

		void SetPos (D3DXVECTOR3 Pos);
		void SetPos (float x, float y, float z);

		// Rotationsfunktionen, die Gradmaße annehmen
		void SetRotX (float X);
		void SetRotY (float Y);
		void SetRotZ (float Z);
		void SetRotA (float A, D3DXVECTOR3 Axis);

		// Rotationsfunktionen, die Radiantmaße annehmen
		void SetRotXR (float X);
		void SetRotYR (float Y);
		void SetRotZR (float Z);
		void SetRotAR (float A, D3DXVECTOR3 Axis);

		// Skalierungsfunktionen
		void SetScaleX (float X);
		void SetScaleY (float Y);
		void SetScaleZ (float Z);
		void SetScale  (D3DXVECTOR3 Scale);
		void SetScale  (float X,
					    float Y,
					    float Z);

		inline D3DXVECTOR3 GetPos () {return m_Pos;}
		inline D3DXVECTOR4 GetRot () {return m_Rot;}

		void SetPath (LPCSTR Path);
		void LoadXFile (LPCSTR File);
		void Render ();

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;

		unsigned long		m_NumMaterials;
		D3DMATERIAL9		*m_MeshMaterials;
		LPDIRECT3DTEXTURE9	*m_MeshTextures;
		CGraphic_Textures	*m_TexMng;
		LPCSTR				m_Path;
		string				*m_StrDir;
		LPD3DXMESH			m_Mesh;

		D3DXMATRIX m_WorldMat;
		D3DXMATRIX m_TransMat;
		D3DXMATRIX m_RotMat1;
		D3DXMATRIX m_RotMat2;
		D3DXMATRIX m_RotMat;
		D3DXMATRIX m_RotMatX;
		D3DXMATRIX m_RotMatY;
		D3DXMATRIX m_RotMatZ;
		D3DXMATRIX m_RotMatA;
		D3DXMATRIX m_ScaleMat;
		D3DXVECTOR3 m_Scale;
		D3DXVECTOR4 m_Rot;
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Axis;
};
#endif