/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------------------------------
*/
#pragma once
#ifndef CE_CPPCORE_CONTAINER_TARRAY_H_INC
#define CE_CPPCORE_CONTAINER_TARRAY_H_INC

#include <cppcore/CPPCoreCommon.h>

#include <cassert>

namespace CPPCore {
	
//-------------------------------------------------------------------------------------------------
///	@class		TArray
///	@ingroup	CPPCore
///
///	@brief	This template class implements a simple array with dynamic boundaries. 
/// You can use it to add new items, remove them and iterate through them. The data items are 
/// stores in an array.
//-------------------------------------------------------------------------------------------------
template<class T>
class TArray {
public:
	///	The iterator type.
	typedef T* Iterator;
	///	The const iterator type.
	typedef const T* ConstIterator;

	///	@enum	SortedMode
	///	@brief	This enum describes the sorting mode of the array.
	enum SortedMode	{
		Unsorted,		///< No sorting performed.
		Ascending,		///< The array is sorted ascending.
		Descending		///< The array is sorted descending.
	};

public:
	///	@brief	The default class constructor.
	TArray();

	///	@brief	The class constructor with an initial size.
	///	@param	size	[in] The initial size.
	TArray( ui32 size );

	///	@brief	The copy constructor.
	///	@param	other	    [in] The instance to copy from.
	TArray( const TArray<T> &other );

	///	@brief	The class destructor.
	~TArray();

	///	@brief	A new item will be added to the array.
	///	@param	newValue    [in] The value to add.
	void add( const T &newValue );

	///	@brief	Removes an item at the given index.
	///	@param	index	    [in] The index of the item to remove.
	void remove( ui32 index );

	///	@brief	Removes the item describes by a given iterator.
	///	@param	it	        [in] The iterator describing the position.
	void remove( Iterator it );

	///	@brief	The last item will be removed.
	void removeBack();

	///	@brief	The item at the given index will be destroyed, the destructor will be called manually.
	///	@param	index	    [in] The index of the item.
	void destroy( ui32 index );

	///	@brief	Returns the first item.
	///	@return	The first item.
	T &front();

	///	@brief	Returns the last item.
	///	@return	The last item.
	T &back();

	///	@brief	Moves the items from the start- to the end-index.
	///	@param	startIdx	[in] The start index.
	///	@param	endIdx		[in] The last index.
	void move( ui32 startIdx, ui32 endIdx );
	
	///	@brief	Ensures, that the capacity of the array is big enough for the given size. 
	///	@param	capacity	[in] The new capacity.
	///	@remark	The size will not be modified.
	void reserve( ui32 capacity );

	///	@brief	Resize the array, new items will be created.
	///	@param	size	    [in] The new size for the array.
	void resize( ui32 size );

	///	@brief	The current size of the array will be returned.
	///	@return	The current size.
	ui32 size() const;

	///	@brief	The current capacity will be returned.
	///	@return	The current capacity.
	ui32 capacity() const;
	
	///	@brief	Returns true, if the array is empty.
	///	@return	true, if the array is empty, false if not.
	bool isEmpty() const;
	
	///	@brief	Search for a given item in the array.
	///	@param	item	    [in] The item to look for.
	///	@return	An iterator showing to the position will be returned.
	Iterator find( const T &item );
	
	///	@brief	The array will be cleared, destructor of the items will be called.
	void clear();

	///	@brief	Returns an iterator showing to the first item.
	///	@return	An iterator showing to the first item.
	///	@remark	If the array is empty, end() will be returned.
	Iterator begin();

	///	@brief	Returns an iterator showing to the end of the array.
	///	@return	An iterator showing the item after the last item.
	///	@remark	You cannot use this iterator to get access to the last item. Its only a marker
	///			for the end of the array.
	Iterator end();

	///	@brief	The	[] operator.
	T &operator[]( ui32 idx ) const;
	
	///	@brief	The assignment operator.
	TArray<T> &operator = (const TArray<T> &rOther );
	
	///	@brief	The compare operator.
	bool operator == ( const TArray<T> &rOther ) const;

protected:
	///	Returns the growing value.
	ui32 getGrowing( ui32 size );

private:
	SortedMode m_Sorted;
	ui32 m_Size;
	ui32 m_Capacity;
	T *m_pData;
};

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TArray<T>::TArray() 
: m_Sorted( Unsorted )
, m_Size( 0 )
, m_Capacity( 0 )
, m_pData( nullptr ) {
	// empty
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TArray<T>::TArray( ui32 size ) 
: m_Sorted( Unsorted )
, m_Size( 0 )
, m_Capacity( 0 )
, m_pData( nullptr )  {
	const ui32 capa = getGrowing( size );
	reserve( capa );
	resize( size );
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TArray<T>::TArray( const TArray<T> &rOther ) 
: m_Sorted( rOther.m_Sorted )
, m_Size( 0 )
, m_Capacity( 0 )
, m_pData( nullptr ) {
	resize( rOther.m_Size );
	for ( ui32 i=0; i<m_Size; ++i )	{
		m_pData[ i ] = rOther.m_pData[ i ];
	}
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TArray<T>::~TArray() {
	m_Size = 0;
	m_Capacity = 0;
	delete [] m_pData;
	m_pData = nullptr;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::add( const T &rValue ) {
	if ( m_Size+1 > m_Capacity ) {
		ui32 newcapa = getGrowing( m_Size + 1 );
		reserve( m_Capacity + newcapa );
	}
	m_pData[ m_Size ] = rValue;
	++m_Size;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::remove( ui32 index ) {
	assert( index < m_Size );

	if ( index == m_Size - 1 ) {
		// Destroy the last index
		destroy( index );
		--m_Size;
	} else {
		// Remove an index in the middle
		this->move( index + 1, index );
	}
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::remove( Iterator it ) {
	ce_assert( it < end() );

	// Look out for the index 
	i32 pos = -1;
	Iterator currentIt = this->begin();
	for ( ui32 i=0; i<m_Size; ++i )	{
		++currentIt;
		if ( it == currentIt ) {
			pos = i;
			break;
		}
	}

	// Remove the item at the position
	if ( -1 != pos ) {
		this->remove( pos );
	}
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::removeBack() {
	assert( !isEmpty() );

	remove( size() - 1 );
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::destroy( ui32 index ) {
	T *pElem = &( m_pData[ index ] );
	pElem->~T();
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
T &TArray<T>::front() {
	assert( m_Size > 0 );

	return m_pData[ 0 ];
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
T &TArray<T>::back() {
	assert( m_Size > 0 );

	return ( m_pData[ m_Size-1 ] );
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::move( ui32 fromIdx, ui32 toIdx ) {
	if ( fromIdx == toIdx ) {
		return;
    }

	ui32 numElements = m_Size - fromIdx;
	ui32 newSize = toIdx + numElements;
	while ( m_Capacity < newSize ) {
		resize( m_Capacity + getGrowing( newSize - m_Capacity ) );
    }

	ui32 index( 0 );
	if ( fromIdx > toIdx ) {
		for ( ui32 i = 0; i < numElements; ++i ) {
			m_pData[ toIdx + i ] = m_pData[ fromIdx + i ];
        }

		for ( ui32 i=toIdx; i<fromIdx+1; --i ) {
			index = i;
			destroy( index );
		}
	} else {
		for ( i32 i=numElements-1; i>=0; --i ) {
			m_pData[ toIdx + i ] = m_pData[ fromIdx + i ];
        }

		for ( ui32 i=0; i<numElements; i++) {
			index = fromIdx + i;
			destroy( index );
		}
	}

	m_Size = toIdx + numElements;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::reserve( ui32 capacity ) {
	if ( capacity <= m_Capacity ) {
		return;
    }

	T *pTmp = nullptr;
	if ( m_Size > 0 )  {
		pTmp = new T[ m_Size ];
		for ( ui32 i=0; i<m_Size; ++i )  {
			pTmp[ i ] = m_pData[ i ];
		}
	}

	if ( m_pData ) {
		delete [] m_pData;
    }
	
	m_pData = new T[ capacity ];
	m_Capacity = capacity;

	if ( m_Size > 0 ) {
		for ( ui32 i=0; i<m_Size; ++i ) {
			m_pData[ i ] = pTmp[ i ];
        }
		delete [] pTmp;
	}
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::resize( ui32 size )
{
	ui32 oldSize = m_Size;
	T *pTmp = nullptr;

	// Store older items
	if ( m_Size > 0 && m_Capacity < size )
	{
		pTmp = new T[ m_Size ];
		for ( ui32 i=0; i<m_Size; ++i )
			pTmp[ i ] = m_pData[ i ];

		delete [] m_pData;
		m_pData = nullptr;
		m_Capacity = 0;
	}

	// Realloc memory
	if ( size > m_Capacity )
	{
		m_pData = new T[ size ];
		if ( pTmp )
		{
			for ( ui32 i=0; i<oldSize; ++i )
				m_pData[ i ] = pTmp[ i ];
			delete [] pTmp;
		}
		m_Capacity = size;
	}
	m_Size = size;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
ui32 TArray<T>::size() const {
	return m_Size;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
ui32 TArray<T>::capacity() const {
	return m_Capacity;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
bool TArray<T>::isEmpty() const {
	return ( 0 == m_Size );
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
typename TArray<T>::Iterator TArray<T>::find( const T &rItem ) {
	if ( m_Sorted == Unsorted ) {
		for ( Iterator it = begin(); it != end(); ++it ) {
			if ( rItem == *it ) {
				return it;
			}
		}
	}

	return end();
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
void TArray<T>::clear() {
	delete [] m_pData;
	m_pData = nullptr;
	m_Size = 0;
	m_Capacity = 0;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
typename TArray<T>::Iterator TArray<T>::begin() {
	if ( 0 == size() ) {
		return end();
	}

	return &m_pData[ 0 ];
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
typename TArray<T>::Iterator TArray<T>::end() {
	T *tmp = m_pData;
	tmp += m_Size;

	return tmp;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
T &TArray<T>::operator[]( ui32 idx ) const {
	assert( idx < m_Size );
	assert( nullptr != m_pData );

	return m_pData[ idx ];
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
TArray<T> &TArray<T>::operator = ( const TArray<T> &rOther ) {
	if ( rOther == *this ) {
		return *this;
	}

	resize( rOther.size() );
	if ( !rOther.isEmpty() ) {
		assert( nullptr != rOther.m_pData );
		if ( m_pData ) {
			for ( ui32 i=0; i<rOther.size(); ++i ) {
				m_pData[ i ] = rOther.m_pData[ i ];
			}
			m_Size = rOther.m_Size;
		}
	}

	return *this;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
bool TArray<T>::operator == ( const TArray<T> &rOther ) const {
	if ( rOther.m_Size != m_Size ) {
		return false;
	}

	for ( ui32 i=0; i<m_Size; ++i )	{
		if ( m_pData[ i ] != rOther.m_pData[ i ] ) {
			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
template<class T>
inline
ui32 TArray<T>::getGrowing( ui32 size ) {
	if ( !size )
		return 0;

	if ( size < 2048 )
		return size * 2;

	return 4096;
}

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore

#endif // CE_CPPCORE_CONTAINER_TARRAY_H_INC
