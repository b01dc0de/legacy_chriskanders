#include "Common.h"

#include "Gamepad.h"

namespace Gamepad
{
	XINPUT_STATE states[XUSER_MAX_COUNT] = {};
	bool connected[XUSER_MAX_COUNT] = {};

	short LX, LY, RX, RY;
	byte LEFT_TRIGGER, RIGHT_TRIGGER;
	bool DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT;
	bool START, BACK, LEFT_THUMB, RIGHT_THUMB;
	bool LEFT_SHOULDER, RIGHT_SHOULDER;
	bool A, B, X, Y;

	void CheckConnected()
	{
		for ( int idx = 0; idx < XUSER_MAX_COUNT; idx++ )
		{
			XINPUT_STATE dummy_state;
			connected[idx] = XInputGetState( DWORD( idx ), &dummy_state ) == ERROR_SUCCESS;
		}
	}

	void Update()
	{
		for ( int idx = 0; idx < XUSER_MAX_COUNT; idx++ )
		{
			if ( connected[idx] )
			{
				states[idx] = {};
				XInputGetState( DWORD( idx ), &states[idx] );
			}
		}

		LX = states[0].Gamepad.sThumbLX;
		LY = states[0].Gamepad.sThumbLY;
		RX = states[0].Gamepad.sThumbRX;
		RY = states[0].Gamepad.sThumbRY;
		LEFT_TRIGGER = states[0].Gamepad.bLeftTrigger;
		RIGHT_TRIGGER = states[0].Gamepad.bRightTrigger;
		DPAD_UP = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		DPAD_DOWN = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		DPAD_LEFT = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		DPAD_RIGHT = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		START = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_START;
		BACK = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		LEFT_THUMB = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		RIGHT_THUMB = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		LEFT_SHOULDER = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		RIGHT_SHOULDER = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		A = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_A;
		B = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_B;
		X = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_X;
		Y = states[0].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	}
}