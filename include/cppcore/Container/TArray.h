/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2024 Kim Kulling

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
-----------------------------------------------------------------------------------------------*/
#pragma once

#include <cppcore/CPPCoreCommon.h>
#include <cppcore/Memory/TDefaultAllocator.h>

namespace cppcore {
namespace Details {

inline static size_t getGrowing(size_t size) {
    if (0u == size) {
        return 0u;
    }

    if (size < 2048u) {
        return size * 2u;
    }

    return 4096u;
}

} // namespace Details

//-------------------------------------------------------------------------------------------------
///	@class		TArray
///	@ingroup	CPPCore
///
///	@brief	This template class implements a simple array with dynamic boundaries.
/// You can use it to add new items, remove them and iterate through them. The data items are
/// stores in an array.
//-------------------------------------------------------------------------------------------------
template <class T, class TAlloc = TDefaultAllocator<T> >
class TArray {
public:
    ///	The iterator type.
    using Iterator = T*;
    ///	The const iterator type.
    using ConstIterator = const T *;
    /// The index address type
    using array_size_type = size_t;

public:
    ///	@brief	The default class constructor.
    TArray();

    ///	@brief	The class constructor with an initial size.
    ///	@param[in] size     The initial size.
    explicit TArray(array_size_type size);

    ///	@brief	The copy constructor.
    ///	@param[in] rhs      The instance to copy from.
    TArray(const TArray<T, TAlloc> &rhs);

    ///	@brief	The class destructor.
    ~TArray();

    ///	@brief	A new item will be added to the array.
    ///	@param[in] newValue The value to add.
    void add(const T &newValue);

    ///	@brief	An array of new items will be added to the array.
    ///	@param[in] newValues   The array of new values to add.
    ///	@param[in] numItems    The number of items in the array.
    void add(const T *newValues, array_size_type numItems);

    ///	@brief	Removes an item at the given index.
    ///	@param[in] index	   The index of the item to remove.
    void remove(array_size_type index);

    ///	@brief	Removes the item describes by a given iterator.
    ///	@param[in] it	       The iterator describing the position.
    void remove(Iterator it);

    ///	@brief	The last item will be removed.
    void removeBack();

    /// @brief Will set all items to the value.
    /// @param value    The value to set.
    void set(const T &value);

    ///	@brief	The item at the given index will be destroyed, the destructor will be called manually.
    ///	@param[in] index	   The index of the item.
    void destroy(array_size_type index);

    ///	@brief	Returns the first item.
    ///	@return	The first item.
    T &front();

    ///	@brief	Returns the last item.
    ///	@return	The last item.
    T &back();

    ///	@brief	Returns the last item as a const reference.
    ///	@return	The last item.
    const T &back() const;

    ///	@brief	Moves the items from the start- to the end-index.
    ///	@param[in] startIdx	   The start index.
    ///	@param[in] endIdx	   The last index.
    void move(array_size_type startIdx, array_size_type endIdx);

    ///	@brief	Ensures, that the capacity of the array is big enough for the given size.
    ///	@param[in] capacity	   The new capacity.
    ///	@remark	The size will not be modified.
    void reserve(array_size_type capacity);

    ///	@brief	Resize the array, new items will be created.
    ///	@param[in] size	       The new size for the array.
    void resize(array_size_type size);

    ///	@brief	Resize the array, new items will be created.
    ///	@param[in] size	       The new size for the array.
    /// @param[in] val         The value for initialization.
    void resize(array_size_type size, T val);

    ///	@brief	The current size of the array will be returned.
    ///	@return	The current size.
    size_t size() const;

    ///	@brief	The current capacity will be returned.
    ///	@return	The current capacity.
    size_t capacity() const;

    ///	@brief	Returns true, if the array is empty.
    ///	@return	true, if the array is empty, false if not.
    bool isEmpty() const;

    ///	@brief	Performs a linear search for a given item in the array.
    ///	@param[in] item	       The item to look for.
    ///	@return	An iterator showing to the position will be returned.
    Iterator linearSearch(const T &item);

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

    /// @brief  Will return the data pointer.
    /// @return The data pointer.
    T data() const;

    ///	@brief	The	[] operator.
    T &operator[](array_size_type idx) const;

    ///	@brief	The assignment operator.
    TArray<T, TAlloc> &operator=(const TArray<T, TAlloc> &rhs);

    ///	@brief	The compare operator.
    bool operator==(const TArray<T, TAlloc> &rOther) const;

private:
    TAlloc mAllocator;
    size_t mSize;
    size_t mCapacity;
    T *mData;
};

template <class T, class TAlloc>
inline TArray<T, TAlloc>::TArray() :
        mAllocator(),
        mSize(0u),
        mCapacity(0u),
        mData(nullptr) {
    // empty
}

template <class T, class TAlloc>
inline TArray<T, TAlloc>::TArray(size_t size) :
        mAllocator(),
        mSize(0u),
        mCapacity(0u),
        mData(nullptr) {
    const size_t capa = Details::getGrowing(size);
    reserve(capa);
    resize(size);
}

template <class T, class TAlloc>
inline TArray<T, TAlloc>::TArray(const TArray<T, TAlloc> &rhs) :
        mAllocator(),
        mSize(0u),
        mCapacity(0u),
        mData(nullptr) {
    resize(rhs.mSize);
    for (size_t i = 0u; i < mSize; ++i) {
        mData[i] = rhs.mData[i];
    }
}

template <class T, class TAlloc>
inline TArray<T, TAlloc>::~TArray() {
    clear();
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::add(const T &value) {
    if (mSize + 1 > mCapacity) {
        const size_t newcapa = Details::getGrowing(mSize + 1);
        reserve(mCapacity + newcapa);
    }
    mData[mSize] = value;
    ++mSize;
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::add(const T *newValues, size_t numItems) {
    if (0 == numItems || newValues == nullptr) {
        return;
    }

    const size_t newCapa = mSize + numItems;
    if (newCapa > mCapacity) {
        reserve(mCapacity + newCapa);
    }
    for (size_t i = 0; i < numItems; ++i) {
        mData[mSize] = newValues[i];
        ++mSize;
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::remove(size_t index) {
    assert(index < mSize);

    if (index == mSize - 1) {
        // Destroy the last index
        destroy(index);
        --mSize;
    } else {
        // Remove an index in the middle
        this->move(index + 1, index);
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::remove(Iterator it) {
    assert(it < end());

    // Look out for the index
    long pos = -1;
    Iterator currentIt = this->begin();
    for (size_t i = 0; i < mSize; ++i) {
        if (it == currentIt) {
            pos = static_cast<long>(i);
            break;
        }
        ++currentIt;
    }

    // Remove the item at the position
    if (-1 != pos) {
        this->remove(pos);
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::removeBack() {
    assert(!isEmpty());

    remove(size() - 1);
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::set(const T &value) {
    if (isEmpty()) {
        return;
    }

    for (size_t i = 0; i < size(); ++i) {
        mData[i] = value;
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::destroy(size_t index) {
    T *pElem = &(mData[index]);
    pElem->~T();
}

template <class T, class TAlloc>
inline T &TArray<T, TAlloc>::front() {
    assert(mSize > 0);

    return mData[0];
}

template <class T, class TAlloc>
inline T &TArray<T, TAlloc>::back() {
    assert(mSize > 0);

    return (mData[mSize - 1]);
}

template <class T, class TAlloc>
inline const T &TArray<T, TAlloc>::back() const {
    assert(mSize > 0);

    return (mData[mSize - 1]);
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::move(size_t fromIdx, size_t toIdx) {
    if (fromIdx == toIdx) {
        return;
    }

    const size_t numElements = mSize - fromIdx;
    const size_t newSize = toIdx + numElements;
    while (mCapacity < newSize) {
        resize(mCapacity + Details::getGrowing(newSize - mCapacity));
    }

    size_t index = 0u;
    if (fromIdx > toIdx) {
        for (size_t i = 0; i < numElements; ++i) {
            mData[toIdx + i] = mData[fromIdx + i];
        }

        for (size_t i = toIdx; i < fromIdx + 1; --i) {
            index = i;
            destroy(index);
        }
    } else {
        for (size_t i = numElements - 1; i != 0; --i) {
            mData[toIdx + i] = mData[fromIdx + i];
        }

        for (size_t i = 0; i < numElements; i++) {
            index = fromIdx + i;
            destroy(index);
        }
    }

    mSize = toIdx + numElements;
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::reserve(size_t capacity) {
    if (capacity <= mCapacity) {
        return;
    }

    T *tmp = nullptr;
    if (mSize > 0u) {
        tmp = mAllocator.alloc(mSize);
        for (size_t i = 0u; i < mSize; ++i) {
            tmp[i] = mData[i];
        }
    }

    if (mData) {
        mAllocator.release(mData);
        mData = nullptr;
    }

    mData = mAllocator.alloc(capacity);
    mCapacity = capacity;

    if (mSize > 0u) {
        for (size_t i = 0u; i < mSize; ++i) {
            mData[i] = tmp[i];
        }
        mAllocator.release(tmp);
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::resize(size_t size) {
    const size_t oldSize = mSize;
    T *tmp = nullptr;

    // Store older items
    if (mSize > 0u && mCapacity < size) {
        tmp = mAllocator.alloc(mSize * sizeof(T));
        for (size_t i = 0u; i < mSize; ++i) {
            tmp[i] = mData[i];
        }

        mAllocator.release(mData);
        mData = nullptr;
        mCapacity = 0u;
    }

    // Realloc memory
    if (size > mCapacity) {
        mData = mAllocator.alloc(size * sizeof(T));
        if (tmp) {
            for (size_t i = 0u; i < oldSize; ++i) {
                mData[i] = tmp[i];
            }
            mAllocator.release(tmp);
        }
        mCapacity = size;
    }
    mSize = size;
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::resize(size_t size, T val) {
    resize(size);
    if (0u != size) {
        for (size_t i = 0u; i < size; ++i) {
            mData[i] = val;
        }
    }
}

template <class T, class TAlloc>
inline size_t TArray<T, TAlloc>::size() const {
    return mSize;
}

template <class T, class TAlloc>
inline size_t TArray<T, TAlloc>::capacity() const {
    return mCapacity;
}

template <class T, class TAlloc>
inline bool TArray<T, TAlloc>::isEmpty() const {
    return (0u == mSize);
}

template <class T, class TAlloc>
inline typename TArray<T, TAlloc>::Iterator TArray<T, TAlloc>::linearSearch(const T &item) {
    for (Iterator it = begin(); it != end(); ++it) {
        if (item == *it) {
            return it;
        }
    }

    return end();
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::clear() {
    mAllocator.release(mData);
    mData = nullptr;
    mSize = 0u;
    mCapacity = 0u;
}

template <class T, class TAlloc>
inline typename TArray<T, TAlloc>::Iterator TArray<T, TAlloc>::begin() {
    if (0u == size()) {
        return end();
    }

    return &mData[0];
}

template <class T, class TAlloc>
inline typename TArray<T, TAlloc>::Iterator TArray<T, TAlloc>::end() {
    T *tmp = mData;
    tmp += mSize;

    return tmp;
}

template <class T, class TAlloc>
inline T TArray<T, TAlloc>::data() const {
    return mData;
}

template <class T, class TAlloc>
inline T &TArray<T, TAlloc>::operator[](size_t idx) const {
    assert(idx < mSize);
    assert(nullptr != mData);

    return mData[idx];
}

template <class T, class TAlloc>
inline TArray<T, TAlloc> &TArray<T, TAlloc>::operator=(const TArray<T, TAlloc> &other) {
    if (other == *this) {
        return *this;
    }

    resize(other.size());
    if (!other.isEmpty()) {
        assert(nullptr != other.mData);
        if (mData) {
            for (size_t i = 0u; i < other.size(); ++i) {
                mData[i] = other.mData[i];
            }
            mSize = other.mSize;
        }
    }

    return *this;
}

template <class T, class TAlloc>
inline bool TArray<T, TAlloc>::operator == (const TArray<T, TAlloc> &rhs) const {
    if (rhs.mSize != mSize) {
        return false;
    }

    for (size_t i = 0u; i < mSize; ++i) {
        if (mData[i] != rhs.mData[i]) {
            return false;
        }
    }

    return true;
}

} // Namespace cppcore
