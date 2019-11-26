//
// Created by CristobalOsvaldoMira on 5/15/2019.
//

#ifndef BITVECTOR_BITVECTOR_H
#define BITVECTOR_BITVECTOR_H

#include <string>

#include <memory>

#include <exception>

#include "CommonUtility.h"

namespace succinct_structures{
  template<typename bv_block_t = uint32_t >
  class BitVector{
  private:
    uint bv_size;
    uint remainder;
    uint num_of_blocks;

    static auto constexpr bv_block_bits = sizeof(bv_block_t) * 8;


    std::unique_ptr<bv_block_t[]> container;

    inline uint getBlockIndex(uint bitposition){
      return bitposition % bv_block_bits != 0 ? bitposition / bv_block_bits + 1 : bitposition / bv_block_bits;
    }

    inline uint getPositionInBlock(uint bitpositon) {
      return ((bitpositon - 1) % bv_block_bits) + 1;
    }

    inline uint ceilOfDiv(uint dividend, uint divisor){
      return (dividend / divisor) + (dividend % divisor == 0 ? 0 : 1);
    }

  public:
    explicit BitVector(uint bv_size);
    explicit BitVector(std::unique_ptr<bv_block_t> &&container, uint32_t bv_size);

    uint getBVSize() const;
    void clearContainer();

    inline uint read_block_pos(uint block_position){
      return container.get()[block_position - 1];
    }

    uint bitsread(uint starting_pos, uint ending_pos){
      if(ending_pos < starting_pos){
        return 0;
      }

      if(ending_pos - starting_pos + 1 > bv_block_bits){
        throw std::runtime_error("bitsread request is too big: " +
        std::to_string(ending_pos) + " - " + std::to_string(starting_pos) + " + 1 > " + std::to_string(bv_block_bits));
      }

      auto right_position_in_block = getPositionInBlock(ending_pos);
      auto left_block_index = ceilOfDiv(starting_pos, bv_block_bits);
      auto right_block_index = ceilOfDiv(ending_pos, bv_block_bits);

      if(left_block_index == right_block_index){
        auto right_block = read_block_pos(right_block_index);
        auto right_block_shifted = right_block >> ((bv_block_bits - right_position_in_block));

        auto result = (right_block_shifted) % (1 << (ending_pos - starting_pos + 1));
        return result;
      }

      auto left_prev_position_in_block = getPositionInBlock(starting_pos) - 1;

      auto right_block = read_block_pos(right_block_index);
      auto left_block = read_block_pos(left_block_index);

      return ((right_block >> (bv_block_bits - right_position_in_block + 1)) << 1) +
      (left_block % (1 << (bv_block_bits - left_prev_position_in_block))) * (1 << right_position_in_block);

    }

    inline bool bitread(uint bitposition){
      auto block_idx = getBlockIndex(bitposition);
      auto r = getPositionInBlock(bitposition);
      auto block = read_block_pos(block_idx); // read mode
      return ((block >> (bv_block_bits - r)) % 2) == 1;
    }

    inline void bitset(uint bitposition){
      if(bitread(bitposition)) return;
      auto block_idx = getBlockIndex(bitposition);
      auto &block = container.get()[block_idx - 1]; // write mode
      auto r = getPositionInBlock(bitposition);
      block += 1 << (bv_block_bits - r);
    }

    inline void bitclear(uint bitposition) {
      if(!bitread(bitposition)) return;
      auto block_idx = getBlockIndex(bitposition);
      auto &block = container.get()[block_idx - 1]; // write mode
      auto r = getPositionInBlock(bitposition);
      block -= 1 << (bv_block_bits - r);
    }

    uint getBitsSize(){
      return bv_size;
    }

  };

}


#endif //BITVECTOR_BITVECTOR_H
