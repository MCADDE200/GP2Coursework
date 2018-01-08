#version 420 core

//output
layout (location = 0) out vec4 color;

//inputs from vertex shader
in VS_OUT
{
	vec3 N;
	vec3 L;
	vec3 V;
} fs_in;

//Material properties
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform vec3 specular_power = 128.0;

void main(void)
{
	//Normalize incoming vectors
	vec3 N = normalize(fs_in.N);
	vec3 L = normalize(fs_in.L);
	vec3 V = normalize(fs_in.V);

	//Calculate R locally
	vec3 H = normalize(L + V);

	//Compute the diffuse and specular components for each fragment
	vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
	vec3 specular = pow(max(dot(N, H), 0.0), specular_power) * specular_albedo;

	//write final color to the framebuffer
	color = vec4(diffuse + specular, 1.0);
}