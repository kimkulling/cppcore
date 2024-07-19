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

    ///	@enum	SortedMode
    ///	@brief	This enum describes the sorting mode of the array.
    enum class SortMode {
        Unsorted, ///< No sorting performed.
        Ascending, ///< The array is sorted ascending.
        Descending ///< The array is sorted descending.
    };

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

    ///	@brief	Search for a given item in the array.
    ///	@param[in] item	       The item to look for.
    ///	@return	An iterator showing to the position will be returned.
    Iterator find(const T &item);

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
    SortMode m_Sorted;
    size_t m_Size;
    size_t m_Capacity;
    T *m_pData;
};

template <class T, class TAlloc>
inline TArray<T, TAlloc>::TArray() :
        mAllocator(),
        m_Sorted(SortMode::Unsorted),
        m_Size(0u),
        m_Capacity(0u),
        m_pData(nullptr) {
    // empty
}

template <class T, class TAlloc>
inline TArray<T, TAlloc>::TArray(size_t size) :
        m_Sorted(SortMode::Unsorted),
        m_Size(0u),
        m_Capacity(0u),
        m_pData(nullptr) {
    const size_t capa = Details::getGrowing(size);
    reserve(capa);
    resize(size);
}

template <class T, class TAlloc>
inline TArray<T, TAlloc>::TArray(const TArray<T, TAlloc> &rhs) :
        m_Sorted(rhs.m_Sorted),
        m_Size(0u),
        m_Capacity(0u),
        m_pData(nullptr) {
    resize(rhs.m_Size);
    for (size_t i = 0u; i < m_Size; ++i) {
        m_pData[i] = rhs.m_pData[i];
    }
}

template <class T, class TAlloc>
inline TArray<T, TAlloc>::~TArray() {
    clear();
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::add(const T &value) {
    if (m_Size + 1 > m_Capacity) {
        const size_t newcapa = Details::getGrowing(m_Size + 1);
        reserve(m_Capacity + newcapa);
    }
    m_pData[m_Size] = value;
    ++m_Size;
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::add(const T *newValues, size_t numItems) {
    if (0 == numItems) {
        return;
    }

    const size_t newCapa = m_Size + numItems;
    if (newCapa > m_Capacity) {
        reserve(m_Capacity + newCapa);
    }
    for (size_t i = 0; i < numItems; ++i) {
        m_pData[m_Size] = newValues[i];
        m_Size++;
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::remove(size_t index) {
    assert(index < m_Size);

    if (index == m_Size - 1) {
        // Destroy the last index
        destroy(index);
        --m_Size;
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
    for (size_t i = 0; i < m_Size; ++i) {
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
        m_pData[i] = value;
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::destroy(size_t index) {
    T *pElem = &(m_pData[index]);
    pElem->~T();
}

template <class T, class TAlloc>
inline T &TArray<T, TAlloc>::front() {
    assert(m_Size > 0);

    return m_pData[0];
}

template <class T, class TAlloc>
inline T &TArray<T, TAlloc>::back() {
    assert(m_Size > 0);

    return (m_pData[m_Size - 1]);
}

template <class T, class TAlloc>
inline const T &TArray<T, TAlloc>::back() const {
    assert(m_Size > 0);

    return (m_pData[m_Size - 1]);
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::move(size_t fromIdx, size_t toIdx) {
    if (fromIdx == toIdx) {
        return;
    }

    const size_t numElements = m_Size - fromIdx;
    const size_t newSize = toIdx + numElements;
    while (m_Capacity < newSize) {
        resize(m_Capacity + Details::getGrowing(newSize - m_Capacity));
    }

    size_t index = 0u;
    if (fromIdx > toIdx) {
        for (size_t i = 0; i < numElements; ++i) {
            m_pData[toIdx + i] = m_pData[fromIdx + i];
        }

        for (size_t i = toIdx; i < fromIdx + 1; --i) {
            index = i;
            destroy(index);
        }
    } else {
        for (size_t i = numElements - 1; i != 0; --i) {
            m_pData[toIdx + i] = m_pData[fromIdx + i];
        }

        for (size_t i = 0; i < numElements; i++) {
            index = fromIdx + i;
            destroy(index);
        }
    }

    m_Size = toIdx + numElements;
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::reserve(size_t capacity) {
    if (capacity <= m_Capacity) {
        return;
    }

    T *pTmp = nullptr;
    if (m_Size > 0u) {
        pTmp = mAllocator.alloc(m_Size);
        for (size_t i = 0u; i < m_Size; ++i) {
            pTmp[i] = m_pData[i];
        }
    }

    if (m_pData) {
        mAllocator.release(m_pData);
        m_pData = nullptr;
    }

    m_pData = mAllocator.alloc(capacity);
    m_Capacity = capacity;

    if (m_Size > 0u) {
        for (size_t i = 0u; i < m_Size; ++i) {
            m_pData[i] = pTmp[i];
        }
        mAllocator.release(pTmp);
    }
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::resize(size_t size) {
    size_t oldSize = m_Size;
    T *pTmp = nullptr;

    // Store older items
    if (m_Size > 0u && m_Capacity < size) {
        pTmp = mAllocator.alloc(m_Size * sizeof(T));
        for (size_t i = 0u; i < m_Size; ++i) {
            pTmp[i] = m_pData[i];
        }

        mAllocator.release(m_pData);
        m_pData = nullptr;
        m_Capacity = 0u;
    }

    // Realloc memory
    if (size > m_Capacity) {
        m_pData = mAllocator.alloc(size * sizeof(T));
        if (pTmp) {
            for (size_t i = 0u; i < oldSize; ++i) {
                m_pData[i] = pTmp[i];
            }
            mAllocator.release(pTmp);
        }
        m_Capacity = size;
    }
    m_Size = size;
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::resize(size_t size, T val) {
    resize(size);
    if (0u != size) {
        for (size_t i = 0u; i < size; ++i) {
            m_pData[i] = val;
        }
    }
}

template <class T, class TAlloc>
inline size_t TArray<T, TAlloc>::size() const {
    return m_Size;
}

template <class T, class TAlloc>
inline size_t TArray<T, TAlloc>::capacity() const {
    return m_Capacity;
}

template <class T, class TAlloc>
inline bool TArray<T, TAlloc>::isEmpty() const {
    return (0u == m_Size);
}

template <class T, class TAlloc>
inline typename TArray<T, TAlloc>::Iterator
    TArray<T, TAlloc>::find(const T &item) {
    if (m_Sorted == SortMode::Unsorted) {
        for (Iterator it = begin(); it != end(); ++it) {
            if (item == *it) {
                return it;
            }
        }
    }

    return end();
}

template <class T, class TAlloc>
inline void TArray<T, TAlloc>::clear() {
    mAllocator.release(m_pData);
    m_pData = nullptr;
    m_Size = 0u;
    m_Capacity = 0u;
}

template <class T, class TAlloc>
inline typename TArray<T, TAlloc>::Iterator TArray<T, TAlloc>::begin() {
    if (0u == size()) {
        return end();
    }

    return &m_pData[0];
}

template <class T, class TAlloc>
inline typename TArray<T, TAlloc>::Iterator TArray<T, TAlloc>::end() {
    T *tmp = m_pData;
    tmp += m_Size;

    return tmp;
}

template <class T, class TAlloc>
inline T TArray<T, TAlloc>::data() const {
    return m_pData;
}

template <class T, class TAlloc>
inline T &TArray<T, TAlloc>::operator[](size_t idx) const {
    assert(idx < m_Size);
    assert(nullptr != m_pData);

    return m_pData[idx];
}

template <class T, class TAlloc>
inline TArray<T, TAlloc> &TArray<T, TAlloc>::operator=(const TArray<T, TAlloc> &other) {
    if (other == *this) {
        return *this;
    }

    resize(other.size());
    if (!other.isEmpty()) {
        assert(nullptr != other.m_pData);
        if (m_pData) {
            for (size_t i = 0u; i < other.size(); ++i) {
                m_pData[i] = other.m_pData[i];
            }
            m_Size = other.m_Size;
        }
    }

    return *this;
}

template <class T, class TAlloc>
inline bool TArray<T, TAlloc>::operator == (const TArray<T, TAlloc> &rhs) const {
    if (rhs.m_Size != m_Size) {
        return false;
    }

    for (size_t i = 0u; i < m_Size; ++i) {
        if (m_pData[i] != rhs.m_pData[i]) {
            return false;
        }
    }

    return true;
}

} // Namespace cppcore
