#include "ENGCommon.h"

#include "PrefabMesh.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ImageManager.h"
#include "GFXEntity.h"
#include "ENG_Win32.h"
#include "Engine.h"

const char* Engine::window_name = "PRJ/ENG";

Engine* global_engine = nullptr;

void Engine::UpdateCamera()
{
	// Toggle between the different CameraControls
	// We want individual presses of G (not holding it down)
	static bool last_frame_pressed = 0;
	bool curr_frame_pressed = Keyboard::GetKeyState( KEY_G );
	if ( curr_frame_pressed && !last_frame_pressed )
	{
		curr_cam = CameraType( ( curr_cam + 1 ) % CameraType_MAX );
		last_frame_pressed = true;
	}
	else if ( !curr_frame_pressed && last_frame_pressed )
	{
		last_frame_pressed = false;
	}

	cam_ctrls[curr_cam]->ProcessInput();
}

void Engine::Init( HINSTANCE hinst, int cmd_show )
{
	// CKA_TODO: In the future, look into if this can be removed (make sure rand() isn't used _ANYWHERE_)
	srand( (unsigned int)time( nullptr ) );

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

	GFXManager::Init( window, width, height );
	PrefabMesh::Init();
	ShaderManager::Init();

	cam_ctrls[CameraType_God] = new GodCamera( width, height, Vector( 0.0f, 0.0f, 0.0f, 0.0f ), Vector( 10.0f, 15.0f, -10.0f ) );
	cam_ctrls[CameraType_FirstPerson] = new FirstPersonCamera( width, height, Vector( 0.0f, 0.0f, 26.0f ), Vector( 0.0f, 0.0f, 25.0f ) );
	cam_ctrls[CameraType_Mouse] = new MouseCamera( width, height, Vector( 0.0f, 0.0f, 0.0f, 0.0f ), Vector( 10.0f, 15.0f, -10.0f ) );
	cam_ctrls[CameraType_UI] = new UICamera( (float)width, (float)height, 1.0f );

	game.Init();

	frame_count = 0;
	Clock::Init();
}

void Engine::Tick()
{
	MSG msg = {};
	while ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	{ // Update
		Clock::Tick();

		if ( CurrActive )
		{
			Mouse::Update();
			if ( frame_count % 2000 == 0 )
			{
				Gamepad::CheckConnected();
			}
			Gamepad::Update();

			UpdateCamera();
		}

		if ( frame_count++ % 4 == 0 )
		{
			SetWindowText( window, CKAString::Outf( "%s: Frame: %d, Time: %.02f, FPS: %.02f", window_name, frame_count, Clock::CurrTime(), frame_count / Clock::CurrTime() ) );
		}
	}

	game.Tick();
}

void Engine::Run()
{
	running = true;

	while ( running )
	{
		Tick();
	}
}

void Engine::Term()
{
	game.Term();

	TextureManager::Term();
	ImageManager::Term();

	Clock::Term();

	GFXManager::Term();
	PrefabMesh::Term();
	ShaderManager::Term();

	for ( uint idx = 0; idx < CameraType_MAX; idx++ )
	{
		delete cam_ctrls[idx];
	}
}