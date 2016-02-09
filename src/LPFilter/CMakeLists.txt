cmake_minimum_required(VERSION 3.0)

project (LPFilter)

add_definitions(-DFILTER_NAME=${PROJECT_NAME})
add_definitions(-DUID=CCONST('x','y','2','s'))

set (SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/../AFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../LPFilter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp
) 

add_library(${PROJECT_NAME}  SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} VST_SDK DSPFilters)