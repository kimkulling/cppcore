# Common
## THash - Simple hash function
### Introduction
This class implement a generic hash function, used for mapping string onto a dedicated type.

### Usecases
- USer wants to compare two string much faster, just calculate their hashes and do a comparison for them.

### Examples
```cpp
#include <cppcore/Common/Hash.h>
#include <iostream>

using UiHash = CPPCore::THash<unsigned int>;

void main() {
    // Simple, just 10
    UiHash myHash2(10U);
    std::cout << "Value " << myHash2.hashValue() << std::endl;

    // Will calculate the hash for string test 
    UiHash myHash3("test", 7);
    std::cout << "Hash for string test is "<< myHash3.hashValue() << endl;
}
```

## TBitField 
### Introduction
A little class to help working with bitsets. 

### Usecases
You need to manage singe bits and you want to avoid dealing with the OR-, AND- and XOR-operations provided by c.

### Examples
```cpp
#include <cppcore/Common/Hash.h>
#include <iostream>

void main() {
    TBitField<uint32_t> bitfield(0);

    // The first bit is set
    bitfield.setBit(1);
    if (bitfield.getBit(1)) std::cout "First bit is set" << std:endl;

    bitfield.clearBit(1);
    if (!bitfield.getBit(1)) std::cout "First bit is not set" << std:endl;
}
```

## TOptional
### Introduction
### Usecases
### Examples

## TSharedPtr
### Introduction
### Usecases
### Examples

## Variant
### Introduction
### Usecases
### Examples
