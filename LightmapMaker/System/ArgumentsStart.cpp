///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../BuildNumber.h"
#include "ArgumentsStart.h"
#include "Logger.h"

//-------------------------------------------------------------------------//

bool ArgumentsStart::IsDisableShadow = false;
bool ArgumentsStart::IsSaveLog = false;

unsigned int ArgumentsStart::MaxSizeLightmap = 16;
unsigned int ArgumentsStart::RadiosityNumberPasses = 3;

string ArgumentsStart::RouteToMap = "";

//-------------------------------------------------------------------------//

void ArgumentsStart::ShowHelp()
{
	cout << endl
		<< LIGHTMAPMAKER << " (Build " << BUILD_NUMBER ")\n\n"
		<< "This Tool Generate Lightmaps For lifeEngine\n"
		<< "Author: Egor Pogulyaka (vk.com/zombihello)\n"
		<< "She Is Must Be Run With Parameters:\n"
		<< "lm.exe -map [File.lmap] <Other Options>\n\n"
		<< "--- Options ---\n\n"
		<< "\t -map # \t : Route To Map *.lmap\n"
		<< "\t -size # \t : Max Size Lightmap\n"
		<< "\t -noshadow \t : Disable Shadows In Lightmaps\n"
		<< "\t -numpasses # \t : The Number Of Passes For Building A Re-lighting\n"
		<< "\t -savelog \t : Save Log In File\n"
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
		else if ( strstr( argv[ i ], "-size" ) && i + 1 < argc )
		{
			MaxSizeLightmap = static_cast< unsigned int >( atof( argv[ i + 1 ] ) );
			i++;
		}
		else if ( strstr( argv[ i ], "-numpasses" ) && i + 1 < argc )
		{
			RadiosityNumberPasses = static_cast< unsigned int >( atof( argv[ i + 1 ] ) );
			i++;
		}
		else if ( strstr( argv[ i ], "-help" ) )
		{
			ShowHelp();
			exit( 0 );
		}

		else if ( strstr( argv[ i ], "-noshadow" ) )	IsDisableShadow = true;
		else if ( strstr( argv[ i ], "-savelog" ) )		IsSaveLog = true;
	}
}

//-------------------------------------------------------------------------//