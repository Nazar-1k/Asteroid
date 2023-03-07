#include "Game.h"
#include <windows.h>

	

int main(int argc, char* args[])
{
	//close console

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	srand(static_cast<int>(time(NULL)));

	Game game;
	game.run();
	
	return 0;
}