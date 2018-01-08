#version 120

attribute vec3 position;
attribute vec2 textureCoords;
attribute vec3 normals;


varying vec2 texCoords;
varying vec3 normalsV;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoords = textureCoords;
	normalsV = (transform * vec4(normals, 0.0)).xyz;
}
