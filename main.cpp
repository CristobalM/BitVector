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
  succinct_structures::BVManager bvmg(1025);

  for(int i = 1; i <= 33; i++){
    bvmg.bitset(i);
  }

  //bvmg.bitset(512);

  for(int i = 1023; i <= 1025; i++){
   // bvmg.bitset(i);
  }

  std::cout << "rank to 1025: " << bvmg.rank(1025) << std::endl;
  std::cout << "rank to 1024: " << bvmg.rank(1024) << std::endl;
  std::cout << "rank to 1023: " << bvmg.rank(1023) << std::endl;
  std::cout << "rank to 512: " << bvmg.rank(512) << std::endl;
  std::cout << "rank to 33: " << bvmg.rank(33) << std::endl;
  std::cout << "rank to 32: " << bvmg.rank(32) << std::endl;

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

  std::cout << "rank to last: " << bvmg.rank(2147483648) << std::endl;
  bvmg.bitclear(2147483648);
  std::cout << "rank to last: " << bvmg.rank(2147483648) << std::endl;
  std::cout << "rank to 1048577: " << bvmg.rank(1048577) << std::endl;
  std::cout << "rank to 1048576: " << bvmg.rank(1048576) << std::endl;
  std::cout << "rank to 1048576: " << bvmg.rank(1048576) << std::endl;
  std::cout << "rank to 65537: " << bvmg.rank(65537) << std::endl;
  std::cout << "rank to 2049: " << bvmg.rank(2049) << std::endl;
  std::cout << "rank to 500: " << bvmg.rank(500) << std::endl;
  std::cout << "rank to 482: " << bvmg.rank(482) << std::endl;
  std::cout << "rank to 480: " << bvmg.rank(480) << std::endl;
  std::cout << "rank to 50: " << bvmg.rank(50) << std::endl;
  std::cout << "rank to 49: " << bvmg.rank(49) << std::endl;
  std::cout << "rank to 4: " << bvmg.rank(4) << std::endl;
  std::cout << "rank to 8: " << bvmg.rank(8) << std::endl;
  std::cout << "rank to 1: " << bvmg.rank(1) << std::endl;



/*
  succinct_structures::BVManager bvmg(1025);

  bvmg.bitset(1);
  bvmg.bitset(8);
  bvmg.bitset(4);
  bvmg.bitset(49);
  bvmg.bitset(50);
  bvmg.bitset(480);
  bvmg.bitset(482);
  bvmg.bitset(500);

  std::cout << "rank to 500: " << bvmg.rank(500) << std::endl;
  std::cout << "rank to 482: " << bvmg.rank(482) << std::endl;
  std::cout << "rank to 480: " << bvmg.rank(480) << std::endl;
  std::cout << "rank to 50: " << bvmg.rank(50) << std::endl;
  std::cout << "rank to 49: " << bvmg.rank(49) << std::endl;
  std::cout << "rank to 4: " << bvmg.rank(4) << std::endl;
  std::cout << "rank to 8: " << bvmg.rank(8) << std::endl;
  std::cout << "rank to 1: " << bvmg.rank(1) << std::endl;
*/


  //bvmg.rank(2);


  return 0;
}