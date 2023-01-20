# The CPP-Core Library

## Introduction
This library is my personal collection of c++ sources which I have used in other projects. 
I have released them as OpenSource to make it possible for others to se it as well.

## Getting started
To work with the library you will need:
- cmake Version 3.10 or higher
- Visual Studio 2019 or higher
- G++ or Clang

Get the library from github. When you have downloaded the source navigate into the source folder and follow these steps:
```
cmake CMakeLists 
cmake --build .
```
# Feature list
The library is pretty small and contains at this moment:

## Common stuff
* **Variant**:          Implements a variant to deal with arbitrary data types.
* **THash**:            A hash function to calculate hash values.
* **TOptional**:        Implements an optional value.
* **TBitField**:        Implements a simple bitfield.

## Containers
* **TStaticArray**:     A static template-based array.
* **TArray**:           A simple dynamic template-based array list, similar to std::vector. [Examples can be found here](https://github.com/kimkulling/cppcore/blob/master/test/container/TArrayTest.cpp)
* **TList**:            A double template-based linked list. [Examples can be found here](https://github.com/kimkulling/cppcore/blob/master/test/container/TListTest.cpp) 
* **TQueue**:           A simple template-based FIFO queue.
* **THashMap**:         A key-value template-based hash map for easy lookup tables.

[Detailed Doc: Containers](./Container.md)  


## Memory
* **TStackAllocator**:  A stack-based allocator, first allocation must be released at last ( FiFo-schema ).
* **TPoolAllocator**:   A pool-based allocator. Not much overhead and really fast. At the moment it is not supported to release single objects.

[Detailed Doc:Memory classes](./Memory.md)  


## Filesystem
* **FileSystem**:      Common file-system abstractions for platform independent access and info.

## Random-Number generators
* **RandomGenerator**: A wrapper class to get random numbers. Currently supported are 
   * The standard c++ random generator, be careful if you want to reach a good distribution of 
     your random values
   * The Mersenne-Twister randome generator which provides a much better distribution of points
