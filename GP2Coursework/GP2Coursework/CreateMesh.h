#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

class TheVertex
{
public:
	TheVertex(const glm::vec3& position, const glm::vec2& textureCoords)
	{
		this->position = position;
		this->textureCoords = textureCoords;
		this->theNormal = theNormal;
	}

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTextureCoords() { return &textureCoords; }
	glm::vec3* GetTheNormal() { return &theNormal; }

private:
	glm::vec3 position;
	glm::vec2 textureCoords;
	glm::vec3 theNormal;
};

struct SphereStruct
{
public:

	SphereStruct() {}

	SphereStruct(glm::vec3& pos, float radius)
	{
		this->position = pos;
	}

	glm::vec3 GetPosition() { return position; }
	float GetRadi() { return radius; }

	void SetPosistion(glm::vec3 pos)
	{
		this->position = pos;
	}

	void SetRadi(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 position;
	float radius;
};

class TheMesh
{
public:
	TheMesh();
	~TheMesh();

	void DrawMesh();
	void initMesh(TheVertex* vertices, unsigned int numOfVertices, unsigned int* indices, unsigned int numIndices);
	void loadTheModel(const std::string& filename);
	void initTheModel(const IndexedModel& model);
	void updateSphereData(glm::vec3 pos, float radius);
	glm::vec3 getSpherePos() { return meshSphere.GetPosition(); }
	float getSphereRadius() { return meshSphere.GetRadi(); }

private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	SphereStruct meshSphere;
	GLuint VAObject;
	GLuint VABuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawNumVAObject; //how much of the vertexArrayObject do we want to draw
};
