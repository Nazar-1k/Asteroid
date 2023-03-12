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
#include "TextBox.h"
#include "CheckBox.h"



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
	bool initeSound();

	void renderAsteroid();
	void moveAsteroid();

	void renderBullets();
	void updateBullets();

	void updateForce();

	void renderMainMenu();
	void renderGameInterface();
	void renderBestScore();
	void renderSetings();

	void deleteObject();

	bool startRound;


	#pragma region Window
	
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	//Timers
	Timer fpsTimer;
	

	bool quit;
	SDL_Event e;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Surface* icon;

	#pragma endregion

	#pragma region Sprites

	std::unique_ptr<Ship> ship;
	bool click = false;

	std::unique_ptr<BG> bg;
	std::unique_ptr<Arrow> arrow;
	std::vector<std::unique_ptr<Asteroid>> Asteroids;

	std::vector<std::unique_ptr<Bullet>> bullets;
	std::vector<std::unique_ptr<DestroyParticles>> destroy_particle;

	void destroyShip();
	std::vector<std::unique_ptr<DestroyParticles>> destroyShip_particle;
	bool stop;

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

	std::unique_ptr<Button> close_button;

	bool closeRecord;

	#pragma region recordMethods

	Player player1;

	std::vector<Player> players;
	// Function for comparing players by number of points
	static bool compare_players(Player& p1, Player& p2){ return p1.points > p2.points; }
		

	void addRecord(std::string new_name = "SHIP", int new_points = 0);

	std::vector<Player> read_players(std::string filename);


	// Function to read data about players from a file
	void write_players(std::string filename, std::vector<Player> players);

	void SetBestRecord();
	#pragma endregion

	#pragma endregion

	#pragma region Setings

	SDL_Rect SetMenuBG;

	std::unique_ptr<Text> Set_text;

	std::unique_ptr<Text> Name_text;

	std::unique_ptr<InputBox> Name_Ship;

	std::unique_ptr<Text> Shot_text;

	std::unique_ptr<Text> ShotMouse_text;
	std::unique_ptr<CheckBox> ShotMouse_check;

	std::unique_ptr<Text> ShotSpace_text;
	std::unique_ptr<CheckBox> ShotSpace_check;

	std::unique_ptr<Text> Sound_text;

	std::unique_ptr<Text> Musik_text;
	std::unique_ptr<CheckBox> Musik_check;

	std::unique_ptr<Text> Effect_text;
	std::unique_ptr<CheckBox> Efeckt_check;

	std::unique_ptr<Button> closeSet_button;
	bool closeSet;






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

	#pragma region Force

		std::vector<std::unique_ptr<Force>> force;
		bool isShield = true;

		bool force1;
		bool force2;
		bool force3;
		bool force4;

		void aimBulletInDirection(Bullet& bullet, const std::vector<std::unique_ptr<Asteroid>>& asteroids);
	
		void createShield(float centerX, float centerY, int radius);

		void setShild(bool shield);
	

		void aimBullet(Bullet& bullet, const std::vector<std::unique_ptr<Asteroid>>& asteroids);

		void Score100();

		int countDestroyShip = 0;
	#pragma endregion

#pragma region Sound

		
	Mix_Music* gMusic = nullptr;

	Mix_Chunk* forceSound = nullptr;
	Mix_Chunk* ShotSound = nullptr;
	Mix_Chunk* destroyAsteroidSound = nullptr;
	Mix_Chunk* destroyShipSound = nullptr;
	
#pragma endregion

};
