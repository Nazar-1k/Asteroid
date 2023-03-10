#pragma once

#include "Sprite.h"
#include "SpaceShip.h"
#include <functional>
#include "Timer.h"

class Ship;


class Force : public Sprite 
{
public:
	Force(SDL_Renderer* SDL_Rerenderernderer, float x, float y);
	
	bool colideShip(Ship& ship);
	
	void ActiveForce(std::function<void()> func1, std::function<void()> func2, std::function<void()> func3, std::function<void()> func4);
	
	void render(int s_width, int s_height);

private:
	Timer timer;

	int countForce;

	bool isShow;
	bool isTake;


	SDL_Rect rect;

	SDL_Renderer* renderer;
};