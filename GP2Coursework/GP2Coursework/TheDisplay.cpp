#include "TheDisplay.h"


TheDisplay::TheDisplay()
{
	window = nullptr;
	widthOfScreen = 1024.0f;
	heightOfScreen = 768.0f;
}

TheDisplay::~TheDisplay()
{
	SDL_GL_DeleteContext(openGlContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

float TheDisplay::getTheWidth() { return widthOfScreen; } //getters
float TheDisplay::getTheHeight() { return heightOfScreen; }

void TheDisplay::errorMessage(std::string error)
{
	std::cout << error << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void TheDisplay::swapDisplayedScreen()
{
	SDL_GL_SwapWindow(window);
}

void TheDisplay::clearTheDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void TheDisplay::initialiseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	window = SDL_CreateWindow("Dodge The Rock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widthOfScreen, heightOfScreen, SDL_WINDOW_OPENGL); // create window

	if (window == nullptr)
	{
		errorMessage("window failed to create");
	}

	openGlContext = SDL_GL_CreateContext(window);

	if (openGlContext == nullptr)
	{
		errorMessage("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		errorMessage("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}
