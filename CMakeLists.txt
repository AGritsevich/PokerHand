cmake_minimum_required (VERSION 3.8)

set(APP_NAME PokerHand)
project (${APP_NAME}) 

if(${CMAKE_BUILD_TYPE} STREQUAL "")
    message(WARNING "BUILD_TYPE doesn't set, going to set Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif(${CMAKE_BUILD_TYPE} STREQUAL "")
message(STATUS "BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include sub-projects.
add_subdirectory (src/)
add_subdirectory (simpleson/)
