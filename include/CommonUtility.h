//
// Created by cristobal, 2019
//

#ifndef BITVECTOR_COMMONVALUES_H
#define BITVECTOR_COMMONVALUES_H

#include <bitset>
#include <type_traits>
#include <limits>

namespace succinct_structures{
  using uint = unsigned int;

  template < typename T > std::size_t popcnt( const T& v );
  uint popcount_uint(uint value);

}

#endif //BITVECTOR_COMMONVALUES_H