#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class AudioClass
{
	struct dataStruct {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		dataStruct(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	struct Vector3Struct
	{
		float x, y, z;
	};
	std::vector<dataStruct> datas;
	ALCcontext* context;
	ALCdevice *device;
	bool isBigEndian(); //Checks to see what type of data is stored so sound data is read properly
	int convertToInt(char* buffer, int length); //converts certain audio files to int which can be read
	char* loadWAVFile(const char* fn, int& chan, int& samplerate, int& bps, int& size); //Load wav file

public:
	AudioClass();
	~AudioClass();
	unsigned int loadSoundFile(const char* filename); //load files
	void deleteSoundFile(unsigned int id); //delete files from memory
	void playSoundFile(unsigned int id); //play files
	void playSoundFile(unsigned int id, glm::vec3& pos); //play files given a position
	void stopSound(unsigned int id); //stop playing sound
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt); //sets a listener;

private:

};
