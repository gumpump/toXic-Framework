#include "Graphic_Text.hpp"

bool CGraphic_Text::Init (LPDIRECT3DDEVICE9 Device, HWND hWnd)
{
	if (Device != ZERO)
	{
		m_D3D9Device = Device;
	}

	else
	{
		return false;
	}

	m_hWnd = hWnd;

	wcscpy (m_FontProps.FaceName, __TEXT("Arial"));
	m_FontProps.Height = 0;
	m_FontProps.Width = 0;
	m_FontProps.Italic = false;
	m_FontProps.MipLevels = 1;
	m_FontProps.Weight = 500;
	m_FontProps.CharSet = DEFAULT_CHARSET;
	m_FontProps.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_FontProps.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	m_FontProps.Quality = DEFAULT_QUALITY;
	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = 0;
	m_Rect.bottom = 0;
	m_Format = DT_LEFT | DT_NOCLIP;

	m_Text = new WCHAR[1024];

	m_Dock = false;

	return true;
}

void CGraphic_Text::Delete ()
{
	if (m_Font != ZERO)
	{
		m_Font->Release ();
		m_Font = ZERO;
	}

	m_hWnd = ZERO;
	m_D3D9Device = ZERO;
}

void CGraphic_Text::SetFont (const WCHAR *FontName)
{
	wcscpy (m_FontProps.FaceName, FontName);
}

void CGraphic_Text::SetLarge (UINT Large)
{
	m_FontProps.Height = static_cast<int>(Large);
}

void CGraphic_Text::SetColor (D3DCOLOR Color)
{
	m_FontColor = Color;
}

void CGraphic_Text::SetColor (int R, int G, int B)
{
	m_FontColor = D3DCOLOR_XRGB (R, G, B);
}

void CGraphic_Text::SetPos (int X, int Y)
{
	m_Rect.left = X;
	m_Rect.top = Y;
	m_Dock = false;
}

RECT CGraphic_Text::Dock (CGraphic_Text *Text, int dir)
{
	CalculateRect ();
	Text->CalculateRect ();

	RECT Tmp;

	if (Text->IsDocked () == true)
	{
		Tmp = Text->GetDockedRect ();
	}

	else
	{
		Tmp = Text->GetRect ();
	}

	switch (dir)
	{
		case TXT_DIR_LEFT:
		{
			m_DockRect.left = Tmp.left - (m_Rect.right - m_Rect.left);
			m_DockRect.top = Tmp.top;
		} break;

		case TXT_DIR_DOWN:
		{
			m_DockRect.left = Tmp.left;
			m_DockRect.top = Tmp.bottom + 1;
		} break;

		case TXT_DIR_RIGHT:
		{
			m_DockRect.left = Tmp.right + 1;
			m_DockRect.top = Tmp.top;
		} break;

		case TXT_DIR_UP:
		{
			m_DockRect.left = Tmp.left;
			m_DockRect.top = Tmp.top - (m_Rect.bottom - m_Rect.top);
		} break;

		default:
		{
		} break;
	}

	m_Dock = true;

	return m_DockRect;
}

void CGraphic_Text::Undock ()
{
	m_Dock = false;
}

void CGraphic_Text::SetText (LPCWSTR Text)
{
	wcscpy (m_Text, Text);
}

void CGraphic_Text::SetFormat (DWORD Format)
{
	m_Format = Format;
}

void CGraphic_Text::Create ()
{
	FAIL (D3DXCreateFontIndirect (m_D3D9Device,
								  &m_FontProps,
								  &m_Font));
}

void CGraphic_Text::Render ()
{
	if (m_Dock == true)
	{
		m_Font->DrawText (ZERO,
						  m_Text,
						  -1,
						  &m_DockRect,
						  DT_CALCRECT,
						  m_FontColor);

		m_Font->DrawText (ZERO,
						  m_Text,
						  -1,
						  &m_DockRect,
						  m_Format,
						  m_FontColor);
	}

	else if (m_Dock == false)
	{
		m_Font->DrawText (ZERO,
						  m_Text,
						  -1,
						  &m_Rect,
						  DT_CALCRECT,
						  m_FontColor);

		m_Font->DrawText (ZERO,
						  m_Text,
						  -1,
						  &m_Rect,
						  m_Format,
						  m_FontColor);
	}
}

void CGraphic_Text::CalculateRect ()
{
	m_Font->DrawText (ZERO,
					  m_Text,
					  -1,
					  &m_Rect,
					  DT_CALCRECT,
					  m_FontColor);
}