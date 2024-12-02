#ifndef IMAGE_H
#define IMAGE_H

#include "types.h"

struct RGBA
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    operator u32()
    {
        return u32((a << 24) | (b << 16) | (g << 8) | (r << 0));
    }
};

struct RGB
{
    u8 r;
    u8 g;
    u8 b;
};

struct Image32
{
    u32 width;
    u32 height;
    u32 pixel_count;
    u32 pixel_bytes;
    RGBA *pixels;
};

struct Image24
{
    u32 width;
    u32 height;
    u32 pixel_count;
    u32 pixel_bytes;
    RGB *pixels;
};

#endif
