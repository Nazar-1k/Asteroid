#include "Force.h"
#include "Game.h"



static const char* pathShield = "data/force/bron.png";
static const char* pathScore = "data/force/star.png";
static const char* pathAutoShot = "data/force/auto.png";
static const char* pathHelpShot = "data/force/bullet.png";

Force::Force(SDL_Renderer* renderer, float x, float y)
	:isShow(true), isTake(false)
{
	countForce = rand() % 4;
	switch (countForce)
	{
	case 0:
		initSprite(pathShield, renderer);
		break;
	case 1:
		initSprite(pathHelpShot, renderer);
		break;
	case 2:
		initSprite(pathAutoShot, renderer);
		break;
	case 3:
		initSprite(pathScore, renderer);
		break;
	}
	this->x = x;
	this->y = y;

	
	rect = { static_cast<int>(x) - width / 2, static_cast<int>(y) - height / 2, getWidth(), getHeight() };
}

bool Force::colideShip(Ship& ship)
{
	float fx = ship.getX() - x;
	float fy = ship.getY() - y;
	
	return  std::sqrt(fx * fx + fy * fy) <= ship.getWidth() + width / 2;
}

void Force::startTimer()
{
	timer.start();
}

void Force::render(int s_width, int s_height)
{
	if (isShow)
	{
		Sprite::render(x, y);
	}

	if (isTake)
	{
		setAlpha(100);
		Sprite::render(s_width - width - 10, s_height - height - 10);
	}
}

void Force::ActiveForce(bool& force1, bool& force2, bool& force3, bool& force4)
{

	
	if (isTake)
	{
		/*std::cout << timer.getTicks() << std::endl;*/
	
	if (timer.getTicks() <= 10'000 and !timer.isPaused())
	{
		/*std::cout << timer.getTicks() - timer.isStarted() << std::endl;*/
		switch (countForce)
		{
		case 0:
			force1 = true;
			break;
		case 1:
			force2 = true;
			break;
		case 2:
			force3 = true;
			break;
		case 3:
			force4 = true;
			timer.pause();
			break;
		}
	}
	else
	{ 
		
		force1 = false;
		force2 = false;
		force3 = false;
		force4 = false;

		delete_ = true;
		
		timer.pause();
		isShow = true;
		isTake = false;
	}
	}
}
