cmake_minimum_required(VERSION 3.0)

project (BPFilter)

add_definitions(-DFILTER_NAME=${PROJECT_NAME})
add_definitions(-DUID="bg9c")

set (SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/../AFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../BPFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Plugin.cpp
) 

add_library(${PROJECT_NAME}  SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} VST_SDK DSPFilters)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)