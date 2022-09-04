# The CppCore-Library
My collection of common tools for c++, which I have written the last couple of years 
for myself or libraries I worked on.
Feel free to use them or to show me, what I did wrong. I am also deploying my unit
tests, so doing a proof of my failures are easy :-).

# Documentation
[The documentation](doc/index.md)

# Build status
[![Build status](https://github.com/kimkulling/cppcore/actions/workflows/cmake.yml/badge.svg)](https://github.com/kimkulling/cppcore/actions/workflows/cmake.yml)

# Feature list
The library is pretty small and contains at this moment:

## Common stuff
* **Variant**:          Implements a variant to deal with arbitrary data types.
* **THash**:            A hash function to calculate hash values.
* **TOptional**:        Implements an optional value.
* **TBitField**:        Implements a simple bitfield.
* **Variant**:          Implements a variant type.

## Containers
* **TStaticArray**:     A static template-based array.
* **TArray**:           A simple dynamic template-based array list, similar to std::vector. [Examples can be found here](https://github.com/kimkulling/cppcore/blob/master/test/container/TArrayTest.cpp)
* **TList**:            A double template-based linked list. [Examples can be found here](https://github.com/kimkulling/cppcore/blob/master/test/container/TListTest.cpp) 
* **TQueue**:           A simple template-based FIFO queue.
* **THashMap**:         A key-value template-based hash map for easy lookup tables

## Memory
* **TStackAllocator**:  A stack-based allocator, first allocation must be released at last ( FiFo-schema ).
* **TPoolAllocator**:   A pool-based allocator. Not much overhead and really fast. At the moment it is not supported to release single objects.

## Filesystem
* **FileSystem**:      Common file-system abstractions for platform independent access and info.

## Random-Number generators
* **RandomGenerator**: A wrapper class to get random numbers. Currently supported are 
   * The standard c++ random generator, be careful if you want to reach a good distribution of 
     your random values
   * The Mersenne-Twister randome generator which provides a much better distribution of points

## Used in...
* OSRE (aka Open-Source-Render-Experience): [The OSRE Repo](https://github.com/kimkulling/osre)
* Openddl-Parser: [The OpenDDL-Parser Repo](https://github.com/kimkulling/openddl-parser)

## How to contribute
See [How to contribute](CONTRIBUTING.md)
