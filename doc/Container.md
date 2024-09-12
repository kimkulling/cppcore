# Container

## CPPCore::TArray
### Introduction
The TArray template class implements a simple dynamic array. You can let the array 
grow and shring during runtime.

### Usecases
- Use this if you need to work with arrays which size are dynamic.
  
# Examples
```cpp
#include <Container/TArray.h>

using IntArray = CPPCore::TArray<int>;

int main() {
    IntArray intArray;
    intArray.add(1);
    intArray.add(2);
    
    return 0;
}
```

## CPPCore::TStaticArray
### Introduction
The TStaticArray template class a static array with bound checks during runtime. 
The dimension of the array will be set during compile time. 

### Usecases
- Use this for any kind of arrays with a fixed size.
- Access like a raw error with more compile-time and -runtime checks.

### Examples
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

## CPPCore::TList
### Introduction
The TList template class implements a double linked list. Each node will be managed
by links to its previous node and the next node. 

### Usecases
- You can use this for any kind of double-linked lists

### Examples
```cpp
#include <Container/TListy.h>

using namespace CPPCore;

int main() {
    TList<float> listTest;
    listTest.addBack( 1.0f );
    listTest.addBack( 2.0f );
    listTest.addBack( 3.0f );

    listTest.addFrone(0.0f);

    return 0;
}
```

## CPPCore::TQueue
The TQueue template class implements a simple queue. You can use it to enque and dequeue 
items. The ordering is Last-in Last-out.

## CPPCore::THashMap
The THashMap template class implements a hash map with collision lists for double calculated
hash values. This container can be used for 0(1) access times when no collisions are there.
