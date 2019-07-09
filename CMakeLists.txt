cmake_minimum_required(VERSION 3.12)
project(BitVector)

set(CMAKE_CXX_STANDARD 14)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
    message("-march=native enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
else()
    message("-march=native not supported")
endif()


set(BitVector BitVector.cpp BitVector.h
        BVManager.h
        SparseSamplingRank.h
        NullPolicies.h
        CommonUtility.h CommonUtility.cpp
        AbstractRankPolicy.h
        AbstractSelectPolicy.h
        )


#add_executable(BitVector main.cpp BitVector.cpp BitVector.h SparseSamplingRank.cpp SparseSamplingRank.h)
add_executable(BitVectorMain main.cpp ${BitVector})