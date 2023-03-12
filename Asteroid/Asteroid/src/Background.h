#pragma once

#include "Sprite.h"

class BG : public Sprite
{
public:
	BG(SDL_Renderer* renderer);
	~BG(){}

	void render() const;
};
