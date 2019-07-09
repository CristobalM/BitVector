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

  class BitVector{

  private:
    uint bv_size;
    uint remainder;
    uint num_of_blocks;


    std::unique_ptr<uint[]> container;

    inline uint getBlockIndex(uint bitposition){
      return bitposition % INT_BITS != 0 ? bitposition / INT_BITS + 1 : bitposition / INT_BITS;
    }

    inline uint getPositionInBlock(uint bitpositon) {
      return ((bitpositon - 1) % INT_BITS) + 1;
    }

    inline uint ceilOfDiv(uint dividend, uint divisor){
      return (dividend / divisor) + (dividend % divisor == 0 ? 0 : 1);
    }

  public:
    explicit BitVector(uint bv_size);

    uint getBVSize() const;
    void clearContainer();

    inline uint read_block_pos(uint block_position){
      return container.get()[block_position - 1];
    }

    uint bitsread(uint starting_pos, uint ending_pos){
      if(ending_pos < starting_pos){
        return 0;
      }

      if(ending_pos - starting_pos + 1 > INT_BITS){
        throw std::runtime_error("bitsread request is too big: " +
        std::to_string(ending_pos) + " - " + std::to_string(starting_pos) + " + 1 > " + std::to_string(INT_BITS));
      }

      auto right_position_in_block = getPositionInBlock(ending_pos);
      auto left_block_index = ceilOfDiv(starting_pos, INT_BITS);
      auto right_block_index = ceilOfDiv(ending_pos, INT_BITS);

      if(left_block_index == right_block_index){
        auto right_block = read_block_pos(right_block_index);
        auto right_block_shifted = right_block >> ((INT_BITS - right_position_in_block));

        auto result = (right_block_shifted) % (1 << (ending_pos - starting_pos + 1));
        return result;
      }

      auto left_prev_position_in_block = getPositionInBlock(starting_pos) - 1;

      auto right_block = read_block_pos(right_block_index);
      auto left_block = read_block_pos(left_block_index);

      return ((right_block >> (INT_BITS - right_position_in_block + 1)) << 1) +
      (left_block % (1 << (INT_BITS - left_prev_position_in_block))) * (1 << right_position_in_block);

    }

    inline bool bitread(uint bitposition){
      auto block_idx = getBlockIndex(bitposition);
      auto r = getPositionInBlock(bitposition);
      auto block = read_block_pos(block_idx); // read_block_pos mode
      return ((block >> (INT_BITS - r)) % 2) == 1;
    }

    inline void bitset(uint bitposition){
      if(bitread(bitposition)) return;
      auto block_idx = getBlockIndex(bitposition);
      auto &block = container.get()[block_idx - 1]; // write mode
      auto r = getPositionInBlock(bitposition);
      block += 1 << (INT_BITS - r);
    }

    inline void bitclear(uint bitposition) {
      if(!bitread(bitposition)) return;
      auto block_idx = getBlockIndex(bitposition);
      auto &block = container.get()[block_idx - 1]; // write mode
      auto r = getPositionInBlock(bitposition);
      block -= 1 << (INT_BITS - r);
    }

    uint getBitsSize(){
      return bv_size;
    }

  };

}


#endif //BITVECTOR_BITVECTOR_H
