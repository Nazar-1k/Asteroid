#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Sprite
{
public:

	Sprite() :width(0), height(0), texture(nullptr), renderer(nullptr) {}
	Sprite(const char* path, int width, int height, SDL_Renderer* renderer);
	virtual ~Sprite();

	//Loads image at specified path
	bool loadFromFile(const char* path);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	void getSize(int& w, int& h);
	int getWidth() { return width; }
	int getHeight() { return height; }

	void setSize(int w, int h);
	void setWith(int w);
	void setHeight(int h);

	//Deallocates texture
	void free();

protected:
	int width, height;
	SDL_Texture* texture;

	SDL_Renderer* renderer;
};

