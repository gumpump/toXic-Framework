#ifndef GRAPHIC_CAMERA_IS_DEFINED
#define GRAPHIC_CAMERA_IS_DEFINED

#include "Graphic_Device.hpp"
#include "Graphic_Camera_Types.hpp"

class CGraphic_Camera
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device, float Range);
		void Delete ();

		void SetPos (D3DXVECTOR3 Pos);
		void SetPos (float x, float y, float z);

		void SetLookAt (D3DXVECTOR3 Pos);
		void SetLookAt (float x, float y, float z);

		D3DXVECTOR3 GetPos() { return m_Pos; }
		D3DXVECTOR3 GetLookAt() { return m_LookAt; }

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;

		D3DXMATRIX m_ViewMat;

		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Up;
		D3DXVECTOR3 m_LookAt;
};
#endif