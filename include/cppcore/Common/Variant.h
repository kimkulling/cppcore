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

#include <string.h>
#include <cassert>
#include <string>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		Variant
///	@ingroup	CPPCore
///
///	@brief	This class can be used to store integer or float data with a dynamical binding.
///
/// It stores the type information at the runtime instead of checking this to compile-time. So it is
///	possible to pass integer or float arguments dynamically to arbitrary customers without changing
///	the calling signature of the used interface.
///	If you are trying to get a float value even if the instance stores currently an integer value
///	on a debug build an assertion will be thrown. On a release build it is possible to get values,
///	but an error will be logged.
//-------------------------------------------------------------------------------------------------
class Variant {
public:
    ///	@enum	Type
    ///	@brief	This enum describes the variable type of the variant instance.
    enum Type {
        None  = -1,     ///< Initialization value.
        Byte,           ///< 1 Byte type.
        Int,            ///< Integer value.
        Int3,           ///< Integer vector, 3 components.
        Int4,           ///< Integer vector, 4 components.
        Float,          ///< Float value.
        Float3,         ///< Float vector, 3 components.
        Float4,         ///< Float vector, 4 components.
        Float4x4,       ///< Float matrix, 4 x 4 components.
        String,         ///< String value.
        Boolean,        ///< Boolean type.
        MaxType         ///< Upper limit.
    };

    ///	@brief	The class default constructor.
    Variant();

    ///	@brief	The class constructor with type information and data. A data buffer will be used to pass
    ///			the data. The size of the buffer will be check on runtime as well.
    ///	@param	type		Type enumeration.
    ///	@param	pData		Pointer to the data buffer.
    ///	@param	numItems	Size of the data buffer.
    Variant(Type type, void *pData, size_t numItems);

    /// @brief  The class constructor with a boolean value.
    /// @param  value       [in] The boolean value.
    explicit Variant(bool value);

    ///	@brief	The class copy constructor.
    ///	@param	other	[in] Other instance to copy from.
    Variant(const Variant &other);

    ///	@brief	The class destructor.
    ~Variant();

    ///	@brief	Returns the type of the instance.
    ///	@return	TYpe enum of the current dynamic type of the instance.
    Type getType() const;

    /// @brief  Will return the size in bytes of the stored type.
    /// @return The size in bytes.
    size_t getSize() const;

    ///	@brief  Will return a raw pointer showing to the data.
    /// @return The pointer.
    void *getPtr() const;

    /// @brief  Will set the payload to the given value.
    /// @param  value   [in] The new given payload.
    void setByte(unsigned char value);

    /// @brief  Will return the current payload as a byte value.
    /// @return The byte value.
    unsigned char getByte() const;

    ///	@brief	Sets a new integer value, old values will be released and destroyed.
    ///	@param	val		[in] A new integer value.
    void setInt(int val);

    ///	@brief	Returns the integer value of the instance.
    ///	@return	The stored integer value will be returned.
    int getInt() const;

    ///	@brief	Set a new integer vector, the old data will be released and destroyed.
    ///	@param	val1	Component 1, integer.
    ///	@param	val2	Component 2, integer.
    ///	@param	val3	Component 3, integer.
    void setInt3(int val1, int val2, int val3);

    ///	@brief	Returns a pointer to the first element of the integer vector. You can access the 2
    ///			following with the index operator for instance.
    ///	@return	Pointer to the first component of th vector array.
    int *getInt3() const;

    ///	@brief	Set a new integer vector, the old data will be released and destroyed.
    ///	@param	val1	Component 1, integer.
    ///	@param	val2	Component 2, integer.
    ///	@param	val3	Component 3, integer.
    ///	@param	val4	Component 3, integer.
    void setInt4(int val1, int val2, int val3, int val4);

    ///	@brief	Returns a pointer to the first element of the integer vector. You can access the 3
    ///			following with the index operator for instance.
    ///	@return	Pointer to the first component of th vector array.
    int *getInt4() const;

    ///	@brief	Returns the float value of the instance.
    ///	@param	val		A new float value.
    void setFloat(float val);

    ///	@brief	Returns the float value of the instance.
    ///	@return	The stored float value will be returned.
    float getFloat() const;

    ///	@brief	Set a new float vector, the old data will be released and destroyed.
    ///	@param	val1	Component 1, float.
    ///	@param	val2	Component 2, float.
    ///	@param	val3	Component 3, float.
    void setFloat3(float val1, float val2, float val3);

    ///	@brief	Returns a pointer to the first element of the float vector. You can access the 2
    ///			following with the index operator for instance.
    ///	@return	Pointer to the first component of th vector array.
    float *getFloat3() const;

    ///	@brief	Set a new float vector, the old data will be released and destroyed.
    ///	@param	val1	Component 1, float.
    ///	@param	val2	Component 2, float.
    ///	@param	val3	Component 3, float.
    ///	@param	val4	Component 4, float.
    void setFloat4(float val1, float val2, float val3, float val4);

    ///	@brief	Returns a pointer to the first element of the float vector. You can access the 3
    ///			following with the index operator for instance.
    ///	@return	Pointer to the first component of th vector array.
    float *getFloat4() const;

    ///	@brief	Assigns a new float 4x4 item.
    ///	@param	pData	[in] A float pointer to the 4x4 buffer.
    void setFloat4x4(float *pData);

    ///	@brief	Returns the pointer to the float 4x4 value.
    ///	@return	A pointer showing to the 4x4 float item.
    float *getFloat4x4() const;

    ///	@brief	Sets a string value.
    ///	@param	value   The new string value.
    void setStdString(const std::string &value);

    ///	@brief	Returns a constant reference to the string value.
    ///	@return	A pointer showing to the data buffer of the string.
    const char *getString() const;

    /// @brief Will set a new bool value.
    /// @param value The new bool value.
    void setBool(bool value);

    /// @brief  Will return the bool value.
    /// @return The bool value.
    bool getBool() const;

    ///	@brief	Clears the variant data, type will set back to None.
    void clear();

    /// @brief  Static helper method to generate a new variant storing a std::string.
    /// @param  value   The std::string data.
    /// @return Thew new created variant as a pointer.
    static Variant *createFromString(const std::string &value);

    ///	@brief	Operator implementations.
    bool operator==(const Variant &rOther) const;
    Variant &operator=(const Variant &rOther);

protected:
    /// @brief  Performs a validation.
    /// @param type         The type to validate for
    /// @param numItems     The number of items to validate.
    /// @return true, if data is valid.
    bool isValid(Type type, size_t numItems) const;

    /// @brief Will reserve a buffer for the requested types.
    /// @param type     The requested type.
    /// @param size     The number of items.
    void reserve(Type type, size_t size);

private:
    Type m_Type;
    size_t m_BufferSize;
    void *m_pData;
};

inline Variant::Variant() :
        m_Type(None),
        m_BufferSize(0),
        m_pData(nullptr) {
    // empty
}

inline Variant::Variant(Type type, void *pData, size_t numItems) :
        m_Type(None),
        m_BufferSize(0),
        m_pData(nullptr) {
    if (isValid(type, numItems)) {
        size_t size = 0;
        m_Type = type;
        if (type == String) {
            assert(nullptr != pData);
            std::string str((char *)pData);
            setStdString(str);
        } else {
            reserve(type, size);
            ::memcpy(m_pData, pData, m_BufferSize);
        }
    }
}

inline Variant::Variant(bool value) :
        m_Type(Boolean),
        m_BufferSize(0),
        m_pData(nullptr) {
    reserve(Boolean, 0);
    ::memcpy(m_pData, &value, m_BufferSize);
}

inline Variant::Variant(const Variant &other) :
        m_Type(None),
        m_BufferSize(0),
        m_pData(nullptr) {
    m_Type = other.m_Type;
    if (String == m_Type) {
        setStdString(other.getString());
    } else {
        reserve(m_Type, 0);
        ::memcpy(m_pData, other.m_pData, m_BufferSize);
    }
}

inline Variant::~Variant() {
    clear();
}

inline Variant::Type Variant::getType() const {
    return m_Type;
}

inline size_t Variant::getSize() const {
    return m_BufferSize;
}

inline void *Variant::getPtr() const {
    return m_pData;
}

inline void Variant::setByte(unsigned char value) {
    clear();
    reserve(Byte, 0);
    ::memcpy(m_pData, &value, sizeof(unsigned char));
}

inline unsigned char Variant::getByte() const {
    return (*reinterpret_cast<unsigned char *>(m_pData));
}

inline void Variant::setInt(int val) {
    clear();
    reserve(Int, 0);
    ::memcpy(m_pData, &val, sizeof(int));
}

inline int Variant::getInt() const {
    assert(m_Type == Int);

    return (*reinterpret_cast<int *>(m_pData));
}

inline void Variant::setInt3(int val1, int val2, int val3) {
    clear();
    reserve(Int3, 0);
    int *ptr = reinterpret_cast<int *>(m_pData);
    *ptr = val1;
    ++ptr;
    *ptr = val2;
    ++ptr;
    *ptr = val3;
}

inline int *Variant::getInt3() const {
    assert(m_Type == Int3);
    return (reinterpret_cast<int *>(m_pData));
}

inline void Variant::setInt4(int val1, int val2, int val3, int val4) {
    clear();
    reserve(Int4, 0);
    int *ptr = reinterpret_cast<int *>(m_pData);
    *ptr = val1;
    ++ptr;
    *ptr = val2;
    ++ptr;
    *ptr = val3;
    ++ptr;
    *ptr = val4;
}

inline int *Variant::getInt4() const {
    assert(m_Type == Int4);

    return (reinterpret_cast<int *>(m_pData));
}

inline void Variant::setFloat(float val) {
    clear();
    reserve(Float, 0);
    ::memcpy(m_pData, &val, sizeof(float));
}

inline float Variant::getFloat() const {
    assert(m_Type == Float);
    return (*reinterpret_cast<float *>(m_pData));
}

inline void Variant::setFloat3(float val1, float val2, float val3) {
    clear();
    reserve(Float3, 0);
    float *ptr = reinterpret_cast<float *>(m_pData);
    *ptr = val1;
    ++ptr;
    *ptr = val2;
    ++ptr;
    *ptr = val3;
}

inline float *Variant::getFloat3() const {
    assert(m_Type == Float3);
    return (reinterpret_cast<float *>(m_pData));
}

inline void Variant::setFloat4(float val1, float val2, float val3, float val4) {
    clear();
    reserve(Float4, 0);
    float *ptr = reinterpret_cast<float *>(m_pData);
    *ptr = val1;
    ++ptr;
    *ptr = val2;
    ++ptr;
    *ptr = val3;
    ++ptr;
    *ptr = val4;
}

inline float *Variant::getFloat4() const {
    assert(m_Type == Float4);
    return (reinterpret_cast<float *>(m_pData));
}

inline void Variant::setFloat4x4(float *pData) {
    clear();
    reserve(Float4x4, 0);
    ::memcpy(m_pData, pData, sizeof(float) * 16);
}

inline float *Variant::getFloat4x4() const {
    assert(m_Type == Float4x4);
    return (reinterpret_cast<float *>(m_pData));
}

inline void Variant::setStdString(const std::string &value) {
    clear();
    m_Type = String;
    if (value.empty()) {
        m_pData = nullptr;
        m_BufferSize = 0;
    }
    m_BufferSize = sizeof(char) * (value.size() + 1);
    m_pData = (char*) ::malloc(m_BufferSize);
    if (m_pData == nullptr) {
        clear();
        return;
    }

    ::memcpy(m_pData, value.c_str(), sizeof(char) * value.size());
    char *ptr = (char *) m_pData;
    ptr[value.size()] = '\0';
}

inline const char *Variant::getString() const {
    assert(m_Type == String);

    return static_cast<char *>(m_pData);
}

inline void Variant::setBool(bool value) {
    clear();
    reserve(Boolean, 0);
    ::memcpy(m_pData, &value, sizeof(bool));
}

inline bool Variant::getBool() const {
    assert(Boolean == m_Type);

    return (*reinterpret_cast<bool *>(m_pData));
}

inline void Variant::clear() {
    if (None == m_Type) {
        return;
    }

    ::free(m_pData);
    m_pData = nullptr;
    m_Type = None;
}

inline Variant *Variant::createFromString( const std::string &value ) {
    Variant *v = new Variant();
    v->setStdString(value);

    return v;
}

inline bool Variant::operator==(const Variant &rOther) const {
    if (rOther.m_Type != m_Type) {
        return false;
    }

    if (rOther.m_BufferSize != m_BufferSize) {
        return false;
    }

    if (0 != ::memcmp(rOther.m_pData, m_pData, m_BufferSize)) {
        return false;
    }

    return true;
}

inline Variant &Variant::operator=(const Variant &rOther) {
    if (!(rOther == *this)) {
        m_Type = rOther.m_Type;
        reserve(m_Type, 0);
        ::memcpy(m_pData, rOther.m_pData, m_BufferSize);
    }

    return *this;
}

inline bool Variant::isValid(Type type, size_t numItems) const {
    bool res = false;
    if (type == Byte) {
        if (1 == numItems) {
            res = true;
        }
    } else if (type == Int || type == Float) {
        if (1 == numItems) {
            res = true;
        }
    } else if (type == Int3 || type == Float3) {
        if (3 == numItems) {
            res = true;
        }
    } else if (type == Int4 || type == Float4) {
        if (4 == numItems) {
            res = true;
        }
    } else if (type == String) {
        if (0 != numItems) {
            res = true;
        }
    } else if (type == None) {
        res = true;
    }

    return res;
}

inline void Variant::reserve(Type type, size_t size) {
    if (0 == size) {
        if (type == Int3) {
            size = sizeof(int) * 3;
        } else if (type == Float3) {
            size = sizeof(float) * 3;
        } else if (type == Int4) {
            size = sizeof(int) * 4;
        } else if (type == Float4) {
            size = sizeof(float) * 4;
        } else if (type == Float4x4) {
            size = sizeof(float) * 4 * 4;
        } else if (type == Byte) {
            size = sizeof(unsigned char);
        } else if (type == Int) {
            size = sizeof(int);
        } else if (type == Float) {
            size = sizeof(float);
        } else if (type == Boolean) {
            size = sizeof(bool);
        }
    }

    m_BufferSize = size;
    m_pData = ::malloc(size);
    m_Type = type;
}

} // Namespace cppcore
