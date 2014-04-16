 The CppCore Library
=====================
Supports common core services in written in C++11.

How to build it:
----------------
At first you have to install CMake on your loal machine. Aftr that start cmake in the working directory of the CppCore library by typing:
> cmake build/CMakeLists.txt

Depending on your operation system CMake will generate a build environment for your special platform in the build directory.

[![Build Status](https://travis-ci.org/kimkulling/cppcore.png)](https://travis-ci.org/kimkulling/cppcore)

Common stuff:
-------------
- CString  Simple string implementation
- Variant  Implements a variant to deal with arbitrary data type.

Container:
----------
- TArray  A simple dynamic array.
- TList   A double linked list.
- TQueue  A simple queue.
