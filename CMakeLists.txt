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

add_compile_definitions(__DEFINED_BUILTIN_POPCOUNT__)

include_directories(include)

set(INCLUDES_FILES
        BitVector.h
        BVManager.h
        SparseSamplingRank.h
        SparseSamplingTwoLevelRank.h
        NullPolicies.h
        CommonUtility.h
        AbstractRankPolicy.h
        AbstractSelectPolicy.h)

set(SOURCES_FILES
        CommonUtility.cpp)

set(INCLUDES_PATHS "")
set(SOURCES_PATHS "")

foreach (header_file IN LISTS INCLUDES_FILES)
    list(APPEND INCLUDES_PATHS "include/${header_file}")
endforeach ()

foreach (source_file IN LISTS SOURCES_FILES)
    list(APPEND SOURCES_PATHS "src/${source_file}")
endforeach ()


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_library(BitVector ${INCLUDES_PATHS} ${SOURCES_PATHS})
