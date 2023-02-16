#include "Game.h"

Game::Game()
	:SCREEN_WIDTH(640), SCREEN_HEIGHT(480), quit(false),
	window(nullptr), screenSurface(nullptr)
{
	init();
}

Game::~Game()
{
	close();
}

bool Game::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{ 
		createWindow();
	}

	return true;
}

void Game::close()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::run()
{	
		while (!quit)
		{
			pollEventWindow();

			//Update the surface
			SDL_UpdateWindowSurface(window);
		}
}

void Game::createWindow()
{
	//Create window
	window = SDL_CreateWindow("Asteroid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (window == nullptr)
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
}

void Game::pollEventWindow()
{
	if(SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
			quit = true;
	}
}


