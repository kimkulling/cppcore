# Memory - Allocators and Tools
The Memory classes provides you a list of wrapper around typical tooles like *memset*. And it offers you some special allocators if the default allocator is not fast enough for you

## CPPCore::TDefaultAllocator
This class implements a default allocation as you know it when using new and delete. This allocator is used as the default 
allocation scheme in all containers.

## CPPCore::TPoolAllocator
This allocator can be use to create an initial pool of object at the program startup. 

## CPPCore::TScratchAllocator
### Introduction
The scratch allocator preallocates a memory block which can be used in your program. You do not have to deallocate any of the allocations. 
This will be done when clearing the allocator. All allocations will be invalidated.

### Usecases
Common use cases include:
- Temporary allocations in algorithms (e.g., path finding, sorting)
- Frame-based memory management in games
- Scratch space for parsing and serialization
- Short-lived computational tasks with multiple dynamic allocations

### Examples
```cpp
#include <Memory/TScratchAllocator.h>

using namespace ::cppcore;

int main() {
    // Will work
    ScratchAllocator myAllocator(1024);
    char *ptr1 = myAllocator.alloc(512);
    assert(ptr1 != nullptr);

    // Overrange shall get catched
    char *ptr2 = myAllocator.alloc(600);
    assert(ptr2 == nullptr);

    return 0;
}
```

## CPPCore::TStackAllocator
The stack allocator preallocates a memory block which can be used in your program. When deallocating your memory you have to follow the first-in last-out rule.
