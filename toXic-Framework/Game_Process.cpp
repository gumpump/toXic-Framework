#include "Game.hpp"

#pragma region "Game::Process" verarbeitet alle Hauptprogramm-Inhalte.
void CGame::Process ()
{
	// New boys in da hood
	g_sEventManager.Update();
	ProcessManager.Update (Timer.GetElapsed ());

	// Graphic-Verarbeitung
	Process_Graphic		();

	// Menue-Verarbeitung
	Process_Menu		();

	// Input-Verarbeitung
	Process_Input		();

	// Audio-Verarbeitung
	Process_Audio		();

	// Background-Verarbeitung
	Process_Background	();

	// Testobjekt-Verarbeitung
	Process_Testobjects ();
}
#pragma endregion

#pragma region "Game::Process_Menu" verarbeitet alle Menü-Aufrufe.
void CGame::Process_Menu ()
{
	wostringstream strCam;
	strCam.clear ();
	strCam << "CAM-LAX = ";
	strCam << static_cast<int>(Camera.GetLookAt().x);
	strCam << "\nCAM-LAY = ";
	strCam << static_cast<int>(Camera.GetLookAt().y);
	strCam << "\nCAM-LAZ = ";
	strCam << static_cast<int>(Camera.GetLookAt().z);
	strCam << "\nCAM-PX = ";
	strCam << static_cast<int>(Camera.GetPos().x);
	strCam << "\nCAM-PY = ";
	strCam << static_cast<int>(Camera.GetPos().y);
	strCam << "\nCAM-PZ = ";
	strCam << static_cast<int>(Camera.GetPos().z);
	TextContainer.Get (TXT_CAM)->Text.SetText (strCam.str ().c_str ());

	wostringstream strLight;
	strLight.clear ();
	strLight << "LIGHT-PX = ";
	strLight << static_cast<int>(Light.GetPos ().x);
	strLight << "\nLIGHT-PY = ";
	strLight << static_cast<int>(Light.GetPos ().y);
	strLight << "\nLIGHT-PZ = ";
	strLight << static_cast<int>(Light.GetPos ().z);
	TextContainer.Get (TXT_LIGHT)->Text.SetText (strLight.str ().c_str ());

	tX_Graphic_Text *Text = TextContainer.Get (TXT_CAM);
	TextContainer.Get (TXT_LIGHT)->Text.Dock (&Text->Text, TXT_DIR_RIGHT);
}
#pragma endregion

#pragma region "Game::Process_Graphic" verarbeitet alle Grafikoperationen.
void CGame::Process_Graphic ()
{
	Heightmap.SetCamPos						(Camera.GetPos());
	Heightmap.SetCamLA						(Camera.GetLookAt());
		
	//Skybox.SetPos (Camera.GetPos());

	CGraphic_Light::SetUltimateLightControl (Window.GetDevice (), LightsOn);

	if (LightsOn == TRUE)
	{
		Light.SetPos (CamLA.Vec);
		Light.RegisterLight ();
	}

	Fog.SetActive (FogOn);
}
#pragma endregion

#pragma region "Game::Process_Input" verarbeitet alle Hauptprogrammeingaben.
void CGame::Process_Input ()
{
	// Vom User gesteuerte Bewegungsabläufe
	Process_Movement ();

	#pragma region Abschaltbedingungen
	{
		if (Keyboard.IsPressed (DIK_ESCAPE) == true)
		{
			PostQuitMessage (0);
		}
	}
	#pragma endregion

	#pragma region Fillmode ändern
	{
		if (Keyboard.IsPressed (DIK_F6) == true)
		{
			Window.GetDevice ()->SetRenderState (D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}

		else if (Keyboard.IsPressed (DIK_F7) == true)
		{
			Window.GetDevice ()->SetRenderState (D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}
	#pragma endregion

	#pragma region Licht-AN-AUS-Schalter
	{
		if (Keyboard.IsPressed (DIK_F4) == true && LightsOn == FALSE && LightLock == false)
		{
			LightsOn = TRUE;
			LightLock = true;
		}

		else if (Keyboard.IsPressed (DIK_F4) == false && LightsOn == TRUE)
		{
			LightLock = false;
		}

		if (Keyboard.IsPressed (DIK_F4) == true && LightsOn == TRUE && LightLock == false)
		{
			LightsOn = FALSE;
			LightLock = true;
		}

		else if (Keyboard.IsPressed (DIK_F4) == false && LightsOn == FALSE)
		{
			LightLock = false;
		}
	}
	#pragma endregion

	#pragma region Nebel-AN-AUS-Schalter
	{
		if (Keyboard.IsPressed (DIK_F5) == true && FogOn == FALSE && FogLock == false)
		{
			FogOn = TRUE;
			FogLock = true;
		}

		else if (Keyboard.IsPressed (DIK_F5) == false && FogOn == TRUE)
		{
			FogLock = false;
		}

		if (Keyboard.IsPressed (DIK_F5) == true && FogOn == TRUE && FogLock == false)
		{
			FogOn = FALSE;
			FogLock = true;
		}

		else if (Keyboard.IsPressed (DIK_F5) == false && FogOn == FALSE)
		{
			FogLock = false;
		}
	}
	#pragma endregion

	#pragma region Skybox
	{
		if (Keyboard.IsPressed (DIK_F1) == true)
		{
			Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/FRONT.jpg", SKY_FRONT);
			Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/BACK.jpg",	SKY_BACK);
			Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/LEFT.jpg",	SKY_LEFT);
			Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/RIGHT.jpg", SKY_RIGHT);
			Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/UP.jpg",	SKY_UP);
			Skybox.SetTexture ("Data/Graphic/Skybox/Lost Valley/DOWN.jpg",	SKY_DOWN);
		}

		else if (Keyboard.IsPressed (DIK_F2) == true)
		{
			Skybox.SetTexture ("Data/Graphic/Skybox/City Night/FRONT.bmp",	SKY_FRONT);
			Skybox.SetTexture ("Data/Graphic/Skybox/City Night/BACK.bmp",	SKY_BACK);
			Skybox.SetTexture ("Data/Graphic/Skybox/City Night/LEFT.bmp",	SKY_LEFT);
			Skybox.SetTexture ("Data/Graphic/Skybox/City Night/RIGHT.bmp",	SKY_RIGHT);
			Skybox.SetTexture ("Data/Graphic/Skybox/City Night/UP.bmp",		SKY_UP);
			Skybox.SetTexture ("Data/Graphic/Skybox/City Night/DOWN.bmp",	SKY_DOWN);
		}

		else if (Keyboard.IsPressed (DIK_F3) == true)
		{
			Skybox.SetTexture ("Data/Graphic/Skybox/Night Sky/FRONT.bmp",	SKY_FRONT);
			Skybox.SetTexture ("Data/Graphic/Skybox/Night Sky/BACK.bmp",	SKY_BACK);
			Skybox.SetTexture ("Data/Graphic/Skybox/Night Sky/LEFT.bmp",	SKY_LEFT);
			Skybox.SetTexture ("Data/Graphic/Skybox/Night Sky/RIGHT.bmp",	SKY_RIGHT);
			Skybox.SetTexture ("Data/Graphic/Skybox/Night Sky/UP.bmp",		SKY_UP);
			Skybox.SetTexture ("Data/Graphic/Skybox/Night Sky/DOWN.bmp",	SKY_DOWN);
		}
	}
	#pragma endregion

	#pragma region Sounds
	{
	}
	#pragma endregion
}

#pragma endregion

#pragma region "Game::Process_Movement" verarbeitet alle Bewegungsabläufe.
void CGame::Process_Movement ()
{
	#pragma region User-gesteuert
	{
		#pragma region Kamerasteuerung
		{
			#pragma region Tastatur
			{
				/*
				if (Keyboard.IsPressed (DIK_W) == true)
				{
					CamPos.Vec.x += CamPos.Speed * sinf (CamRotAngleY) * Timer.GetElapsed ();
					CamPos.Vec.y += CamPos.Speed * sinf (CamRotAngleX) * Timer.GetElapsed ();
					CamPos.Vec.z += CamPos.Speed * cosf (CamRotAngleY) * Timer.GetElapsed ();
				}

				if (Keyboard.IsPressed (DIK_S) == true)
				{
					CamPos.Vec.x -= CamPos.Speed * sinf (CamRotAngleY) * Timer.GetElapsed ();
					CamPos.Vec.y -= CamPos.Speed * sinf (CamRotAngleX) * Timer.GetElapsed ();
					CamPos.Vec.z -= CamPos.Speed * cosf (CamRotAngleY) * Timer.GetElapsed ();
				}

				if (Keyboard.IsPressed (DIK_LSHIFT) == true)
				{
					if (Keyboard.IsPressed (DIK_A) == true)
					{
						CamPos.Vec.x -= CamPos.Speed * sinf (CamRotAngleY+MAXCAMROT_X) * Timer.GetElapsed ();
						CamPos.Vec.z -= CamPos.Speed * cosf (CamRotAngleY+MAXCAMROT_X) * Timer.GetElapsed ();
					}

					if (Keyboard.IsPressed (DIK_D) == true)
					{
						CamPos.Vec.x += CamPos.Speed * sinf (CamRotAngleY+MAXCAMROT_X) * Timer.GetElapsed ();
						CamPos.Vec.z += CamPos.Speed * cosf (CamRotAngleY+MAXCAMROT_X) * Timer.GetElapsed ();
					}
				}

				else
				{
					if (Keyboard.IsPressed (DIK_A) == true)
					{
						CamRotAngleY -= CamLA.Speed * Timer.GetElapsed ();
					}

					if (Keyboard.IsPressed (DIK_D) == true)
					{
						CamRotAngleY += CamLA.Speed * Timer.GetElapsed ();
					}
				}

				if (Keyboard.IsPressed (DIK_UP) == true)
				{
					CamRotAngleX += CamLA.Speed * Timer.GetElapsed ();
				}

				if (Keyboard.IsPressed (DIK_DOWN) == true)
				{
					CamRotAngleX -= CamLA.Speed * Timer.GetElapsed ();
				}

				if (Keyboard.IsPressed (DIK_LEFT) == true)
				{
					CamPos.Vec.y += CamPos.Speed * Timer.GetElapsed ();
				}

				if (Keyboard.IsPressed (DIK_RIGHT) == true)
				{
					CamPos.Vec.y -= CamPos.Speed * Timer.GetElapsed ();
				}
				*/
			}
			#pragma endregion
			#pragma region Maus
			{/*
				tX_MOUSE_DATA Data = Mouse.GetMouseData ();
				switch (Data.Situation)
				{
					case DIMOFS_X:
					{
						CamRotAngleY += (Data.Data / 10);
					} break;

					case DIMOFS_Y:
					{
						CamRotAngleX += (Data.Data / 10);
					} break;

					default:
					{
					} break;
				};
			*/}
			#pragma endregion
		}
		#pragma endregion
	}
	#pragma endregion

	#pragma region Programm-gesteuert
	{
		Camera.SetPos(MovingCamera.GetPosition());
		Camera.SetLookAt(MovingLA.GetPosition());
	}
	#pragma endregion

	#pragma region Grenzeinhaltung
	{
	}
	#pragma endregion
}
#pragma endregion

#pragma region "Game::Process_Audio" verarbeitet alle Audiooperationen.
void CGame::Process_Audio ()
{
}
#pragma endregion

#pragma region "Game::Process_Background" ist eine Funktion, die momentan keinen bestimmten Verwendungszweck hat.
void CGame::Process_Background ()
{
	// Sonstiges
	// Sonst nichts
}
#pragma endregion

#pragma region "Game::Process_Testobjects" verarbeitet alle Testobjekte.
void CGame::Process_Testobjects ()
{
}
#pragma endregion