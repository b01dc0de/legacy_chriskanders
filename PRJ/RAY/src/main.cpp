#include "CKAShared/src/Common.h"

#include "BMP.h"
#include "Raytracing.h"

int _stdcall WinMain
(
	HINSTANCE hinst,
	HINSTANCE hprev_inst,
	LPSTR cmd_line,
	int cmd_show
)
{
	UnusedVariable( hinst );
	UnusedVariable( hprev_inst );
	UnusedVariable( cmd_line );
	UnusedVariable( cmd_show );

	int width = 200;
	int height = 100;
	int num_samples = 50;
	BMP bmp( (size_t)width, (size_t)height );

	//V4 lower_left_corner( -2.0f, -1.0f, -1.0f );
	//V4 hor( 4.0f, 0.0f, 0.0f );
	//V4 ver( 0.0f, 2.0f, 0.0f );
	//V4 origin( 0.0f, 0.0f, 0.0f );
	V4 look_from( 3.0f, 3.0f, 2.0f );
	V4 look_at( 0.0f, 0.0f, -1.0f );
	float dist_to_focus = ( look_from - look_at ).Length();
	float aperture = 2.0f;
	DynamicArray<HitEntity*> list;
	int i = 0;
	list[(size_t)i++] = new Sphere( V4( 0.0f, -1000.0f, 0 ), 1000, new Lambertian( V4( 0.5f, 0.5f, 0.5f ) ) );
	list[(size_t)i++] = new Sphere( V4( 0.0f, 1.0f, 0.0f ), 1.0f, new Dielectric( 1.5f ) );
	list[(size_t)i++] = new Sphere( V4( -4.0f, 1.0f, 0.0f ), 1.0f, new Lambertian( V4( 0.4f, 0.2f, 0.1f ) ) );
	list[(size_t)i++] = new Sphere( V4( 4.0f, 1.0f, 0.0f ), 1.0f, new Metal( V4( 0.7f, 0.6f, 0.5f ), 0.0f ) );
	for ( int a = -11; a < 11; a++ )
	{
		for ( int b = -11; b < 11; b++ )
		{
			float choose_mat = GetRandomUnit();
			V4 center( a + 0.9f * GetRandomUnit(), 0.2f, b + 0.9f * GetRandomUnit() );
			if ( ( ( center - V4( 4.0f, 0.2f, 0.0f ) ).Length() > 0.9f ) )
			{
				float c = GetRandomUnit();
				float d = GetRandomUnit();
				float e = GetRandomUnit();
				float f = GetRandomUnit();
				float g = GetRandomUnit();
				float h = GetRandomUnit();
				if ( choose_mat < 0.8f ) // diffuse
				{
					list[(size_t)i++] = new Sphere( center, 0.2f, new Lambertian( V4( g * h, c * d, e * f ) ) );
				}
				else if ( choose_mat < 0.95f ) // metal
				{
					list[(size_t)i++] = new Sphere( center, 0.2f, new Metal( V4( 0.5f* ( 1.0f + g ), 0.5f *( 1.0f + h ), 0.5f * ( 1.0f + c ) ), 0.5f * d ) );
				}
				else // glass
				{
					list[(size_t)i++] = new Sphere( center, 0.2f, new Dielectric( 1.5f ) );
				}
			}
		}
	}
	HitList* world = new HitList( list.data, (int)list.num );
	RayCamera cam( look_from, look_at, V4( 0.0f, 1.0f, 0.0f ), 20.0f, float( width ) / float( height ), aperture, dist_to_focus );
	for ( int y = height - 1; y >= 0; y-- )
	{
		for ( int x = 0; x < width; x++ )
		{
			V4 col;
			for ( int s = 0; s < num_samples; s++ )
			{
				float u = float( x + GetRandomUnit() ) / float( width );
				float v = float( y + GetRandomUnit() ) / float( height );
				Ray r = cam.GetRay( u, v );
				col += GetColor( r, world, 0 );
			}
			col /= float( num_samples );
			col = V4( sqrtf( col.x ), sqrtf( col.y ), sqrtf( col.z ) );

			u8 ri = u8( 255.99 * col.x );
			u8 gi = u8( 255.99 * col.y );
			u8 bi = u8( 255.99 * col.z );

			int reverse_y = ( height - 1 ) - y;
			bmp.Get( x, reverse_y ) = { ri, gi, bi };
		}
	}

	bmp.Write( "test.bmp" );
}