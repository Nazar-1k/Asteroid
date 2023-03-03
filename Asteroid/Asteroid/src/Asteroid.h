#pragma once

#include "SpaceShip.h"

class Asteroid : public Sprite
{
public:
	Asteroid(int x, int y, float mass, int angle, SDL_Renderer* renderer);
	~Asteroid();

	void move();
	void deleteAsteroid();
	bool isActive() const  { return to_be_deleted; }


	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static bool checkColition(Asteroid& asteroid1, Asteroid& asteroid2);
	static void reflectingAsteroids(Asteroid& asteroid1, Asteroid& asteroid2);

	friend bool Ship::colideAsteroid(Asteroid& ast);
	friend bool Bullet::colideAsteroid(Asteroid& ast);

private:
	float dx, dy;

	float mass;

	const float velocity = 2;
	const float maxVelocity = 4;

	float radius;
	bool to_be_deleted;

	//rotation left or right
	bool b_rotation;

	float speedrotation;
	
};
