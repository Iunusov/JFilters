cmake_minimum_required(VERSION 3.0)

project (HPFilter)

set (CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../JFilters_DLL")

add_definitions(-DEFFECT_NAME="${PROJECT_NAME}")
add_definitions(-DPRODUCT_NAME="${PROJECT_NAME}")
add_definitions(-DUID="pxoi")

set (SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/../AFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../HPFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Plugin.cpp
) 

add_library(${PROJECT_NAME}  SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} VST_SDK DSPFilters)
