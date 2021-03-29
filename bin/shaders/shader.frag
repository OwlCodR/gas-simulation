#version 330 core

in vec3 direction;

out vec4 finalColor;	

void main()
{
	float len = length(direction);
	finalColor = vec4(len / 0.015f, 0.0f, 0.015f / len, 1.0f);
	// It works!
}