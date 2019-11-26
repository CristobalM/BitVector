//
// Created by cristobal, 2019
//

#ifndef BITVECTOR_SPARSESAMPLINGTWOLEVELRANK_H
#define BITVECTOR_SPARSESAMPLINGTWOLEVELRANK_H

#include "SparseSamplingRank.h"

namespace succinct_structures {

  template<class BV>
  class SparseSamplingTwoLevelRank : public SparseSamplingRank<BV> {
    using ushort = unsigned short;
    static const uint s_value = SparseSamplingRank<BV>::s_value;
    static constexpr auto bv_block_bits = BV::bv_block_bits;

  protected:
    std::unique_ptr<ushort[]> rank_sample_subblock;

    uint rank(BV &bv, uint i) {
      if(AbstractRankPolicy<BV>::dirty){
        buildRankStructure();
      }

      auto prev_sample_idx = i / s_value;
      auto prev_block_idx = i / bv_block_bits;

      auto acc_rank = SparseSamplingRank<BV>::rank_sample[prev_sample_idx];

      if(i % s_value == 0){
        return acc_rank;
      }

      acc_rank += (uint)rank_sample_subblock[prev_block_idx];

      if(i % bv_block_bits == 0){
        return acc_rank;
      }

      auto left_remaining_pos = prev_block_idx*bv_block_bits + 1;
      auto right_remaining_pos = left_remaining_pos - 1 + (i % bv_block_bits);

      auto last_read_bits = bv.bitsread(left_remaining_pos, right_remaining_pos);
      auto remaining_count = popcount_uint(last_read_bits);
      auto result = acc_rank + remaining_count;

      return result;
    }

    void buildRankSample() {
      SparseSamplingRank<BV>::buildRankSample();
      auto bv_size = AbstractRankPolicy<BV>::bv->getBitsSize();
      auto blocks_num = bv_size / bv_block_bits + (bv_size % bv_block_bits == 0 ? 0 : 1);
      auto rank_sb_sample_sz = bv_size / bv_block_bits + (bv_size % bv_block_bits == 0 ? 0 : 1) + 1;

      if(!rank_sample_subblock){
        rank_sample_subblock = std::make_unique<ushort[]>(rank_sb_sample_sz);
      }
      else{
        std::memset(rank_sample_subblock.get(), 0, rank_sb_sample_sz);
      }

      ushort acc_rank = 0;
      for(uint i = 0; i < blocks_num; i++){
        auto bv_pos = i * bv_block_bits + 1;
        if((bv_pos-1) % s_value == 0){
          acc_rank = 0;
        }
        rank_sample_subblock[i] = acc_rank;

        auto current_block = AbstractRankPolicy<BV>::bv->read_block_pos(i+1);
        acc_rank += (ushort)popcount_uint(current_block);
      }

    }

    inline void buildRankStructure() {
      buildRankSample();
      AbstractRankPolicy<BV>::dirty = false;
    }

    explicit SparseSamplingTwoLevelRank(BV *bv) : SparseSamplingRank<BV>(bv){}

  };
}
#endif //BITVECTOR_SPARSESAMPLINGTWOLEVELRANK_H
