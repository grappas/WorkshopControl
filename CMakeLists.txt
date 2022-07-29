include(cmake/external_dependencies.cmake)
include(cmake/functions.cmake)

cmake_minimum_required(VERSION 3.11)

set(ProjectName "WorkshopControl")

project(${ProjectName})
setup_steamworkssdk()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} CACHE PATH "Executable output path")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} CACHE PATH "Library output path")

add_subdirectory(extern/cxxopts)
target_include_directories(${ProjectName} cxxopts)

include_directories("${PROJECT_SOURCE_DIR}")
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_executable(WorkshopControl ${SOURCES})

target_link_libraries(WorkshopControl
    steamworks_sdk
    cxxopts
    )

install (TARGETS WorkshopControl DESTINATION bin)
