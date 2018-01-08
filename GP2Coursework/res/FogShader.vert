#version 400

layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec3 VertexNormal;

out vec3 pos;
out vec3 normals;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main()
{
	normals = normalize(NormalMatrix * VertexNormal);
	pos = vec3(ModdelViewMatrix * vec4(VertexPos, 1.0));
	gl_Position = MVP * vec4(VertexPos, 1.0);
}