//
// Created by CristobalOsvaldoMira on 5/15/2019.
//

#ifndef BITVECTOR_SPARSESAMPLINGRANK_H
#define BITVECTOR_SPARSESAMPLINGRANK_H

#include <array>
#include <memory>

#include "CommonUtility.h"
#include "AbstractRankPolicy.h"



#include <iostream> // debug

namespace succinct_structures{

  template<class BV>
  class SparseSamplingRank : public AbstractRankPolicy<BV> {
    const static uint s_value = INT_BITS * INT_BITS;
  private:
    std::unique_ptr<uint[]> rank_sample;


  protected:
    uint rank(BV &bv, uint i) {
      if(this->dirty){
        buildRankStructure();
      }

      auto prev_sample_idx = i / s_value;
      auto prev_block_idx = i / INT_BITS;

      auto acc_rank = rank_sample[prev_sample_idx];

      for(auto it_i = prev_sample_idx * INT_BITS + 1; it_i <= prev_block_idx; it_i++){
        acc_rank += popcount_uint(bv.read_block_pos(it_i));
      }

      auto left_remaining_pos = prev_block_idx*INT_BITS + 1;
      auto right_remaining_pos = left_remaining_pos - 1 + (i % INT_BITS);

      auto last_read_bits = bv.bitsread(left_remaining_pos, right_remaining_pos);
      auto remaining_count = popcount_uint(last_read_bits);
      auto result = acc_rank + remaining_count;
      return result;

    }
/* OLD NAIVE BUILD
    inline void buildRankSample(){
      auto bv_size = this->bv->getBitsSize();
      auto rank_sample_sz = bv_size/s_value + (bv_size % s_value == 0 ? 0 : 1) + 1;
      rank_sample = std::make_unique<uint[]>(rank_sample_sz);

      uint acc_rank = 0;
      for(uint i = 0; i < bv_size; i++){
        acc_rank += this->bv->bitread(i+1);

        if(i> 0 && (i+1) % s_value == 0){
          rank_sample[(i+1) / s_value] = acc_rank;
        }
      }
      rank_sample[rank_sample_sz-1] = acc_rank;
    }
*/

    inline void buildRankSample(){
      auto bv_size = this->bv->getBitsSize();
      auto blocks_num = bv_size / INT_BITS + (bv_size % INT_BITS == 0 ? 0 : 1);
      auto rank_sample_sz = bv_size/s_value + (bv_size % s_value == 0 ? 0 : 1) + 1;
      rank_sample = std::make_unique<uint[]>(rank_sample_sz);

      uint acc_rank = 0;
      for(uint i = 0; i < blocks_num; i++){
        auto bv_pos = i * INT_BITS + 1;
        if((bv_pos-1) % s_value == 0){
          auto rank_sample_idx = bv_pos / s_value;
          rank_sample[rank_sample_idx] = acc_rank;
        }

        auto current_block = this->bv->read_block_pos(i+1);
        acc_rank += popcount_uint(current_block);
      }
      rank_sample[rank_sample_sz-1] = acc_rank;


    }

    void buildRankStructure(){
      buildRankSample();
      this->dirty = false;
    }

    explicit SparseSamplingRank(BV *bv) : AbstractRankPolicy<BV>(bv){}

  };
}



#endif //BITVECTOR_SPARSESAMPLINGRANK_H
