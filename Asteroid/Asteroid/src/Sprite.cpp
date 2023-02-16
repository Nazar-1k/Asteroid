#include "Sprite.h"

Sprite::~Sprite()
{
	destroySprite();
}

void Sprite::createSprite(const char path[])
{
	/*texture = IMG_LoadTexture(g_renderer, path);
	if (!texture) {
		printf_s(stderr, "Couldn't load %s: %s\n", path, SDL_GetError());
		
	}*/
}

void Sprite::drawSprite(int x, int y)
{
	SDL_Rect r;
	r.w = width;
	r.h = height;
	r.x = x;
	r.y = y;
	/*SDL_RenderCopy(g_renderer, texture, NULL, &r);*/
}

void Sprite::getSpriteSize(int& w, int& h)
{
}

void Sprite::setSpriteSize(int w, int h)
{
	this->width = w;
	this->height = h;
}

void Sprite::setSpriteWith(int w)
{
	this->width = w;
}

void Sprite::setSpriteHeight(int h)
{
	this->height = h;
}

void Sprite::destroySprite()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}
}
