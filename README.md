 The CppCore-Library
=====================
My collection of common tools for c++, which I have written the last couple of years 
for myself or libraries I worked on.
Feel free to use them or to show me, what I did wrong. I am also deploying my unit
tests, so doing a proof of my failures are easy :-).

Documentation
-------------

How to build it:
----------------
At first you have to install CMake on your loal machine. After that start cmake
in the working directory of the CppCore library by typing:
> cmake build/CMakeLists.txt

Depending on your operation system CMake will generate a build environment for your 
special platform in the build directory.

If you are using Visual Studio on windows a solution file will be generated.

If you are using Linux, you can build it with the make-command:
> make -j3

[![Build status](https://github.com/kimkulling/cppcore/actions/workflows/cmake.yml/badge.svg)](https://github.com/kimkulling/cppcore/actions/workflows/cmake.yml)


The library is pretty small and contains at this moment:

Common stuff
------------
* **Variant**:          Implements a variant to deal with arbitrary data types.
* **THash**:            A hash function to calculate hash values.
* **TOptional**:        Implements an optional value.
* **TBitField**:        Implements a simple bitfield.
* **Variant**:          Implements a variant type.

Containers
----------
* **TStaticArray**:     A static template-based array.
* **TArray**:           A simple dynamic template-based array list, similar to std::vector. [Examples can be found here](https://github.com/kimkulling/cppcore/blob/master/test/container/TArrayTest.cpp)
* **TList**:            A double template-based linked list. [Examples can be found here](https://github.com/kimkulling/cppcore/blob/master/test/container/TListTest.cpp) 
* **TQueue**:           A simple template-based FIFO queue.
* **THashMap**:         A key-value template-based hash map for easy lookup tables

Memory
------
* **TStackAllocator**:  A stack-based allocator, first allocation must be released at last ( FiFo-schema ).
* **TPoolAllocator**:   A pool-based allocator. Not much overhead and really fast. At the moment it is not supported to release single objects.

IO-Filesystem
-------------
* **FileSystem**:      Common file-system abstractions for platform independent access and info.

Random
------
* **RandomGenerator**: A wrapper class to get random numbers. Currently supported are 
   * The standard c++ random generator, be careful if you want to reach a good distribution of 
     your random values
   * The Mersenne-Twister randome generator which provides a much better distribution of points

Used in...
----------
* OSRE (aka Open-Source-Render-Experience): [The OSRE Repo](https://github.com/kimkulling/osre)
* Openddl-Parser: [The OpenDDL-Parser Repo](https://github.com/kimkulling/openddl-parser)

How to contribute
-----------------
See [How to contribute](CONTRIBUTING.md)
