#include "Game.hpp"

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFensterStil)
{
	CGame Game;
	Game.Init (hThisInstance);
	Game.Run ();
	return Game.Delete ();
}