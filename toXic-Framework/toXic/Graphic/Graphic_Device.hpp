#ifndef GRAPHIC_DEVICE_IS_DEFINED
#define GRAPHIC_DEVICE_IS_DEFINED

#include "../Common/Common.hpp"

#pragma comment (lib, "x64/d3d9.lib")
#pragma comment (lib, "x64/d3dx9.lib")

#include <d3dx9.h>

class IGraphic_Device
{
	public:
		IGraphic_Device ();
		~IGraphic_Device ();

		LPDIRECT3D9 GetInterface () {return m_D3D9;}

	private:
		LPDIRECT3D9 m_D3D9;
};

IGraphic_Device *CreateGraphicDevice ();
void ReleaseGraphicDevice (IGraphic_Device *Device);
#endif