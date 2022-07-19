include(ExternalProject)
include(cmake/CMakeLists.txt)

cmake_minimum_required(VERSION 3.11)

set(ProjectName "WorkshopControl")

project(${ProjectName})

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} CACHE PATH "Executable output path")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} CACHE PATH "Library output path")

include_directories("${PROJECT_SOURCE_DIR}")
add_executable(WorkshopControl ${PROJECT_SOURCE_DIR}/WorkshopControl.cpp)
#target_link_libraries(STEAMWORKSSDK::STEAMWORKSSDK)
install (TARGETS WorkshopControl DESTINATION bin)
