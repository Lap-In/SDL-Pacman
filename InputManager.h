#pragma once

#include <map>
#include <functional>
#include <SDL.h>

// Forward declare the struct for the callback
struct VirtualButton;
// Define a callback a virtual button is going to call when processed
class VirtualButtonCallback : public std::function<void(const VirtualButton&)> 
{
	using std::function<void(const VirtualButton&)>::function;
};

struct VirtualButton
{
	enum class State
	{
		RELEASED,
		PRESSED,
		REPEAT_PRESSED
	};

	VirtualButton();

	State PressState;
	VirtualButtonCallback OnPressed;
	VirtualButtonCallback OnRepeatPressed;
	VirtualButtonCallback OnReleased;
};

class InputManager
{
public:
	void RegisterInput(SDL_Keycode keyInput, VirtualButton::State inputState, VirtualButtonCallback callback);
	void ProcessInput(const SDL_Event& sdlEvent);

private:
	std::map<SDL_Keycode, VirtualButton> _RegisteredInput;
};

