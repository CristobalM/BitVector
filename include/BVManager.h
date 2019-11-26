//
// Created by cristobal, 2019
//

#ifndef BITVECTOR_BVMANAGER_H
#define BITVECTOR_BVMANAGER_H

#include "BitVector.h"
#include "NullPolicies.h"
#include "SparseSamplingRank.h"
#include "SparseSamplingTwoLevelRank.h"

namespace succinct_structures{
  template<template<class> class RankPolicy = SparseSamplingTwoLevelRank,
          template<class> class SelectPolicy = NullSelectPolicy,
                  class BV = BitVector<>>
  class BVManager_ : public RankPolicy<BV>, public SelectPolicy<BV> {
  private:
    BV bv;

  public:
    using RankPolicy<BV>::rank;
    using SelectPolicy<BV>::select;
    explicit BVManager_(uint bv_size) : bv(bv_size), RankPolicy<BV>(&bv), SelectPolicy<BV>(&bv){};

    inline uint rank(uint i){
      return rank(bv, i);
    }

    inline uint select(uint i){
      return select(bv, i);
    }

    BV &getBitVector(){
      return bv;
    };

    uint getBVSize() const{
      return bv.getBVSize();
    };

    void clearContainer(){
      this->dirty = true;
      bv.clearContainer();
    };

    inline uint read_block_pos(uint block_position){
      return bv.read_block_pos(block_position);
    }

    inline bool bitread(uint bitposition){
      return bv.bitread(bitposition);
    }

    inline void bitset(uint bitposition){
      this->dirty = true;
      bv.bitset(bitposition);
    }

    inline void bitclear(uint bitposition) {
      this->dirty = true;
      bv.bitclear(bitposition);
    }

    void buildRankStructure(){
      RankPolicy<BV>::buildRankStructure();
    }

  };

  typedef BVManager_<> BVManager;

}

#endif //BITVECTOR_BVMANAGER_H
