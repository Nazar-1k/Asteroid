#pragma once
#include "Sprite.h"
class Asteroid;

class Bullet : public Sprite
{
public:
	Bullet(const char* path, SDL_Renderer* renderer);
	~Bullet() { }

	void poolEvent(SDL_Event& event);
	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void move();

	bool colideAsteroid(Asteroid& ast);
};

