#ifndef CKAUTIL_INL
#define CKAUTIL_INL

template <typename T>
T&& CKAMove( T& ref )
{
	return static_cast<T&&>( ref );
}

#endif // CKAUTIL_INL