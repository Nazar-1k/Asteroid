#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Sprite
{
public:

	Sprite() :width(0), height(0), texture(nullptr), renderer(nullptr),
		angle(0.0), center(nullptr), flip(SDL_FLIP_NONE),
		is_Empty(false), x(0), y(0) {}
	Sprite(const char* path, SDL_Renderer* renderer);
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
	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void getSize(int& w, int& h);
	int getWidth() { return width; }
	int getHeight() { return height; }

	float getX() { return x; }
	float getY() { return y; }

	void setRenderer(SDL_Renderer* renderer);

	void setSize(int w, int h);
	void setWith(int w);
	void setHeight(int h);

	float setX();
	float setY();

	//Deallocates texture
	void free();

	bool isEmpty() { return is_Empty; }

	Sprite operator=(const Sprite& other);

protected:
	int width, height;

	SDL_Texture* texture;
	SDL_Renderer* renderer;

	float angle;
	SDL_Point* center;
	SDL_RendererFlip flip;

	bool is_Empty;
	float x, y;
};

