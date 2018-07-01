﻿///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <sstream>
#include <iomanip>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Logger.h"
#include "Directories.h"

//-------------------------------------------------------------------------//

ofstream Logger::Log = ofstream();
string Logger::NameLog = "";
time_t Logger::RawTime = 0;
tm* Logger::NowTime = NULL;

//-------------------------------------------------------------------------//

void Logger::CreateLogFile()
{
	stringstream RouteFile;

	time( &RawTime );
	NowTime = localtime( &RawTime );

	RouteFile << Directories::LogDirectory
		<< "\\" << setw( 2 ) << setfill( '0' ) << NowTime->tm_mday << "-"
		<< setw( 2 ) << setfill( '0' ) << NowTime->tm_mon + 1 << "-"
		<< NowTime->tm_year + 1900 << "_"
		<< setw( 2 ) << setfill( '0' ) << NowTime->tm_hour << "-"
		<< setw( 2 ) << setfill( '0' ) << NowTime->tm_min << "-"
		<< setw( 2 ) << setfill( '0' ) << NowTime->tm_sec << ".log";

	NameLog = RouteFile.str();

	Log.open( NameLog );
}

//-------------------------------------------------------------------------//

void Logger::DeleteLogFile()
{
	if ( Log.is_open() )
	{
		Log.close();
		remove( NameLog.c_str() );
	}
}

//-------------------------------------------------------------------------//

string Logger::GetTime()
{
	stringstream Time;

	time( &RawTime );
	NowTime = localtime( &RawTime );

	Time << "[" << setw( 2 ) << setfill( '0' ) << NowTime->tm_hour << ":"
		<< setw( 2 ) << setfill( '0' ) << NowTime->tm_min << ":"
		<< setw( 2 ) << setfill( '0' ) << NowTime->tm_sec << "] ";

	return Time.str();
}

//-------------------------------------------------------------------------//