#pragma once
#include "Sprite.h"
#include "Bullet.h"

class Ship;

class Arrow : public Sprite
{
public:
	Arrow(const char* path, SDL_Renderer* renderer) : Sprite(path, renderer) {}
	~Arrow() {}

	void PoolEvent(SDL_Event& e);

	void render(int width_s, int height_s);

	friend void Bullet::creatBullet(Ship& Ship, Arrow& arrow);
};