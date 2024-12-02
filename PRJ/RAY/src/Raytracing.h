#ifndef RAYTRACING_H
#define RAYTRACING_H

struct Ray
{
	V4 A;
	V4 B;

	V4 At( float t ) const
	{
		return A + ( B * t );
	}

	Ray( const V4& in_a = V4(), const V4& in_b = V4() )
		: A( in_a )
		, B( in_b )
	{
	}
};

struct Material;

struct HitRecord
{
	float t;
	V4 p;
	V4 normal;
	Material* mat;
};

struct HitEntity
{
	virtual bool Hit( const Ray& r, float t_min, float t_max, HitRecord& rec ) const = 0;
};

V4 GetColor( const Ray& r, HitEntity* world, int depth );
float GetRandomUnit();
V4 GetRandomUnitSphere();
V4 GetRandomUnitDisk();
V4 Reflect( const V4& v, const V4& n );
bool Refract( const V4& v, const V4& n, float ni_over_nt, V4& refracted );
float Schlick( float cosine, float ref_idx );

struct Sphere : HitEntity
{
	V4 center;
	float radius;
	Material* mat;
	Sphere( V4 cen, float r, Material* in_mat )
		: center( cen )
		, radius( r )
		, mat( in_mat )
	{ }
	virtual bool Hit( const Ray& r, float t_min, float t_max, HitRecord& rec ) const override;
};

struct HitList : HitEntity
{
	HitEntity** list;
	int list_size;

	HitList( HitEntity** in_list, int in_size )
		: list( in_list )
		, list_size( in_size )
	{ }

	virtual bool Hit( const Ray& r, float t_min, float t_max, HitRecord& rec ) const override;
};

struct RayCamera
{
	V4 lower_left;
	V4 hor;
	V4 ver;
	V4 origin;
	V4 u, v, w;
	float lens_radius;

	RayCamera( V4 look_from, V4 look_at, V4 v_up, float v_fov, float aspect_ratio, float aperture, float focus_dist )
	{
		lens_radius = aperture / 2.0f;
		// v_fov: top to bottom in degrees
		float theta = v_fov * PI / 180.0f;
		float half_height = tanf( theta / 2.0f );
		float half_width = aspect_ratio * half_height;
		origin = look_from;
		w = ( look_from - look_at ).GetNorm();
		u = Cross( v_up, w ).GetNorm();
		v = Cross( w, u );
		lower_left = origin - ( u * half_width * focus_dist ) - ( v * half_height * focus_dist ) - w * focus_dist;
		hor = u * 2.0f * half_width * focus_dist;
		ver = v * 2.0f * half_height * focus_dist;

	}
	Ray GetRay( float s, float t )
	{
		V4 rd = GetRandomUnitDisk() * lens_radius;
		V4 offset = u * rd.x + v * rd.y;
		return Ray( origin + offset, lower_left + hor * s + ver * t - origin - offset );
	}
};

struct Material
{
	virtual bool Scatter( const Ray& in_r, const HitRecord& rec, V4& attenuation, Ray& scattered ) const = 0;
};

struct Lambertian : Material
{
	V4 albedo;

	virtual bool Scatter( const Ray& in_r, const HitRecord& rec, V4& attenuation, Ray& scattered ) const
	{
		UnusedVariable( in_r );
		V4 target = rec.p + rec.normal + GetRandomUnitSphere();
		scattered = Ray( rec.p, target - rec.p );
		attenuation = albedo;
		return true;
	}
	Lambertian( const V4& in_albedo )
		: albedo( in_albedo )
	{
	}
};

struct Metal : Material
{
	V4 albedo;
	float fuzz;

	virtual bool Scatter( const Ray& in_r, const HitRecord& rec, V4& attenuation, Ray& scattered ) const
	{
		V4 reflected = Reflect( in_r.B.GetNorm(), rec.normal );
		scattered = Ray( rec.p, reflected + GetRandomUnitSphere() * fuzz );
		attenuation = albedo;
		return Dot( scattered.B, rec.normal ) > 0;
	}
	Metal( const V4& in_albedo, float in_fuzz )
		: albedo( in_albedo )
		, fuzz( in_fuzz < 1.0f ? in_fuzz : 1.0f )
	{
	}
};

struct Dielectric : Material
{
	float ref_idx;

	virtual bool Scatter( const Ray& in_r, const HitRecord& rec, V4& attenuation, Ray& scattered ) const
	{
		V4 outward_normal;
		V4 reflected = Reflect( in_r.B, rec.normal );
		float ni_over_nt;
		attenuation = V4( 1.0f, 1.0f, 1.0f );
		V4 refracted;
		float reflect_prob;
		float cosine;
		if ( Dot( in_r.B, rec.normal ) > 0.0f )
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * Dot( in_r.B, rec.normal ) / in_r.B.Length();
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0f / ref_idx;
			cosine = -Dot( in_r.B, rec.normal ) / in_r.B.Length();
		}

		if ( Refract( in_r.B, outward_normal, ni_over_nt, refracted ) )
		{
			scattered = Ray( rec.p, refracted );
			reflect_prob = Schlick( cosine, ref_idx );
		}
		else
		{
			scattered = Ray( rec.p, reflected );
			reflect_prob = 1.0f;
		}
		if ( GetRandomUnit() < reflect_prob )
		{
			scattered = Ray( rec.p, reflected );
		}
		else
		{
			scattered = Ray( rec.p, refracted );
		}
		return true;
	}
	Dielectric( float in_ref_idx ) : ref_idx( in_ref_idx )
	{
	}
};

#endif // RAYTRACING_H