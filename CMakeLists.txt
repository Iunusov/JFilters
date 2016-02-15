cmake_minimum_required(VERSION 3.0)

project (JFilters)

add_definitions(-DEFFECT_NAME="${PROJECT_NAME}")
add_definitions(-DPRODUCT_NAME="JFilters")
add_definitions(-DVENDOR_STRING="JSound.org")
add_definitions(-DVENDOR_VERSION=1001)

set(CMAKE_BUILD_TYPE Release)

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"))
  set(MYFLAGS "/GL /Ox /Ob2 /WX- /Oi /Oy /MT /openmp /Ot /LTCG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYFLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${MYFLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MYFLAGS}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${MYFLAGS}")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/LIB)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)


