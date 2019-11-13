//
// Created by cristobal, 2019
//

#ifndef BITVECTOR_ABSTRACTRANKPOLICY_H
#define BITVECTOR_ABSTRACTRANKPOLICY_H
namespace  succinct_structures {
  template <class BV>
  class AbstractRankPolicy{
  protected:
    BV *bv;
    bool dirty;
    explicit AbstractRankPolicy(BV *bv) : bv(bv), dirty(true) {}
  };
}
#endif //BITVECTOR_ABSTRACTRANKPOLICY_H
