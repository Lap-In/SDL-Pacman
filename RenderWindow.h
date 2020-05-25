#pragma once

#include <SDL.h>
#include <GL/glew.h>

class RenderWindow
{
private:
	SDL_Window* Window;
	SDL_GLContext GLContext;

public:
	int XSize, YSize;

	// Constructors
	RenderWindow();
	RenderWindow(int xSize, int ySize);

	// Destructor
	~RenderWindow();

	void InitWindow();
	void CleanUpWindow();

	void Render();

private:
	void SetGlParameters();
	void CreateWindow();
	void CreateGLContext();
	void LoadGLModules();

	void ClearWindow();
};

