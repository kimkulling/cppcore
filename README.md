 The CppCore Library
=====================
My collection of common tools for c++, which I have written the last couple of years.
Feel free to use them or to show me, what I did wrong. I am also deploying my unit
tests, so doing a proof of my failures are easy :-).

How to build it:
----------------
At first you have to install CMake on your loal machine. After that start cmake
in the working directory of the CppCore library by typing:
> cmake build/CMakeLists.txt

Depending on your operation system CMake will generate a build environment for your special platform in the build directory.

[![Build Status](https://travis-ci.org/kimkulling/cppcore.png)](https://travis-ci.org/kimkulling/cppcore)

The library is pretty small and contains at this moment:

Common stuff:
-------------
- CString  Simple string implementation without the big overhead of a std::string
- Variant  Implements a variant to deal with arbitrary data types.
- THash    A hash function to calculate hash values.

Containers:
----------
- TArray  A simple dynamic array.
- TList   A double linked list.
- TQueue  A simple queue.
- THashMap  A key-value hash map for easy lookup tables
