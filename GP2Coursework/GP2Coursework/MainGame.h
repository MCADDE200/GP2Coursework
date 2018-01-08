#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "TheDisplay.h" 
#include "CreateShaders.h"
#include "CreateMesh.h"
#include "GetTextures.h"
#include "TransformMaths.h"
#include "AudioClass.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void runGame();

private:

	void initialiseSystems();
	void inputHandler();
	void gameLoop();
	void drawToScreen();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);

	TheDisplay gameDisplay;
	GameState state;
	TheMesh mesh1;
	TheMesh mesh2;
	TheCamera myCamera;
	GetTextures texture;
	GetTextures texture2;
	GetTextures texture3;
	CreateShaders shader;
	CreateShaders fogShader;
	AudioClass audioDevice;

	unsigned int backgroundMusic;
	unsigned int crashSound;

	float counter;
	float playerPosX;
	float rockPosZ;

	bool collided;
	bool crashSoundBool;
};


