#pragma once

#include "SpaceShip.h"

class Asteroid : public Sprite
{
public:
	Asteroid(int x, int y, float mass, int angle, SDL_Renderer* renderer);
	~Asteroid();

	SDL_Point getPosition() const;

	bool isActive() const  { return to_be_deleted; }

	void move();
	
	int getMass() const { return mass; }
	

	void render(int S_width, int S_height, SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static bool checkColition(Asteroid& asteroid1, Asteroid& asteroid2);
	static void reflectingAsteroids(Asteroid& asteroid1, Asteroid& asteroid2);

	static void reflectingShildAsteroids(Ship& ship, Asteroid& asteroid1);
	static bool checkColitionShiled(float x, float y, float radius, Asteroid& asteroid1);


	friend bool Ship::colideAsteroid(Asteroid& ast);
	friend bool Bullet::colideAsteroid(Asteroid& ast);

	void deleteAsteroid();

private:
	float dx, dy;

	int mass;

	const float velocity = 2;
	const float maxVelocity = 4;

	float radius;
	bool to_be_deleted;

	//rotation left or right
	bool b_rotation;

	float speedrotation;
	
};
