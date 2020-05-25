#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

#include "RenderWindow.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Game CurrentGame;
	CurrentGame.InitGame();
	
	SDL_Log("Hello World !");
	
	while (CurrentGame.IsRunning())
	{
		CurrentGame.UpdateGame();
	}

	return EXIT_SUCCESS;
}