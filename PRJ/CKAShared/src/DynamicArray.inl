#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

template <typename T>
void DynamicArray<T>::Resize( size_t new_size )
{
	// We only support non-decreasing arrays right now
	assert( new_size > num );
	size = new_size;
	data = (T*)realloc( data, new_size * sizeof( T ) );
}

template <typename T>
void DynamicArray<T>::Add( T new_item )
{
	if ( size == num )
	{
		Resize( size_t( (float)size * DYNARR_DEFAULT_GROWTH ) );
	}
	data[num++] = new_item;
}

// Will only compile when T is a pointer type
template <typename T>
void DynamicArray<T>::DeleteAll()
{
	for ( size_t idx = 0; idx < num; idx++ )
	{
		delete data[idx];
	}
	num = 0;
}

template <typename T>
void DynamicArray<T>::ClearAll()
{
	for ( u64 idx = 0; idx < num; idx++ )
	{
		data[idx].~T();
	}
	num = 0;
}

template <typename T>
void DynamicArray<T>::RemoveItemLinear( T in_item )
{
	bool removed = false;
	for ( u64 idx = 0; idx < num - u64( removed ); idx++ )
	{
		if ( removed )
		{
			data[idx] = CKAMove(data[idx + 1]);
		}
		else if ( data[idx] == in_item )
		{
			removed = true;
			idx--;
		}
	}
	assert( removed );
	num--;
}

template <typename T>
void DynamicArray<T>::RemoveItemFast( T in_item )
{
	bool removed = false;
	for ( u64 idx = 0; idx < num; idx++ )
	{
		if ( data[idx] == in_item )
		{
			removed = true;
			data[idx] = CKAMove( data[num - 1] );
			break;
		}
	}
	assert( removed );
	num--;
}

template <typename T>
void DynamicArray<T>::RemoveAtLinear( size_t in_idx )
{
	for ( u64 idx = in_idx; idx < num - 1; idx++ )
	{
		data[idx] = CKAMove( data[idx + 1] );
	}
	num--;
}

template <typename T>
void DynamicArray<T>::RemoveAtFast( size_t idx )
{
	assert(idx < num);
	data[idx] = CKAMove(data[num - 1]);
	num--;
}

template <typename T>
T& DynamicArray<T>::operator[]( size_t idx )
{
	assert( idx < num );
	return data[idx];
}

template <typename T>
DynamicArray<T>::DynamicArray( size_t in_size )
	: size( in_size )
	, num( 0 )
	, data( new T[in_size] )
{}

template <typename T>
DynamicArray<T>::DynamicArray( DynamicArray<T>&& other )
	: size( other.size )
	, num( other.num )
	, data( other.num )
{
	other.size = 0;
	other.num = 0;
	other.data = nullptr;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=( DynamicArray<T>&& other )
{
	if ( data )
	{
		delete data;
	}
	size = other.size;
	num = other.num;
	data = other.data;

	other.size = 0;
	other.num = 0;
	other.data = nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] data;
}


#endif // DYNAMICARRAY_H