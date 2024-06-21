#include "Game.hpp"

#pragma region "Game::Init" wird benötigt, um das Hauptprogramm zu initialisieren.
void CGame::Init (HINSTANCE hInst)
{
	m_hInst = hInst;
	m_wincl.hInstance = m_hInst;
	m_wincl.lpszClassName = L"toXic";
	m_wincl.lpfnWndProc = WindowProcedure;
	m_wincl.style = CS_DBLCLKS;
	m_wincl.cbSize = sizeof (WNDCLASSEX);
	m_wincl.hIcon = LoadIcon (m_hInst, MAKEINTRESOURCE (IDI_ICON1));
	m_wincl.hIconSm = LoadIcon (m_hInst, MAKEINTRESOURCE (IDI_ICON1));
	m_wincl.hCursor = LoadCursor (ZERO, IDI_APPLICATION);
	m_wincl.lpszMenuName = ZERO;
	m_wincl.cbClsExtra = 0;
	m_wincl.cbWndExtra = 0;
	m_wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	RegisterClassEx (&m_wincl);

	m_hWnd = CreateWindowEx (0,
						     m_wincl.lpszClassName,
						     L"toXic",
						     WS_OVERLAPPEDWINDOW,
						     CW_USEDEFAULT,
						     CW_USEDEFAULT,
						     544,
						     375,
						     HWND_DESKTOP,
						     ZERO,
						     m_wincl.hInstance,
						     ZERO);

	ShowWindow (m_hWnd, SW_SHOW);

	Timer.Start (0);
	ProcessManager.AttachProcess (&Timer);
	Time = 0;

	GraphicActive = false;

	#ifndef KBAA
	if (MessageBox (m_hWnd,
					L"Soll DirectX-Grafik aktiviert werden?",
					L"Optionen",
					MB_YESNO | MB_ICONQUESTION)
					== IDYES)
	{
		Init_Graphic ();
		GraphicActive = true;
	}

	else
	{
		GraphicActive = false;
	}
	#else
	Init_Graphic ();
	GraphicActive = true;
	#endif

	Init_Input ();
	Init_Audio ();
	Init_Testobjects ();
}
#pragma endregion

#pragma region "Game::Run" startet das Hauptprogramm und lässt es laufen, bis die Abschaltbedingungen erfüllt werden.
void CGame::Run ()
{
	while(m_messages.message != WM_QUIT)
    {
        if(PeekMessage (&m_messages, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage (&m_messages);
            DispatchMessage (&m_messages);
        }

		else
		{
			Process ();
			if (GraphicActive)
			{
				Render ();
			}
		}
	}
}
#pragma endregion

#pragma region "Game::Delete" beendet alle DX-, und alle toXic-Interfaces und entfernt ihre Übereste aus dem Speicher.
int CGame::Delete ()
{
	Delete_Testobjects ();
	Delete_Audio ();
	Delete_Input ();
	if (GraphicActive == true)
	{
		Delete_Graphic ();
	}
	Timer.Delete ();

	return static_cast<int> (m_messages.wParam);
}
#pragma endregion

#pragma region "Game::WindowProcedure" wird als Message-Handler benutzt.
LRESULT CALLBACK CGame::WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage (0);
		} break;

		default:
		{
			return DefWindowProc (hwnd, message, wParam, lParam);
		} break;
	}
}
#pragma endregion