#pragma once
#include "Sprite.h"

class Game
{
public:
	Game();
	~Game();

	bool init();

	void run();

private:
#pragma region Window
	
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	bool quit;
	SDL_Event e;

	void createWindow();
	void pollEventWindow();
	void close();
	
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screenSurface;

#pragma endregion

};

