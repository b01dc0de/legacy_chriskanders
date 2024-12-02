#ifndef CKAUTIL_H
#define CKAUTIL_H

#define Verify(exp) assert(SUCCEEDED(exp))
#define ArraySize(arr) (sizeof(arr) / sizeof(arr[0]))
#define SafeRelease(ptr) if (ptr) ptr->Release(); ptr = nullptr
#define UnusedVariable(var) (void)var

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using ullong = unsigned long long;

using f32 = float;
using f64 = double;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;

template <typename T>
struct DXPtr
{
	T* ptr;

	T*& Get() { return ptr; }
	T** operator&() { return &ptr; }
	T*& operator->() { return ptr; }
	operator T*( ) { return ptr; }

	DXPtr( T* in_ptr = nullptr )
		: ptr( in_ptr )
	{
	}
	DXPtr( const DXPtr& ) = delete;
	DXPtr& operator=( const DXPtr& ) = delete;
	~DXPtr()
	{
		SafeRelease( ptr );
	}
};

template <typename T>
T&& CKAMove( T& ref );

void Outf( const char* fmt, ... );
size_t GetStringLength( const char* in_str );

struct Vector;
Vector GetRandomColor();

struct CKAString
{
	static const int DEFAULT_SIZE;

	size_t size;
	size_t len;
	char* str;

	static CKAString Outf( const char* fmt, ... );
	static u64 Hash(CKAString& str);

	bool operator==( const CKAString& other ) const;
	char& operator[]( size_t idx );
	operator char*() { return str; }

	CKAString( const char* in_str = nullptr );
	CKAString( const CKAString& other );
	CKAString& operator=( const CKAString& other );
	CKAString( CKAString&& other );
	CKAString& operator=( CKAString&& other );
	~CKAString();
};

const size_t DYNARR_DEFAULT_SIZE = 32ull;
const float DYNARR_DEFAULT_GROWTH = 1.5f;

template <typename T>
struct DynamicArray
{
	size_t size;
	size_t num;
	T* data;

	void Resize( size_t new_size );

	void Add( T new_item );
	void DeleteAll();
	void ClearAll();
	void RemoveItemLinear( T in_item );
	void RemoveItemFast( T in_item );
	void RemoveAtLinear( size_t in_idx );
	void RemoveAtFast( size_t idx );

	T& operator[]( size_t idx );

	DynamicArray( size_t in_size = DYNARR_DEFAULT_SIZE );
	DynamicArray( const DynamicArray& ) = delete;
	DynamicArray& operator=( const DynamicArray& ) = delete;
	DynamicArray( DynamicArray&& other );
	DynamicArray& operator=( DynamicArray&& other );
	~DynamicArray();
};

template <typename T>
struct Map
{
	struct Pair
	{
		u64 key;
		T val;
	};

	size_t size;
	size_t num;
	DynamicArray<Pair> arr;

	void Add( CKAString new_key, T new_item );
	T& Get( CKAString in_key );
	void Remove( CKAString in_key );

	Map( size_t in_size = DYNARR_DEFAULT_SIZE );
	Map( const Map& ) = delete;
	Map& operator=( const Map& ) = delete;
	Map( Map&& other );
	Map& operator=( Map&& other );
	~Map();
};

#include "CKAUtil.inl"
#include "CKAFile.h"
#include "DynamicArray.inl"
#include "Map.inl"

#endif // CKAUTIL_H