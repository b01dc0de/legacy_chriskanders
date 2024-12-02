#include "gif.h"

internal void
WriteGIF(char *String, Image32 Image)
{
    GIF gif = {};
    // TODO(chris)
    gif.header.signature[0] = 'G';
    gif.header.signature[1] = 'I';
    gif.header.signature[2] = 'F';
    gif.header.version[0] = '8';
    gif.header.version[1] = '9';
    gif.header.version[2] = 'a';

}
