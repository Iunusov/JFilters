cmake_minimum_required(VERSION 3.0)

project (JFilters)

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/JFilters_DLL")

add_definitions(-DEFFECT_NAME="${PROJECT_NAME}")
add_definitions(-DPRODUCT_NAME="JFilters")
add_definitions(-DVENDOR_STRING="https://github.com/R-Tur/JFilters")
add_definitions(-DVENDOR_VERSION=1001)

set(CMAKE_BUILD_TYPE Release)

if((${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC))
  set(MYFLAGS "/Ox /WX- /MT")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYFLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${MYFLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MYFLAGS}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${MYFLAGS}")
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)


