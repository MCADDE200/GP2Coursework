#pragma once
#include <string>
#include <GL\glew.h>

class GetTextures
{
public:
	GetTextures();

	void BindTextures(unsigned int unit); // bind upto 32 textures
	void initTextures(const std::string& fileName);

	~GetTextures();

protected:
private:

	GLuint textureManager;
};
