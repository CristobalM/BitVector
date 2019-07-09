//
// Created by cristobal, 2019
//

#include "CommonUtility.h"


namespace succinct_structures{

  template < typename T > std::size_t popcnt( const T& v )
  {
    static_assert( std::is_integral<T>::value && std::is_unsigned<T>::value, "an unsigned integral type expected" ) ;
    return std::bitset< std::numeric_limits<T>::digits >(v).count() ;
  }

  uint popcount_uint(uint value){
    return (uint)popcnt<uint>(value);
  }

}