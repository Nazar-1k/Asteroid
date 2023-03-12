#pragma once
#include "Sprite.h"
#include "Bullet.h"

class Ship;

class Arrow : public Sprite
{
public:
	Arrow(SDL_Renderer* renderer);
	~Arrow() {}

	void PoolEvent(SDL_Event& e);

	void render(int width_s, int height_s) const;

	friend void Bullet::creatBullet(Ship& Ship, Arrow& arrow);
};