#ifndef TOY_H
#define TOY_H

struct TOY
{
	static const char* window_name;

	int width;
	int height;
	bool running;
	int frame_count;

	HWND window;

	void Init( HINSTANCE hinst, int cmd_show );
	void Run();
	void Term();
};

extern TOY* global_toy;

#endif // TOY_H