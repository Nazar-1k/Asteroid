#include "Game.h"

Game::Game()
	:SCREEN_WIDTH(1000), SCREEN_HEIGHT(600), quit(false),
	window(nullptr), renderer(nullptr), bg(nullptr)
{
}

Game::~Game()
{
	close();
}

bool Game::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize!SDL Error :\n" << SDL_GetError() << std::endl;
		return false;
	}

	//Create window
	window = SDL_CreateWindow("Asteroid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Window could not be created! SDL Error:\n"<< SDL_GetError()<<std::endl;
		return false;
	}
	
	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "Renderer could not be created!SDL Error :\n" << SDL_GetError() << std::endl;
		return false;
	}
	//Create BG
	bg = std::unique_ptr<BG>(new BG{ "data/background.png", SCREEN_WIDTH, SCREEN_HEIGHT, renderer });
	if (!bg->isEmpty())
	{
		std::cout << "BG ERRoR: \n" << std::endl;
		return false;
	}

	ship = std::unique_ptr<Ship>(new Ship{ "data/spaceship.png", SCREEN_WIDTH, SCREEN_HEIGHT, renderer });
	if (!bg->isEmpty())
	{
		std::cout << "Ship ERRoR: \n" << std::endl;
		return false;
	}

	return true;
}

void Game::update()
{
	ship->move();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	bg->render();
	ship->render();


	SDL_RenderPresent(renderer);
}

void Game::pollEventWindow()
{
	if(SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
			quit = true;
		ship->PoolEvent(e);
	}
}

void Game::run()
{	
	if (!init())
	{
		std::cout<<"Failed to initialize!\n"<<std::endl;
	}
	else
	{
		while (!quit)
		{
			pollEventWindow();
			update();
			render();
		}
	}	
}

void Game::close()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}