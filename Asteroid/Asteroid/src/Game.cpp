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
	if (!initWindow() or !initeObject() or !initButton())
		return false;
	return true;
}

void Game::update()
{
	ship->move();

	#pragma region Asteroids

	//BIG Asteroid
	for (auto& asteroid : bigAsteroids)
	{
		asteroid->move();
		#pragma region colideBigAsteroid__SHIP

		if (ship->colideAsteroid(*asteroid))
		{
			ship->setColor(0, 0, 0);
		}
		#pragma endregion

		#pragma region colideBigAsteroid__Bullet
		for (auto& bullet : bullets)
		{
			if (bullet->colideAsteroid(*asteroid))
			{
				bullet->destroy();
			}
		}
		#pragma endregion
	}

	//Small Asteroid
	for (auto& asteroid : smallAsteroids)
	{
		asteroid->move();
		#pragma region colide_SHIP
		if (ship->colideAsteroid(*asteroid))
		{
			ship->setColor(0, 0, 0);
		}
		#pragma endregion

		#pragma region colide__Bullet
		for (auto& bullet : bullets)
		{
			if (bullet->colideAsteroid(*asteroid))
			{
				bullet->destroy();
				destroy_particle.push_back( std::unique_ptr<DestroyParticles>( new DestroyParticles{ asteroid->getX(), asteroid->getY() , asteroid->getWidth(), renderer }));
				asteroid->deleteAsteroid();
			}
		}
		#pragma endregion
	}

	#pragma region Colide-BigAsteroid__BigAsteroid
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
	#pragma endregion

	#pragma region Colide-SmallAsteroid__SmallAsteroid
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
	#pragma endregion

	#pragma region Colide-BigAsteroid__SmallAsteroid
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
	#pragma endregion

	#pragma endregion

	for (auto& bullet : bullets)
	{
		bullet->move(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	bg->render();

	if (!destroy_particle.empty())
	{
		for (size_t i = 0; i < destroy_particle.size(); i++)
		{
				destroy_particle[i]->render();
			if (destroy_particle[i]->getOut())
			{
				destroy_particle.erase(destroy_particle.begin() + i);
			}
			
		}
	}
	

	for (size_t i = 0; i < smallAsteroids.size(); i++)
	{
		if (!smallAsteroids[i]->isActive())
			smallAsteroids[i]->render();
		else
		{
		
			smallAsteroids.erase(smallAsteroids.begin() + i);
		}
	}

	for (size_t i = 0; i < bigAsteroids.size(); i++)
	{
		if (!bigAsteroids[i]->isActive())
			bigAsteroids[i]->render();
		else
			bigAsteroids.erase(bigAsteroids.begin() + i);
	}
	
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isActive()) 
			bullets[i]->render();
		else
			bullets.erase(bullets.begin() + i);
	}
	
	ship->render();

	arrow->render(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(button)
		button->draw();
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
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT) 
			{
				bullets.push_back(std::unique_ptr<Bullet>(new Bullet{"data/bullet.png", renderer, *ship, *arrow}));
			}			
		}
		button->handleEvent(e, arrow->getX(), arrow->getY());
	}
}

void Game::showCursor(bool bShow)
{
	SDL_ShowCursor(bShow ? 1 : 0);
}

void Game::run()
{	
	if (!init() and !init())
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

			if (frameDelay > static_cast<int>(fpsTimer.getTicks()))
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
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Game::initWindow()
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
		std::cout << "Window could not be created! SDL Error:\n" << SDL_GetError() << std::endl;
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


	bg = std::unique_ptr<BG>(new BG{ "data/background.png", renderer });
	if (!bg->isEmpty())
	{
		std::cout << "BG ERRoR: \n" << std::endl;
		return false;
	}

	arrow = std::unique_ptr<Arrow>(new Arrow{ "data/arrow.tga", renderer });
	if (!arrow->isEmpty())
	{
		std::cout << "Arrow ERRoR: \n" << std::endl;
		return false;
	}

	showCursor(false);

	return true;
}

bool Game::initeObject()
{
	ship = std::unique_ptr<Ship>(new Ship{ "data/spaceship.png", renderer });
	if (!ship->isEmpty())
	{
		std::cout << "Ship ERRoR: \n" << std::endl;
		return false;
	}

	bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 4, "data/big_asteroid.png", renderer }));
	bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 4, "data/big_asteroid.png", renderer }));
	bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 4, "data/big_asteroid.png", renderer }));

	for (auto& asteroid : bigAsteroids)
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

	for (auto& bullet : bullets)
		if (!bullet->isEmpty())
		{
			return false;
		}

	return true;
}

bool Game::initButton()
{
	
#pragma region Text_Asteroid


	button = std::unique_ptr<Button>(new Button(renderer, "Click me!", { 100, 100, 200, 50 }));
	button->setPosition(200, 200);
	button->setTextColor({ 255, 255, 255, 255 });
	button->setRectColor({ 63, 74, 92, 255 });

	return true;
}

void Game::deleteObject()
{
	bigAsteroids.clear();
	smallAsteroids.clear();
	bullets.clear();

}