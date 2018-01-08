#include "CreateMesh.h"
#include <vector>


void TheMesh::initMesh(TheVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTextureCoords());
		model.normals.push_back(*vertices[i].GetTheNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	initTheModel(model);
}

void TheMesh::initTheModel(const IndexedModel& model)
{

	drawNumVAObject = model.indices.size();

	glGenVertexArrays(1, &VAObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(VAObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFERS, VABuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, VABuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VABuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VABuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VABuffers[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
}

TheMesh::TheMesh()
{
	drawNumVAObject = NULL;
}

void TheMesh::loadTheModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initTheModel(model);
	SphereStruct meshSphere();
}

TheMesh::~TheMesh()
{
	glDeleteVertexArrays(1, &VAObject); // delete arrays
}

void TheMesh::DrawMesh()
{
	glBindVertexArray(VAObject);

	glDrawElements(GL_TRIANGLES, drawNumVAObject, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glBindVertexArray(0);
}

void TheMesh::updateSphereData(glm::vec3 pos, float radius)
{
	meshSphere.SetPosistion(pos);
	meshSphere.SetRadi(radius);
}