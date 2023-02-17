#pragma once
#include "Sprite.h"

class BG : public Sprite
{
public:
	BG() :Sprite() {}
	BG(const char* path, int width, int height, SDL_Texture* texture, SDL_Renderer* renderer) : Sprite(path, width, height, texture, renderer) {}
	~BG();

	void render(int x, int y);
};
