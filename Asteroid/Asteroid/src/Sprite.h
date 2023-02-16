#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite
{
public:

	Sprite() :width(0), height(0), texture(nullptr) {}
	Sprite(int w, int h, SDL_Texture* tex) :width(w), height(h), texture(tex) {}
	~Sprite();


	void createSprite(const char path[]);
	void drawSprite(int x, int y);

	void getSpriteSize(int& w, int& h);
	int getSpriteWidth() { return width; }
	int getSpriteHeight() { return height; }

	void setSpriteSize(int w, int h);
	void setSpriteWith(int w);
	void setSpriteHeight(int h);

	void destroySprite();

private:
	int width, height;
	SDL_Texture* texture;
};

