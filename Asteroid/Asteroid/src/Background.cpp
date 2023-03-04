#include "Background.h"
#include "Game.h"

static const char path[] = "data/BG/background.png";

BG::BG(SDL_Renderer* renderer)
{
	initSprite(path, renderer);
}

void BG::render() const
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}