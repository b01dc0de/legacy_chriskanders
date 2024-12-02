#ifndef BMP_H
#define BMP_H

ENABLE_PACKING()
struct BMPInfoHeader
{
	u32 struct_size = sizeof( BMPInfoHeader ); // size of info header
	s32 width;
	s32 height; // NOTE: if positive, pixel data is bottom to top
	u16 planes = 1; // 1
	u16 bit_count = 24; // bits per pixel
	u32 compression = 0; // 0
	u32 size_image = 0; // only used when compression != 0
	s32 x_meter = 0; // horizontal res
	s32 y_meter = 0; // vertical res
	u32 colors_used = 0; // 0
	u32 colors_important = 0; // 0
};

struct BMPFileHeader
{
	u16 type = 'M' << 8 | 'B'; // always ascii 'BM'
	u32 size_bytes; // size (in bytes) of file
	u16 reserved1 = 0; // 0
	u16 reserved2 = 0; // 0
	u32 offset_bytes = sizeof( BMPFileHeader ) + sizeof( BMPInfoHeader ); // offset to pixel data
};

struct BMPPixel
{
	u8 b;
	u8 g;
	u8 r;

	BMPPixel( u8 red = 0, u8 green = 0, u8 blue = 0 )
		: b( blue )
		, g( green )
		, r( red )
	{}
};

struct BMP
{
	BMPFileHeader file_hdr;
	BMPInfoHeader info_hdr;
	BMPPixel* pixels;

	size_t width;
	size_t height;
	size_t stride;

	BMPPixel& Get( int in_w, int in_h );
	void Write( const char* filename );

	BMP( size_t in_width, size_t in_height );
};
DISABLE_PACKING()

#endif // BMP_H