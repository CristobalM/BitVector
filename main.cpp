#include <iostream>
#include <sstream>

#include "BitVector.h"
#include "BVManager.h"


std::string debugGetStrRep(succinct_structures::BitVector &bv) {
    std::stringstream ss;
    for (uint i = 1; i <= bv.getBVSize(); i++) {
        ss << bv.bitread(i);
    }
    return ss.str();
}


int main() {


  /*
    BitVector bv(500);

    bv.bitset(8);
    bv.bitset(4);
    bv.bitset(49);
    bv.bitset(50);
    bv.bitset(1);
    bv.bitset(499);
    std::cout << "BV Size: " << bv.getBVSize() << std::endl;
    std::cout << "representation:\t" << debugGetStrRep(bv) << std::endl;

    bv.bitclear(499);
    bv.bitclear(1);
    bv.bitset(2);
    bv.bitset(32);
    bv.bitset(500);


    std::cout << "representation:\t" << debugGetStrRep(bv) << std::endl;

   */

  succinct_structures::BVManager bvmg(2147483648);

  bvmg.bitset(1);
  bvmg.bitset(8);
  bvmg.bitset(4);
  bvmg.bitset(49);
  bvmg.bitset(50);
  bvmg.bitset(480);
  bvmg.bitset(482);
  bvmg.bitset(500);
  bvmg.bitset(2049);
  bvmg.bitset(65537);
  bvmg.bitset(1048576);
  bvmg.bitset(1048577);
  bvmg.bitset(2147483648);
  bvmg.bitset(2147483644);

  //bvmg.bitset(1);
  /*

  std::cout << "BV Size: " << bvmg.getBVSize() << std::endl;
  std::cout << "representation:\t" << debugGetStrRep(bvmg.getBitVector()) << std::endl;

  bvmg.bitclear(499);
  bvmg.bitclear(1);
  bvmg.bitset(2);
  bvmg.bitset(32);
  bvmg.bitset(500);

*/



  //std::cout << "representation:\t" << debugGetStrRep(bvmg.getBitVector()) << std::endl;

  //std::cout << "bv size: " << bvmg.getBVSize() << std::endl;
  std::cout << "rank to last: " << bvmg.rank(2147483648) << std::endl;
  bvmg.bitclear(2147483644);
  std::cout << "rank to last: " << bvmg.rank(2147483648) << std::endl;


  //bvmg.rank(2);


  return 0;
}