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
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError();
		return  false;
	}
	
	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "Renderer could not be created!SDL Error :\n" << SDL_GetError() << std::endl;
		return false;
	}
	//Create BG
	bg = std::unique_ptr<BG>(new BG{ "data/background.png", renderer });
	if (!bg->isEmpty())
	{
		std::cout << "BG ERRoR: \n" << std::endl;
		return false;
	}

	ship = std::unique_ptr<Ship>(new Ship{ "data/spaceship.png", renderer });
	if (!ship->isEmpty())
	{
		std::cout << "Ship ERRoR: \n" << std::endl;
		return false;
	}

	arrow = std::unique_ptr<Arrow>(new Arrow{ "data/arrow.tga", renderer });
	if (!arrow->isEmpty())
	{
		std::cout << "Arrow ERRoR: \n" << std::endl;
		return false;
	}

	bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 4, "data/big_asteroid.png", renderer }));
	bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 4, "data/big_asteroid.png", renderer }));
	/*bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ "data/big_asteroid.png", renderer }));*/

	
	for (auto &asteroid : bigAsteroids)
		if (!asteroid->isEmpty())
		{
			return false;
		}

	smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 3, "data/small_asteroid.png", renderer }));
	smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 3, "data/small_asteroid.png", renderer }));
	smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 3, "data/small_asteroid.png", renderer }));
	smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 3, "data/small_asteroid.png", renderer }));

	for (auto& asteroid : smallAsteroids)
		if (!asteroid->isEmpty())
		{
			return false;
		}
	
	
	


	showCursor(false);

	return true;
}

void Game::update()
{

	ship->move();

	for (auto& asteroid : bigAsteroids)
	{
		asteroid->move();
		if (ship->colideAsteroid(*asteroid))
		{
			ship->setColor(0, 0, 0);
		}
		/*else
		{
			ship->setColor(200,200, 200);
		}*/
		
	}

	for (auto& asteroid : smallAsteroids)
	{
		asteroid->move();
		if (ship->colideAsteroid(*asteroid))
		{
			ship->setColor(0, 0, 0);
		}
		/*else
		{
			ship->setColor(200, 200, 200);
		}*/
	}

	for (auto& asteroid1 : bigAsteroids)
	{
		for (auto& asteroid2 : bigAsteroids)
		{
			if (asteroid1 != asteroid2 and Asteroid::checkColition(*asteroid1, *asteroid2))
			{
				Asteroid::reflectingAsteroids(*asteroid1, *asteroid2);
			}
		}
		
	}
	
	for (auto& asteroid1 : smallAsteroids)
	{
		for (auto& asteroid2 : smallAsteroids)
		{
			if (asteroid1 != asteroid2 and Asteroid::checkColition(*asteroid1, *asteroid2))
			{
				Asteroid::reflectingAsteroids(*asteroid1, *asteroid2);
			}
		}
	}

	for (auto& asteroid1 : bigAsteroids)
	{
		for (auto& asteroid2 : smallAsteroids)
		{
			if (Asteroid::checkColition(*asteroid1, *asteroid2))
			{
				Asteroid::reflectingAsteroids(*asteroid1, *asteroid2);
			}
		}
	}


}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	bg->render();

	for (auto& asteroid : bigAsteroids)
	{
		asteroid->render();
	}

	for (auto& asteroid : smallAsteroids)
	{
		asteroid->render();
	}
	
	ship->render();

	arrow->render(SCREEN_WIDTH, SCREEN_HEIGHT);
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
		arrow->PoolEvent(e);
		

	}
}

void Game::showCursor(bool bShow)
{
	SDL_ShowCursor(bShow ? 1 : 0);
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
			fpsTimer.start();

			pollEventWindow();
			update();
			render();

			if (frameDelay > fpsTimer.getTicks())
			{
				//Wait remaining time
				SDL_Delay(frameDelay - fpsTimer.getTicks());
			}
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
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}