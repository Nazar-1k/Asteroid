/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>



#include "Game.h"
int main(int argc, char* args[])
{
	Game game;
	game.run();
	/*delete game;*/
	////Start up SDL and create window
	//if (!init())
	//{
	//	printf("Failed to initialize!\n");
	//}
	//else
	//{
	//	//Load media
	//	if (!loadMedia())
	//	{
	//		printf("Failed to load media!\n");
	//	}
	//	else
	//	{
	//		//Main loop flag
	//		bool quit = false;

	//		//Event handler
	//		SDL_Event e;

	//		//While application is running
	//		while (!quit)
	//		{
	//			//Handle events on queue
	//			while (SDL_PollEvent(&e) != 0)
	//			{
	//				//User requests quit
	//				if (e.type == SDL_QUIT)
	//				{
	//					quit = true;
	//				}
	//			}

	//			//Apply the PNG image
	//			SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

	//			//Update the surface
	//			SDL_UpdateWindowSurface(gWindow);
	//		}
	//	}
	//}

	////Free resources and close SDL
	//close();

	return 0;
}