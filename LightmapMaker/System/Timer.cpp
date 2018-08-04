#include "Timer.h"

//-------------------------------------------------------------------------//

Time::Time() :
	Hours( 0 ),
	Minutes( 0 ),
	Seconds( 0 ),
	InSeconds( 0 )
{}

//-------------------------------------------------------------------------//

Time::Time( float InSeconds )
{
	Init( InSeconds );
}

//-------------------------------------------------------------------------//

Time::Time( size_t Hours, size_t Minutes, size_t Seconds ) :
	Hours( Hours ),
	Minutes( Minutes ),
	Seconds( Seconds )
{}

//-------------------------------------------------------------------------//

void Time::Init( float InSeconds )
{
	this->InSeconds = InSeconds;

	Hours = InSeconds / 3600;
	Minutes = ( InSeconds - Hours * 3600 ) / 60;
	Seconds = InSeconds - Hours * 3600 - Minutes * 60;
}

//-------------------------------------------------------------------------//

void Time::Init( size_t Hours, size_t Minutes, size_t Seconds )
{
	this->Hours = Hours;
	this->Minutes = Minutes;
	this->Seconds = Seconds;
}

//-------------------------------------------------------------------------//

Time& Time::operator=( const Time& Time )
{
	Hours = Time.Hours;
	Minutes = Time.Minutes;
	Seconds = Time.Seconds;
	InSeconds = Time.InSeconds;

	return *this;
}

//-------------------------------------------------------------------------//

Time& Time::operator*( const size_t& Velue )
{
	InSeconds *= Velue;

	Hours = InSeconds / 3600;
	Minutes = ( InSeconds - Hours * 3600 ) / 60;
	Seconds = InSeconds - Hours * 3600 - Minutes * 60;

	return *this;
}

//-------------------------------------------------------------------------//





//-------------------------------------------------------------------------//

void Timer::Start()
{
	CountingStart = clock();
}

//-------------------------------------------------------------------------//

void Timer::End()
{
	CountingEnd = clock();
}

//-------------------------------------------------------------------------//

Time Timer::GetTime()
{
	return Time( ( CountingEnd - CountingStart ) / 1000.f );
}

//-------------------------------------------------------------------------//