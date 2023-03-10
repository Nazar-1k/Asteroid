#include "Force.h"



static const char* pathShield = "data/force/bron.png";
static const char* pathScore = "data/force/score.png";
static const char* pathAutoShot = "data/force/auto.png";
static const char* pathHelpShot = "data/force/bullet.png";

Force::Force(SDL_Renderer* SDL_Rerenderernderer, float x, float y)
{
	countForce = rand() % 4;
	switch (countForce)
	{
	case 0:
		initSprite(pathShield, renderer);
		break;
	case 1:
		initSprite(pathScore, renderer);
		break;
	case 2:
		initSprite(pathAutoShot, renderer);
		break;
	case 3:
		initSprite(pathHelpShot, renderer);
		break;
	}
	this->x = x;
	this->y = y;

	rect = { static_cast<int>(x), static_cast<int>(y) , getWidth(), getHeight() };
}

bool Force::colideShip(Ship& ship)
{
	float fx = ship.getX() - x;
	float fy = ship.getY() - y;

	return  std::sqrt(fx * fx + fy * fy) <= ship.getWidth() + width / 2;
}

void Force::ActiveForce(std::function<void()> func1, std::function<void()> func2, std::function<void()> func3, std::function<void()> func4)
{
	switch (countForce)
	{
	case 0:
		func1();
		break;
	case 1:
		func2();
		break;
	case 2:
		func3();
		break;
	case 3:
		func4();
		break;
	}
}