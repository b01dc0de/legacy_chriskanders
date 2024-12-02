#ifndef GIF_H
#define GIF_H

#include "types.h"

#pragma pack(push, 1)
struct GIF_HDR
{
    u8 signature[3]; // Ascii GIF
    u8 version[3]; // Ascii 89a or 87a
};

struct GIF_LSD
{
    u16 width;
    u16 height;
    /*
      gct_flag: global color table flag
      col_res:
      sort_flag:
      sz_gct: size of global color table
    */
    u8 gct_flag : 1, col_res : 3, sort_flag : 1, sz_gct : 3;
    u8 bg_index;
    u8 aspect_ratio;
};

struct GIF_GCE
{
    u8 ext_intro; // = 0x21
    u8 label; // = 0xF9
    u8 byte_size;
    u8 res : 3, disp_method : 3, input_flag : 1, alpha_flag : 1;
    u16 delay_time;
    u16 alpha_index;
    u8 term; // = 0x00
};

struct GIF_IMG
{
};

#pragma pack(pop)

struct GIF
{
    GIF_HDR header;
    GIF_LSD lsd;
    GIF_GCE gce;
};

#endif
