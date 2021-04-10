#version 330 core

uniform vec4 currentColor;

out vec4 finalColor;	

void main()
{
	//float len = length(direction);
	//finalColor = vec4(len / 0.002f, 0.0f, 0.002f / len, 1.0f);
	// It works!

	finalColor = currentColor;
}