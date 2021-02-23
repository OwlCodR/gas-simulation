#version 330 core

out vec4 finalColor;	

uniform vec4 currentColor;

void main()
{
	finalColor = currentColor;
}