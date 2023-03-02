#include "Game.h"

int main(int argc, char* args[])
{
	srand(static_cast<int>(time(NULL)));
	Game game;
	game.run();
	
	return 0;
}

//#include "Button.h"
//#include <iostream>
//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <memory>

//int main(int argc, char* args[]) {
//    SDL_Window* window;
//    SDL_Renderer* renderer;
//
//    // Initialize SDL and create a window
//    SDL_Init(SDL_INIT_VIDEO);
//    window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
//
//    // Create a renderer
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//    // Initialize SDL_ttf
//    TTF_Init();
//
//    // Create a font
//    TTF_Font* font = TTF_OpenFont("font/lazy.ttf", 24);
//
//    // Create a Button object using a unique_ptr
//    std::unique_ptr<Button> button(new Button(renderer, font, "Click me!", { 100, 100, 200, 50 }));
//
//    // Set the button's position
//    button->setPosition(200, 200);
//
//    // Set the button's text color
//    button->setTextColor({ 255, 255, 255, 255 });
//
//    // Set the button's rectangle color
//    button->setRectColor({ 0, 0, 0, 255 });
//
//    // Main loop
//    bool quit = false;
//    while (!quit) {
//        SDL_Event event;
//        while (SDL_PollEvent(&event)) {
//            switch (event.type) {
//            case SDL_QUIT:
//                quit = true;
//                break;
//            case SDL_MOUSEMOTION:
//                // Check if the mouse is over the button and set its hovered state accordingly
//                if (button->isMouseOver(event.motion.x, event.motion.y)) {
//                    button->setHovered(true);
//                }
//                else {
//                    button->setHovered(false);
//                }
//                break;
//            }
//        }
//
//        // Clear the renderer
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//        SDL_RenderClear(renderer);
//
//        // Draw the button
//        button->draw();
//
//        // Present the renderer
//        SDL_RenderPresent(renderer);
//    }
//
//    // Clean up
//    TTF_CloseFont(font);
//    TTF_Quit();
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
