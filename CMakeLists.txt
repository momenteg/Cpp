cmake_minimum_required(VERSION 2.8)
project(OrderBook)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

find_package(Boost 1.46 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable(OrderBook ${PROJECT_SOURCE_DIR}/OrderbookTemplate.cpp)
TARGET_LINK_LIBRARIES( OrderBook LINK_PUBLIC ${Boost_LIBRARIES} )
