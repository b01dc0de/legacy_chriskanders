#include "ENGCommon.h"

/* Included by ENGCommon.h */

Clock* Clock::inst = nullptr;

__int64 Clock::T0()
{
	return Inst()->t0;
}

double Clock::CurrTime()
{
	return Inst()->curr_time;
}

float Clock::Delta()
{
	return Inst()->delta;
}

void Clock::Init()
{
	Inst()->PrivInit();
}
void Clock::PrivInit()
{
	LARGE_INTEGER tmp;
	QueryPerformanceFrequency( &tmp );
	freq = tmp.QuadPart;

	QueryPerformanceCounter( &tmp );
	t0 = tmp.QuadPart;

	curr_time = 0.0;
	delta = 0.0;
}

const double MS_60_FPS = 1000.0f / 60.0f;

void Clock::Tick()
{
	Inst()->PrivTick();
}
void Clock::PrivTick()
{
	double last_frame_time = curr_time;

	LARGE_INTEGER tmp;
	QueryPerformanceCounter( &tmp );
	curr_time = ( (double)tmp.QuadPart - (double)t0 ) / (double)freq;

	delta = float( curr_time - last_frame_time );

	if ( delta * 1000.f < MS_60_FPS )
	{
		Sleep( DWORD( MS_60_FPS - delta * 1000.0f ) );
	}
}

void Clock::Term()
{
	delete inst;
	inst = nullptr;
}

Clock* Clock::Inst()
{
	if ( inst == nullptr )
	{
		inst = new Clock;
	}
	return inst;
}
