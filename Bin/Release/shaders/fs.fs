#version 130

in vec2 out_TexCoord;

out vec4 Color;
uniform sampler2D LightMap;

void main()
{
	Color = texture( LightMap, out_TexCoord );
}