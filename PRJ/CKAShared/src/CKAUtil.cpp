#include "Common.h"

/* Included by Common.h */


const uint OutfBufferSize = 1024;
char OutfBuffer[OutfBufferSize];

void Outf( const char* fmt, ... )
{
	va_list args;
	va_start( args, fmt );
	vsprintf_s( OutfBuffer, OutfBufferSize, fmt, args );
	OutputDebugString( OutfBuffer );
	va_end( args );
}

size_t GetStringLength( const char* in_str )
{
	size_t result = 0;

	while ( in_str && *in_str )
	{
		result++;
		in_str++;
	}

	return result;
}

Vector GetRandomColor()
{
	Vector random_color;

	random_color.x = CKARand::WithinRangeInc(0.0f, 1.0f);
	random_color.y = CKARand::WithinRangeInc(0.0f, 1.0f);
	random_color.z = CKARand::WithinRangeInc(0.0f, 1.0f);
	random_color.w = 1.0f;
	return random_color;
}

#include "Common.h"

/* Included by Common.h */

const uint CKAStringOutfBufferSize = 1024;
char CKAStringOutfBuffer[CKAStringOutfBufferSize];

const int CKAString::DEFAULT_SIZE = 32;

CKAString CKAString::Outf( const char* fmt, ... )
{
	int str_len;
	va_list args;
	va_start( args, fmt );
	str_len = vsprintf_s( CKAStringOutfBuffer, CKAStringOutfBufferSize, fmt, args );
	va_end( args );

	assert( str_len != -1 );
	return CKAString( CKAStringOutfBuffer );
}

u64 CKAString::Hash(CKAString& str)
{
	if ( str.len == 0 )
	{
		return 0;
	}

	//https://stackoverflow.com/questions/8317508/hash-function-for-a-string
	// Not a very good implementation (I don't care)
	const u64 A = 54059ull;
	const u64 B = 76963ull;
	const u64 C = 86969ull;
	u64 result = 37ull;
	char* c = str.str;
	while ( *c )
	{
		result = ( result * A ) ^ ( *c * B );
		c++;
	}
	result %= C;
	return result;
}

bool CKAString::operator==( const CKAString& other ) const
{
	if ( len != other.len )
	{
		return false;
	}

	bool equal = true;
	for ( u64 idx = 0; idx < len; idx++ )
	{
		if ( str[idx] != other.str[idx] )
		{
			equal = false;
			break;
		}
	}
	return equal;
}

char& CKAString::operator[]( size_t idx )
{
	assert( idx < len );
	return str[idx];
}

CKAString::CKAString( const char* in_str )
{
	if ( !in_str )
	{
		size = 32;
		len = 0;
		str = new char[size];
		str[len] = '\0';
	}
	else
	{
		size = GetStringLength( in_str ) + 1;
		len = size - 1;
		str = new char[size];
		memcpy_s( str, size, in_str, size );
	}
}

CKAString::CKAString( const CKAString& other )
	: size( other.size )
	, len( other.len )
	, str( new char[size] )
{
	memcpy_s( str, size, other.str, size );
}

CKAString& CKAString::operator=( const CKAString& other )
{
	if ( str )
	{
		delete str;
	}

	size = other.size;
	len = other.len;
	str = new char[size];

	memcpy_s( str, size, other.str, size );

	return *this;
}

CKAString::CKAString( CKAString&& other )
	: size( other.size )
	, len( other.len )
	, str( other.str )
{
	other.size = 0;
	other.len = 0;
	other.str = nullptr;
}

CKAString& CKAString::operator=( CKAString&& other )
{
	if ( str )
	{
		delete str;
	}

	size = other.size;
	len = other.len;
	str = other.str;

	other.size = 0;
	other.len = 0;
	other.str = nullptr;

	return *this;
}

CKAString::~CKAString()
{
	delete[] str;
}

