#ifndef GRAPHIC_WINDOW_IS_DEFINED
#define GRAPHIC_WINDOW_IS_DEFINED

#include "Graphic_Device.hpp"

class CGraphic_Window
{
	public:
		bool Init (IGraphic_Device *Device);
		void Delete ();

		void InitWnd (HWND hWnd, int Width, int Height, bool bWindowed);

		void SetClearColor (D3DCOLOR Color);
		void SetClearColor (int R, int G, int B);

		void BeginScene ();
		void EndScene ();

		LPDIRECT3DDEVICE9 GetDevice () {return m_D3D9Device;}

	private:
		LPDIRECT3D9 m_D3D9;

		LPDIRECT3DDEVICE9 m_D3D9Device;
		HWND m_hWnd;
		D3DCOLOR m_ClearColor;
};
#endif