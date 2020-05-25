#pragma once

#include "RenderWindow.h"
#include "InputManager.h"

/**
*	class Game
*
*	Manage the lifetime of a game program
*/
class Game
{
	/**
		Properties ===================================================
	*/
private:
	// The main window used to display the game world
	class RenderWindow _MainWindow;
	class InputManager _InputManager;

	bool _IsRunning;

	// Flag used if we want to stop the game 
	// (prefered method as it will stop the game only after the current update finish)
	bool _AskedStop;

	// Time since start in seconds
	float _TimeSinceStart;

	// Time it took to complete a cycle in a second
	float _DeltaTime;

public:
	void InitGame();
	void StopGame();
	void UpdateGame();
	void ParseInput();

	const bool IsRunning();
	const RenderWindow* GetMainRenderWindow();
	const float GetTimeSinceStart();
	const float GetDeltaTime();
};

