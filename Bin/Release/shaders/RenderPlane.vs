#version 130

//--------------------------------------------

in vec3 Position;
in vec2 TexCoord0;
in vec2 TexCoord1;

//--------------------------------------------

out vec2 out_TexCoord0;
out vec2 out_TexCoord1;

//--------------------------------------------

uniform mat4 PVMatrix;

//--------------------------------------------

void main()
{
	out_TexCoord0 = TexCoord0;
	out_TexCoord1 = TexCoord1;
	gl_Position = PVMatrix * vec4( Position, 1.0f );
}

//--------------------------------------------