#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>



#include "Background.h"
#include "Arrow.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "DestroyParticles.h"
#include "Button.h"
#include "Text.h"



struct Player
{
	std::string name;
	int points;
};

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
	void initAsteroid(int count);

	void renderAsteroid();
	void moveAsteroid();

	void renderBullets();
	void updateBullets();

	void renderMainMenu();
	void renderGameInterface();
	void renderBestScore();


	void deleteObject();

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

	SDL_Surface* icon;

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
	std::unique_ptr<Button> quit_button;

	std::unique_ptr<Button> setings_button;
	std::unique_ptr<Button> score_button;
	std::unique_ptr<Button> info_button;

	bool menu;
	bool game;

	bool setings;
	bool info;
	bool bestsRecord;

	#pragma region BestRecord

	SDL_Rect BestRecordMenu;

	std::unique_ptr<Text> BestRecord_text;

	std::unique_ptr<Text> FirstRecord_text;
	std::unique_ptr<Text> SecondRecord_text;
	std::unique_ptr<Text> ThirdRecord_text;
	std::unique_ptr<Text> FourthRecord_text;
	std::unique_ptr<Text> FifthRecord_text;

	std::unique_ptr<Button> closeRecord_button;

	bool closeRecord;

	#pragma region recordMethods
	std::vector<Player> players;
	// Function for comparing players by number of points
	static bool compare_players(Player& p1, Player& p2){ return p1.points > p2.points; }
		

	void addRecord(std::string new_name, int new_points);

	std::vector<Player> read_players(std::string filename);


	// Function to read data about players from a file
	void write_players(std::string filename, std::vector<Player> players);

	void SetBestRecord();
	#pragma endregion

	#pragma endregion

	#pragma endregion

#pragma region GameInterface

	std::unique_ptr<Text> score_text;
	int score_points;
	std::unique_ptr<Button> stop_button;

	std::unique_ptr<Sprite> heart;
	
	bool stop_menu;
	Timer stop_timer;


	#pragma region stopMenu
	
	SDL_Rect bgStopMenu;

	std::unique_ptr<Text> pause_text;

	std::unique_ptr<Button> continue_button;
	std::unique_ptr<Button> restart_button;
	std::unique_ptr<Button> back_button;

	bool continue_stopMenu;
	bool restart_stopMenu;
	bool back_stopMenu;

	#pragma endregion

	#pragma region GameOverMenu

	bool gameover;
	std::unique_ptr<Text> gameOver_text;

	std::unique_ptr<Button> restart_button_;
	std::unique_ptr<Button> back_button_;

	bool restart_GameOver;
	bool back_GameOver;

	#pragma endregion
	
#pragma endregion
	


};

