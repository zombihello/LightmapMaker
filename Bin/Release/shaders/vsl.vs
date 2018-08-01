#version 130

in vec3 Position;

uniform mat4 PV;

void main()
{
	gl_Position = PV * vec4( Position, 1.0f );
}