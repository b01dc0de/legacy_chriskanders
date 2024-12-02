#ifndef CLOCK_H
#define CLOCK_H

struct Clock
{
	__int64 freq;
	__int64 t0;

	float delta;
	double curr_time;

	static Clock* inst;
	static Clock* Inst();

	static __int64 T0();
	static double CurrTime();
	static float Delta();

	static void Init();
	static void Tick();
	static void Term();
	void PrivInit();
	void PrivTick();
};

#endif // CLOCK_H
