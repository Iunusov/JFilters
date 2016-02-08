cmake_minimum_required(VERSION 3.0)

project (HPFilter)

add_definitions(-DFILTER_NAME=${PROJECT_NAME})
add_definitions(-DUID=7652372)
#(CCONST('w','l','2','p'))

set (SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/../AFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../HPFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp
) 

add_library(${PROJECT_NAME}  SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} VST_SDK DSPFilters)