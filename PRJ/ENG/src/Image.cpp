#include "ENGCommon.h"

#include "Texture.h"
#include "Image.h"

Image::Image( Texture* in_texture, Rect in_rect )
{
	texture = in_texture;
	rect = in_rect;
}
