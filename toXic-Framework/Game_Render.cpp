#include "Game.hpp"

#pragma region "Game::Render" rendert alle Objekte.
void CGame::Render ()
{
	Window.BeginScene		();
	Render_Skybox			();
	Render_Area_Ingredients ();
	Render_GUI_Elements		();
	RenderManager.Update	(Timer.GetElapsed());
	AssimpMesh.Render();
	Window.EndScene			();
}
#pragma endregion

#pragma region "Game::Render_GUI_Elements" rendert alle GUI-Elemente
void CGame::Render_GUI_Elements ()
{
	tX_TXT *Text = TextContainer.Get (TXT_CAM);
	Text->Text.Render ();
	Text = TextContainer.Get (TXT_LIGHT);
	Text->Text.Render ();
}
#pragma endregion

#pragma region "Game::Render_Skybox" rendert die Skybox.
void CGame::Render_Skybox ()
{
	Skybox.Render ();
}
#pragma endregion

#pragma region "Game::Render_Area_Ingredients" rendert alle Umgebungsgegenstände
void CGame::Render_Area_Ingredients ()
{
	Heightmap.Render ();
}
#pragma endregion