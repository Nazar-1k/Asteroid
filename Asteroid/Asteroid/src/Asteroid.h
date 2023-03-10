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
	float getMass() const { return mass; }
	

	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static bool checkColition(Asteroid& asteroid1, Asteroid& asteroid2);
	static void reflectingAsteroids(Asteroid& asteroid1, Asteroid& asteroid2);


	Asteroid& operator=(const Asteroid& other) 
	{
		if (this != &other)
		{
			dx = other.dx;
			dy = other.dy;

			mass = other.mass;

			radius = other.radius;
			to_be_deleted = other.to_be_deleted;

			width = other.width;
			height = other.height;

			texture = other.texture;
			renderer = other.renderer;

			angle = other.angle;
			center = other.center;
			flip = other.flip;

			is_Empty = other.is_Empty;
			x = other.x;
			y = other.y;
		}
		return *this;
	}



	friend bool Ship::colideAsteroid(Asteroid& ast);
	friend bool Bullet::colideAsteroid(Asteroid& ast);

	SDL_Point getPosition()
	{
		return { (int)x,(int)y };
	}

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
