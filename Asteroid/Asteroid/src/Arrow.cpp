#include "Arrow.h"

void Arrow::PoolEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		x = e.button.x;
		y = e.button.y;
	}
}


 void Arrow::render()
{
	 SDL_Rect renderQuad = { static_cast<int>(x - width / 2),  static_cast<int>(y - height / 2), width, height };
	
	 SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
