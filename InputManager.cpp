#include "InputManager.h"

VirtualButton::VirtualButton()
{
	PressState = VirtualButton::State::RELEASED;
}

void InputManager::RegisterInput(SDL_Keycode keyInput, VirtualButton::State inputState, VirtualButtonCallback callback)
{
	switch (inputState)
	{
	case VirtualButton::State::RELEASED:
		_RegisteredInput[keyInput].OnReleased = callback;
		break;
	case VirtualButton::State::PRESSED:
		_RegisteredInput[keyInput].OnPressed = callback;
		break;
	case VirtualButton::State::REPEAT_PRESSED:
		_RegisteredInput[keyInput].OnRepeatPressed = callback;
		break;
	}
}

void InputManager::ProcessInput(const SDL_Event& sdlEvent)
{
	// Find the virtual button linked to the SDL event,
	// exit early if none found
	SDL_KeyboardEvent keyboardEvent = sdlEvent.key;
	auto btnIt = _RegisteredInput.find(keyboardEvent.keysym.sym);
	if (btnIt == _RegisteredInput.end())
		return;

	VirtualButton btn = btnIt->second;
	switch (keyboardEvent.type)
	{

	case SDL_KEYDOWN:
		btn.PressState = VirtualButton::State::RELEASED;
		if (!btn.OnReleased) break;
		btn.OnReleased(btn);
		break;

	case SDL_KEYUP:
		if (keyboardEvent.repeat)
		{
			btn.PressState = VirtualButton::State::REPEAT_PRESSED;
			if (!btn.OnRepeatPressed) break;
			btn.OnRepeatPressed(btn);
		}
		else
		{
			btn.PressState = VirtualButton::State::PRESSED;
			if (!btn.OnPressed) break;
			btn.OnPressed(btn);
		}
		break;

	default:
		break;
	}
}
