#version 120

attribute vec3 positions;
attribute vec2 textureCoords;


varying vec2 textureCoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(positions, 1.0);
	textureCoord = textureCoords;
}
