#include "CKAShared/src/Common.h"

#include "TOY_Win32.h"
#include "TOY.h"

const char* TOY::window_name = "PRJ/TOY";

TOY* global_toy = nullptr;

void TOY::Init( HINSTANCE hinst, int cmd_show )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	WNDCLASSEX window_class = {};
	window_class.cbSize = sizeof( WNDCLASSEX );
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = WindowProcedure;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = hinst;
	window_class.hCursor = LoadCursor( nullptr, IDC_ARROW );
	window_class.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	window_class.lpszMenuName = nullptr;
	window_class.lpszClassName = window_name;

	Verify( RegisterClassEx( &window_class ) );

	width = 1280;
	height = 720;

	RECT win_rect = { 0, 0, width, height };

	AdjustWindowRect( &win_rect, WS_OVERLAPPEDWINDOW, FALSE );
	window = CreateWindowEx
	(
		0,
		window_name,
		window_name,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		win_rect.right - win_rect.left,
		win_rect.bottom - win_rect.top,
		nullptr,
		nullptr,
		hinst,
		nullptr
	);

	assert( window );
	ShowWindow( window, cmd_show );

	running = true;
}

void TOY::Run()
{
	while ( running )
	{
		MSG msg = {};
		while ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
}

void TOY::Term()
{

}