#ifndef ENGINE_H
#define ENGINE_H

#include "Game.h"

struct Engine
{
	static const char* window_name;

	int width;
	int height;
	bool running;
	int frame_count;

	HWND window;

	Game game;

	void UpdateCamera();
	void Init(HINSTANCE hinst, int cmd_show);
	void Tick();
	void Run();
	void Term();
};

extern Engine* global_engine;

#endif // ENGINE_H