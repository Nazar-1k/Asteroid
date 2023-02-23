#pragma once
#include "Sprite.h"
#include "Timer.h"

class Ship : public Sprite
{
public:
	Ship();
	Ship(const char* path, SDL_Renderer* renderer);
	~Ship(){}
	void PoolEvent(SDL_Event& event);
	void moveArrow();
	void moveMouse();
	void move(int width, int height);

	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	bool teleport(float& ox, float& oy, int w_scrin, int h_scrin);

private:
	bool keyUP = false;
	bool keyDown = false;
	bool keyRight = false;
	bool keyLeft = false;

	const float velocity = 0.99999;
	const float maxVelocity = 10;


	float angleVelocity;



	float dx, dy;
	
};
