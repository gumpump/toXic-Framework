#include "Graphic_Device.hpp"

IGraphic_Device::IGraphic_Device ()
{
	m_D3D9 = Direct3DCreate9 (D3D9b_SDK_VERSION);
}

IGraphic_Device::~IGraphic_Device ()
{
	if (m_D3D9 != ZERO)
	{
		m_D3D9->Release ();
		m_D3D9 = ZERO;
	}
}

IGraphic_Device *CreateGraphicDevice ()
{
	return new IGraphic_Device;
}

void ReleaseGraphicDevice (IGraphic_Device *Device)
{
	delete Device;
}