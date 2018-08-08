#version 130

//--------------------------------------------

out vec4 Color;

//--------------------------------------------

uniform float Intensivity;
uniform vec3 Light_Color;

//--------------------------------------------

void main()
{
	Color = vec4( Light_Color, 1 ) * Intensivity;
}

//--------------------------------------------