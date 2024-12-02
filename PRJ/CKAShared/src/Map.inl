#ifndef MAP_INL
#define MAP_INL

template <typename T>
void Map<T>::Add( CKAString new_key, T new_item )
{
	assert( num < size );
	assert( *new_key.str != '\0' );
	u64 hash = CKAString::Hash( new_key );
	for ( u64 i = 0; i < size; i++ )
	{
		u64 idx = ( hash + i ) % size;
		assert( arr[idx].key != hash );
		if ( arr[idx].key == 0 )
		{
			arr[idx].key = hash;
			arr[idx].val = new_item;
			break;
		}
	}
	num++;
}

template <typename T>
T& Map<T>::Get( CKAString in_key )
{
	assert( *in_key.str != '\0' );
	u64 hash = CKAString::Hash( in_key );
	u64 result_idx = 0;
	bool found = false;

	for ( u64 i = 0; i < size; i++ )
	{
		u64 idx = ( hash + i ) % size;
		if ( arr[idx].key == hash )
		{
			result_idx = idx;
			found = true;
			break;
		}
		else if ( arr[idx].key == 0 )
		{
			break;
		}
	}

	assert( found );
	return arr[result_idx].val;
}

template <typename T>
void Map<T>::Remove( CKAString in_key )
{
	assert( *in_key.str != '\0' );
	u64 hash = CKAString::Hash( in_key );
	bool found = false;
	for ( u64 i = 0; i < size; i++ )
	{
		u64 idx = ( hash + i ) % size;
		if ( arr[idx].key == hash )
		{
			arr[idx].key = 0;
			found = true;
			break;
		}
	}
	assert( found );
	num--;
}

template <typename T>
Map<T>::Map( size_t in_size )
	: size( in_size )
	, num( 0 )
	, arr( in_size )
{
	for ( size_t idx = 0; idx < size; idx++ )
	{
		arr.Add( { 0, {} } );
	}
}

template <typename T>
Map<T>::Map( Map&& other )
	: size( other.size )
	, num( other.num )
	, arr( CKAMove( other.arr ) )
{
	other.size = 0;
	other.num = 0;
}

template <typename T>
Map<T>& Map<T>::operator=( Map&& other )
{
	size = other.size;
	num = other.num;
	arr = CKAMove( other.arr );

	other.size = 0;
	other.num = 0;
}

template <typename T>
Map<T>::~Map()
{

}

#endif // MAP_INL