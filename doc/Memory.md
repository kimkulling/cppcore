# Memory - Allocators and Tools
The Memory classes provides you a list of wrapper around typical tooles like *memset*. And it offers you some special allocators if the default allocator is not fast enough for you

## CPPCore::TDefaultAllocator
This class implements a default allocation as you know it when using new and delete. This allocator is used as the default 
allocation scheme in all containers.

## CPPCore::TPoolAllocator
This allocator can be use to create an initial pool of object at the program startup. 

## CPPCore::TStackAllocator
The stack allocator preallocates a memory block which can be used in your program. When deallocating your memory you have to follow the first-in last-out rule.
