include(cmake/external_dependencies.cmake)
include(cmake/functions.cmake)


cmake_minimum_required(VERSION 3.11)

set(ProjectName "WorkshopControl")

project(${ProjectName})
setup_steamworkssdk()

execute_process(COMMAND git submodule init)
execute_process(COMMAND git submodule update)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} CACHE PATH "Executable output path")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE} CACHE PATH "Library output path")

include_directories("${PROJECT_SOURCE_DIR}")
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_executable(WorkshopControl ${SOURCES})

add_subdirectory(extern/cxxopts)
target_include_directories(${ProjectName} PUBLIC cxxopts)

target_link_libraries(${ProjectName}
    steamworks_sdk
    cxxopts)


if(MSVC)
    add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND if $<CONFIG:Debug> neq 0 ("${CMAKE_COMMAND}" -E copy_if_different "${STEAMWORKS_LIB_PATH}" "${CMAKE_BINARY_DIR}/Debug")
        COMMAND if $<CONFIG:Release> neq 0 ("${CMAKE_COMMAND}" -E copy_if_different "${STEAMWORKS_LIB_PATH}" "${CMAKE_BINARY_DIR}/Release")
        COMMENT "Copying steam_api64.dll DLL"
        )
endif()

install (TARGETS WorkshopControl DESTINATION bin)
