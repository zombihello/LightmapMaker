#include "Logger.h"

//-------------------------------------------------------------------------//

stringstream Logger::Log = stringstream();

//-------------------------------------------------------------------------//

void Logger::SaveInFile( const string& Route )
{
	ofstream File( Route );

	if ( !File.is_open() )
		return;

	File << Log.str();
	File.close();
}

//-------------------------------------------------------------------------//

void Logger::Clear()
{
	Log.clear();
}

//-------------------------------------------------------------------------//