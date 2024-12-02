#include "noise.h"

#include "image.cpp"
#include "bmp.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    Image32 image = {};
    image.width = 100;
    image.height = 100;
    image.pixel_count = image.width * image.height;
    image.pixel_bytes = image.pixel_count * sizeof(RGBA);
    image.pixels = (RGBA *)malloc(image.pixel_bytes);
    /*
          NOTE(chris):
              RED       0x00FF0000
              GREEN     0x0000FF00
              BLUE      0x000000FF
    */
    CreateDirectoryA("img", nullptr);
    CreateCircleGradient(image);
    WriteBMP("img/test.bmp", image);

    return(0);
}
