#pragma once

#include <iostream>
#include "SpaceShip.h"
#include "Background.h"

class Game
{
public:
	Game();
	~Game();

	bool init();
	void update();
	void render();

	void pollEventWindow();
	void close();

	void run();


private:
#pragma region Window
	
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	bool quit;
	SDL_Event e;

	SDL_Window* window;
	SDL_Renderer* renderer;

#pragma endregion
#pragma region Sprites

	std::unique_ptr<BG> bg;
	std::unique_ptr<Ship> ship;

#pragma endregion
};

