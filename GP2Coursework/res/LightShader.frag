#version 120 

varying vec2 textureCoords;
varying vec3 normals;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, textureCoords) * clamp(dot(vec3(0,0,1), normals), 0.5, 1.0);
}