#include "Game.h"

Game::Game()
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
}

Game::~Game()
{
	close();
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	return true;
}

void Game::close()
{
	//Free loaded image
	/*SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;*/

	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::run()
{	
	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Apply the PNG image
			/*SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);*/

			//Update the surface
			SDL_UpdateWindowSurface(window);
		}
	}

	//Free resources and close SDL
	close();
}


