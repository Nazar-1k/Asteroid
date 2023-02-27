#include "Game.h"

int main(int argc, char* args[])
{
	srand(static_cast<int>(time(NULL)));
	Game game;
	game.run();
	
	return 0;
}
