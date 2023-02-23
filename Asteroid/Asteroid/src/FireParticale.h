#pragma once

#include "Sprite.h"

class Fire
{
public:
	//Initialize position and animation
	Fire();
	Fire(SDL_Renderer* renderer);

	//Shows the particle
	void render(Sprite* ShimmerTexture);

	//Checks if particle is dead
	bool isDead();

private:
	//Offsets
	int x, y;

	//Current frame of animation
	int Frame;

	//Type of particle
	Sprite* Texture;

	
};

