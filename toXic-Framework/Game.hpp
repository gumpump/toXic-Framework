#ifndef GAME_IS_DEFINED
#define GAME_IS_DEFINED

#include "tX_Input.hpp"
#include "tX_Controlling.hpp"
#include "tX_Graphic.hpp"

#include "Timer.hpp"
#include <sstream>

#pragma region Defines

// KBAA schaltet die Abfrage nach Grafikabschaltung ab
#define KBAA // = Kein Bock auf Abfrage

#define TXT_CAM		1
#define TXT_LIGHT	2
#define TXT_FPS		3

#pragma endregion

using namespace std;

class CGame
{
	public:
		void Init  (HINSTANCE hInst);
		void Run   ();
		int Delete (); // Programm, mach dich bereit auf deine Vernichtung!!!!

	private: // Auf Deutsch, DIE PRIVATEN VARIABLEN/FUNKTIONEN GEHEN KEINEN WAS AN!!!!
		// WinApi-CALLBACK-Funktion (Message-Schleife) 
		static LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

		
		// Initialisierung
		#pragma region Initialisierungsfunktionen
		void Init_Graphic ();		// Beinhaltet Movement-Initialisierung
		void Init_Input	  ();
		void Init_Audio   ();
		void Init_Testobjects ();
		#pragma endregion

		// Arbeitsphase
		#pragma region Prozessfunktionen
		void Process				();
		void Process_Menu			();
		void Process_Graphic		();
		void Process_Input			();	// Beinhaltet Process_Movement ();
		void Process_Movement		();
		void Process_Audio			();
		void Process_Background		();
		void Process_Testobjects	();
		#pragma endregion

		// Anzeige
		#pragma region Grafikfunktionen
		void Render					 ();
		void Render_GUI_Elements	 ();
		void Render_Skybox			 ();
		void Render_Area_Ingredients ();// Rendert alle Umgebungsgegenstände, wie z.B. Räume oder ganze Levels.
		#pragma endregion

		// Aufräumarbeiten
		#pragma region Löschfunktionen
		void Delete_Graphic		();	// Beinhaltet Movement-Entfernung
		void Delete_Input		();
		void Delete_Audio		();
		void Delete_Testobjects ();
		#pragma endregion
		

		// Variablen
		#pragma region WinApi-Variablen

		HINSTANCE	m_hInst;
		HWND		m_hWnd;
		WNDCLASSEX	m_wincl;
		MSG			m_messages;

		#pragma endregion

		#pragma region Allgemeine Interfaces und Variablen

		CTimer	Timer;
		float	Time;

		CProcess_Manager ProcessManager;
		CProcess_Timer *WaitProcess;

		#pragma endregion

		#pragma region Grafik-Interfaces und -Variablen

		CProcess_Manager RenderManager;

		bool						GraphicActive;
		IGraphic_Device				*DeviceGraphic;

		CGraphic_Window				Window;

		CGraphic_Textures			Textures;

		CGraphic_SimpleMesh			Mesh;
		float						Dist;
		bool						Collision;
		CGraphic_AssimpMesh			AssimpMesh;
		CGraphic_Process_Render		*HouseRender;

		CGraphic_Light				Light;
		bool						LightLock;
		BOOL						LightsOn;

		CGraphic_Fog				Fog;
		bool						FogLock;
		BOOL						FogOn;

		CGraphic_Camera				Camera;
		tX_MOVE						CamPos;
		CMovement_Process			MovingCamera;
		tX_MOVE						CamLA;
		CMovement_Process			MovingLA;
		float						CamRotAngleY;
		float						CamRotAngleX;

		CGraphic_Heightmap			Heightmap;

		CGraphic_Text_Container		TextContainer;

		CGraphic_Skybox				Skybox;

		#pragma endregion

		#pragma region Input-Interfaces und -Variablen

		IInput_Device	*DeviceInput;
		CInput_Keyboard	Keyboard;
		//CInput_Mouse	Mouse;

		#pragma endregion

		#pragma region Audio-Interfaces und -Variablen

		// Keine vorhanden

		#pragma endregion
		
		#pragma region Testobjekte

		wstring Coords;

		#pragma endregion
};
#endif