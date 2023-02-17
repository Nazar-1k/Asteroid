#include "Background.h"
#include "Game.h"

void BG::render()
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}