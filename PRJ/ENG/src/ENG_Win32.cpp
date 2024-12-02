#include "ENGCommon.h"

#include <windowsx.h>

#include "Engine.h"
#include "ENG_Win32.h"

bool CurrActive = true;

LRESULT CALLBACK WindowProcedure( HWND window, UINT msg, WPARAM wparam, LPARAM lparam )
{
	LRESULT lresult = 0;
	switch ( msg )
	{
#if LEGACY_INPUT
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			if ( wparam == VK_ESCAPE )
			{
				global_engine->running = false;
			}
		} break;
		case WM_MOUSEMOVE:
		{
			Mouse::X = GET_X_LPARAM( lparam );
			Mouse::Y = GET_Y_LPARAM( lparam );
		} break;
#else
		case WM_INPUT:
		{
			
		} break;
#endif // LEGACY_INPUT
		case WM_ACTIVATE:
		case WM_ACTIVATEAPP:
		{
			CurrActive = wparam != 0;
			/*
			if ( CurrActive )
			{
				SetCapture( window );
			}
			else
			{
				ReleaseCapture();
			}
			*/
		} break;
		case WM_DESTROY:
		{
			global_engine->running = false;
		} break;
		default:
		{
			lresult = DefWindowProc( window, msg, wparam, lparam );
		} break;
	}
	return lresult;
}
