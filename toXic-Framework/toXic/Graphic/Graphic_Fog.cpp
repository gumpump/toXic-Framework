#include "Graphic_Fog.hpp"

bool CGraphic_Fog::Init (LPDIRECT3DDEVICE9 Device)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	return true;
}

void CGraphic_Fog::Delete ()
{
	m_D3D9Device = ZERO;
}

void CGraphic_Fog::SetActive (BOOL Active)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGENABLE, Active));
}

void CGraphic_Fog::SetMode (int Mode1, int Mode2)
{
	switch (Mode1)
	{
		case FOG_VERTEX:
		{
			FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGVERTEXMODE, Mode2));
		} break;

		case FOG_TABLE:
		{
			FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGTABLEMODE, Mode2));
		} break;
	}
}

void CGraphic_Fog::SetColor (D3DCOLOR Color)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGCOLOR, Color));
}

void CGraphic_Fog::SetColor (int R, int G, int B)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGCOLOR, D3DCOLOR_XRGB (R, G, B)));
}

void CGraphic_Fog::SetDistance (float Dist)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGSTART, *(DWORD*)&Dist));
}

void CGraphic_Fog::SetEnd (float End)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGEND, *(DWORD*)&End));
}

void CGraphic_Fog::SetDensity (float Dens)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_FOGDENSITY, *(DWORD*)&Dens));
}

void CGraphic_Fog::EnableRangeFog (BOOL Active)
{
	FAIL (m_D3D9Device->SetRenderState (D3DRS_RANGEFOGENABLE, Active));
}