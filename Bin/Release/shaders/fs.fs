#version 130

in vec2 out_TexCoord0;
in vec2 out_TexCoord1;

out vec4 Color;

uniform sampler2D DiffuseMap;
uniform sampler2D LightMap;

void main()
{
	Color = texture( DiffuseMap, out_TexCoord0 ) * texture( LightMap, out_TexCoord1 );
}