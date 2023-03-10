#pragma once

#include "Particale.h"
#include <SDL_mixer.h>
#include "Bullet.h"
#include "Force.h"
#include "DestroyParticles.h"
#include <vector>

class Asteroid;
class Arrow;



class Ship : public Sprite
{
public:
	Ship(SDL_Renderer* renderer, int s_width, int s_height);
	~Ship();
	void PoolEvent(SDL_Event& event);
	void move();

	void starSet(int s_width, int s_heigth);
	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	bool colideAsteroid(Asteroid& ast);

	friend void Bullet::creatBullet(Ship& Ship, Arrow& arrow);
	friend void Bullet::creatBullet(Ship& Ship);

	

	int getLife() const { return count_life; }
	void setLife(int life);
	void takeLife();

	bool isDead() const { return dead; }
	void setDead(bool dead);
	
private:
	bool keyUP = false;
	bool keyDown = false;
	bool keyRight = false;
	bool keyLeft = false;

	const float velocity = 1.5;
	const float maxVelocity = 8;

	float dx, dy;

	bool dead;
	int count_life;

	//Particle count
	static const int TOTAL_PARTICLES = 20;
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	//Shows the particles
	void renderParticles();
};
