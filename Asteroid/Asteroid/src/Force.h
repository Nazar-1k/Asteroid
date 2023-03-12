#pragma once

#include "Sprite.h"
#include "SpaceShip.h"
#include <functional>
#include "Timer.h"
//#include "Game.h"
class Game;
class Ship;


class Force : public Sprite 
{
public:
	Force(SDL_Renderer* SDL_Rerenderernderer, float x, float y);
	
	bool colideShip(Ship& ship);

	void takeForce();

	void ActiveForce(bool& force1, bool& force2, bool& force3, bool& force4);
	
	
	void startTimer();
	void render(int s_width, int s_height);

	bool isDelete() { return delete_; }

private:
	bool delete_;
	Timer timer;

	int countForce;

	bool isShow;
	bool isTake;


	SDL_Rect rect;

	SDL_Renderer* renderer;
};