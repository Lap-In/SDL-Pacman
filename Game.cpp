#include "Game.h"

#include <ctime>

void Game::InitGame()
{
	_TimeSinceStart = 0.0f;
	_DeltaTime = 0.0f;
	_IsRunning = true;
	_AskedStop = false;

	// Start by initializing SDL2
	if (SDL_Init(SDL_VIDEO_OPENGL))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed init");
	}

	_MainWindow.InitWindow();
	_InputManager.RegisterInput(SDLK_ESCAPE, VirtualButton::State::PRESSED,
		[&](const VirtualButton& btn) { _AskedStop = true; });
}

void Game::StopGame()
{
	_MainWindow.CleanUpWindow();
	_IsRunning = false;
	_AskedStop = false;

	SDL_Quit();
}

void Game::UpdateGame()
{
	if (!_IsRunning) return;

	// Current time
	clock_t renderTime = clock();

	ParseInput();
	_MainWindow.Render();

	// Update the time before finishing
	renderTime = clock() - renderTime;
	_DeltaTime = ((float)renderTime) / CLOCKS_PER_SEC;
	_TimeSinceStart += _DeltaTime;

	// Stop the game if asked to
	if (_AskedStop)
		StopGame();
}

void Game::ParseInput()
{
	// Get the input event captured by SDL
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
			// If user ask to quit
		case SDL_QUIT:
			_AskedStop = true;
			return;

		case SDL_KEYUP:
		case SDL_KEYDOWN:
			_InputManager.ProcessInput(Event);
			return;

		default:
			break;
		}
	}
}

const bool Game::IsRunning()
{
	return !_AskedStop && _IsRunning;
}

const RenderWindow* Game::GetMainRenderWindow()
{
	return &_MainWindow;
}

const float Game::GetTimeSinceStart()
{
	return _TimeSinceStart;
}

const float Game::GetDeltaTime()
{
	return _DeltaTime;
}
