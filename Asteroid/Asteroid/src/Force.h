#pragma once

#include "Sprite.h"
#include "SpaceShip.h"
#include <functional>

class Ship;


class Force : public Sprite 
{
public:
	Force(SDL_Renderer* SDL_Rerenderernderer, float x, float y);
	
	bool colideShip(Ship& ship);
	
	void ActiveForce(std::function<void()> func1, std::function<void()> func2, std::function<void()> func3, std::function<void()> func4);
	

private:
	int countForce;

	SDL_Rect rect;

	SDL_Renderer* renderer;
	Sprite sprite;
};