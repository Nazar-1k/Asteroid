#include "Background.h"
#include "Game.h"

void BG::render() const
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}