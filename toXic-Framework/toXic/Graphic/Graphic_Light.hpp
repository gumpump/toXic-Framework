#ifndef GRAPHIC_LIGHT_IS_DEFINED
#define GRAPHIC_LIGHT_IS_DEFINED

#include "Graphic_Window.hpp"

class CGraphic_Light
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		void Delete ();

		void SetLightData	(D3DLIGHT9 *Light);
		void SetType		(D3DLIGHTTYPE Type);
		void SetDiffuse		(D3DCOLORVALUE Diffuse);
		void SetDiffuse		(float R, float G, float B, float A);
		void SetSpecular	(D3DCOLORVALUE Specular);
		void SetSpecular	(float R, float G, float B, float A);
		void SetAmbient		(D3DCOLORVALUE Ambient);
		void SetAmbient		(float R, float G, float B, float A);
		void SetPos			(D3DXVECTOR3 Pos);
		void SetPos			(float X, float Y, float Z);
		void SetDir			(D3DXVECTOR3 Dir);
		void SetDir			(float X, float Y, float Z);
		void SetRange		(float Range);
		void SetFalloff		(float Falloff);
		void SetAttenuation (float Attenuation, int Index);
		void SetTheta		(float Theta);
		void SetPhi			(float Phi);

		void SetIndex (int Index);
		void RegisterLight ();
		void SetEnable (BOOL Value);

		D3DXVECTOR3 GetPos () {if (m_Light != NULL){return m_Light->Position;}}
		D3DXVECTOR3 GetDir () {if (m_Light != NULL){return m_Light->Direction;}}

		static void CGraphic_Light::SetUltimateLightControl (LPDIRECT3DDEVICE9 Device, BOOL Value)
		{
			FAIL (Device->SetRenderState(D3DRS_LIGHTING, Value));
		}

		static void CGraphic_Light::SetRoomLight (LPDIRECT3DDEVICE9 Device,
												  int A, int R, int G, int B)
		{
			FAIL (Device->SetRenderState (D3DRS_AMBIENT, D3DCOLOR_ARGB (A, R, G, B)));
		}
			
	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;
		D3DLIGHT9 *m_Light;
		int m_Index;
		bool Refer;
};
#endif