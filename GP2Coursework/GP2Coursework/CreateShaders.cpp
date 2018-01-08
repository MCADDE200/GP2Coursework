#include "CreateShaders.h"
#include <iostream>
#include <fstream>

CreateShaders::CreateShaders()
{

}

void CreateShaders::initShaders(const std::string& filename)
{
	shaderProgram = glCreateProgram(); // create shader program (openGL saves as ref number)
	arrayShaders[0] = MakeShader(LoadShaderFile("..\\res\\shader.vert"), GL_VERTEX_SHADER); // create vertex shader
	arrayShaders[1] = MakeShader(LoadShaderFile("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUM_OF_SHADERS; i++)
	{
		glAttachShader(shaderProgram, arrayShaders[i]); //add all our shaders to the shader program "shaders" 
	}

	glBindAttribLocation(shaderProgram, 0, "positions"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(shaderProgram, 1, "textureCoords");
	

	glLinkProgram(shaderProgram); //create executables that will run on the GPU shaders
	ReturnShaderError(shaderProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(shaderProgram); //check the entire program is valid
	ReturnShaderError(shaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderProgram, "transform"); // associate with the location of uniform variable within a program
}

//void CreateShaders::initFogShaders(const std::string& filename)
//{
//	shaderProgram = glCreateProgram(); // create shader program (openGL saves as ref number)
//	arrayShaders[2] = MakeShader(LoadShaderFile("..\\res\\FogShader.vert"), GL_VERTEX_SHADER); // create vertex shader
//	arrayShaders[3] = MakeShader(LoadShaderFile("..\\res\\FogShader.frag"), GL_FRAGMENT_SHADER); // create fragment shader
//
//	for (unsigned int i = 0; i < NUM_OF_SHADERS; i++)
//	{
//		glAttachShader(shaderProgram, arrayShaders[i]); //add all our shaders to the shader program "shaders" 
//	}
//
//	glBindAttribLocation(shaderProgram, 0, "positions"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
//	glBindAttribLocation(shaderProgram, 1, "textureCoords");
//	glBindAttribLocation(shaderProgram, 2, "normals");
//
//	glLinkProgram(shaderProgram); //create executables that will run on the GPU shaders
//	ReturnShaderError(shaderProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // check for error
//
//	glValidateProgram(shaderProgram); //check the entire program is valid
//	ReturnShaderError(shaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");
//
//	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderProgram, "transform"); // associate with the location of uniform variable within a program
//}



CreateShaders::~CreateShaders()
{
	for (unsigned int i = 0; i < NUM_OF_SHADERS; i++)
	{
		glDetachShader(shaderProgram, arrayShaders[i]); //detach shader from program
		glDeleteShader(arrayShaders[i]); //delete the sahders
	}
	glDeleteProgram(shaderProgram); // delete the program
}

void CreateShaders::BindShaders()
{
	glUseProgram(shaderProgram); //installs the program object specified by program as part of rendering state
}

void CreateShaders::UpdateShaders(const TheTransform& transform, const TheCamera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}

GLuint CreateShaders::MakeShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	ReturnShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string CreateShaders::LoadShaderFile(const std::string& fileName)
{
	std::ifstream shaderFile;
	shaderFile.open((fileName).c_str());

	std::string output;
	std::string line;

	if (shaderFile.is_open())
	{
		while (shaderFile.good())
		{
			getline(shaderFile, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void CreateShaders::ReturnShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
