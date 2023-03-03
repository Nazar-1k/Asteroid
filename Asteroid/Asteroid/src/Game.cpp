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
	initAsteroid();
	ship->move();

	#pragma region Asteroids

	//BIG Asteroid
	for (auto& asteroid : bigAsteroids)
	{
		asteroid->move();
		#pragma region colideBigAsteroid__SHIP

		if (ship->colideAsteroid(*asteroid))
		{
			deleteObject();
			ship->starSet(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		#pragma endregion

		#pragma region colideBigAsteroid__Bullet
		for (auto& bullet : bullets)
		{
			if (bullet->colideAsteroid(*asteroid))
			{
				bullet->destroy();
				destroy_particle.push_back(std::unique_ptr<DestroyParticles>(new DestroyParticles{ asteroid->getX(), asteroid->getY() , asteroid->getWidth() / 6, renderer }));
				smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ static_cast<int>(asteroid->getX()), static_cast<int>(asteroid->getY()), 90, 3, renderer }));
				smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ static_cast<int>(asteroid->getX()), static_cast<int>(asteroid->getY()), 180, 3, renderer }));
				asteroid->deleteAsteroid();																											  
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
			deleteObject();
			ship->starSet(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		#pragma endregion

		#pragma region colide__Bullet
		for (auto& bullet : bullets)
		{
			if (bullet->colideAsteroid(*asteroid))
			{
				bullet->destroy();
				destroy_particle.push_back( std::unique_ptr<DestroyParticles>( new DestroyParticles{ asteroid->getX(), asteroid->getY() , asteroid->getWidth() / 6, renderer }));
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
	
	/*button->draw();*/
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
				bullets.push_back(std::unique_ptr<Bullet>(new Bullet{ renderer, *ship, *arrow}));
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


	bg = std::unique_ptr<BG>(new BG{ renderer });
	if (!bg->isEmpty())
	{
		std::cout << "BG ERRoR: \n" << std::endl;
		return false;
	}

	arrow = std::unique_ptr<Arrow>(new Arrow{  renderer });
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
	ship = std::unique_ptr<Ship>(new Ship{ renderer, SCREEN_WIDTH, SCREEN_HEIGHT });
	if (!ship->isEmpty())
	{
		std::cout << "Ship ERRoR: \n" << std::endl;
		return false;
	}

	

	return true;
}

bool Game::initButton()
{
	
#pragma region Text_Asteroid


	button = std::unique_ptr<Button>(new Button(renderer, "Click me!", { 100, 100, 200, 50 }, 20));
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
	SDL_Delay(100);
}

void Game::initAsteroid()
{
	if ((bigAsteroids.size() + smallAsteroids.size() < 5))
	{
		int randScreenSide = rand() % 2;
		int randAsteroid = rand() % 2;
		if (ship->getX() < SCREEN_WIDTH / 2 and ship->getY() < SCREEN_HEIGHT / 2)
		{
			switch (randAsteroid)
			{
			case 0:

				switch (randScreenSide)
				{
					//down
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 3, renderer }));
					break;

					//right
				case 1:
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 4, renderer }));
					break;

					//right
				case 1:
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 4, renderer }));
					break;
				}
			}

			std::cout << "1";
			//down, right
		}
		else if (ship->getX() > SCREEN_WIDTH / 2 and ship->getY() < SCREEN_HEIGHT / 2)
		{
			switch (randAsteroid)
			{
			case 0:

				switch (randScreenSide)
				{
					//down
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 3, renderer }));
					break;

					//left
				case 1:
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(190 + rand() % (350 - 191)), 4, renderer }));
					break;

					//left
				case 1:
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 4, renderer }));
					break;
				}
			}
			std::cout << "2";
			//down, left
		}
		else if (ship->getX() < SCREEN_WIDTH / 2 and ship->getY() > SCREEN_HEIGHT / 2)
		{
			switch (randAsteroid)
			{
			case 0:

				switch (randScreenSide)
				{
					//top
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 3, renderer }));
					break;

					//right
				case 1:
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 4, renderer }));
					break;

					//right
				case 1:
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 4, renderer }));
					break;
				}
			}

			std::cout << "3";
			//top, right
		}
		else if (ship->getX() > SCREEN_WIDTH / 2 and ship->getY() > SCREEN_HEIGHT / 2)
		{
			switch (randAsteroid)
			{
			case 0:

				switch (randScreenSide)
				{
					//top
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 3, renderer }));
					break;

					//left
				case 1:
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 4, renderer }));
					break;

					//left
				case 1:
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 4, renderer }));
					break;
				}
			}
			std::cout << "4";
			//top, left
		}
		else
		{

			randScreenSide = rand() % 4;
			switch (randAsteroid)
			{
			case 0:

				switch (randScreenSide)
				{
					//top
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 3, renderer }));
					break;

					//left
				case 1:
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 3, renderer }));
					break;
					//down
				case 2:
					/*int num = min + rand() % (max - min + 1);*/
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 3, renderer }));
					break;

					//right
				case 3:
					smallAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//top
				case 0:
					/*int num = min + rand() % (max - min + 1);*/
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 4, renderer }));
					break;

					//left
				case 1:
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 4, renderer }));
					break;
					//down
				case 2:
					/*int num = min + rand() % (max - min + 1);*/
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 4, renderer }));
					break;

					//right
				case 3:
					bigAsteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 4, renderer }));
					break;
				}
			}

			//midle start game
		}
	}
}
