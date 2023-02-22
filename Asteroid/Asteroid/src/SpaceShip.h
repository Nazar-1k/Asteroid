#pragma once
#include "Sprite.h"
#include "Timer.h"

class Ship : public Sprite
{
public:
	Ship();
	Ship(const char* path, int width, int height, SDL_Renderer* renderer) : Sprite(path, width, height, renderer) {}
	~Ship(){}
	void PoolEvent(SDL_Event& event);
	void moveArrow();
	void moveMouse();
	void move(int width, int height);
	
	void teleport(float w_scrin, float h_scrin);

private:
	bool keyUP = false;
	bool keyDown = false;
	bool keyRight = false;
	bool keyLeft = false;

	const float velocity = 0.99999;
	const float maxVelocity = 10;


	float dx, dy;
	
};
