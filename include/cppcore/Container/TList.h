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

//-------------------------------------------------------------------------------------------------
///	@class		TList
///	@ingroup	CPPCore
///
///	@brief This template class implements a simple double linked list container.
//-------------------------------------------------------------------------------------------------
template <class T, class TAlloc = TDefaultAllocator<T>>
class TList {
    //	Forward declarations
    class Node;

public:
    class Iterator;

    ///	@brief	The class default constructor.
    TList() noexcept;

    ///	@brief	The class copy constructor.
    ///	@param	rhs	Instance to copy from.
    TList(const TList<T, TAlloc> &rhs);

    ///	@brief	The class destructor.
    ~TList();

    ///	@brief	Copy the data from a given instance.
    ///	@param	rOther	Instance to copy from.
    void copyFrom(const TList<T, TAlloc> &rOther);

    ///	@brief	Adds a new item at the front of the list.
    ///	@param	item	Instance to add
    Iterator addFront(const T &item);

    ///	@brief	Adds a new item at the back of the list.
    ///	@param	item	Instance to add
    Iterator addBack(const T &item);

    ///	@brief	The first item will be removed.
    void removeFront();

    ///	@brief	The hast item will be removed.
    void removeBack();

    ///	@brief	Returns the first item.
    ///	@return	The first item.
    T &front() const;

    ///	@brief	Returns the last item.
    ///	@return	The last item.
    T &back() const;

    ///	@brief	The number of stored items will be returned.
    ///	@return	The number of stored items.
    size_t size() const;

    ///	@brief	Returns true, if the list is empty.
    ///	@return	true, if no items are store, false if items are there.
    bool isEmpty() const;

    ///	@brief	The list will be cleared.
    void clear();

    ///	@brief	Returns the iterator showing to the first entry.
    ///	@return	An iterator referencing to the begin of the list.
    Iterator begin() const;

    ///	@brief	Returns the iterator showing to the last entry.
    ///	@return	An iterator referencing to the end of the list.
    Iterator end() const;

    ///	@brief	Compare operator.
    bool operator == (const TList<T, TAlloc> &rOther) const;

    ///	@brief	Assignment operator.
    TList<T, TAlloc> &operator = (const TList<T, TAlloc> &rOther);

    //---------------------------------------------------------------------------------------------
    ///	@class	Iterator
    ///	@brief	Access implementation class.
    //---------------------------------------------------------------------------------------------
    class Iterator {
    public:
        /// The default class constructor.
        Iterator();
        /// Constructor with a node instance.
        Iterator(Node *pNode);
        /// The copy constructor.
        Iterator(const Iterator &rOther);
        /// The destructor, non virtual.
        ~Iterator() = default;
        /// The assignment operator.
        Iterator &operator=(const Iterator &rOther);
        /// The compare operator.
        bool operator==(const Iterator &rOther) const;
        /// The not equal operator.
        bool operator!=(const Iterator &rOther) const;
        /// The post increment operator.
        const Iterator &operator++(int);
        /// The pre-increment operator.
        Iterator &operator++();
        /// The post decrement operator.
        const Iterator &operator--(int);
        /// The pre-decrement operator.
        Iterator &operator--();
        /// The -> operator.
        T *operator->() const;
        /// The dereference operator.
        T &operator*() const;

    private:
        Node *mNode;
    };

private:
    class Node {
    public:
        T mItem;
        Node *mPrev;
        Node *mNext;

        Node(const T &rItem);
        void setNext(Node *pNode);
        Node *getNext() const;
        void setPrev(Node *pNode);
        Node *getPrev() const;
        T &getItem() const;
    };

    Node *mFist;
    Node *mLast;
    size_t mSize;
};

template <class T, class TAlloc>
inline TList<T, TAlloc>::TList() noexcept :
        mFist(nullptr),
        mLast(nullptr),
        mSize(0) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::TList(const TList<T, TAlloc> &rhs) :
        mFist(nullptr),
        mLast(nullptr),
        mSize(0) {
    copyFrom(rhs);
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::~TList() {
    clear();
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::copyFrom(const TList<T, TAlloc> &rhs) {
    clear();
    Node *current = rhs.mFist;
    if (nullptr == current) {
        return;
    }

    Node *prevNode = nullptr;
    for (Iterator it = rhs.begin(); it != rhs.end(); ++it) {
        mLast = new Node(current->mItem);
        if (!mFist) {
            mFist = mLast;
        }

        if (nullptr != prevNode) {
            mLast->setPrev(prevNode);
            prevNode->setNext(mLast);
        }
        prevNode = mLast;
        current = current->getNext();
    }

    mSize = rhs.mSize;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::addFront(const T &item) {
    Node *node = new Node(item);
    if (nullptr == mFist) {
        mFist = node;
        mLast = node;
    } else {
        node->setNext(mFist);
        mFist->setPrev(node);
        mFist = node;
    }
    ++mSize;

    return Iterator(node);
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::addBack(const T &item) {
    Node *node = new Node(item);
    if (nullptr == mFist) {
        mFist = node;
        mLast = node;
    } else {
        node->setPrev(mLast);
        mLast->setNext(node);
        mLast = node;
    }
    ++mSize;

    return Iterator(node);
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::removeFront() {
    Node *tmp = mFist->getNext();
    if (tmp) {
        tmp->setPrev(nullptr);
    }

    delete mFist;
    mFist = tmp;
    --mSize;
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::removeBack() {
    Node *last = mLast->getPrev();
    last->setNext(nullptr);
    delete mLast;
    mLast = last;
    --mSize;
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::front() const {
    assert(nullptr != mFist);

    return (mFist->mItem);
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::back() const {
    assert(nullptr != mLast);

    return (mLast->mItem);
}

template <class T, class TAlloc>
inline size_t TList<T, TAlloc>::size() const {
    return mSize;
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::isEmpty() const {
    return (0u == mSize);
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::clear() {
    if (isEmpty()) {
        return;
    }

    Node *current = mFist;
    while (mFist->getNext()) {
        current = mFist;
        mFist = mFist->getNext();
        delete current;
    }
    delete mFist;
    mFist = nullptr;
    mLast = nullptr;
    mSize = 0;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::begin() const {
    if (isEmpty()) {
        return end();
    }

    return Iterator(mFist);
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::end() const {
    return 0;
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::operator == (const TList<T, TAlloc> &rhs) const {
    if (mSize != rhs.mSize) {
        return false;
    }

    Iterator otherIt = rhs.begin();
    for (Iterator it = begin(); it != end(); ++it) {
        if (!(*it == *otherIt)) {
            return false;
        }
    }

    return true;
}

template <class T, class TAlloc>
inline TList<T, TAlloc> &TList<T, TAlloc>::operator=(const TList<T, TAlloc> &rhs) {
    if (*this == rhs) {
        return *this;
    }

    clear();
    for (Iterator it = rhs.begin(); it != rhs.end(); ++it) {
        addBack(*it);
    }

    return *this;
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Node::Node(const T &item) :
        mItem(item),
        mPrev(nullptr),
        mNext(nullptr) {
    // empty
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::Node::setNext(Node *pNode) {
    mNext = pNode;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Node *TList<T, TAlloc>::Node::getNext() const {
    return mNext;
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::Node::setPrev(Node *node) {
    mPrev = node;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Node *TList<T, TAlloc>::Node::getPrev() const {
    return mPrev;
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::Node::getItem() const {
    return mItem;
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::Iterator() :
        mNode(nullptr) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::Iterator(Node *node) :
        mNode(node) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::Iterator(const Iterator &rhs) :
        mNode(rhs.mNode) {
    // empty
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator=(const Iterator &rhs) {
    if (*this == rhs) {
        return *this;
    }

    mNode = rhs.mNode;

    return *this;
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::Iterator::operator==(const Iterator &rhs) const {
    return (mNode == rhs.mNode);
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::Iterator::operator!=(const Iterator &rhs) const {
    return (mNode != rhs.mNode);
}

template <class T, class TAlloc>
inline const typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator++(int) {
    assert(nullptr != mNode);

    Iterator inst(mNode);
    mNode = mNode->getNext();

    return inst;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator++() {
    assert(nullptr != mNode);

    mNode = mNode->getNext();

    return *this;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator const &TList<T, TAlloc>::Iterator::operator--(int) {
    assert(nullptr != mNode);
    
    Iterator inst(mNode);
    mNode = mNode->getPrev();

    return inst;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator--() {
    assert(nullptr != mNode);

    mNode = mNode->getPrev();

    return *this;
}

template <class T, class TAlloc>
inline T *TList<T, TAlloc>::Iterator::operator->() const {
    assert(nullptr != mNode);

    return &(mNode->mItem);
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::Iterator::operator*() const {
    assert(nullptr != mNode);

    return mNode->mItem;
}

} // Namespace cppcore
