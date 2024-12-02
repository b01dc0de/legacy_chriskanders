#include "CKAShared/src/Common.h"



#include "Sudoku.h"
#define CKA_SUDOKU 1

#include "Digits.h"
#define CKA_DIGITS 0

#define CKA_PROJECT_SELECTED (CKA_SUDOKU || CKA_DIGITS)
#if !CKA_PROJECT_SELECTED
#error "One CKA_PROJECT must be defined"
#endif // !CKA_PROJECT_SELECTED

int __stdcall WinMain(
	HINSTANCE inst,
	HINSTANCE prev_hinst,
	LPSTR     cmd_line,
	int       cmd_show
)
{
	UnusedVariable( inst );
	UnusedVariable( prev_hinst );
	UnusedVariable( cmd_line );
	UnusedVariable( cmd_show );

#if CKA_SUDOKU
	SudokuGrid sudo;
	sudo.Generate();
	sudo.Print();

	sudo.Test();
#endif // CKA_SUDOKU

#if CKA_DIGITS
#endif // CKA_DIGITS

	return 0;
}

