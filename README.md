# Bit Vector

This project implements the **compact** and **static** bit vector
 data structure with constant rank support

## Current features

* Bit vector basic operations: bitread, bitset in **O(1)** time
* Constant time rank

## Not yet implemented features

* Constant time select

## Build

```
mkdir build
cd build
cmake ..
```

## Usage

* To use only the bit-vector without rank or select support include
 BitVector.h and use the class specified there

* For the bit-vector with rank support, include BVManager and instantiate
the class BVManager

* Link the .a static library file to your project (e.g. with
 cmake: target_link_libraries(your_project BitVector)