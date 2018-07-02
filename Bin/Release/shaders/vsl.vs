#version 130

in vec3 Position;

uniform mat4 PV;
uniform mat4 TR;

void main()
{
	gl_Position = PV * TR * vec4( Position, 1.0f );
}