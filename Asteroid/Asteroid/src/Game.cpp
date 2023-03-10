#include "Game.h"

Game::Game()
	:SCREEN_WIDTH(1000), SCREEN_HEIGHT(600), quit(false),
	window(nullptr), renderer(nullptr), bg(nullptr),
	 menu(true), game(false), stop_menu(false), setings(false), info(false),  score_points(0), gameover(false), stop(false)
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
	if (menu)
	{
		
			
		initAsteroid(8);
		moveAsteroid();
	}
	else if (game)
	{
		if (!stop_menu)
		{
			
			if (!stop)
			ship->move();
			
			
			initAsteroid(20);///
			moveAsteroid();
			
			/*Asteroids[1]->setX(0);
			Asteroids[1]->setY(0);*/
			
			updateBullets();
			
				
				if (bullets.size() ==0)
				{
				bullets.push_back(std::unique_ptr<Bullet>(new Bullet{ renderer, *ship, *arrow }));

				}
				for (auto& bull : bullets)
				{
					aimBullet(*bull, Asteroids);
				}
				/*bullets[0]->SeekTarget(Asteroids[0]->getX(), Asteroids[0]->getY());*/
				
			
			
		}
		
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	bg->render();

	if (menu)
	{
		renderAsteroid();

		renderMainMenu();

		if (setings)
		{
			renderSetings();
		}
		else if (info)
		{
			/*renderSetings();*/
		}
		else if(bestsRecord)
		{
			renderBestScore();
		}
	}
	else if (game)
	{
		renderAsteroid();

		renderBullets();

		ship->render();

		renderGameInterface();
	}
	arrow->render(SCREEN_WIDTH, SCREEN_HEIGHT);

	/*createShield(ship->getX(), ship->getY(), ship->getHeight() / 2 + 8);*/

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
			
			if (e.button.button == SDL_BUTTON_LEFT and game) 
			{
				if(!stop_menu)
					bullets.push_back(std::unique_ptr<Bullet>(new Bullet{ renderer, *ship, *arrow}));
			}	

		}
		if (e.type == SDL_KEYDOWN) 
			if(e.key.keysym.sym == SDLK_SPACE)
			{
					bullets.push_back(std::unique_ptr<Bullet>(new Bullet{ renderer, *ship }));
			}

		pLay_button->handleEvent(e, arrow->getX(), arrow->getY());
		quit_button->handleEvent(e, arrow->getX(), arrow->getY());

		score_button->handleEvent(e, arrow->getX(), arrow->getY());
		setings_button->handleEvent(e, arrow->getX(), arrow->getY());
		info_button->handleEvent(e, arrow->getX(), arrow->getY());

		stop_button->handleEvent(e, arrow->getX(), arrow->getY());

		continue_button->handleEvent(e, arrow->getX(), arrow->getY());
		restart_button-> handleEvent(e, arrow->getX(), arrow->getY());;
		back_button->handleEvent(e, arrow->getX(), arrow->getY());
		restart_button_->handleEvent(e, arrow->getX(), arrow->getY());
		back_button_->handleEvent(e, arrow->getX(), arrow->getY());

		close_button->handleEvent(e, arrow->getX(), arrow->getY());

		Name_Ship->handleEvent(e);

		ShotMouse_check->handleEvent(e);
		ShotSpace_check->handleEvent(e);
		Musik_check->handleEvent(e);
		Efeckt_check->handleEvent(e);

		Size500x300_button->handleEvent(e, arrow->getX(), arrow->getY());
		Size1000x600_button->handleEvent(e, arrow->getX(), arrow->getY());
		SizeFullScreen_button->handleEvent(e, arrow->getX(), arrow->getY());

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{

			#pragma region MenuButton
				if (menu)
				{
					if (bestsRecord == false and info == false and setings == false)
					{
						if (pLay_button->isPressed())
						{
							game = true;
							menu = false;
							deleteObject();
							ship->starSet(SCREEN_WIDTH, SCREEN_HEIGHT);
						}
						else if (quit_button->isPressed())
						{
							quit = true;
						}
					}
					if (setings_button->isPressed())
					{
						if (!setings)
							setings = true;
						else if (setings)
							setings = false;
						bestsRecord = false;
						info = false;
					}
					else if (score_button->isPressed())
					{
						SetBestRecord();
						if(!bestsRecord)
							bestsRecord = true;
						else if (bestsRecord)
							bestsRecord = false;
						info = false;
						setings = false;
					}
					else if (info_button->isPressed())
					{
						if (!info)
							info = true;
						else if (info)
							info = false;
						bestsRecord = false;
						setings = false;
					}

					//close bestRecord
					if (bestsRecord or setings or info)
					{
						if (close_button->isPressed())
						{
							bestsRecord = false;
							setings = false;
							info = false;
						}
					}

					

				}

#pragma endregion

			#pragma region GameMenu
				if (game)
				{
					if (stop_button->isPressed() and !gameover)
					{
						if (stop_menu == false)
							stop_menu = true;
						else if (stop_menu == true)
							stop_menu = false;
					}
					if (stop_menu and !gameover)
					{
						if (continue_button->isPressed())
						{
							stop_menu = false;
						}
						else if(restart_button->isPressed())
						{
							deleteObject();
							ship->setDead(true);
							score_points = 0;
							ship->setLife(3);
							ship->starSet(SCREEN_WIDTH,SCREEN_HEIGHT);
							stop_menu = false;
						}
						else if (back_button->isPressed())
						{
							deleteObject();
							ship->setDead(true);
							ship->setLife(3);
							score_points = 0;
							menu = true;
							game = false;
							stop_menu = false;
						}
					}
					if (gameover)
					{
						
						if (restart_button_->isPressed())
						{
							deleteObject();
							score_points = 0;
							ship->setLife(3);
							ship->starSet(SCREEN_WIDTH, SCREEN_HEIGHT);
							gameover = false;
							stop_menu = false;
						}
						else if (back_button_->isPressed())
						{
							deleteObject();
							ship->setLife(3);
							score_points = 0;
							menu = true;
							game = false;
							gameover = false;
							stop_menu = false;
						}
					}

				}
			#pragma endregion
			}
		}
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

	icon = IMG_Load("data/icon/icon.png");
	if (!icon)
	{
		std::cout << "Icon ERRoR: \n" << std::endl;
		return false;
	}
	SDL_SetWindowIcon(window, icon);

	

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
	
#pragma region MainMenu

	#pragma region MainButton
	Asteroid_main_menu_text = std::unique_ptr<Text>(new Text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, renderer, "Asteroid", 80, { 89, 104, 130, 255 }));

	pLay_button = std::unique_ptr<Button>(new Button{ renderer, "Play", {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 250, 100}});
	pLay_button->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	pLay_button->setTextColor({ 255, 255, 255, 255 });
	pLay_button->setRectColor({ 46, 97, 186, 255 });


	quit_button = std::unique_ptr<Button>(new Button{ renderer, "Exit", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 5),"data/Menu/exit.png",{60, 88, 160} });

	info_button = std::unique_ptr<Button>(new Button{ renderer, SCREEN_WIDTH - SCREEN_WIDTH / 15, SCREEN_HEIGHT - SCREEN_HEIGHT / 10,"data/Menu/info1.png" });
	setings_button = std::unique_ptr<Button>(new Button{ renderer, SCREEN_WIDTH - SCREEN_WIDTH /15 - info_button->getWidth() - info_button->getWidth(), SCREEN_HEIGHT - SCREEN_HEIGHT / 10,"data/Menu/setings1.png"});
	score_button = std::unique_ptr<Button>(new Button{ renderer, SCREEN_WIDTH - SCREEN_WIDTH / 15 - info_button->getWidth() - info_button->getWidth() - setings_button->getWidth() - info_button->getWidth() / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 10,"data/Menu/score1.png"});
	#pragma endregion

	#pragma region RecordMenu


	BestRecordMenu = { SCREEN_WIDTH / 6 ,  SCREEN_HEIGHT / 6,SCREEN_WIDTH - SCREEN_WIDTH / 3 ,SCREEN_HEIGHT - SCREEN_HEIGHT / 3 };

	BestRecord_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2, BestRecordMenu.y + 50, renderer, "Best Record:", 40, { 255, 255, 255, 255 } });

	close_button = std::unique_ptr<Button>(new Button{ renderer, BestRecordMenu.x + BestRecordMenu.w - 30, BestRecordMenu.y + 30 , "data/Menu/close.png" });

	FirstRecord_text  = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2,BestRecordMenu.y + 150 , renderer, "1", 25, {255, 255, 255, 255}});
	SecondRecord_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2,BestRecordMenu.y + 200, renderer, "2", 25, { 255, 255, 255, 255 } });
	ThirdRecord_text  = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2,BestRecordMenu.y + 250, renderer, "3", 25, { 255, 255, 255, 255 } });
	FourthRecord_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2,BestRecordMenu.y + 300, renderer, "4", 25, { 255, 255, 255, 255 } });
	FifthRecord_text  = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2,BestRecordMenu.y + 350, renderer, "5", 25, { 255, 255, 255, 255 } });
	
	SetBestRecord();

	#pragma endregion

	#pragma region SetMenu

	SetMenuBG = { SCREEN_WIDTH / 6 ,  SCREEN_HEIGHT / 6,SCREEN_WIDTH - SCREEN_WIDTH / 3 ,SCREEN_HEIGHT - SCREEN_HEIGHT / 4 };

	Set_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2, BestRecordMenu.y + 50, renderer, "Settings", 40, { 255, 255, 255, 255 } });
	
	Name_text = std::unique_ptr<Text>(new Text{ SetMenuBG.x + 70, BestRecordMenu.y + 110, renderer, "Name", 25, { 255, 255, 255, 255 } });
	Name_Ship = std::unique_ptr<InputBox>(new InputBox{ renderer,  SetMenuBG.x + 140 , BestRecordMenu.y + 90 , 300, 50,"font/TerminatorCyr.ttf",  25, {255,255,255,255}, {55, 116, 224,255} });
	
	Shot_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2 - 150, BestRecordMenu.y + 180, renderer, "Shot", 25, { 255, 255, 255, 255 } });//

	ShotMouse_text = std::unique_ptr<Text>(new Text{ SetMenuBG.x + 170,BestRecordMenu.y + 220, renderer, "Mouse", 20, { 255, 255, 255, 255 } });//
	ShotMouse_check = std::unique_ptr<CheckBox>(new CheckBox{ renderer,  SetMenuBG.x + 70,BestRecordMenu.y + 210,25,25 });

	ShotSpace_text = std::unique_ptr<Text>(new Text{ SetMenuBG.x + 170, BestRecordMenu.y + 260, renderer, "Space", 20, { 255, 255, 255, 255 } });//
	ShotSpace_check = std::unique_ptr<CheckBox>(new CheckBox{ renderer,  SetMenuBG.x + 70,BestRecordMenu.y + 250,25,25 });

	Sound_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2 + 150,  BestRecordMenu.y + 180, renderer, "Sound", 25, { 255, 255, 255, 255 } });;//

	Musik_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2 + 110,BestRecordMenu.y + 220, renderer, "Musik", 20, { 255, 255, 255, 255 } });//
	Musik_check = std::unique_ptr<CheckBox>(new CheckBox{ renderer, SCREEN_WIDTH / 2 + 20,BestRecordMenu.y + 210,25,25 });

	Effect_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2 + 130, BestRecordMenu.y + 260, renderer, "Effect", 20, { 255, 255, 255, 255 } });//
	Efeckt_check = std::unique_ptr<CheckBox>(new CheckBox{ renderer, SCREEN_WIDTH / 2 + 20,BestRecordMenu.y + 250,25,25 });

	ScreenSize_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2 , BestRecordMenu.y + 320, renderer, "Screen Size", 25, { 255, 255, 255, 255 } });//

	Size500x300_button = std::unique_ptr<Button>(new Button{ renderer,BestRecordMenu.x+100,BestRecordMenu.y + 360, "500x300",20,{ 0, 0, 0, 255 } });
	Size1000x600_button = std::unique_ptr<Button>(new Button{ renderer,SCREEN_WIDTH / 2-50,BestRecordMenu.y + 360, "1000x600",20,{ 0, 0, 0, 255 } });
	SizeFullScreen_button = std::unique_ptr<Button>(new Button{ renderer,SCREEN_WIDTH / 2+200,BestRecordMenu.y + 360, "Full Screen",20,{ 0, 0, 0, 255 } });



	#pragma endregion
#pragma endregion
	
#pragma region GameInterface

	stop_button = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/stop.png" });
	stop_button->setPosition(SCREEN_WIDTH - stop_button->getWidth(), 25);
	stop_button->setTextColor({ 255, 255, 255, 255 });
	stop_button->setRectColor({ 46, 97, 186, 255 });

	score_text = std::unique_ptr<Text>(new Text(1, 1, renderer, "Score", 30, { 89, 104, 130, 255 }));
	score_text->setPosition(SCREEN_WIDTH - stop_button->getWidth() - score_text->getWidth () , 25);


	heart = std::unique_ptr<Sprite>(new Sprite{ "data/Menu/heart.png", renderer });
	
	heart->setX(static_cast<float>(heart->getWidth() + 50));
	heart->setY(static_cast<float>(heart->getHeight() + 50));



	#pragma region stopMenu

	bgStopMenu = { SCREEN_WIDTH / 6 ,  SCREEN_HEIGHT / 6,SCREEN_WIDTH - SCREEN_WIDTH / 3 ,SCREEN_HEIGHT - SCREEN_HEIGHT / 3 };

	pause_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2, bgStopMenu.y + 60, renderer, "Pause", 80, { 255, 255, 255, 255 } });

	back_button  = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/back.png" });
	back_button->setPosition(SCREEN_WIDTH/ 2 - 200, SCREEN_HEIGHT / 2 + 50);

	continue_button = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/pause_.png" });
	continue_button->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);

	restart_button = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/restart.png" });
	restart_button->setPosition(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 50);
	
	




	#pragma endregion

#pragma region GameOverMenu
	gameOver_text = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2, bgStopMenu.y + 60, renderer, "Game Over", 100, { 255, 255, 255, 255 } });

	restart_button_ = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/restart.png" });
	restart_button_->setPosition(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 + 50);
	
	back_button_ = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/back.png" });
	back_button_->setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50);

	

#pragma endregion

#pragma endregion

	return true;
}

void Game::initAsteroid(int count)
{
	if ((Asteroids.size() < count))
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
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 3, renderer }));
					break;

					//right
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
				
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 4, renderer }));
					break;

					//right
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 4, renderer }));
					break;
				}
			}

		
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
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 3, renderer }));
					break;

					//left
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(190 + rand() % (350 - 191)), 4, renderer }));
					break;

					//left
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 4, renderer }));
					break;
				}
			}
			
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
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 3, renderer }));
					break;

					//right
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 4, renderer }));
					break;

					//right
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 4, renderer }));
					break;
				}
			}

			
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
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 3, renderer }));
					break;

					//left
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//down
				case 0:
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 4, renderer }));
					break;

					//left
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 4, renderer }));
					break;
				}
			}
			
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
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 3, renderer }));
					break;

					//left
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 3, renderer }));
					break;
					//down
				case 2:
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 3, renderer }));
					break;

					//right
				case 3:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 3, renderer }));
					break;
				}

				break;
			case 1:
				switch (randScreenSide)
				{
					//top
				case 0:
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(170 + rand() % (350 - 171)), 4, renderer }));
					break;

					//left
				case 1:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ 0, rand() % SCREEN_HEIGHT, static_cast<float>(260 + rand() % (440 - 261)), 4, renderer }));
					break;
					//down
				case 2:
					
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ rand() % SCREEN_WIDTH, SCREEN_HEIGHT, static_cast<float>(10 + rand() % (170 - 11)), 4, renderer }));
					break;

					//right
				case 3:
					Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ SCREEN_WIDTH, rand() % SCREEN_HEIGHT, static_cast<float>(100 + rand() % (270 - 101)), 4, renderer }));
					break;
				}
			}

			//midle start game
		}
	}
}

void  Game::renderAsteroid()
{
	for (size_t i = 0; i < Asteroids.size(); i++)
	{
		if (!Asteroids[i]->isActive())
			Asteroids[i]->render();
		else
			Asteroids.erase(Asteroids.begin() + i);
	}
}

void Game::moveAsteroid()
{
	//BIG Asteroid
	for (auto& asteroid : Asteroids)
	{
		if(!stop)
		asteroid->move();

	#pragma region colideBigAsteroid__SHIP

			if (ship->colideAsteroid(*asteroid) and menu == false)
			{
				destroyShip();
			}
	#pragma endregion

	#pragma region colideBigAsteroid__Bullet
			for (auto& bullet : bullets)
			{
				if (bullet->colideAsteroid(*asteroid))
				{
					bullet->destroy();
					destroy_particle.push_back(std::unique_ptr<DestroyParticles>(new DestroyParticles{ asteroid->getX(), asteroid->getY() , asteroid->getWidth() / 10 , renderer }));
					if (asteroid->getMass() == 4)
					{
						Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ static_cast<int>(asteroid->getX()), static_cast<int>(asteroid->getY()), 90, 3, renderer }));
						Asteroids.push_back(std::unique_ptr<Asteroid>(new Asteroid{ static_cast<int>(asteroid->getX()), static_cast<int>(asteroid->getY()), 180, 3, renderer }));
					}
					asteroid->deleteAsteroid();
					score_points += 10;
				}
			}
	#pragma endregion

	#pragma region ColisionAsteroid__Asteroid
			for (auto& asteroid2 : Asteroids)
			{
				if (asteroid != asteroid2 and Asteroid::checkColition(*asteroid, *asteroid2))
				{
					Asteroid::reflectingAsteroids(*asteroid, *asteroid2);
				}
			}
	#pragma endregion 

	}
}

void Game::aimBulletInDirection(Bullet& bullet, const std::vector<std::unique_ptr<Asteroid>>& asteroids)
{
	double closestDistance = std::numeric_limits<double>::max();
	SDL_Point closestAsteroidPos = { -1, -1 };
	SDL_Point bulletPos = { bullet.getX(), bullet.getY() };
	SDL_Point bulletDir = { bullet.getDx(), bullet.getDy() };
	// перебираємо всі астероїди на екрані
	for (const auto& asteroid : asteroids) {
		SDL_Point asteroidPos = asteroid->getPosition();
		// обчислюємо відстань між кулею та поточним астероїдом
		SDL_Point diff = { asteroidPos.x - bulletPos.x, asteroidPos.y - bulletPos.y };
		double distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
		// обчислюємо косинус кута між напрямком кулі та відстанню до астероїда
		double cosAngle = (bulletDir.x * diff.x + bulletDir.y * diff.y) / distance;
		// якщо астероїд знаходиться впереді кулі, то наводимо на нього
		if (cosAngle > 0 && distance < closestDistance) {
			closestDistance = distance;
			closestAsteroidPos = asteroidPos;
		}
	}
	// наводимо кулю на знайдену позицію
	SDL_Point targetPos = { closestAsteroidPos.x, closestAsteroidPos.y };
	if (targetPos.x > 0 or targetPos.y > 0)
	{

		bullet.SeekTarget(targetPos.x, targetPos.y);
	}
	else
	{
		bullet.setColor(255, 255, 255);
	}

}

void Game::destroyShip()
{
	
	if (destroyShip_particle.size() <= 5 and !stop)
		destroyShip_particle.push_back(std::unique_ptr<DestroyParticles>(new DestroyParticles{ ship->getX(), ship->getY() , ship->getWidth() / 15 ,10000, renderer }));
	
	if (ship->getLife() > 0)
	{
		if (ship->getLife() == 1)
		{
			ship->takeLife();
			ship->setAlpha(0);
		
			addRecord("SHIP", score_points);
			
			stop_menu = true;
			gameover = true;

		}
	}
	
	if (!gameover)
	{
		if (destroyShip_particle.empty())
		{
			ship->starSet(SCREEN_WIDTH, SCREEN_HEIGHT);
			deleteObject();
			
			ship->takeLife();
			stop = false;
		}
		else
		{
			ship->setAlpha(0);
			stop = true;
		}

	}

}

void Game::renderBullets()
{
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
	if (!destroyShip_particle.empty())
	{
		for (size_t i = 0; i < destroyShip_particle.size(); i++)
		{
			destroyShip_particle[i]->render();
			if (destroyShip_particle[i]->getOut())
			{
				destroyShip_particle.erase(destroyShip_particle.begin() + i);
			}

		}
	}

	if (!stop)
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isActive())
			bullets[i]->render();
		else
			bullets.erase(bullets.begin() + i);
	}
}

void Game::updateBullets()
{
	for (auto& bullet : bullets)
	{
		if(!stop)
		bullet->move(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

void Game::renderMainMenu()
{
	Asteroid_main_menu_text->draw();

	pLay_button->draw();

	quit_button->draw(static_cast<Uint8>(100));

	score_button->drawSpriteButton();
	setings_button->drawSpriteButton();
	info_button->drawSpriteButton();
}

void Game::renderGameInterface()
{
	score_text->SetText("Score: " + std::to_string(score_points));
	score_text->draw();
	stop_button->drawSpriteButton();

	if (ship->getLife() >= 1)
	{
		heart->setX(10);
		heart->setY(10);
		heart->render();
	}

	if (ship->getLife() >= 2)
	{
		heart->setX(heart->getX() + heart->getWidth());
		heart->render();
	}
	
	

	if (ship->getLife() == 3)
	{

		heart->setX(heart->getX() + heart->getWidth());
		heart->render();
	}

	#pragma region stopMenu
	if (stop_menu and !gameover)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer,  89, 104, 130, static_cast<Uint8>(200) );
		SDL_RenderFillRect(renderer, &bgStopMenu);

		pause_text->draw();
		
		continue_button->drawSpriteButton();
		restart_button->drawSpriteButton();
		back_button->drawSpriteButton();
	}
	else if (gameover)
	{
			gameOver_text->draw();

			restart_button_->drawSpriteButton();
			back_button_->drawSpriteButton();
	}

	#pragma endregion


}

void Game::renderBestScore()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 89, 104, 130, static_cast<Uint8>(200));
	SDL_RenderFillRect(renderer, &BestRecordMenu);

	BestRecord_text->draw();

	close_button->drawSpriteButton();

	FirstRecord_text->draw();
	SecondRecord_text->draw();
	ThirdRecord_text->draw();
	FourthRecord_text->draw();
	FifthRecord_text->draw();
}

void Game::renderSetings()
{

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 89, 104, 130, static_cast<Uint8>(200));
	SDL_RenderFillRect(renderer, &SetMenuBG);

	Set_text->draw();


	Name_Ship->render();
	Name_text->draw();
	

	Shot_text->draw();

	ShotMouse_text->draw();
	ShotMouse_check->render();

	ShotSpace_text->draw();
	ShotSpace_check->render();

	Sound_text->draw();

	Musik_text->draw();
	Musik_check->render();

	Effect_text->draw();
	Efeckt_check->render();

	ScreenSize_text->draw();

	Size500x300_button->drawTextButton();
	Size1000x600_button->drawTextButton();
	SizeFullScreen_button->drawTextButton();

	close_button->drawSpriteButton();
}

void Game::deleteObject()
{
	Asteroids.clear();
	bullets.clear();
	stop = false;
}

//file record
void  Game::addRecord(std::string new_name, int new_points)
{
	bool added = false;
	for (Player& player : players) {
		if (player.name == new_name)
		{
			added = true;
			if (new_points > player.points)
				player.points = new_points;

			break;
		}
	}

	if (!added)
	{
		players.push_back({ new_name, new_points });
	}

	// Сортування гравців за кількістю point
	std::sort(players.begin(), players.end(), compare_players);

	// Запис даних про гравців до файлу
	write_players(".info/Best_points.txt", players);
}

std::vector<Player>  Game::read_players(std::string filename) {
	std::vector<Player> players;
	std::ifstream fin(filename);
	if (!fin) {
		std::cerr << "Error: could not open file " << filename << std::endl;
		exit(1);
	}
	std::string line;
	while (getline(fin, line)) {
		if (line.empty()) {
			continue;
		}
		std::stringstream ss(line);
		std::string name;
		int points;
		if (ss >> name && ss >> points && ss.eof()) {
			players.push_back({ name, points });
		}
	}
	fin.close();
	return players;
}

void  Game::write_players(std::string filename, std::vector<Player> players) {
	std::ofstream fout(filename);
	if (!fout) {
		std::cerr << "Error: could not open file " << filename << std::endl;
		exit(1);
	}
	for (Player player : players) {
		fout << player.name << " " << player.points << std::endl;
	}
	fout.close();
}

void Game::SetBestRecord()
{
	players = read_players(".info/Best_points.txt");
	FirstRecord_text->SetText("1. " + players[0].name + " " + std::to_string(players[0].points) + "\n");
	SecondRecord_text->SetText("2. " + players[1].name + " " + std::to_string(players[1].points) + "\n");
	ThirdRecord_text->SetText("3. " + players[2].name + " " + std::to_string(players[2].points) + "\n");
	FourthRecord_text->SetText("4. " + players[3].name + " " + std::to_string(players[3].points) + "\n");
	FifthRecord_text->SetText("5. " + players[4].name + " " + std::to_string(players[4].points) + "\n");
}

