///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../BuildNumber.h"
#include "ArgumentsStart.h"
#include "Logger.h"

//-------------------------------------------------------------------------//

bool ArgumentsStart::IsSaveLog = false;
bool ArgumentsStart::IsNoShadow = false;
bool ArgumentsStart::IsNoRadiosity = false;

unsigned int ArgumentsStart::MaxSizeLightmap = 16;
unsigned int ArgumentsStart::RadiosityNumberPasses = 3;
unsigned int ArgumentsStart::SizeRenderTexture = 32;

string ArgumentsStart::RouteToMap = "";

//-------------------------------------------------------------------------//

void ArgumentsStart::ShowHelp()
{
	cout << endl
		<< LIGHTMAPMAKER << " (Build " << BUILD_NUMBER ")\n\n"
		<< "This Tool Generate Lightmaps For lifeEngine\n"
		<< "Author: Egor Pogulyaka (vk.com/zombihello)\n"
		<< "She Is Must Be Run With Parameters:\n"
		<< "lm.exe -map [File.lmap] -textures [Route To Directory With Textures] <Other Options>\n\n"
		<< "--- Options ---\n\n"
		<< "\t -map # \t : Route To Map *.lmap\n"
		<< "\t -maxsize # \t : Max Size Lightmap\n"
		<< "\t -numpasses # \t : The Number Of Passes For Building A Re-lighting\n"
		<< "\t -rendersize # \t : Size Render Texture\n"
		<< "\t -textures # \t : Route To Directory With Textures\n"
		<< "\t -savelog \t : Save Log In File\n"
		<< "\t -noshadows \t : Disable Shadows\n"
		<< "\t -noradiosity \t : Disable Secondary Light\n"
		<< "\t -help \t\t : Show Help\n";
}

//-------------------------------------------------------------------------//

void ArgumentsStart::InitArgumentsStart( int argc, char** argv )
{
	for ( int i = 0; i < argc; i++ )
	{
		if ( strstr( argv[ i ], "-map" ) && i + 1 < argc )
		{
			RouteToMap = argv[ i + 1 ];
			i++;
		}
		else if ( strstr( argv[ i ], "-maxsize" ) && i + 1 < argc )
		{
			MaxSizeLightmap = static_cast< unsigned int >( atof( argv[ i + 1 ] ) );
			i++;
		}
		else if ( strstr( argv[ i ], "-numpasses" ) && i + 1 < argc )
		{
			RadiosityNumberPasses = static_cast< unsigned int >( atof( argv[ i + 1 ] ) );
			i++;
		}
		else if ( strstr( argv[ i ], "-rendersize" ) && i + 1 < argc )
		{
			SizeRenderTexture = static_cast< unsigned int >( atof( argv[ i + 1 ] ) );
			bool isPowerOfTwo = SizeRenderTexture && !( SizeRenderTexture & ( SizeRenderTexture - 1 ) );

			if ( !isPowerOfTwo )
				SizeRenderTexture = static_cast< unsigned int >( pow( 2, ( int ) ( log( SizeRenderTexture ) / log( 2 ) ) ) );

			i++;
		}
		else if ( strstr( argv[ i ], "-textures" ) && i + 1 < argc )
		{
			Directories::TexturesDirectory = argv[ i + 1 ];
			i++;
		}
		else if ( strstr( argv[ i ], "-help" ) )
		{
			ShowHelp();
			exit( 0 );
		}

		else if ( strstr( argv[ i ], "-savelog" ) )		IsSaveLog = true;
		else if ( strstr( argv[ i ], "-noshadows" ) ) IsNoShadow = true;
		else if ( strstr( argv[ i ], "-noradiosity" ) ) IsNoRadiosity = true;
	}
}

//-------------------------------------------------------------------------//