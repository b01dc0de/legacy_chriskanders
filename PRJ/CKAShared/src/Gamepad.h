#ifndef GAMEPAD_H
#define GAMEPAD_H

namespace Gamepad
{
	extern short LX, LY, RX, RY;
	extern byte LEFT_TRIGGER, RIGHT_TRIGGER;
	extern bool DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT;
	extern bool START, BACK, LEFT_THUMB, RIGHT_THUMB;
	extern bool LEFT_SHOULDER, RIGHT_SHOULDER;
	extern bool A, B, X, Y;

	void CheckConnected();
	void Update();
}

#endif // GAMEPAD_H