#include "bmp.h"
#include "image.h"

#include <stdio.h>

internal void
WriteBMP(char *file_name, Image32 image)
{
    u32 pixels_bytes = sizeof(u32)*image.pixel_count;

    BMP bmp = {};

    bmp.file_header.type = 0x4D42;
    bmp.file_header.size_bytes = sizeof(bmp) + pixels_bytes;
    //bmp.file_header.reserved1 = 0;
    //bmp.file_header.reserved2 = 0;
    bmp.file_header.offset_bytes = sizeof(bmp);

    bmp.info_header.struct_size = sizeof(bmp) - 14;
    bmp.info_header.width = (s32)image.width;
    bmp.info_header.height = -(s32)image.height;
    bmp.info_header.planes = 1;
    bmp.info_header.bit_count = 32;
    bmp.info_header.compression = 0;
    bmp.info_header.size_image = pixels_bytes;
    //bmp.info_header.x_meter = 0;
    //bmp.info_header.y_meter = 0;
    //bmp.info_header.colors_used = 0;
    //bmp.info_header.colors_important = 0;


    FILE *bmp_file= nullptr;
    fopen_s(&bmp_file, file_name, "wb");
    if (bmp_file != nullptr)
    {
        fwrite(&bmp.file_header, sizeof(bmp.file_header), 1, bmp_file);
        fwrite(&bmp.info_header, sizeof(bmp.info_header), 1, bmp_file);
        fwrite(image.pixels, image.pixel_bytes, 1, bmp_file);
        fclose(bmp_file);
    } else
    {
        printf("ERROR: Cannot open file \"%s\"\n", file_name);
    }
}
