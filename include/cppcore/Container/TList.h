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
    bool operator==(const TList<T, TAlloc> &rOther) const;

    ///	@brief	Assignment operator.
    TList<T, TAlloc> &operator=(const TList<T, TAlloc> &rOther);

    //---------------------------------------------------------------------------------------------
    ///	@class	Iterator
    ///	@brief	Access implementation class.
    //---------------------------------------------------------------------------------------------
    class Iterator {
    public:
        ///	The default class constructor.
        Iterator();
        ///	Constructor with a node instance.
        Iterator(Node *pNode);
        ///	The copy constructor.
        Iterator(const Iterator &rOther);
        ///	The destructor, non virtual.
        ~Iterator();
        ///	The assignment operator.
        Iterator &operator=(const Iterator &rOther);
        ///	The compare operator.
        bool operator==(const Iterator &rOther) const;
        ///	The not equal operator.
        bool operator!=(const Iterator &rOther) const;
        ///	The post increment operator.
        const Iterator &operator++(int);
        ///	The pre-increment operator.
        Iterator &operator++();
        ///	The post decrement operator.
        const Iterator &operator--(int);
        ///	The pre-decrement operator.
        Iterator &operator--();
        ///	The -> operator.
        T *operator->() const;
        ///	The dereference operator.
        T &operator*() const;

    private:
        Node *m_pNode;
    };

private:
    class Node {
    public:
        T m_Item;
        Node *m_pPrev;
        Node *m_pNext;

        Node(const T &rItem);
        void setNext(Node *pNode);
        Node *getNext() const;
        void setPrev(Node *pNode);
        Node *getPrev() const;
        T &getItem() const;
    };

    Node *m_pFist;
    Node *m_pLast;
    size_t m_size;
};

template <class T, class TAlloc>
inline TList<T, TAlloc>::TList() noexcept :
        m_pFist(nullptr),
        m_pLast(nullptr),
        m_size(0) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::TList(const TList<T, TAlloc> &rhs) :
        m_pFist(nullptr),
        m_pLast(nullptr),
        m_size(0) {
    copyFrom(rhs);
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::~TList() {
    clear();
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::copyFrom(const TList<T, TAlloc> &rhs) {
    clear();
    Node *pCurrent = rhs.m_pFist;
    if (nullptr == pCurrent) {
        return;
    }

    Node *pPrevNode = nullptr;
    for (Iterator it = rhs.begin(); it != rhs.end(); ++it) {
        m_pLast = new Node(pCurrent->m_Item);
        if (!m_pFist) {
            m_pFist = m_pLast;
        }

        if (nullptr != pPrevNode) {
            m_pLast->setPrev(pPrevNode);
            pPrevNode->setNext(m_pLast);
        }
        pPrevNode = m_pLast;
        pCurrent = pCurrent->getNext();
    }

    m_size = rhs.m_size;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::addFront(const T &item) {
    Node *pNode = new Node(item);
    if (nullptr == m_pFist) {
        m_pFist = pNode;
        m_pLast = pNode;
    } else {
        pNode->setNext(m_pFist);
        m_pFist->setPrev(pNode);
        m_pFist = pNode;
    }
    ++m_size;

    return Iterator(pNode);
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::addBack(const T &item) {
    Node *pNode = new Node(item);
    if (nullptr == m_pFist) {
        m_pFist = pNode;
        m_pLast = pNode;
    } else {
        pNode->setPrev(m_pLast);
        m_pLast->setNext(pNode);
        m_pLast = pNode;
    }
    ++m_size;

    return Iterator(pNode);
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::removeFront() {
    Node *pTmp = m_pFist->getNext();
    if (pTmp) {
        pTmp->setPrev(nullptr);
    }

    delete m_pFist;
    m_pFist = pTmp;
    --m_size;
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::removeBack() {
    Node *pLast = m_pLast->getPrev();
    pLast->setNext(nullptr);
    delete m_pLast;
    m_pLast = pLast;
    --m_size;
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::front() const {
    assert(nullptr != m_pFist);

    return (m_pFist->m_Item);
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::back() const {
    assert(nullptr != m_pLast);

    return (m_pLast->m_Item);
}

template <class T, class TAlloc>
inline size_t TList<T, TAlloc>::size() const {
    return m_size;
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::isEmpty() const {
    return (0 == m_size);
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::clear() {
    if (isEmpty()) {
        return;
    }

    Node *pCurrent = m_pFist;
    while (m_pFist->getNext()) {
        pCurrent = m_pFist;
        m_pFist = m_pFist->getNext();
        delete pCurrent;
    }
    delete m_pFist;
    m_pFist = nullptr;
    m_pLast = nullptr;
    m_size = 0;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::begin() const {
    if (isEmpty()) {
        return end();
    }

    return Iterator(m_pFist);
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator TList<T, TAlloc>::end() const {
    return 0;
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::operator == (const TList<T, TAlloc> &rhs) const {
    if (m_size != rhs.m_size) {
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
        m_Item(item),
        m_pPrev(nullptr),
        m_pNext(nullptr) {
    // empty
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::Node::setNext(Node *pNode) {
    m_pNext = pNode;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Node *TList<T, TAlloc>::Node::getNext() const {
    return m_pNext;
}

template <class T, class TAlloc>
inline void TList<T, TAlloc>::Node::setPrev(Node *pNode) {
    m_pPrev = pNode;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Node *TList<T, TAlloc>::Node::getPrev() const {
    return m_pPrev;
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::Node::getItem() const {
    return m_Item;
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::Iterator() :
        m_pNode(nullptr) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::Iterator(Node *pNode) :
        m_pNode(pNode) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::Iterator(const Iterator &rhs) :
        m_pNode(rhs.m_pNode) {
    // empty
}

template <class T, class TAlloc>
inline TList<T, TAlloc>::Iterator::~Iterator() {
    // empty
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator=(const Iterator &rhs) {
    if (*this == rhs) {
        return *this;
    }

    m_pNode = rhs.m_pNode;

    return *this;
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::Iterator::operator==(const Iterator &rhs) const {
    return (m_pNode == rhs.m_pNode);
}

template <class T, class TAlloc>
inline bool TList<T, TAlloc>::Iterator::operator!=(const Iterator &rhs) const {
    return (m_pNode != rhs.m_pNode);
}

template <class T, class TAlloc>
inline const typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator++(int) {
    assert(nullptr != m_pNode);

    Iterator inst(m_pNode);
    m_pNode = m_pNode->getNext();

    return inst;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator++() {
    assert(nullptr != m_pNode);

    m_pNode = m_pNode->getNext();

    return *this;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator const &TList<T, TAlloc>::Iterator::operator--(int) {
    assert(nullptr != m_pNode);
    
    Iterator inst(m_pNode);
    m_pNode = m_pNode->getPrev();

    return inst;
}

template <class T, class TAlloc>
inline typename TList<T, TAlloc>::Iterator &TList<T, TAlloc>::Iterator::operator--() {
    assert(nullptr != m_pNode);

    m_pNode = m_pNode->getPrev();

    return *this;
}

template <class T, class TAlloc>
inline T *TList<T, TAlloc>::Iterator::operator->() const {
    assert(nullptr != m_pNode);

    return &(m_pNode->m_Item);
}

template <class T, class TAlloc>
inline T &TList<T, TAlloc>::Iterator::operator*() const {
    assert(nullptr != m_pNode);

    return m_pNode->m_Item;
}

} // Namespace cppcore
