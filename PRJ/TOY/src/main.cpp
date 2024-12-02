#include "CKAShared/src/Common.h"

#include "Toy.h"

int _stdcall WinMain
(
	HINSTANCE hinst,
	HINSTANCE hprev_inst,
	LPSTR cmd_line,
	int cmd_show
)
{
	UnusedVariable( hprev_inst );
	UnusedVariable( cmd_line );
	TOY toy;
	global_toy = &toy;
	toy.Init( hinst, cmd_show );
	toy.Run();
	toy.Term();
}
