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
///	@class		THashMap
///	@ingroup	CPPCore
///
///	@brief  This class implements a hash map. You can access your data like:
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
    ///	@brief  The initial hash size.
    static constexpr size_t InitSize = 1024;
    ///	@brief  Marker for unset node keys.
    static constexpr unsigned int UnsetNode = 999999999;

public:
    ///	@brief  The class constructor.
    /// @param  init    [in] The initial size for the hash.
    THashMap(size_t init = InitSize);

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

    ///	@brief  Will init the hash-map.
    /// @param  init    [in] The initial size for the hash.
    void init(size_t init);

    /// @brief  The hash-map will be cleared.
    void clear();

    ///	@brief  A new key value pair will be entered.
    ///	@param  key     [in] The key.
    ///	@param  value   [in] The value to store.
    void insert(const T &key, const U &value);

    ///	@brief  Will remove a given key-value pair form the hash-map.
    ///	@param  key     [in] The key to look for.
    ///	@return true, if key-value pair was found and removed.
    bool remove(const T &key);

    ///	@brief  Looks for a given key and returns true, if a key-value pair is stored in the list.
    ///	@param  key     [in] The key to look for.
    ///	@return true, if key-value pair was found.
    bool hasKey(const T &key) const;

    ///	@brief  Returns the assigned value for the given key.
    ///	@param  key     [in] The key to look for.
    ///	@param  value   [in] The value, unset when no key-value pair was found.
    ///	@return true, if key-value pair was found, false if not.
    bool getValue(const T &key, U &value) const;

    ///	@brief  Returns the assigned value for the given key.
    ///	@param  key     [in] The key to look for.
    ///	@return The value, will unset when no key-value pair was found.
    U &operator[](const T &key) const;

    /// Avoid copying.
    THashMap<T, U, TAlloc>(const THashMap<T, U> &) = delete;
    THashMap<T, U, TAlloc> &operator=(const THashMap<T, U> &) = delete;

private:
    struct Node {
        T m_key;
        U m_value;
        Node *m_next;

        Node();
        ~Node();
        void append(T key, const U &value);
        bool remove(T key);
        void releaseList();
    };

    Node **m_buffer;
    size_t m_numItems;
    size_t m_buffersize;
};

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::THashMap(size_t initSize) :
        m_buffer(nullptr),
        m_numItems(0u),
        m_buffersize(0u) {
    init(initSize);
}

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::~THashMap() {
    clear();
}

template <class T, class U, class TAlloc>
inline size_t THashMap<T, U, TAlloc>::size() const {
    return m_numItems;
}

template <class T, class U, class TAlloc>
inline size_t THashMap<T, U, TAlloc>::capacity() const {
    return m_buffersize;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::isEmpty() const {
    return (0u == m_numItems);
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::init(size_t init) {
    m_buffer = new Node *[init];
    for (size_t i = 0; i < init; i++) {
        m_buffer[i] = nullptr;
    }
    m_buffersize = init;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::clear() {
    for (size_t i = 0; i < m_buffersize; ++i) {
        if (nullptr != m_buffer[i]) {
            m_buffer[i]->releaseList();
        }
    }
    delete[] m_buffer;
    m_buffer = nullptr;
    m_numItems = 0;
    m_buffersize = 0;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::insert(const T &key, const U &value) {
    const unsigned int hash = Hash::toHash(key, (unsigned int)m_buffersize);
    if (nullptr == m_buffer[hash]) {
        Node *node = new Node;
        node->m_key = key;
        node->m_value = value;
        m_buffer[hash] = node;
    } else {
        m_buffer[hash]->append(key, value);
    }
    ++m_numItems;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::remove(const T &key) {
    const unsigned int hash = Hash::toHash(key, (unsigned int)m_buffersize);
    if (nullptr == m_buffer[hash]) {
        return false;
    }

    bool found = false;
    Node *current = m_buffer[hash];
    if (current->m_key == key) {
        Node *next = current->m_next;
        m_buffer[hash] = next;
        delete current;
        --m_numItems;
        found = true;
        return true;
    }

    found = current->remove(key);
    if (found) {
        --m_numItems;
    }

    return found;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::hasKey(const T &key) const {
    // no buffer, so no items stored
    if (0 == m_buffersize) {
        return false;
    }
    const unsigned int hash(Hash::toHash(key, (unsigned int)m_buffersize));
    const Node *node = m_buffer[hash];
    if (nullptr == node) {
        return false;
    }

    if (node->m_key == key) {
        return true;
    }

    if (nullptr != node->m_next) {
        Node *next = node->m_next;
        while (nullptr != next) {
            if (next->m_key == key) {
                return true;
            }
            next = next->m_next;
        }
    }

    return false;
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::getValue(const T &key, U &value) const {
    const size_t pos = Hash::toHash(key, (unsigned int)m_buffersize);
    if (m_buffer[pos]->m_key == key) {
        value = m_buffer[pos]->m_value;
        return true;
    }

    Node *node = m_buffer[pos];
    Node *next = node->m_next;
    while (next->m_key != key) {
        next = next->m_next;
        if (nullptr == next) {
            return false;
        }
    }
    value = next->m_value;

    return true;
}

template <class T, class U, class TAlloc>
inline U &THashMap<T, U, TAlloc>::operator[](const T &key) const {
    static U dummy;
    const unsigned int pos = Hash::toHash(key, m_buffersize);
    if (m_buffer[pos]->m_key == key) {
        return m_buffer[pos]->m_value;
    } 

    Node next = m_buffer[pos]->m_next;
    while (next->m_key != key) {
        next = next->m_next;
        if (nullptr == next) {
            return dummy;
        }
    }

    return next->m_value;
}

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::Node::Node() :
        m_key(UnsetNode), 
        m_value(), 
        m_next(nullptr) {
    // empty
}

template <class T, class U, class TAlloc>
inline THashMap<T, U, TAlloc>::Node::~Node() {
    m_next = nullptr;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::Node::append(T key, const U &value) {
    if (m_key == UnsetNode) {
        m_key = key;
        m_value = value;
        return;
    }

    Node *current = m_next;
    if (nullptr != current) {
        // already collisions, traverse
        while (current->m_next) {
            current = current->m_next;
        }
        current->m_next = new Node;
        current->m_next->m_key = key;
        current->m_next->m_value = value;
    } else {
        // first collision
        m_next = new Node;
        current = m_next;
        current->m_key = key;
        current->m_value = value;
    }
}

template <class T, class U, class TAlloc>
inline bool THashMap<T, U, TAlloc>::Node::remove(T key) {
    if (nullptr == m_next) {
        return false;
    }

    bool found = false;
    Node *current = m_next, *prev = nullptr;
    while (nullptr != current) {
        if (current->m_key == key) {
            if (nullptr != prev) {
                prev->m_next = current->m_next;
                delete current;
            }
            found = true;
            break;
        }
        prev = current;
        current = current->m_next;
    }

    return found;
}

template <class T, class U, class TAlloc>
inline void THashMap<T, U, TAlloc>::Node::releaseList() {
    if (nullptr == m_next) {
        return;
    }

    Node *current = m_next;
    while (nullptr != current) {
        Node *tmp = current;
        current = current->m_next;
        delete tmp;
    }
}

} // Namespace cppcore
