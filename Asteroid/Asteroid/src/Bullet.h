#pragma once
#include "Sprite.h"

class Asteroid;
class Ship;
class Arrow;

class Bullet : public Sprite
{
public:
	Bullet(SDL_Renderer* renderer, Ship& ship, Arrow& arrow);
	Bullet(SDL_Renderer* renderer, Ship& ship);
	~Bullet() {  }

	/*void poolEvent(SDL_Event& event) const;*/
	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void creatBullet(Ship& Ship, Arrow& arrow);
	void creatBullet(Ship& Ship);

	void move(int w_screen, int h_screen);

	bool colideAsteroid(Asteroid& ast);
	void destroy() { is_bullet_active = false; }

	bool isActive() const { return is_bullet_active; }

private:
	float dx, dy;

	float bulletSpeed = 15;

	float angle;
	bool is_bullet_active;
};

