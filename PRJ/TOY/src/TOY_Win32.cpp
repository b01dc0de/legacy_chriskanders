#include "CKAShared/src/Common.h"

#include <windowsx.h>

#include "TOY.h"
#include "TOY_Win32.h"

LRESULT CALLBACK WindowProcedure( HWND window, UINT msg, WPARAM wparam, LPARAM lparam )
{
	LRESULT lresult = 0;
	switch ( msg )
	{
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			if ( wparam == VK_ESCAPE )
			{
				global_toy->running = false;
			}
		} break;
		case WM_MOUSEMOVE:
		{
			Mouse::X = GET_X_LPARAM( lparam );
			Mouse::Y = GET_Y_LPARAM( lparam );
		} break;
		case WM_ACTIVATE:
		case WM_ACTIVATEAPP:
		{
		} break;
		case WM_DESTROY:
		{
			global_toy->running = false;
		} break;
		default:
		{
			lresult = DefWindowProc( window, msg, wparam, lparam );
		} break;
	}
	return lresult;
}
