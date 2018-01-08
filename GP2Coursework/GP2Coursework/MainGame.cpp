#include "MainGame.h"
#include <iostream>
#include <string>

TheTransform transform;

MainGame::MainGame()
{
	state = GameState::PLAY;
	TheDisplay* gameDisplay = new TheDisplay(); //new display
	TheMesh* mesh1();
	TheMesh* mesh2();
	GetTextures* texture();
	GetTextures* texture2();
	CreateShaders* shader();
	CreateShaders* fogShader();
	AudioClass* audioDevice();
	playerPosX = 0.0f;
	rockPosZ = 10.0f;
	collided = false;
	crashSoundBool = false;
}

MainGame::~MainGame()
{
}

void MainGame::runGame()
{
	initialiseSystems();
	gameLoop();
}

void MainGame::initialiseSystems()
{
	gameDisplay.initialiseDisplay();
	
	mesh1.loadTheModel("..\\res\\Car.obj");
	mesh2.loadTheModel("..\\res\\RockOBJ.obj");

	texture.initTextures("..\\res\\Rock.jpg"); //get bricks texture
	texture2.initTextures("..\\res\\black.jpg");
	shader.initShaders("..\\res\\shader"); //new shader
	fogShader.initShaders("..\\res\\shader");

	backgroundMusic = audioDevice.loadSoundFile("..\\res\\backgroundMusic.wav");
	crashSound = audioDevice.loadSoundFile("..\\res\\bang.wav");

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)gameDisplay.getTheWidth() / gameDisplay.getTheHeight(), 0.01f, 1000.0f);
	counter = 0.0f;
}

void MainGame::gameLoop()
{
	while (state != GameState::EXIT)
	{
		inputHandler();
		drawToScreen();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
		playAudio(backgroundMusic, myCamera.GetCameraPosition());

	}
}

void MainGame::inputHandler()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) //get and process events
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			state = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym)
			{
			case SDLK_UP:
				myCamera.MoveForward(1.0f); //Allow the camera to zoom in
				break;
			case SDLK_DOWN:
				myCamera.MoveForward(-1.0f); //Allow the camera to zoom out
				break;
			case SDLK_LEFT:
				myCamera.MoveRight(1.0f); //Allow the camera to move left
				break;
			case SDLK_RIGHT:
				myCamera.MoveRight(-1.0f); //Allow the camera to move right
				break;
			case SDLK_e:
				myCamera.RotateY(10); //Can rotate the comera by an angle of 10
				break;
			case SDLK_q:
				myCamera.RotateY(-10); //Can rotate the comera by an angle of 10
				break;
			case SDLK_d:
				playerPosX = playerPosX - 0.05f; //Moves the player (car) to the right
				break;
			case SDLK_a:
				playerPosX = playerPosX + 0.05f; //Moves the player (car) to the left	q
				break;
			}
		}
	}

}

void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audioDevice.playSoundFile(Source, pos);
	}
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		collided = true;
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::drawToScreen()
{
	gameDisplay.clearTheDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	if (!collided)
	{
		transform.SetPos(glm::vec3(playerPosX, -2.0, 0.0));
		transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		transform.SetScale(glm::vec3(0.02, 0.02, 0.02));

		shader.BindShaders();
		shader.UpdateShaders(transform, myCamera);
		texture2.BindTextures(0);
		mesh1.DrawMesh();
		mesh1.updateSphereData(*transform.GetPos(), 0.6f);

		if (counter > 11)
		{
			counter = 0;
		}
		transform.SetPos(glm::vec3(0.0, -2.0, rockPosZ - counter));
		transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		transform.SetScale(glm::vec3(0.05, 0.05, 0.05));

		fogShader.BindShaders();
		fogShader.UpdateShaders(transform, myCamera);
		texture.BindTextures(0);
		mesh2.DrawMesh();
		mesh2.updateSphereData(*transform.GetPos(), 0.6f);
		counter = counter + 0.05f;
	}
	else
	{
		mesh1.~TheMesh();
		mesh2.~TheMesh();
		crashSoundBool = true;
	}

	if (crashSoundBool)
	{
		playAudio(crashSound, myCamera.GetCameraPosition());
		crashSoundBool = false;
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.swapDisplayedScreen();
}