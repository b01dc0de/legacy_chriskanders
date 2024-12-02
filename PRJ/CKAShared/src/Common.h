#ifndef COMMON_H
#define COMMON_H

#define DISABLE_WARNING_PUSH() __pragma( warning( push ) )
#define DISABLE_WARNING_POP() __pragma( warning( pop ) )
#define DISABLE_WARNING( warn_no ) __pragma( warning( disable : warn_no ) )
#define ENABLE_PACKING() __pragma( pack(push, 1) )
#define DISABLE_PACKING() __pragma( pack(pop) )

#define CKA_COMPILE_ON 1
#define CKA_COMPILE_OFF 0

DISABLE_WARNING_PUSH()
DISABLE_WARNING( 4061 )
DISABLE_WARNING( 4365 )
DISABLE_WARNING( 4514 )
DISABLE_WARNING( 4820 )
DISABLE_WARNING( 5039 )
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// MSVC+DX files
#include <Windows.h>
#ifndef USE_D3D12
#define USE_D3D12 0
#endif
#if USE_D3D12
#include <d3d12.h>
#else
#include <d3d11.h>
#endif
#include <d3dcompiler.h>
#include <hidusage.h>
#include <xinput.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif
// C++ standard library
DISABLE_WARNING( 4571 )
DISABLE_WARNING( 5026 )
DISABLE_WARNING( 5027 )
DISABLE_WARNING( 4774 )
DISABLE_WARNING( 4625 )
DISABLE_WARNING( 4626 )
#include <random>
// C standard library
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
DISABLE_WARNING_POP()

#pragma region CKA_DEFINES
#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])
#ifdef _DEBUG
	// CKA_TODO: Replace all existing calls of assert with CKA_ASSERT
	//			 Gives me more control
	#define CKA_ASSERT(exp) \
		if (!(exp)) \
		{ \
			__debugbreak(); \
		}
#else
	#define CKA_ASSERT(exp) ((void)0)
#endif // _DEBUG
#pragma endregion

#include "CKAUtil.h"
#include "CKAMath.h"
#include "CKAGFX.h"
#include "CKAInput.h"

#endif // COMMON_H