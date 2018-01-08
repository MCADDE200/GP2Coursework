#version 420 core

//per-vertex inputs
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

//Matrices
layout(std140) uniform constants
{
	mat4 mv_matrix;
	mat4 view_matric;
	mat4 proj_matrix;
};

//inputs from vertex shader
out VS_OUT
{
	vec3 N;
	vec3 L;
	vec3 V;
} vs_out;

//Position of light
uniform vec3 light_pos = vec3(100.0, 100.0, 100.0);

void main(void)
{
	//Calculate view space coords
	vec4 P = mv_matrix* position;

	//Calculate normal in view space
	vs_out.N = mat3(mv_matrix)* normal;

	//Calculate light vector
	vs_out.V = -P.xyz;

	//Calculate the clip-space projection of each vertex
	gl_Position = proj_matrix * P;
}