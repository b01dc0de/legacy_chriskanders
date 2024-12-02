#ifndef CKAMATH_H
#define CKAMATH_H

extern float PI;

struct Vector;
struct Matrix;

float Clamp( float c, float a, float b );
int Clamp( int c, int a, int b );
float ClampToUnit( float c );

float Min( float a, float b );
float Max( float a, float b );
int Min( int a, int b );
int Max( int a, int b );

float Lerp( float a, float b, float t );
Vector Lerp( Vector a, Vector b, float t );

f32 Dot( const Vector& a, const Vector& b );
Vector Cross( const Vector& a, const Vector& b );
f32 Proj( const Vector& a, const Vector& b );
f32 Dist( const Vector& a, const Vector& b );
f32 DistSq( const Vector& a, const Vector& b );

struct Vector
{
	f32 x;
	f32 y;
	f32 z;
	f32 w;

	Vector& Norm();
	Vector GetNorm() const;
	f32 LengthSq() const;
	f32 Length() const;

	Vector operator-() const;

	Vector operator+( const Vector& b ) const;
	Vector operator-( const Vector& b ) const;
	Vector operator*( f32 s ) const;
	Vector operator/( f32 s ) const;
	Vector operator*( const Vector& b ) const;
	Vector operator/( const Vector& b ) const;

	Vector& operator+=( const Vector& b );
	Vector& operator-=( const Vector& b );
	Vector& operator*=( f32 s );
	Vector& operator/=( f32 s );
	Vector& operator*=( const Vector& b );
	Vector& operator/=( const Vector& b );

	Vector( f32 _x = 0.0f, f32 _y = 0.0f, f32 _z = 0.0f, f32 _w = 1.0f )
		: x( _x )
		, y( _y )
		, z( _z )
		, w( _w )
	{}
	Vector( const Vector& ) = default;
	Vector& operator=( const Vector& ) = default;
	~Vector() = default;
};

enum MatrixZero { ZERO };
enum MatrixIdentity { IDENTITY };
enum MatrixTranslate { TRANS };
enum MatrixScale { SCALE };
enum MatrixRotation { ROT_X, ROT_Y, ROT_Z };
enum MatrixRotationAxis { ROT_AXIS };
enum MatrixRotationOrient { ROT_ORIENT };

Matrix Mult( const Matrix& a, const Matrix& b );
Matrix Mult( const Matrix& a, const Matrix& b, const Matrix& c );
Matrix Mult( const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d );
Vector Mult( const Vector& v, const Matrix& m );

Vector operator*( const Vector& v, const Matrix& m );
Vector& operator*=( const Vector& v, const Matrix& m );
Matrix operator*( const Matrix& a, const Matrix& b );
Matrix& operator*=( Matrix& a, const Matrix& b );

struct Matrix
{
	Vector row_0;
	Vector row_1;
	Vector row_2;
	Vector row_3;

	Matrix& Zero();
	Matrix& Identity();

	Matrix& T();
	Matrix GetT() const;

	Matrix& QInv();
	Matrix GetQInv() const;

	Matrix& Trans( f32 x, f32 y, f32 z );
	Matrix& Trans( const Vector& t );
	Matrix& Rot( MatrixRotation rot, float angle );
	Matrix& Rot( MatrixRotationAxis rot, const Vector& axis, float angle );
	Matrix& Rot( MatrixRotationOrient rot, const Vector& dir, const Vector& up = Vector( 0.0f, 1.0f, 0.0f, 0.0f ) );
	Matrix& Scale( f32 s );
	Matrix& Scale( f32 sx, f32 sy, f32 sz );

	Matrix() = default;
	Matrix( MatrixZero zero );
	Matrix( MatrixIdentity identity );
	Matrix( MatrixTranslate trans, float x, float y, float z );
	Matrix( MatrixTranslate trans, const Vector& t );
	Matrix( MatrixRotation rot, float angle );
	Matrix( MatrixRotationAxis rot, const Vector& axis, float angle );
	Matrix( MatrixRotationOrient rot, const Vector& dir, const Vector& up = Vector( 0.0f, 1.0f, 0.0f, 0.0f ) );
	Matrix( MatrixScale scale, float s );
	Matrix( MatrixScale scale, float sx, float sy, float sz );
};

struct CKARand
{
	static s32 WithinRangeInc(s32 Begin, s32 End);
	static u32 WithinRangeInc(u32 Begin, u32 End);
	static float WithinRangeInc(float Begin, float End);

	s32 PrivWithinRangeInc(s32 Begin, s32 End);
	u32 PrivWithinRangeInc(u32 Begin, u32 End);
	float PrivWithinRangeInc(float Begin, float End);

	CKARand();
	~CKARand() = default;
	CKARand(const CKARand&) = delete;
	CKARand& operator=(const CKARand&) = delete;

	std::random_device rand_dev;
	std::mt19937 mersene_twister_engine;
	std::uniform_int_distribution<s32> int_gen;
	std::uniform_int_distribution<u32> uint_gen;
	std::uniform_real_distribution<float> float_gen;

	static bool bInit;
	void Init();
	void Term();

	static CKARand* SInst;
	static CKARand* Inst();
};

using V4 = Vector;
using M4 = Matrix;

#endif // CKAMATH_H