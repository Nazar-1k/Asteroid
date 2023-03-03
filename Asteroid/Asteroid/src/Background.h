#pragma once

#include "Sprite.h"

class BG : public Sprite
{
public:
	BG(const char* path, SDL_Renderer* renderer) : Sprite(path, renderer){}
	~BG(){}

	void render() const;
};
