#include "Common.h"

#include "Mouse.h"

namespace Mouse
{
	int X = 0;
	int Y = 0;
	int PrevX = 0;
	int PrevY = 0;
	int DeltaX = 0;
	int DeltaY = 0;
	bool SetPos = false;

	void Update()
	{
		DeltaX = X - PrevX;
		DeltaY = Y - PrevY;

		PrevX = X;
		PrevY = Y;
	}
}