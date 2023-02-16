#pragma once
#include "Sprite.h"

class Game
{
public:
	Game();
	~Game();

	bool init();

	bool loadMedia();

	void close();

	void run();

private:
	//Screen dimension constants
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screenSurface = nullptr;
};

