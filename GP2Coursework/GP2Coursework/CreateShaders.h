#pragma once
#include <string>
#include <GL\glew.h>
#include "TransformMaths.h"
#include "TheCamera.h"

class CreateShaders
{
public:
	CreateShaders();

	void BindShaders(); //Set gpu to use our shaders
	void UpdateShaders(const TheTransform& transform, const TheCamera& camera);
	void initShaders(const std::string& filename);
	void initFogShaders(const std::string& filename);

	std::string CreateShaders::LoadShaderFile(const std::string& fileName);
	void CreateShaders::ReturnShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShaders::MakeShader(const std::string& text, unsigned int type);



	~CreateShaders();


protected:
private:
	static const unsigned int NUM_OF_SHADERS = 2; // number of shaders
	
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint shaderProgram; // Track the shader program
	GLuint arrayShaders[NUM_OF_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS];
};
