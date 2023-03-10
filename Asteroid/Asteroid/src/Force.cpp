#include "Force.h"



static const char* pathShield = "data/force/bron.png";
static const char* pathScore = "data/force/score.png";
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
	isShow = false;
	isTake = true;
	timer.start();
	return  std::sqrt(fx * fx + fy * fy) <= ship.getWidth() + width / 2;
}

void Force::render(int s_width, int s_height)
{
	if (isShow)
	{
		Sprite::render(x, y);
	}

	if (isTake)
	{
		SDL_Rect renderQuad = { static_cast<int>(s_width - width - 10),  static_cast<int>(s_height - height - 10), width, height };
		SDL_Rect* clip{};

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		//Render to screen
		SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
	}
}

void Force::ActiveForce(std::function<void()> func1, std::function<void()> func2, std::function<void()> func3, std::function<void()> func4)
{
	if (timer.getTicks() - timer.isStarted() <= 10'000)
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
}