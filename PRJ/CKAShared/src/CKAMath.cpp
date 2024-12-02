#include "Common.h"

/* Included by Common.h */

float PI = 3.14159265359f;

float Clamp( float c, float a, float b )
{
	assert( a <= b );
	if ( c < a )
	{
		c = a;
	}
	else if ( c > b )
	{
		c = b;
	}
	return c;
}

int Clamp( int c, int a, int b )
{
	assert( a <= b );
	if ( c < a )
	{
		c = a;
	}
	else if ( c > b )
	{
		c = b;
	}
	return c;
}

float ClampToUnit( float c )
{
	if ( c < 0.0f )
	{
		c = 0.0f;
	}
	else if ( c > 1.0f )
	{
		c = 1.0f;
	}
	return c;
}

float Min( float a, float b )
{
	return a < b ? a : b;
}

float Max( float a, float b )
{
	return a > b ? a : b;
}

int Min( int a, int b )
{
	return a < b ? a : b;
}

int Max( int a, int b )
{
	return a > b ? a : b;
}

float Lerp( float a, float b, float t )
{
	return a + ( b - a ) * t;
}

Vector Lerp( Vector a, Vector b, float t )
{
	return a + ( b - a ) * t;
}

f32 Dot( const Vector& a, const Vector& b )
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector Cross( const Vector& a, const Vector& b )
{
	Vector result;

	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - b.x*a.y;
	result.w = 0.0f;

	return result;
}

f32 Proj( const Vector& a, const Vector& b )
{
	return Dot( a, b.GetNorm() );
}

f32 Dist( const Vector& a, const Vector& b )
{
	return sqrtf( DistSq( a, b ) );
}

f32 DistSq( const Vector& a, const Vector& b )
{
	float diff_x = b.x - a.x;
	float diff_y = b.y - a.y;
	float diff_z = b.z - a.z;

	return diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;
}

Vector& Vector::Norm()
{
	f32 len = Length();
	assert( len != 0.0f );
	x = x / len;
	y = y / len;
	z = z / len;
	return *this;
}

Vector Vector::GetNorm() const
{
	Vector result = *this;
	return result.Norm();
}

f32 Vector::LengthSq() const
{
	return x * x + y * y + z * z;
}

f32 Vector::Length() const
{
	return sqrtf( LengthSq() );
}

Vector Vector::operator-() const
{
	Vector result;
	result.x = -x;
	result.y = -y;
	result.z = -z;
	return result;
}

Vector Vector::operator+( const Vector& b ) const
{
	Vector result;
	result.x = x + b.x;
	result.y = y + b.y;
	result.z = z + b.z;
	result.w = w;
	return result;
}

Vector Vector::operator-( const Vector& b ) const
{
	Vector result;
	result.x = x - b.x;
	result.y = y - b.y;
	result.z = z - b.z;
	return result;
}

Vector Vector::operator*( f32 s ) const
{
	Vector result;
	result.x = x * s;
	result.y = y * s;
	result.z = z * s;
	return result;
}

Vector Vector::operator/( f32 s ) const
{
	Vector result;
	result.x = x / s;
	result.y = y / s;
	result.z = z / s;
	return result;
}

Vector Vector::operator*( const Vector& b ) const
{
	Vector result;
	result.x = x * b.x;
	result.y = y * b.y;
	result.z = z * b.z;
	return result;
}

Vector Vector::operator/( const Vector& b ) const
{
	Vector result;
	result.x = x / b.x;
	result.y = y / b.y;
	result.z = z / b.z;
	return result;
}

Vector& Vector::operator+=( const Vector& b )
{
	*this = operator+( b );
	return *this;
}

Vector& Vector::operator-=( const Vector& b )
{
	*this = operator-( b );
	return *this;
}

Vector& Vector::operator*=( f32 s )
{
	*this = operator*( s );
	return *this;
}

Vector& Vector::operator/=( f32 s )
{
	*this = operator/( s );
	return *this;
}

Vector& Vector::operator*=( const Vector& b )
{
	*this = operator*( b );
	return *this;
}

Vector& Vector::operator/=( const Vector& b )
{
	*this = operator/( b );
	return *this;
}

Matrix Mult( const Matrix &a, const Matrix &b )
{
	Matrix result;

	result.row_0.x = ( a.row_0.x * b.row_0.x ) + ( a.row_0.y * b.row_1.x ) + ( a.row_0.z * b.row_2.x ) + ( a.row_0.w * b.row_3.x );
	result.row_0.y = ( a.row_0.x * b.row_0.y ) + ( a.row_0.y * b.row_1.y ) + ( a.row_0.z * b.row_2.y ) + ( a.row_0.w * b.row_3.y );
	result.row_0.z = ( a.row_0.x * b.row_0.z ) + ( a.row_0.y * b.row_1.z ) + ( a.row_0.z * b.row_2.z ) + ( a.row_0.w * b.row_3.z );
	result.row_0.w = ( a.row_0.x * b.row_0.w ) + ( a.row_0.y * b.row_1.w ) + ( a.row_0.z * b.row_2.w ) + ( a.row_0.w * b.row_3.w );

	result.row_1.x = ( a.row_1.x * b.row_0.x ) + ( a.row_1.y * b.row_1.x ) + ( a.row_1.z * b.row_2.x ) + ( a.row_1.w * b.row_3.x );
	result.row_1.y = ( a.row_1.x * b.row_0.y ) + ( a.row_1.y * b.row_1.y ) + ( a.row_1.z * b.row_2.y ) + ( a.row_1.w * b.row_3.y );
	result.row_1.z = ( a.row_1.x * b.row_0.z ) + ( a.row_1.y * b.row_1.z ) + ( a.row_1.z * b.row_2.z ) + ( a.row_1.w * b.row_3.z );
	result.row_1.w = ( a.row_1.x * b.row_0.w ) + ( a.row_1.y * b.row_1.w ) + ( a.row_1.z * b.row_2.w ) + ( a.row_1.w * b.row_3.w );

	result.row_2.x = ( a.row_2.x * b.row_0.x ) + ( a.row_2.y * b.row_1.x ) + ( a.row_2.z * b.row_2.x ) + ( a.row_2.w * b.row_3.x );
	result.row_2.y = ( a.row_2.x * b.row_0.y ) + ( a.row_2.y * b.row_1.y ) + ( a.row_2.z * b.row_2.y ) + ( a.row_2.w * b.row_3.y );
	result.row_2.z = ( a.row_2.x * b.row_0.z ) + ( a.row_2.y * b.row_1.z ) + ( a.row_2.z * b.row_2.z ) + ( a.row_2.w * b.row_3.z );
	result.row_2.w = ( a.row_2.x * b.row_0.w ) + ( a.row_2.y * b.row_1.w ) + ( a.row_2.z * b.row_2.w ) + ( a.row_2.w * b.row_3.w );

	result.row_3.x = ( a.row_3.x * b.row_0.x ) + ( a.row_3.y * b.row_1.x ) + ( a.row_3.z * b.row_2.x ) + ( a.row_3.w * b.row_3.x );
	result.row_3.y = ( a.row_3.x * b.row_0.y ) + ( a.row_3.y * b.row_1.y ) + ( a.row_3.z * b.row_2.y ) + ( a.row_3.w * b.row_3.y );
	result.row_3.z = ( a.row_3.x * b.row_0.z ) + ( a.row_3.y * b.row_1.z ) + ( a.row_3.z * b.row_2.z ) + ( a.row_3.w * b.row_3.z );
	result.row_3.w = ( a.row_3.x * b.row_0.w ) + ( a.row_3.y * b.row_1.w ) + ( a.row_3.z * b.row_2.w ) + ( a.row_3.w * b.row_3.w );

	return result;
}
Matrix Mult( const Matrix& a, const Matrix& b, const Matrix& c )
{
	return Mult( Mult( a, b ), c );
}
Matrix Mult( const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d )
{
	return Mult( Mult( Mult( a, b ), c ), d );
}
Vector Mult( const Vector& v, const Matrix& m )
{
	Vector result;

	// row major
	result.x = v.x*m.row_0.x + v.y*m.row_1.x + v.z * m.row_2.x + v.w*m.row_3.x;
	result.y = v.x*m.row_0.y + v.y*m.row_1.y + v.z * m.row_2.y + v.w*m.row_3.y;
	result.z = v.x*m.row_0.z + v.y*m.row_1.z + v.z * m.row_2.z + v.w*m.row_3.z;
	result.w = v.x*m.row_0.w + v.y*m.row_1.w + v.z * m.row_2.w + v.w*m.row_3.w;

	/*
	// column major
	result.x = m.row_0.x*v.x + m.row_0.y*v.y + m.row_0.z*v.z + m.row_0.w*v.w;
	result.y = m.row_1.x*v.x + m.row_1.y*v.y + m.row_1.z*v.z + m.row_1.w*v.w;
	result.z = m.row_2.x*v.x + m.row_2.y*v.y + m.row_2.z*v.z + m.row_2.w*v.w;
	result.w = m.row_3.x*v.x + m.row_3.y*v.y + m.row_3.z*v.z + m.row_3.w*v.w;
	*/

	return result;
}

Vector operator*( const Vector& v, const Matrix& m )
{
	return Mult( v, m );
}
Vector& operator*=( Vector& v, const Matrix& m )
{
	return v = Mult( v, m );
}
Matrix operator*( const Matrix& a, const Matrix& b )
{
	return Mult( a, b );
}
Matrix& operator*=( Matrix& a, const Matrix& b )
{
	return a = Mult( a, b );
}

Matrix& Matrix::Zero()
{
	row_0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	row_1 = { 0.0f, 0.0f, 0.0f, 0.0f };
	row_2 = { 0.0f, 0.0f, 0.0f, 0.0f };
	row_3 = { 0.0f, 0.0f, 0.0f, 0.0f };
	return *this;
}
Matrix& Matrix::Identity()
{
	row_0 = { 1.0f, 0.0f, 0.0f, 0.0f };
	row_1 = { 0.0f, 1.0f, 0.0f, 0.0f };
	row_2 = { 0.0f, 0.0f, 1.0f, 0.0f };
	row_3 = { 0.0f, 0.0f, 0.0f, 1.0f };
	return *this;
}

Matrix& Matrix::T()
{
	float tmp;

	// _1 <-> _4
	tmp = row_0.y;
	row_0.y = row_1.x;
	row_1.x = tmp;

	// _2 <-> _8
	tmp = row_0.z;
	row_0.z = row_2.x;
	row_2.x = tmp;

	// _3 <-> _c
	tmp = row_0.w;
	row_0.w = row_3.x;
	row_3.x = tmp;

	// _6 <-> _9
	tmp = row_1.z;
	row_1.z = row_2.y;
	row_2.y = tmp;

	// _7 <-> _d
	tmp = row_1.w;
	row_1.w = row_3.y;
	row_3.y = tmp;

	// _b <-> e
	tmp = row_2.w;
	row_2.w = row_3.z;
	row_3.z = tmp;

	return *this;
}
Matrix Matrix::GetT() const
{
	Matrix result = *this;
	return result.T();
}

Matrix& Matrix::QInv()
{
	float tmp;

	// _1 <-> _4
	tmp = row_0.y;
	row_0.y = row_1.x;
	row_1.x = tmp;

	// _2 <-> _8
	tmp = row_0.z;
	row_0.z = row_2.x;
	row_2.x = tmp;

	// _6 <-> _9
	tmp = row_1.z;
	row_1.z = row_2.y;
	row_2.y = tmp;

	// "negative-ing" the pos
	row_3.x = -row_3.x;
	row_3.y = -row_3.y;
	row_3.z = -row_3.z;

	return *this;
}
Matrix Matrix::GetQInv() const
{
	Matrix result = *this;
	return result.T();
}

Matrix& Matrix::Trans( f32 x, f32 y, f32 z )
{
	row_0 = { 1.0f, 0.0f, 0.0f, 0.0f };
	row_1 = { 0.0f, 1.0f, 0.0f, 0.0f };
	row_2 = { 0.0f, 0.0f, 1.0f, 0.0f };
	row_3 = { x,    y,    z, 1.0f };
	return *this;
}
Matrix& Matrix::Trans( const Vector& t )
{
	row_0 = { 1.0f, 0.0f, 0.0f, 0.0f };
	row_1 = { 0.0f, 1.0f, 0.0f, 0.0f };
	row_2 = { 0.0f, 0.0f, 1.0f, 0.0f };
	row_3 = { t.x,  t.y,  t.z, 1.0f };
	return *this;
}
Matrix& Matrix::Rot( MatrixRotation rot, float angle )
{
	Identity();
	float c = cosf( angle );
	float s = sinf( angle );
	switch ( rot )
	{
		case ROT_X:
		{
			row_0 = { 1.0f, 0.0f, 0.0f, 0.0f };
			row_1 = { 0.0f,    c,   -s, 0.0f };
			row_2 = { 0.0f,    s,    c, 0.0f };
		} break;
		case ROT_Y:
		{
			row_0 = { c, 0.0f,    s, 0.0f };
			row_1 = { 0.0f, 1.0f, 0.0f, 0.0f };
			row_2 = { -s, 0.0f,    c, 0.0f };
		} break;
		case ROT_Z:
		{
			row_0 = { c,   -s, 0.0f, 0.0f };
			row_1 = { s,    c, 0.0f, 0.0f };
			row_2 = { 0.0f, 0.0f, 1.0f, 0.0f };
		} break;
		default:
		{
			assert( false );
		} break;
	}
	return *this;

}
Matrix& Matrix::Rot( MatrixRotationAxis rot, const Vector& axis, float angle )
{
	UnusedVariable( rot );

	/*
	float c = cosf(angle);
	float s = sinf(angle);
	float c_opp = 1.0f - c;
	Vector axis_norm = axis.GetNorm();

	Vector  right( 1.0f, 0.0f, 0.0f, 0.0f );
	Vector up( 0.0f, 1.0f, 0.0f, 0.0f );
	Vector forward( 0.0f, 0.0f, 1.0f, 0.0f );

	row_0 = (right * c) + (Cross(axis_norm, right) * s) + (axis_norm * c_opp);
	row_1 = (up * c) + (Cross(axis_norm, up) * s) + (axis_norm * c_opp);
	row_2 = (forward * c) + (Cross(axis_norm, forward) * s) + (axis_norm * c_opp);
	row_3 = { 0.0f, 0.0f, 0.0f, 1.0f };

	if ((row_0.y > 0.0f ? row_0.y : -row_0.y) > 0.0f)
	{
		int i = 0;
		Outf("%d\n", i);
	}

	//static int i = 0;
	*/


	Vector k = axis.GetNorm();

	float C = cosf( angle );
	float S = sinf( angle );
	float C_inv = 1.0f - C;

	float k_xx = k.x * k.x;
	float k_yy = k.y * k.y;
	float k_zz = k.z * k.z;

	float k_xy = k.x * k.y;
	float k_yz = k.y * k.z;
	float k_xz = k.x * k.z;

	float S_x = S * k.x;
	float S_y = S * k.y;
	float S_z = S * k.z;

	row_0 = { C + k_xx * C_inv, +S_z + k_xy * C_inv, -S_y + k_xz * C_inv, 0.0f };
	row_1 = { -S_z + k_xy * C_inv, C + k_yy * C_inv, +S_x + k_yz * C_inv, 0.0f };
	row_2 = { +S_y + k_xz * C_inv, -S_x + k_yz * C_inv, C + k_zz * C_inv, 0.0f };
	row_3 = { 0.0f, 0.0f, 0.0f, 1.0f };

	/*
	Identity();
	V4 k = axis.GetNorm();

	float x = k.x;
	float y = k.y;
	float z = k.z;

	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - c;

	row_0.x = (t*x*x) + c;
	row_0.y = (t*x*y) - (s*z);
	row_0.z = (t*x*z) + (s*y);

	row_1.x = (t*x*y) + (s*z);
	row_1.y = (t*y*y) + c;
	row_1.z = (t*y*z) - (s*x);

	row_2.x = (t*x*z) - (s*y);
	row_2.y = (t*y*z) + (s*x);
	row_2.z = (t*z*z) + c;
	*/

	return *this;
}
Matrix& Matrix::Rot( MatrixRotationOrient rot, const Vector& dir, const Vector& up )
{
	UnusedVariable( rot );
	row_2 = dir.GetNorm();
	row_0 = Cross( up, row_2 ).GetNorm();
	row_1 = Cross( row_2, row_0 ).GetNorm();
	row_3 = { 0.0f, 0.0f, 0.0f, 1.0f };
	return *this;
}
Matrix& Matrix::Scale( f32 s )
{
	Identity();
	row_0.x = s;
	row_1.y = s;
	row_2.z = s;
	return *this;
}
Matrix& Matrix::Scale( f32 sx, f32 sy, f32 sz )
{
	Identity();
	row_0.x = sx;
	row_1.y = sy;
	row_2.z = sz;
	return *this;
}

Matrix::Matrix( MatrixZero zero )
{
	UnusedVariable( zero );
	Zero();
}
Matrix::Matrix( MatrixIdentity identity )
{
	UnusedVariable( identity );
	Identity();
}
Matrix::Matrix( MatrixTranslate trans, float x, float y, float z )
{
	UnusedVariable( trans );
	Trans( x, y, z );
}
Matrix::Matrix( MatrixTranslate trans, const Vector& t )
{
	UnusedVariable( trans );
	Trans( t );
}
Matrix::Matrix( MatrixRotation rot, float angle )
{
	Rot( rot, angle );
}
Matrix::Matrix( MatrixRotationAxis rot, const Vector& axis, float angle )
{
	Rot( rot, axis, angle );
}
Matrix::Matrix( MatrixRotationOrient rot, const Vector& dir, const Vector& up )
{
	Rot( rot, dir, up );
}
Matrix::Matrix( MatrixScale scale, float s )
{
	UnusedVariable( scale );
	Scale( s );
}
Matrix::Matrix( MatrixScale scale, float sx, float sy, float sz )
{
	UnusedVariable( scale );
	Scale( sx, sy, sz );
}

#if 1 // CKA_COMPILE_OFF

CKARand::CKARand()
	: rand_dev()
	, mersene_twister_engine(rand_dev())
{
}

s32 CKARand::WithinRangeInc(s32 Begin, s32 End)
{
	return Inst()->PrivWithinRangeInc(Begin, End);
}
s32 CKARand::PrivWithinRangeInc(s32 Begin, s32 End)
{
	using GenParamType = std::uniform_int_distribution<s32>::param_type;
	int_gen.param(GenParamType(Begin, End));
	return int_gen(mersene_twister_engine);
}

u32 CKARand::WithinRangeInc(u32 Begin, u32 End)
{
	return Inst()->PrivWithinRangeInc(Begin, End);
}
u32 CKARand::PrivWithinRangeInc(u32 Begin, u32 End)
{
	using GenParamType = std::uniform_int_distribution<u32>::param_type;
	uint_gen.param(GenParamType(Begin, End));
	return uint_gen(mersene_twister_engine);
}

float CKARand::WithinRangeInc(float Begin, float End)
{
	return Inst()->PrivWithinRangeInc(Begin, End);
}
float CKARand::PrivWithinRangeInc(float Begin, float End)
{
	using GenParamType = std::uniform_real_distribution<float>::param_type;
	float_gen.param(GenParamType(Begin, End));
	return float_gen(mersene_twister_engine);
}

void CKARand::Init()
{
	assert(SInst == nullptr);
	(void)Inst();
}

void CKARand::Term()
{
	assert(SInst != nullptr);
	delete SInst;
	SInst = nullptr;
}

CKARand* CKARand::SInst = nullptr;

CKARand* CKARand::Inst()
{
	if (SInst == nullptr)
	{
		SInst = new CKARand();
	}

	return SInst;
}

#endif // CKA_COMPILE_OFF
