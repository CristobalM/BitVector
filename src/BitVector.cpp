//
// Created by CristobalOsvaldoMira on 5/15/2019.
//

#include "BitVector.h"
#include <cstring>

namespace succinct_structures{
  template<typename bv_block_t>
  BitVector<bv_block_t>::BitVector(uint bv_size) : bv_size(bv_size) {
    remainder = bv_size % bv_block_bits;
    num_of_blocks = remainder == 0 ? bv_size / bv_block_bits : bv_size / bv_block_bits + 1;
    container = std::make_unique<bv_block_t[]>(num_of_blocks);
    clearContainer();
  }

  template<typename bv_block_t>
  uint BitVector<bv_block_t>::getBVSize() const {
    return bv_size;
  }

  template<typename bv_block_t>
  void BitVector<bv_block_t>::clearContainer() {
    std::memset(container.get(), 0, num_of_blocks);
  }

  template<typename bv_block_t>
  BitVector<bv_block_t>::BitVector(std::unique_ptr<bv_block_t[]> &&container, uint32_t bv_size) :
          container(std::move(container)), bv_size(bv_size) {
    remainder = bv_size % bv_block_bits;
    num_of_blocks = remainder == 0 ? bv_size / bv_block_bits : bv_size / bv_block_bits + 1;
  }

  template<typename bv_block_t>
  bv_block_t *BitVector<bv_block_t>::bvInternal() {
    return container.get();
  }


}