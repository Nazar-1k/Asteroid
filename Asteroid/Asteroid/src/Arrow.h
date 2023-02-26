#include "Sprite.h"

class Arrow : public Sprite
{
public:
	Arrow(const char* path, SDL_Renderer* renderer) : Sprite(path, renderer) {}
	~Arrow() {}

	void PoolEvent(SDL_Event& e);

	void render();

};