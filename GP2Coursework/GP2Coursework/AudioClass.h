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
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAVFile(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	AudioClass();
	~AudioClass();
	unsigned int loadSoundFile(const char* filename);
	void deleteSoundFile(unsigned int id);
	void playSoundFile(unsigned int id);
	void playSoundFile(unsigned int id, glm::vec3& pos);
	void stopSound(unsigned int id);
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt);

private:

};
