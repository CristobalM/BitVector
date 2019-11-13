//
// Created by cristobal, 2019
//

#ifndef BITVECTOR_NULLPOLICIES_H
#define BITVECTOR_NULLPOLICIES_H

#include <stdexcept>
#include "AbstractRankPolicy.h"
#include "AbstractSelectPolicy.h"

namespace succinct_structures{
  using uint = unsigned int;

  template<class BV>
  class NullRankPolicy : public AbstractRankPolicy<BV>{
  protected:
    uint rank(BV &bv, uint i) {
      throw std::runtime_error("Calling rank on NullRankPolicy");
    };

    void buildRankStructure(){}

    NullRankPolicy(BV *bv) : AbstractRankPolicy<BV>(bv){}
  };

  template<class BV>
  class NullSelectPolicy : public AbstractSelectPolicy<BV>{
  protected:
    uint select(BV &bv, uint i) {
      throw std::runtime_error("Calling select on NullSelectPolicy");
    };
    NullSelectPolicy(BV *bv) : AbstractSelectPolicy<BV>(bv){}
  };
}

#endif //BITVECTOR_NULLPOLICIES_H
