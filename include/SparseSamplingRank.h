//
// Created by CristobalOsvaldoMira on 5/15/2019.
//

#ifndef BITVECTOR_SPARSESAMPLINGRANK_H
#define BITVECTOR_SPARSESAMPLINGRANK_H

#include <array>
#include <memory>

#include <cstring>

#include "CommonUtility.h"
#include "AbstractRankPolicy.h"



#include <iostream> // debug

namespace succinct_structures{

  template<class BV>
  class SparseSamplingRank : public AbstractRankPolicy<BV> {
  protected:
    const static uint s_value = INT_BITS * INT_BITS;

    std::unique_ptr<uint[]> rank_sample;

    uint rank(BV &bv, uint i) {
      if(AbstractRankPolicy<BV>::dirty){
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

    void buildRankSample(){
      auto bv_size = AbstractRankPolicy<BV>::bv->getBitsSize();
      auto blocks_num = bv_size / INT_BITS + (bv_size % INT_BITS == 0 ? 0 : 1);
      auto rank_sample_sz = bv_size/s_value + (bv_size % s_value == 0 ? 0 : 1) + 1;
      if(!rank_sample){
        rank_sample = std::make_unique<uint[]>(rank_sample_sz);
      }
      else{
        std::memset(rank_sample.get(), 0, rank_sample_sz);
      }


      uint acc_rank = 0;
      for(uint i = 0; i < blocks_num; i++){
        auto bv_pos = i * INT_BITS + 1;
        if((bv_pos-1) % s_value == 0){
          auto rank_sample_idx = bv_pos / s_value;
          rank_sample[rank_sample_idx] = acc_rank;
        }

        auto current_block = AbstractRankPolicy<BV>::bv->read_block_pos(i+1);
        acc_rank += popcount_uint(current_block);
      }
      rank_sample[rank_sample_sz-1] = acc_rank;
    }

    inline void buildRankStructure(){
      buildRankSample();
      AbstractRankPolicy<BV>::dirty = false;
    }

    explicit SparseSamplingRank(BV *bv) : AbstractRankPolicy<BV>(bv){}

  };
}



#endif //BITVECTOR_SPARSESAMPLINGRANK_H
