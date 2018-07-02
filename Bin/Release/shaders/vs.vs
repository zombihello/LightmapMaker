#version 130

in vec3 Position;
in vec2 TexCoord;

out vec2 out_TexCoord;

uniform mat4 PV;

void main()
{
	out_TexCoord = TexCoord;
	gl_Position = PV * vec4( Position, 1.0f );
}