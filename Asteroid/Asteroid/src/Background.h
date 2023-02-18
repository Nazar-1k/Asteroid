#pragma once

#include "Sprite.h"

class BG : public Sprite
{
public:
	BG(const char* path, int width, int height, SDL_Renderer* renderer) : Sprite(path, width, height, renderer){}
	~BG(){}

	void render() ;
};
