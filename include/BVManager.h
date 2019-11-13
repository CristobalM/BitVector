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
          template<class> class SelectPolicy = NullSelectPolicy>
  class BVManager_ : public RankPolicy<BitVector>, public SelectPolicy<BitVector> {
  private:
    BitVector bv;

  public:
    using RankPolicy<BitVector>::rank;
    using SelectPolicy<BitVector>::select;
    explicit BVManager_(uint bv_size) : bv(bv_size), RankPolicy<BitVector>(&bv), SelectPolicy<BitVector>(&bv){};

    inline uint rank(uint i){
      return rank(bv, i);
    }

    inline uint select(uint i){
      return select(bv, i);
    }

    BitVector &getBitVector(){
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
      RankPolicy<BitVector>::buildRankStructure();
    }

  };

  typedef BVManager_<> BVManager;

}

#endif //BITVECTOR_BVMANAGER_H
