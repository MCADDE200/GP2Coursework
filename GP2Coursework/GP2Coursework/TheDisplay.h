#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class TheDisplay
{
public:
	TheDisplay();
	~TheDisplay();
	void initialiseDisplay();
	void swapDisplayedScreen();
	void clearTheDisplay(float r, float g, float b, float a);

	float getTheWidth();
	float getTheHeight();

private:
	void errorMessage(std::string error);

	SDL_GLContext openGlContext;
	SDL_Window* window;
	float widthOfScreen;
	float heightOfScreen;
};

