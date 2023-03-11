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

	static void reflectingShildAsteroids(Ship& ship, Asteroid& asteroid1)
	{
		// Calculate the angle of collision
		float angle = atan2(asteroid1.getY() - ship.getY(), asteroid1.getX() - ship.getX());

		// Calculate the new velocities after the collision
		float velocity1 = std::sqrt(asteroid1.dx * asteroid1.dx + asteroid1.dy * asteroid1.dy);
		float velocity2 = std::sqrt(ship.getDx() * ship.getDx() + ship.getDy() * ship.getDy());

		float direction1 = atan2(asteroid1.dy, asteroid1.dx);
		float direction2 = atan2(ship.getDy(), ship.getDx());

		// Calculate the new velocities after the collision, taking into account the masses of the asteroids
		float newVelocity1 = (velocity1 * (asteroid1.mass - 4) + 2 * 4 * velocity2) / (asteroid1.mass + 4);
		float newVelocity2 = (velocity2 * (4 - asteroid1.mass) + 2 * asteroid1.mass * velocity1) / (asteroid1.mass + 4);

		float newDirection1 = direction1 - angle;
		float newDirection2 = direction2 - angle;

		asteroid1.dx = static_cast<float>(newVelocity1 * cos(newDirection1) + velocity1 * sin(direction1 - angle) * cos(angle + M_PI / 2));
		asteroid1.dy = static_cast<float>(newVelocity1 * sin(newDirection1) + velocity1 * sin(direction1 - angle) * sin(angle + M_PI / 2));

		/*asteroid2.dx = static_cast<float>(newVelocity2 * cos(newDirection2) + velocity2 * sin(direction2 - angle) * cos(angle + M_PI / 2));
		asteroid2.dy = static_cast<float>(newVelocity2 * sin(newDirection2) + velocity2 * sin(direction2 - angle) * sin(angle + M_PI / 2));*/

		float fx = asteroid1.x - ship.getX();
		float fy = asteroid1.y - ship.getY();

		float distance = std::sqrt(fx * fx + fy * fy);

		// Move the asteroids away from each other to avoid multiple collisions
		float overlap = asteroid1.radius + ship.getWidth() / 2 + 18 - distance;
		float moveX = overlap * cos(angle);
		float moveY = overlap * sin(angle);

		asteroid1.x = asteroid1.x + moveX / 2;
		asteroid1.y = asteroid1.y + moveY / 2;

		/*asteroid2.x = asteroid2.x - moveX / 2;
		asteroid2.y = asteroid2.y - moveY / 2;*/
	}
	static bool checkColitionShiled(int x, int y, int radius, Asteroid& asteroid1)
	{
		float fx = asteroid1.x - x;
		float fy = asteroid1.y - y;

		return  std::sqrt(fx * fx + fy * fy) <= asteroid1.radius + radius;
	
	}


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
