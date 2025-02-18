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

#include <cppcore/Common/Hash.h>
#include <cppcore/Memory/TDefaultAllocator.h>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class   THashMap
///	@ingroup CPPCore
///
///	@brief  This class implements a hash map. 
///
/// You can work with the hashmap in the following way:
///
/// @code
/// using TestHashMap = THashMap<int, String>:
/// TestHashMap hm;
/// hm.insert(1, "test");
/// hm.hasKey(1); // will return true;
/// hm.remove(1);
/// hm.hasKey(1); // will return false;
/// @endcode
//-------------------------------------------------------------------------------------------------
template <class T, class U, class TAlloc = TDefaultAllocator<T>>
class THashMap {
public:
    /// The alias
    using Hash = THash<T>;

    ///	@brief  The initial hash size.
    static constexpr size_t InitSize = 1024;
    ///	@brief  Marker for unset node keys.
    static constexpr unsigned int UnsetNode = 999999999;

public:
    ///	@brief  The class constructor.
    /// @param  init    [in] The initial size for the hash.
    explicit THashMap(size_t init = InitSize);

    /// @brief  The class destructor.
    ~THashMap();

    ///	@brief  Returns the number of stored items in the hash-map.
    /// @return The number of items within the hash-map.
    size_t size() const;

    /// @brief  Will return the number of possible hash items stored in the hash map.
    /// @return The number of possible hash items.
    size_t capacity() const;

    ///	@brief  Will return true, if hash-map is empty.
    ///	@return true for empty, false for not empty.
    bool isEmpty() const;

    ///	@brief  Will init the hash-map with the given size.
    /// @param[in] init  The initial size for the hash.
    void init(size_t init);

    /// @brief The hash-map will be cleared.
    void clear();

    ///	@brief A new key value pair will be entered.
    ///	@param[in] key    The key.
    ///	@param[in] value  The value to store.
    void insert(const T &key, const U &value);

    ///	@brief  Will remove a given key-value pair form the hash-map.
    ///	@param[in] key  The key to look for.
    ///	@return true, if key-value pair was found and removed.
    bool remove(const T &key);

    ///	@brief  Looks for a given key and returns true, if a key-value pair is stored in the list.
    ///	@param[in] key   The key to look for.
    ///	@return true, if key-value pair was found.
    bool hasKey(const T &key) const;

    ///	@brief  Returns the assigned value for the given key.
    ///	@param[in] key     The key to look for.
    ///	@param[in] value   The value, unset when no key-value pair was found.
    ///	@return true, if key-value pair was found, false if not.
    bool getValue(const T &key, U &value) const;

    ///	@brief  Returns the assigned value for the given key.
    ///	@param[in] key   The key to look for.
    ///	@return The value, will unset when no key-value pair was found.
    U &operator[](const T &key) const;

    /// Avoid copying.
    THashMap<T, U, TAlloc>(const THashMap<T, U> &) = delete;
    THashMap<T, U, TAlloc> &operator=(const THashMap<T, U> &) = delete;

private:
    struct Node {
        T mKey;
        U mValue;
        Node *mNext;

        Node();
        ~Node();
        void append(T key, const U &value);
        bool remove(T key);
        void releaseList();
    };

    Node **mBuffer;
    size_t mNumItems;
    size_t mBuffersize;
};

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::THashMap(size_t initSize) :
        mBuffer(nullptr),
        mNumItems(0u),
        mBuffersize(0u) {
    init(initSize);
}

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::~THashMap() {
    clear();
}

template <class T, class U, class TAlloc>
inline size_t THashMap<T, U, TAlloc>::size() const {
    return mNumItems;
}

template <class T, class U, class TAlloc>
inline size_t THashMap<T, U, TAlloc>::capacity() const {
    return mBuffersize;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::isEmpty() const {
    return (0u == mNumItems);
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::init(size_t init) {
    mBuffer = new Node *[init];
    for (size_t i = 0; i < init; i++) {
        mBuffer[i] = nullptr;
    }
    mBuffersize = init;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::clear() {
    for (size_t i = 0; i < mBuffersize; ++i) {
        if (nullptr != mBuffer[i]) {
            mBuffer[i]->releaseList();
        }
    }
    delete[] mBuffer;
    mBuffer = nullptr;
    mNumItems = 0;
    mBuffersize = 0;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::insert(const T &key, const U &value) {
    const T hash = Hash::toHash(key, static_cast<T>(mBuffersize));
    if (nullptr == mBuffer[hash]) {
        Node *node = new Node;
        node->mKey = key;
        node->mValue = value;
        mBuffer[hash] = node;
    } else {
        mBuffer[hash]->append(key, value);
    }
    ++mNumItems;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::remove(const T &key) {
    const T hash = Hash::toHash(key, static_cast<unsigned int>(mBuffersize));
    if (nullptr == mBuffer[hash]) {
        return false;
    }

    bool found = false;
    Node *current = mBuffer[hash];
    if (current->mKey == key) {
        Node *next = current->mNext;
        mBuffer[hash] = next;
        delete current;
        --mNumItems;
        found = true;
        return true;
    }

    found = current->remove(key);
    if (found) {
        --mNumItems;
    }

    return found;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::hasKey(const T &key) const {
    // no buffer, so no items stored
    if (0 == mBuffersize) {
        return false;
    }
    const T hash = THash<T>::toHash(key, (unsigned int)mBuffersize);
    const Node *node = mBuffer[hash];
    if (nullptr == node) {
        return false;
    }

    if (node->mKey == key) {
        return true;
    }

    if (nullptr != node->mNext) {
        Node *next = node->mNext;
        while (nullptr != next) {
            if (next->mKey == key) {
                return true;
            }
            next = next->mNext;
        }
    }

    return false;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::getValue(const T &key, U &value) const {
    const size_t pos = Hash::toHash(key, (unsigned int) mBuffersize);
    if (mBuffer[pos]->mKey == key) {
        value = mBuffer[pos]->mValue;
        return true;
    }

    Node *node = mBuffer[pos];
    Node *next = node->mNext;
    while (next->mKey != key) {
        next = next->mNext;
        if (nullptr == next) {
            return false;
        }
    }
    value = next->mValue;

    return true;
}

template <class T, class U, class TAlloc>
inline U &THashMap<T, U, TAlloc>::operator[](const T &key) const {
    static U dummy;
    const unsigned int pos = Hash::toHash(key, mBuffersize);
    if (mBuffer[pos]->mKey == key) {
        return mBuffer[pos]->mValue;
    } 

    Node *next = mBuffer[pos]->mNext;
    while (next->mKey != key) {
        next = next->mNext;
        if (nullptr == next) {
            return dummy;
        }
    }

    return next->mValue;
}

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::Node::Node() :
        mKey(UnsetNode), 
        mValue(), 
        mNext(nullptr) {
    // empty
}

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::Node::~Node() {
    mNext = nullptr;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::Node::append(T key, const U &value) {
    if (mKey == UnsetNode) {
        mKey = key;
        mValue = value;
        return;
    }

    Node *current = mNext;
    if (nullptr != current) {
        // already collisions, traverse
        while (current->mNext) {
            current = current->mNext;
        }
        current->mNext = new Node;
        current->mNext->mKey = key;
        current->mNext->mValue = value;
    } else {
        // first collision
        mNext = new Node;
        current = mNext;
        current->mKey = key;
        current->mValue = value;
    }
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::Node::remove(T key) {
    if (nullptr == mNext) {
        return false;
    }

    bool found = false;
    Node *current = mNext, *prev = nullptr;
    while (nullptr != current) {
        if (current->mKey == key) {
            if (nullptr != prev) {
                prev->mNext = current->mNext;
                delete current;
            }
            found = true;
            break;
        }
        prev = current;
        current = current->mNext;
    }

    return found;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::Node::releaseList() {
    if (nullptr == mNext) {
        return;
    }

    Node *current = mNext;
    while (nullptr != current) {
        Node *tmp = current;
        current = current->mNext;
        delete tmp;
    }
}

} // Namespace cppcore
