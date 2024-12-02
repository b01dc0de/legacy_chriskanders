#include "CKAShared/src/Common.h"

DISABLE_WARNING_PUSH()
DISABLE_WARNING( 4365 )
DISABLE_WARNING( 4571 )
DISABLE_WARNING( 4625 )
DISABLE_WARNING( 4626 )
DISABLE_WARNING( 4774 )
DISABLE_WARNING( 5026 )
DISABLE_WARNING( 5027 )
#include <random>
DISABLE_WARNING_POP()

#include "Raytracing.h"

V4 GetColor( const Ray& r, HitEntity* world, int depth )
{
	UnusedVariable( depth );
	HitRecord rec;
	if ( world->Hit( r, 0.001f, FLT_MAX, rec ) )
	{
		Ray scattered;
		V4 attenuation;
		if ( depth < 50.0f && rec.mat->Scatter( r, rec, attenuation, scattered ) )
		{
			return attenuation * GetColor( scattered, world, depth + 1 );
		}
		else
		{
			return V4( 0.0f, 0.0f, 0.0f );
		}
	}
	else
	{
		V4 unit_dir = r.B.GetNorm();
		float t = ( unit_dir.y + 1.0f ) * 0.5f;
		return V4( 1.0f, 1.0f, 1.0f ) * ( 1.0f - t ) + V4( 0.5f, 0.7f, 1.0f ) * t;
	}
}

float GetRandomHalf()
{
	static std::random_device rand_dev;
	static std::uniform_real_distribution<float> random_gen( -0.5f, 1.0f );//-FLT_EPSILON);

	return random_gen( rand_dev );
}

float GetRandomUnit()
{
	static std::random_device rand_dev;
	static std::uniform_real_distribution<float> random_gen( 0.0f, 1.0f );//-FLT_EPSILON);

	return random_gen( rand_dev );
}

V4 GetRandomUnitSphere()
{
	V4 p;
	do
	{
		p = V4( GetRandomUnit(), GetRandomUnit(), GetRandomUnit() ) * 2.0f - V4( 1.0f, 1.0f, 1.0f );
	}
	while ( p.LengthSq() > 1.0f );
	return p;
}

V4 GetRandomUnitDisk()
{
	V4 p;
	do
	{
		p = V4( GetRandomUnit(), GetRandomUnit(), 0.0f ) * 2.0f - V4( 1.0f, 1.0f, 0.0f );
	}
	while ( p.LengthSq() > 1.0f );
	return p;
}

V4 Reflect( const V4& v, const V4& n )
{
	return v - ( n * Dot( v, n ) * 2.0f );
}

bool Refract( const V4& v, const V4& n, float ni_over_nt, V4& refracted )
{
	V4 uv = v.GetNorm();
	float dt = Dot( uv, n );
	float discr = 1.0f - ni_over_nt * ni_over_nt*( 1.0f - dt * dt );
	if ( discr > 0.0f )
	{
		refracted = ( uv - n * dt ) * ni_over_nt - n * sqrt( discr );
		return true;
	}
	else
	{
		return false;
	}
}

float Schlick( float cosine, float ref_idx )
{
	float r0 = ( 1.0f - ref_idx ) / ( 1.0f + ref_idx );
	r0 = r0 * r0;
	return r0 + ( 1.0f - r0 ) * powf( 1.0f - cosine, 5.0f );
}

bool Sphere::Hit( const Ray& r, float t_min, float t_max, HitRecord& rec ) const
{
	V4 oc = r.A - center;
	float a = Dot( r.B, r.B );
	float b = Dot( oc, r.B );
	float c = Dot( oc, oc ) - radius * radius;
	float discriminant = b * b - a * c;
	if ( discriminant > 0 )
	{
		float tmp = ( -b - sqrtf( b*b - a * c ) ) / a;
		if ( tmp < t_max && tmp > t_min )
		{
			rec.t = tmp;
			rec.p = r.At( rec.t );
			rec.normal = ( rec.p - center ) / radius;
			rec.mat = mat;
			return true;
		}
		tmp = ( ( -b ) + sqrtf( b*b - a * c ) ) / a;
		if ( tmp < t_max && tmp > t_min )
		{
			rec.t = tmp;
			rec.p = r.At( rec.t );
			rec.normal = ( rec.p - center ) / radius;
			rec.mat = mat;
			return true;
		}
	}
	return false;
}

bool HitList::Hit( const Ray& r, float t_min, float t_max, HitRecord& rec ) const
{
	HitRecord tmp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for ( int i = 0; i < list_size; i++ )
	{
		if ( list[i]->Hit( r, t_min, closest_so_far, tmp_rec ) )
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	}
	return hit_anything;
}

