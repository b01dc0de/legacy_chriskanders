#ifndef BMP_H
#define BMP_H

#include "types.h"

#pragma pack(push, 1)
struct BMPFileHeader
{
    u16 type; // Always Ascii BM
    u32 size_bytes; // Size (bytes) of file
    u16 reserved1; // 0
    u16 reserved2; // 0
    u32 offset_bytes; // Offset (bytes) to actual pixel data
};

struct BMPInfoHeader
{
    u32 struct_size; // Size (bytes) of InfoHeader
    s32 width;
    s32 height; // NOTE(chris): If positive, pixel data is bottom to top
    u16 planes; // Must be 1
    u16 bit_count; // Bits-per-pixel (0, 1, 4, 8, 16, 24, 32)
    u32 compression; // *Should* be 0
    u32 size_image; // Only used if Compression is weird (not 0)
    s32 x_meter; // Horizontal resolution
    s32 y_meter; // Vertical resolution
    u32 colors_used; // 0 for our purposes
    u32 colors_important; // 0 for our purposes
};
#pragma pack(pop)

struct BMP
{
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
};

#endif
