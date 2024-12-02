#include "ENGCommon.h"

#include "Engine.h"

int __stdcall WinMain
(
	HINSTANCE hinst,
	HINSTANCE prev_hinst,
	LPSTR     cmd_line,
	int       cmd_show
)
{
	UnusedVariable( prev_hinst );
	UnusedVariable( cmd_line );
	Engine eng;
	global_engine = &eng;
	eng.Init(hinst, cmd_show);
	eng.Run();
	eng.Term();
}