# Sample Version Of CMake minimum setup
cmake_minimum_required(VERSION 3.15)

#Project name and version
project(PathFinding VERSION 0.1 LANGUAGES CXX)

#set variable 
set(PATH_FINDING_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(EXECUTABLE_OUTPUT_PATH ${PATH_FINDING_ROOT_DIR}/Bin)

# Compiler setup
if (MSVC)
    add_compile_options(/W4)
else()
    # Clang all warning
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# configure header file to pass version number
configure_file("${PATH_FINDING_ROOT_DIR}/Source/PathFindingConfig.h.in" "${PATH_FINDING_ROOT_DIR}/Source/PathFindingConfig.h")

# add executable
#add_executable( ${PROJECT_NAME} ${SRCS} )

file(GLOB HEADER_FILES_CLIENT "${PATH_FINDING_ROOT_DIR}/Source/*.h")
file(GLOB SOURCE_FILES_CLIENT "${PATH_FINDING_ROOT_DIR}/Source/*.cpp")

# Setup your library or executable:
add_executable(PathFinding ${HEADER_FILES_CLIENT} ${SOURCE_FILES_CLIENT})
include_directories(${PATH_FINDING_ROOT_DIR}/Source)

# setup project properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PathFinding)

# add the binary tree to the search path for include files
# so that we will find PathFindingConfig.h
target_include_directories(PathFinding PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS PathFinding DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/PathFindingConfig.h"
  DESTINATION include
  )