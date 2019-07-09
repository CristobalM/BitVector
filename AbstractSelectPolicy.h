//
// Created by cristobal, 2019
//

#ifndef BITVECTOR_ABSTRACTSELECTPOLICY_H
#define BITVECTOR_ABSTRACTSELECTPOLICY_H
namespace  succinct_structures {
  template <class BV>
  class AbstractSelectPolicy{
  protected:
    BV *bv;
    explicit AbstractSelectPolicy(BV *bv) : bv(bv) {}
  };
}
#endif //BITVECTOR_ABSTRACTSELECTPOLICY_H
