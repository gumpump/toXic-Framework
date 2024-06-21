#ifndef GRAPHIC_FOG_IS_DEFINED
#define GRAPHIC_FOG_IS_DEFINED

#include "Graphic_Window.hpp"
#include "Graphic_Fog_Types.hpp"

class CGraphic_Fog
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device);
		void Delete ();

		void SetActive		(BOOL Active);
		void SetMode		(int Mode1, int Mode2);
		void SetColor		(D3DCOLOR Color);
		void SetColor		(int R, int G, int B);
		void SetDistance	(float Dist);
		void SetEnd			(float End);
		void SetDensity		(float Dens);
		void EnableRangeFog (BOOL Active);

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;
};
#endif