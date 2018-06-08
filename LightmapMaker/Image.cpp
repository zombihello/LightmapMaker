#include "Image.h"

///////////////////////////
// STB
///////////////////////////
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

//-------------------------------------------------------------------------//

void Image::Create( size_t Width, size_t Height, const glm::vec4& Color )
{
	if ( Width && Height )
	{
		vector<uint8_t> newPixels( Width * Height * 4 );

		uint8_t* ptr = &newPixels[ 0 ];
		uint8_t* end = ptr + newPixels.size();
		while ( ptr < end )
		{
			*ptr++ = Color.x;
			*ptr++ = Color.y;
			*ptr++ = Color.z;
			*ptr++ = Color.w;
		}

		Pixels.swap( newPixels );

		Size.x = Width;
		Size.y = Height;
	}
	else
	{
		vector<uint8_t>().swap( Pixels );

		Size.x = 0;
		Size.y = 0;
	}
}

//-------------------------------------------------------------------------//

void Image::SaveInFile( const string& Route )
{
	stbi_write_png( Route.c_str(), Size.x, Size.y, 4, Pixels.data(), Size.x * 4 );
}

//-------------------------------------------------------------------------//

void Image::Clear()
{
	Pixels.clear();
}

//-------------------------------------------------------------------------//

void Image::SetPixel( size_t X, size_t Y, const glm::vec4& Color )
{
	uint8_t* Pixel = &Pixels[ ( X + Y * Size.x ) * 4 ];
	*Pixel++ = Color.x;
	*Pixel++ = Color.y;
	*Pixel++ = Color.z;
	*Pixel++ = Color.w;
}

//-------------------------------------------------------------------------//