#ifndef MOUSE_H
#define MOUSE_H

namespace Mouse
{
	extern int X;
	extern int Y;
	extern int PrevX;
	extern int PrevY;
	extern int DeltaX;
	extern int DeltaY;
	extern bool SetPos;

	void Update();
}

#endif // MOUSE_H