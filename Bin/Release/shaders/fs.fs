#version 130

in vec2 out_TexCoord;

out vec4 Color;

void main()
{
	Color = vec4( out_TexCoord.x, out_TexCoord.y, 0, 1 );
}