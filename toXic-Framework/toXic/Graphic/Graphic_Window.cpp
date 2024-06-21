#include "Graphic_Window.hpp"

bool CGraphic_Window::Init (IGraphic_Device *Device)
{
	if (Device != ZERO)
	{
		if (Device->GetInterface () == ZERO)
		{
			return false;
		}

		else
		{
			m_D3D9 = Device->GetInterface ();
		}
	}

	else
	{
		return false;
	}

	return true;
}

void CGraphic_Window::Delete ()
{
	m_D3D9 = ZERO;

	if (m_D3D9Device != ZERO)
	{
		m_D3D9Device->Release ();
		m_D3D9Device = ZERO;
	}
}

void CGraphic_Window::InitWnd (HWND hWnd, int Width, int Height, bool bWindowed)
{

	// Parameter fuer den Modus festlegen
	D3DPRESENT_PARAMETERS PParams;
	ZeroMemory(&PParams, sizeof (PParams));

	PParams.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	PParams.hDeviceWindow    = hWnd;
	PParams.Windowed         = bWindowed;

	PParams.BackBufferWidth  = Width;
	PParams.BackBufferHeight = Height;
	PParams.BackBufferFormat = D3DFMT_A8R8G8B8;

	// Z-Buffer erzeugen
	PParams.AutoDepthStencilFormat = D3DFMT_D16;
	PParams.EnableAutoDepthStencil = TRUE;

	FAIL (m_D3D9->CreateDevice(D3DADAPTER_DEFAULT,
							   D3DDEVTYPE_HAL,
							   hWnd,
							   D3DCREATE_HARDWARE_VERTEXPROCESSING,
							   &PParams,
							   &m_D3D9Device));

	// Aktivieren des Z-Buffers
	FAIL (m_D3D9Device->SetRenderState(D3DRS_ZENABLE, TRUE));
}

void CGraphic_Window::SetClearColor (D3DCOLOR Color)
{
	m_ClearColor = Color;
}

void CGraphic_Window::SetClearColor (int R, int G, int B)
{
	m_ClearColor = D3DCOLOR_XRGB (R, G, B);
}

void CGraphic_Window::BeginScene ()
{
	FAIL (m_D3D9Device->Clear (ZERO, ZERO, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_ClearColor, 1.0f, ZERO));
	FAIL (m_D3D9Device->BeginScene ());
}

void CGraphic_Window::EndScene ()
{
	FAIL (m_D3D9Device->EndScene ());
	FAIL (m_D3D9Device->Present (ZERO, ZERO, ZERO, ZERO));
}