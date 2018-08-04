//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef TIMER_H
#define TIMER_H

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <ctime>
#include <cmath>
using namespace std;

//-------------------------------------------------------------------------//

struct Time
{
	/* КОНСТРУКТОР */
	Time();
	Time( float InSeconds );
	Time( size_t Hours, size_t Minutes, size_t Seconds );

	/* ИНИЦИАЛИЗИРОВАТЬ */
	void Init( float InSeconds );
	void Init( size_t Hours, size_t Minutes, size_t Seconds );

	Time& operator=( const Time& Time );
	Time& operator*( const size_t& Velue );

	size_t		Hours;
	size_t		Minutes;
	size_t		Seconds;

private:
	float		InSeconds;
};

//-------------------------------------------------------------------------//

class Timer
{
public:
	/* НАЧАТЬ ОТСЧЕТ */
	void Start();

	/* ЗАКОНЧИТЬ ОТСЧЕТ */
	void End();

	/* ПОЛУЧИТЬ ПРОМЕЖУТОК ВРЕМЕНИ */
	Time GetTime();

private:
	size_t			CountingStart;
	size_t			CountingEnd;
};

//-------------------------------------------------------------------------//

#endif // !TIMER_H

