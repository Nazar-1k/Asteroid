#pragma once

#include "Sprite.h"

class Particle
{
public:
	//Initialize position and animation
	Particle(float x, float y, float side, float angle, SDL_Renderer* renderer);
	


	//Shows the particle
	void render();
	//Checks if particle is dead
	bool isDead();
	void setdead(bool dead);

	//Offsets
	float x, y;
	
	float dx, dy;
private:

	//Current frame of animation
	int Frame;

	//Type of particle
	Sprite* Texture;

	bool dead;
};

