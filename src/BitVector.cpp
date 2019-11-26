//
// Created by CristobalOsvaldoMira on 5/15/2019.
//

#include "BitVector.h"
#include <cstring>

namespace succinct_structures{
  template<typename bv_block_sz>
  BitVector<bv_block_sz>::BitVector(uint bv_size) : bv_size(bv_size) {
    remainder = bv_size % bv_block_bits;
    num_of_blocks = remainder == 0 ? bv_size / bv_block_bits : bv_size / bv_block_bits + 1;
    container = std::make_unique<uint[]>(num_of_blocks);
    clearContainer();
  }

  template<typename bv_block_sz>
  uint BitVector<bv_block_sz>::getBVSize() const {
    return bv_size;
  }

  template<typename bv_block_sz>
  void BitVector<bv_block_sz>::clearContainer() {
    std::memset(container.get(), 0, num_of_blocks);
  }

  template<typename bv_block_t>
  BitVector<bv_block_t>::BitVector(std::unique_ptr<bv_block_t[]> &&container, uint32_t bv_size) :
          container(std::move(container)), bv_size(bv_size) {
    remainder = bv_size % bv_block_bits;
    num_of_blocks = remainder == 0 ? bv_size / bv_block_bits : bv_size / bv_block_bits + 1;
  }


}