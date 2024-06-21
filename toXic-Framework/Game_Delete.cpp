#include "Game.hpp"

#pragma region "Game::Delete_Graphic" beendet und entfernt alle Grafikobjekte und -Interfaces.
void CGame::Delete_Graphic ()
{
	Skybox.Delete			();
	Light.Delete			();
	//Mesh.Delete				();
	Heightmap.Delete		();
	Textures.Delete			();
	Camera.Delete			();
	TextContainer.Delete	();
	Window.Delete			();

	ReleaseGraphicDevice (DeviceGraphic);
}
#pragma endregion

#pragma region "Game::Delete_Input" beendet und entfernt alle Input-Interfaces.
void CGame::Delete_Input ()
{
//	Mouse.Delete	();
	Keyboard.Delete ();

	ReleaseInputDevice (DeviceInput);
}
#pragma endregion

#pragma region "Game::Delete_Audio" beendet und entfernt alle Audioobjekte und -Interfaces.
void CGame::Delete_Audio ()
{
}
#pragma endregion

#pragma region "Game::Delete_Testobjects" beendet und entfernt alle Testobjekte.
void CGame::Delete_Testobjects ()
{
	AssimpMesh.Delete ();
}
#pragma endregion