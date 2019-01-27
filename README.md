 The CppCore-Library
=====================
My collection of common tools for c++, which I have written the last couple of years 
for myself or libraries I worked on.
Feel free to use them or to show me, what I did wrong. I am also deploying my unit
tests, so doing a proof of my failures are easy :-).

How to build it:
----------------
At first you have to install CMake on your loal machine. After that start cmake
in the working directory of the CppCore library by typing:
> cmake build/CMakeLists.txt

Depending on your operation system CMake will generate a build environment for your 
special platform in the build directory.

[![Build Status](https://travis-ci.org/kimkulling/cppcore.png)](https://travis-ci.org/kimkulling/cppcore)

The library is pretty small and contains at this moment:

Common stuff:
-------------
- **CString**:          Simple string implementation without the big overhead of a std::string
- **Variant**:          Implements a variant to deal with arbitrary data types.
- **THash**:            A hash function to calculate hash values.

Containers:
----------
- **TStaticArray**:     A static template-based array.
- **TArray**:           A simple dynamic template-based array list, similar to std::vector.
- **TList**:            A double template-based linked list.
- **TQueue**:           A simple template-based FIFO queue.
- **THashMap**:         A key-value template-based hash map for easy lookup tables

Memory:
-------
- **TStackAllocator**:  A stack-based allocator, first allocation must be released at last ( FiFo-schema ).
- **TPoolAllocator**:   A pool-based allocator. Not much overhead and really fast. At the moment it is not supported to release single objects.

IO:
---
- **FileSystem**:      Common file-system abstractions for platform independent access and info.

Random:
-------
- **RandomGenerator**: A wrapper class to get random numbers. Currently supported are 
  + The standard c++ random generator, be careful if you want to reach a good distribution of 
    your random values
  + The Mersenne-Twister randome generator which provides a much better distribution of points

Used in...
----------
- OSRE ( aka Open-Source-Render-Experience ): https://github.com/kimkulling/osre
