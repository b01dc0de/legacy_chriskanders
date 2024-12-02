#include "Common.h"

#include "Keyboard.h"

static const int CKAKeysToVKCodes[KEY_NUM]
{
	// 0-9 keys
	0x30, // KEY_0
	0x31, // KEY_1
	0x32, // KEY_2
	0x33, // KEY_3
	0x34, // KEY_4
	0x35, // KEY_5
	0x36, // KEY_6
	0x37, // KEY_7
	0x38, // KEY_8
	0x39, // KEY_9

	// a-z keys
	0x41, // KEY_A
	0x42, // KEY_B
	0x43, // KEY_C
	0x44, // KEY_D
	0x45, // KEY_E
	0x46, // KEY_F
	0x47, // KEY_G
	0x48, // KEY_H
	0x49, // KEY_I
	0x4A, // KEY_J
	0x4B, // KEY_K
	0x4C, // KEY_L
	0x4D, // KEY_M
	0x4E, // KEY_N
	0x4F, // KEY_O
	0x50, // KEY_P
	0x51, // KEY_Q
	0x52, // KEY_R
	0x53, // KEY_S
	0x54, // KEY_T
	0x55, // KEY_U
	0x56, // KEY_V
	0x57, // KEY_W
	0x58, // KEY_X
	0x59, // KEY_Y
	0x5A, // KEY_Z

	// function keys
	VK_F1, // KEY_F1
	VK_F2, // KEY_F2
	VK_F3, // KEY_F3
	VK_F4, // KEY_F4
	VK_F5, // KEY_F5
	VK_F6, // KEY_F6
	VK_F7, // KEY_F7
	VK_F8, // KEY_F8
	VK_F9, // KEY_F9
	VK_F10, // KEY_F10
	VK_F11, // KEY_F11
	VK_F12, // KEY_F12

	// various keys
	VK_TAB, // KEY_TAB
	VK_CAPITAL, // KEY_CAPSLOCK
	VK_SHIFT, // KEY_SHIFT
	VK_CONTROL, // KEY_CTRL
	VK_APPS, // KEY_WIN
	VK_MENU, // KEY_ALT
	VK_SPACE, // KEY_SPACE
	VK_RETURN, // KEY_ENTER
	VK_BACK, // KEY_BACKSPACE

	// punctuation keys
	// NOTE: US keyboard layout!
	VK_OEM_3, // KEY_TILDE
	VK_OEM_MINUS, // KEY_MINUS
	VK_OEM_PLUS, // KEY_EQUAL
	VK_OEM_4, // KEY_LEFT_BRACKET
	VK_OEM_6, // KEY_RIGHT_BRACKET
	VK_OEM_5, // KEY_BACKSLASH
	VK_OEM_1, // KEY_SEMICOLON
	VK_OEM_7, // KEY_QUOTE
	VK_OEM_COMMA, // KEY_COMMA
	VK_OEM_PERIOD, // KEY_PERIOD
	VK_OEM_2, // KEY_SLASH

	// "home" keys
	VK_PRIOR, // KEY_PAGEUP
	VK_NEXT, // KEY_PAGEDOWN
	VK_END, // KEY_END
	VK_HOME, // KEY_HOME
	VK_DELETE, // KEY_DEL
	VK_INSERT, // KEY_INS

	// arrow keys
	VK_LEFT, // KEY_LEFT
	VK_UP, // KEY_UP
	VK_RIGHT, // KEY_RIGHT
	VK_DOWN, // KEY_DOWN

	// numpad keys
	VK_NUMPAD0, // KEY_NUMPAD0
	VK_NUMPAD1, // KEY_NUMPAD1
	VK_NUMPAD2, // KEY_NUMPAD2
	VK_NUMPAD3, // KEY_NUMPAD3
	VK_NUMPAD4, // KEY_NUMPAD4
	VK_NUMPAD5, // KEY_NUMPAD5
	VK_NUMPAD6, // KEY_NUMPAD6
	VK_NUMPAD7, // KEY_NUMPAD7
	VK_NUMPAD8, // KEY_NUMPAD8
	VK_NUMPAD9, // KEY_NUMPAD9

	// numpad other keys
	VK_DECIMAL, // KEY_NUMPAD_PERIOD
	VK_RETURN, // KEY_NUMPAD_ENTER
	VK_ADD, // KEY_NUMPAD_PLUS
	VK_SUBTRACT, // KEY_NUMPAD_MINUS
	VK_MULTIPLY, // KEY_NUMPAD_MULT
	VK_DIVIDE, // KEY_NUMPAD_DIV
	VK_NUMLOCK, // KEY_NUMLOCK

	// size of enum
	// KEY_NUM
};

namespace Keyboard
{

	bool GetKeyState( CKAKey key )
	{
		const int is_down_mask = 0x8000;
		if ( key < 0 || key >= KEY_NUM )
		{
			Outf( "Error(GFXPKG): Attempted to get state of invalid GFXPKG_KEY: 0x%x\n", key );
			return 0;
		}
		return ::GetKeyState( CKAKeysToVKCodes[key] ) & is_down_mask;
	}

}
