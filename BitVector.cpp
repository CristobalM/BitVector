//
// Created by CristobalOsvaldoMira on 5/15/2019.
//

#include "BitVector.h"

succinct_structures::BitVector::BitVector(uint bv_size) : bv_size(bv_size) {
    remainder = bv_size % INT_BITS;
    num_of_blocks = remainder == 0 ? bv_size / INT_BITS : bv_size / INT_BITS + 1;
    container = std::make_unique<uint[]>(num_of_blocks);
    clearContainer();
}

uint succinct_structures::BitVector::getBVSize() const {
    return bv_size;
}

void succinct_structures::BitVector::clearContainer() {
    for (uint i = 0; i < num_of_blocks; i++) {
        container.get()[i] = 0;
    }
}
