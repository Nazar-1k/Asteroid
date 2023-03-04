#pragma once

#include <iostream>
#include "Background.h"
#include "Arrow.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "DestroyParticles.h"
#include "Button.h"
#include "Text.h"
#include <vector>


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

	void run();


private:
	bool initWindow();
	bool initeObject();
	bool initButton();
	void deleteObject();
	void initAsteroid();

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
	std::vector<std::unique_ptr<Asteroid>> bigAsteroids;
	std::vector<std::unique_ptr<Asteroid>> smallAsteroids;
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::vector<std::unique_ptr<DestroyParticles>> destroy_particle;

	#pragma endregion

	#pragma region Main_menu
	std::unique_ptr<Text> Asteroid_main_menu_text;
	
	std::unique_ptr<Button> pLay_button;

	std::unique_ptr<Button> quit_play;

	#pragma endregion
	


};

