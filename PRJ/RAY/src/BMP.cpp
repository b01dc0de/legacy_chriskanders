#include "CKAShared/src/Common.h"

#include "BMP.h"

BMPPixel& BMP::Get( int in_w, int in_h )
{
	assert( in_w >= 0 && (size_t)in_w < width );
	assert( in_h >= 0 && (size_t)in_h < height );
	return ( BMPPixel& )*( (u8*)pixels + ( stride * in_h ) + ( sizeof( BMPPixel ) * in_w ) );
}

void BMP::Write( const char* filename )
{
	FILE* bmp_file = nullptr;
	fopen_s( &bmp_file, filename, "w+b" );
	assert( bmp_file );

	fwrite( &file_hdr, file_hdr.offset_bytes, 1, bmp_file );
	fwrite( pixels, file_hdr.size_bytes - file_hdr.offset_bytes, 1, bmp_file );
}

BMP::BMP( size_t in_width, size_t in_height )
{
	width = in_width;
	height = in_height;
	stride = sizeof( BMPPixel ) * width % 4 == 0
		? sizeof( BMPPixel ) * width
		: sizeof( BMPPixel ) * width + ( 4 - ( sizeof( BMPPixel ) * width % 4 ) ); // extra padding to make 4-byte aligned stride

	info_hdr.width = (s32)width;
	info_hdr.height = -(s32)height;
	file_hdr.size_bytes = u32( file_hdr.offset_bytes + stride * height );

	pixels = new BMPPixel[width * height];
}
