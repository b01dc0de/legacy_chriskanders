#ifndef NOISE_H
#define NOISE_H

#define DEBUG_BUILD 0
#if DEBUG_BUILD
#define ASSERT(x) {if (!(x)) {*(int *)0 = 0;}}
#else
#define ASSERT(x) {(void)0;}
#endif

#define internal static

#endif
