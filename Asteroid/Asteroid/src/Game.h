#pragma once

#include <iostream>
#include "SpaceShip.h"
#include "Background.h"
#include "Timer.h"
#include "Arrow.h"


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

	void showCursor(bool bShow);
	void onMouseMove();

	void run();


private:
#pragma region Window
	
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	//Timers
	Timer fpsTimer;
	

	bool quit;
	SDL_Event e;
	SDL_MouseMotionEvent mouse_e;

	SDL_Window* window;
	SDL_Renderer* renderer;

#pragma endregion
#pragma region Sprites

	std::unique_ptr<BG> bg;
	std::unique_ptr<Ship> ship;
	std::unique_ptr<Arrow> arrow;

#pragma endregion
};

