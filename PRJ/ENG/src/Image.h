#ifndef IMAGE_H
#define IMAGE_H

struct Texture;

struct Rect
{
	float x;
	float y;
	float width;
	float height;
};

struct Image
{
	Texture* texture;
	Rect rect;

	Image( Texture* in_texture, Rect in_rect = { 0.0f, 0.0f, 1.0f, 1.0f } );
};

#endif // IMAGE_H