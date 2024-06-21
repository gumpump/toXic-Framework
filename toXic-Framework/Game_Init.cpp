#include "Game.hpp"

#pragma region "Game::Init_Graphic" initialisiert sämtliche Grafik-Interfaces.
void CGame::Init_Graphic ()
{
	DeviceGraphic = CreateGraphicDevice ();

	#pragma region Initialisieren des Hauptfensters
	{
		if (Window.Init (DeviceGraphic) == false)
		{
			MessageBox (m_hWnd,
						L"Fenster konnte nicht erstellt werden. \n"
						L"Fehlercode: 1",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}

		tX_XML_Wnd *WndProperties = new tX_XML_Wnd;

		bool bScriptLoad = LoadWndScript (WndProperties,
										  "Data/Script/Prgcfg/Wnd.xml");

		if (bScriptLoad == false)
		{
			MessageBox (m_hWnd,
						L"Konfigurationsdatei konnte nicht geladen werden.",
						L"Fataler Fehler",
						MB_ICONWARNING);
		}

		else
		{
			Window.InitWnd (m_hWnd,
							WndProperties->Width,
							WndProperties->Height,
							WndProperties->Windowed);
			Window.SetClearColor (WndProperties->R,
								  WndProperties->G,
								  WndProperties->B);

			if (Window.GetDevice () == ZERO)
			{
				MessageBox (m_hWnd,
							L"Fenster ist ungültig. \n"
							L"Fehlercode: 14",
							L"Fataler Fehler",
							MB_ICONWARNING);
				PostQuitMessage (0);
			}
		}

		delete WndProperties;
	}
	#pragma endregion

	#pragma region Initialisieren der Texte
	{
		if (TextContainer.Init () == false)
		{
			MessageBox (m_hWnd,
						L"Text-Container konnte nicht initialisiert werden.",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}

		#pragma region Kamera-Koordinaten
		{
			tX_XML_Txt *TxtProperties = new tX_XML_Txt;
			bool bScriptLoad = LoadTxtScript (TxtProperties,
											  "Data/Script/Txtcfg/Cam.xml");
			if (bScriptLoad == false)
			{
				MessageBox (m_hWnd,
							L"Konfigurationsdatei konnte nicht geladen werden.",
							L"Fataler Fehler",
							MB_ICONWARNING);
				PostQuitMessage (0);
			}

			LPWSTR Tmp = NULL;

			tX_TXT *Text = TextContainer.Add (TXT_CAM);
			Text->Text.Init		(Window.GetDevice (), m_hWnd);

			int s = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Name.c_str (), -1, 0, 0);
			Tmp = new WCHAR[s];
			MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Name.c_str (), -1, Tmp, s);

			Text->Text.SetFont	(Tmp);

			delete[] Tmp;

			Text->Text.SetLarge (TxtProperties->Large);
			Text->Text.SetPos	(TxtProperties->PosX,
								 TxtProperties->PosY);
			Text->Text.SetColor (TxtProperties->R,
								 TxtProperties->G,
								 TxtProperties->B);

			s = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Text.c_str (), -1, 0, 0);
			Tmp = new WCHAR[s];
			MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Text.c_str (), -1, Tmp, s);

			Text->Text.SetText	(Tmp);

			delete[] Tmp;

			Text->Text.Create	();
		}
		#pragma endregion

		#pragma region Licht-Koordinaten
		{
			tX_XML_Txt *TxtProperties = new tX_XML_Txt;
			bool bScriptLoad = LoadTxtScript (TxtProperties,
											  "Data/Script/Txtcfg/Light.xml");
			if (bScriptLoad == false)
			{
				MessageBox (m_hWnd,
							L"Konfigurationsdatei konnte nicht geladen werden.",
							L"Fataler Fehler",
							MB_ICONWARNING);
				PostQuitMessage (0);
			}

			LPWSTR Tmp = NULL;

			tX_TXT *Text = TextContainer.Add (TXT_LIGHT);
			Text->Text.Init		(Window.GetDevice (), m_hWnd);

			int s = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Name.c_str (), -1, 0, 0);
			Tmp = new WCHAR[s];
			MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Name.c_str (), -1, Tmp, s);

			Text->Text.SetFont	(Tmp);

			delete[] Tmp;

			Text->Text.SetLarge (TxtProperties->Large);
			Text->Text.SetPos	(TxtProperties->PosX,
								 TxtProperties->PosY);
			Text->Text.SetColor (TxtProperties->R,
								 TxtProperties->G,
								 TxtProperties->B);

			s = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Text.c_str (), -1, 0, 0);
			Tmp = new WCHAR[s];
			MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, TxtProperties->Text.c_str (), -1, Tmp, s);

			Text->Text.SetText	(Tmp);

			delete[] Tmp;

			Text->Text.Create	();
			
			tX_Graphic_Text *TextCam = TextContainer.Get (TXT_CAM);
			Text->Text.Dock (&TextCam->Text, TXT_DIR_RIGHT);
		}
		#pragma endregion
	}
	#pragma endregion

	#pragma region Initialisieren der Kamera
	{
		if (Camera.Init (Window.GetDevice (), 10000.0f) == false)
		{
			MessageBox (m_hWnd,
						L"Kamera konnte nicht erstellt werden. \n"
						L"Fehlercode: 13",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}

		CamPos = tX_MOVE(0.0f, 30.0f, 0.0f, STANDART_SPEED);
		MovingCamera.SetPosition (CamPos.Vec);
		MovingCamera.AddPosition(tX_MOVE(255.0f,	20.0f,		0.0f,	STANDART_SPEED));
		MovingCamera.AddPosition(tX_MOVE(255.0f,	10.0f,		255.0f, STANDART_SPEED));
		MovingCamera.AddPosition(tX_MOVE(0.0f,		20.0f,		255.0f, STANDART_SPEED));
		MovingCamera.AddPosition(tX_MOVE(0.0f,		10.0f,		0.0f,	STANDART_SPEED));
		MovingCamera.Loop(true);
		MovingCamera.Start(0);
		ProcessManager.AttachProcess(&MovingCamera);

		CamLA = tX_MOVE (127.0f, 1.0f, 127.0f, STANDART_SPEED);
		MovingLA.SetPosition (CamLA.Vec);
		MovingLA.AddPosition(tX_MOVE(255.0f, 80.0f, 0.0f, STANDART_SPEED));
		MovingLA.AddPosition(tX_MOVE(0.0f, 20.0f, 255.0f, STANDART_SPEED));
		MovingLA.AddPosition(tX_MOVE(128.0f, 0.0f, 128.0f, STANDART_SPEED));
		MovingLA.Loop(true);
		MovingLA.Start(0);
		ProcessManager.AttachProcess(&MovingLA);

		CamRotAngleY = 0.4f;
		CamRotAngleX = 0.4f;

		Camera.SetPos	 (CamPos.Vec);
		Camera.SetLookAt (CamLA.Vec);
	}
	#pragma endregion

	#pragma region Initialisieren des Textur-Managers
	{
		if (Textures.Init (Window.GetDevice ()) == false)
		{
			MessageBox (m_hWnd,
						L"Textur-Manager konnte nicht erstellt werden. \n"
						L"Fehlercode: 18",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}
	}
	#pragma endregion

	#pragma region Initialisieren der Meshes
	{
		#pragma region Haus
		{
			AssimpMesh.Init(Window.GetDevice());
			AssimpMesh.LoadMeshFile("Data/Graphic/Mesh/Door/door3ds.3DS");
		}
		#pragma endregion
	}
	#pragma endregion

	#pragma region Initialisieren der Lichtquellen
	{
		if (Light.Init (Window.GetDevice ()) == false)
		{
			MessageBox (m_hWnd,
						L"Lichtquelle 1 konnte nicht initialisiert werden. \n"
						L"Fehlercode: 16",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}

		D3DCOLORVALUE Diffuse;
		Diffuse.r = 255.0f;
		Diffuse.g = 255.0f;
		Diffuse.b = 255.0f;
		Diffuse.a = 1.0f;

		Light.SetType			(D3DLIGHT_POINT);
		Light.SetDiffuse		(Diffuse);
		Light.SetAmbient		(Diffuse);
		Light.SetPos			(CamLA.Vec);
		Light.SetAttenuation	(0.0f, 0);
		Light.SetAttenuation	(0.125f, 1);
		Light.SetAttenuation	(0.0f, 2);
		Light.SetRange			(10.0f);
		Light.SetFalloff		(1.0f);
		Light.SetPhi			(D3DXToRadian (20.0f));
		Light.SetTheta			(D3DXToRadian (10.0f));
		Light.SetIndex			(0);
		Light.RegisterLight		();
		LightLock = false;
		LightsOn = FALSE;
		Light.SetEnable			(TRUE);

		// Die Belichtung wird sorglos in die Hände von DirectX gelegt,
		// (weil ich zu blöd dafür bin)....war

		// Mittlerweil geht das Licht, aber es verschiebt sich nur auf der X- und Z-Achse, d.h. die Winkel werden nicht berücksichtigt.
		CGraphic_Light::SetUltimateLightControl (Window.GetDevice (), LightsOn);
	}
	#pragma endregion

	#pragma region Initialisieren des Nebels
	{
		Fog.Init (Window.GetDevice ());
		Fog.SetMode (FOG_VERTEX, FOG_LINEAR);
		Fog.SetColor (255, 255, 255);
		Fog.SetDistance (200.0f);
		Fog.SetEnd (1000.0f);
		Fog.SetDensity (0.005f);
		Fog.EnableRangeFog (TRUE);
		FogOn = FALSE;
		Fog.SetActive (FogOn);
		FogLock = false;
	}
	#pragma endregion

	#pragma region Initialisieren der Skybox
	{
		Skybox.Init (Window.GetDevice ());
		Skybox.InitTextures (&Textures);
		Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/FRONT.jpg", SKY_FRONT);
		Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/BACK.jpg",	SKY_BACK);
		Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/LEFT.jpg",	SKY_LEFT);
		Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/RIGHT.jpg", SKY_RIGHT);
		Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/UP.jpg",	SKY_UP);
		Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/DOWN.jpg",	SKY_DOWN);
		Skybox.SetPos (CamPos.Vec);
		Skybox.Create ();
	}
	#pragma endregion

	#pragma region Initialisieren der Umgebungsobjekte
	{
		#pragma region Heightmap
		{
			Heightmap.Init (Window.GetDevice ());
			Heightmap.SetFilename ("Data/Graphic/Area/Heightmap/HM.bmp");
			Heightmap.SetTexturename ("Data/Graphic/Area/Heightmap/TM.bmp");
			Heightmap.SetDetailname ("Data/Graphic/Area/Heightmap/DM.bmp");
			Heightmap.SetTilesPerColumn (32);
			Heightmap.SetTilesPerRow (32);
			D3DXVECTOR3 Temp = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
			Heightmap.SetCamPos (Temp);
			Heightmap.SetCamLA (CamLA.Vec);
			Heightmap.Create ();

			D3DXVECTOR3 Vec = Mesh.GetPos ();
			Vec.y = Heightmap.AdjustHeight (Vec);
			Mesh.SetPos (Vec);
		}
		#pragma endregion
	}
	#pragma endregion
}
#pragma endregion

#pragma region "Game::Init_Input" initialisiert alle Input-Interfaces.
void CGame::Init_Input ()
{
	DeviceInput = CreateInputDevice (m_hWnd, m_hInst);

	#pragma region Initialisieren der Tastatur
	{
		if (Keyboard.Init (DeviceInput) == false)
		{
			MessageBox (m_hWnd,
						L"Tastatur wurde nicht gefunden. \n"
						L"Fehlercode: 2",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}

		else
		{
			Keyboard.Start (0);
			ProcessManager.AttachProcess(&Keyboard);
		}
	}
	#pragma endregion
	/*
	#pragma region Initialisieren der Maus
	{
		if (Mouse.Init (DeviceInput) == false)
		{
			MessageBox (m_hWnd,
						L"Maus wurde nicht gefunden. \n"
						L"Fehlercode: 3",
						L"Fataler Fehler",
						MB_ICONWARNING);
			PostQuitMessage (0);
		}
	}
	#pragma endregion
	*/
	#pragma region Initialisieren des Joysticks
	{
		// Kein Joystick vorhanden
	}
	#pragma endregion
}
#pragma endregion

#pragma region "Game::Init_Audio" initialisiert alle Audio-Interfaces.
void CGame::Init_Audio ()
{
}
#pragma endregion

#pragma region "Game::Init_Testobjects" initialisiert alle Testobjekte.
void CGame::Init_Testobjects ()
{
//	AssimpMesh.Init (Window.GetDevice ());
//	AssimpMesh.LoadMeshFile ("Data/Graphic/Mesh/Lamborghini/Lamborghini.x");
//	Window.GetDevice ()->SetRenderState (D3DRS_FILLMODE, D3DFILL_SOLID);
}
#pragma endregion