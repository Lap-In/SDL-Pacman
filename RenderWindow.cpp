#include "RenderWindow.h"

// Constructors
RenderWindow::RenderWindow()
{
	XSize = 840;
	YSize = 720;

	Window = nullptr;
	GLContext = nullptr;
}

RenderWindow::RenderWindow(int xSize, int ySize)
{
	XSize = xSize;
	YSize = ySize;

	Window = nullptr;
	GLContext = nullptr;
}

// Destructor
RenderWindow::~RenderWindow()
{
	CleanUpWindow();
}

void RenderWindow::InitWindow()
{
	SetGlParameters();

	CreateWindow();
	CreateGLContext();
	LoadGLModules();

	ClearWindow();
	Render();
}

void RenderWindow::CleanUpWindow()
{
	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(Window);
}

void RenderWindow::Render()
{
	SDL_GL_SwapWindow(Window);
	ClearWindow();
}

void RenderWindow::SetGlParameters()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void RenderWindow::CreateWindow() 
{
	Window = SDL_CreateWindow(
		"SDL2 Pacman",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		XSize,
		YSize,
		SDL_WINDOW_OPENGL);

	if (Window == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error in the creation of the window !");
	}
}

void RenderWindow::CreateGLContext()
{
	GLContext = SDL_GL_CreateContext(Window);

	if (GLContext == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error in the creation of the OpenGL context !");
	}
}

void RenderWindow::LoadGLModules()
{
	glViewport(0, 0, XSize, YSize);

	auto glewInitSate = glewInit();

	if (glewInitSate != GLEW_OK)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error in the glew load !");
	}
}


void RenderWindow::ClearWindow()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
