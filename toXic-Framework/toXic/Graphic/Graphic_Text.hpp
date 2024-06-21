#ifndef GRAPHIC_TEXT_IS_DEFINED
#define GRAPHIC_TEXT_IS_DEFINED

#include "Graphic_Window.hpp"
#include "Graphic_Text_Types.hpp"

class CGraphic_Text
{
	public:
		bool Init (LPDIRECT3DDEVICE9 Device, HWND hWnd);
		void Delete ();

		void SetFont (const WCHAR *FontName);
		void SetLarge (UINT Large);
		void SetColor (D3DCOLOR Color);
		void SetColor (int R, int G, int B);
		void SetPos (int X, int Y);
		RECT Dock (CGraphic_Text *Text, int dir);
		void Undock ();
		void SetText (LPCWSTR Text);
		void SetFormat (DWORD Format);

		void Create ();

		void Render ();

		void CalculateRect ();
		RECT GetRect () {return m_Rect;}
		RECT GetDockedRect () {return m_DockRect;}
		bool IsDocked () {return m_Dock;}

	private:
		LPDIRECT3DDEVICE9 m_D3D9Device;
		LPD3DXFONT m_Font;
		D3DXFONT_DESC m_FontProps;
		RECT m_Rect;
		RECT m_DockRect;
		bool m_Dock;
		D3DCOLOR m_FontColor;
		DWORD m_Format;

		LPWSTR m_Text;

		HWND m_hWnd;
};
#endif