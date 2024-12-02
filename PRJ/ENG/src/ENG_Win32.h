#ifndef ENG_WIN32_H
#define ENG_WIN32_H

#define LEGACY_INPUT 1

LRESULT CALLBACK WindowProcedure(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);

extern bool CurrActive;

#endif // ENG_WIN32_H