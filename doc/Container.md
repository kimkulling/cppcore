# Container

## CPPCore::TArray
The TArray template class implements a simple dynamic array. You can let the array 
grow and shring during runtime.

```cpp
#include <Container/TStaticArray.h>

using IntArray = CPPCore::TStaticArray<int, 2>;

int main() {
    IntArray intArray;
    intArray[0] = 1;
    intArray[2] = 1;
    
    return 0;
}
```

## CPPCore::TStaticArray
The TStaticArray template class a static array with bound checks during runtime. 
The dimension of the array will be set during compile time.

## CPPCore::TList
The TList template class implements a double linked list. Each node will be managed
by links to its previous node and the next node. 

## CPPCore::TQueue
The TQueue template class implements a simple queue. You can use it to enque and dequeue 
items. The ordering is Last-in Last-out.

## CPPCore::THashMap
The THashMap template class implements a hash map with collision lists for double calculated
hash values. This container can be used for 0(1) access times when no collisions are there.
