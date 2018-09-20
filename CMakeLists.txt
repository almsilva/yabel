# ==================================================================================
# General project details.
# ==================================================================================
cmake_minimum_required(VERSION 2.8)
project(sandbox)

# Project's type. Can be:
# EXEC        - Binary executable file.
# STATIC_LIB  - Static library.
# SHARED_LIB  - Shared library.
set (PROJECT_TYPE "EXEC")

# Project's major version, minor version and patch version.
set (MAJOR_VERSION "0")
set (MINOR_VERSION "1")
set (PATCH_VERSION "0")

# Project's final artifact name in the format <project name>-<major version>.<minor version>.<patch version>.
set (FULL_VERSION_SUFFIX "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set (PROJECT_ARTIFACT_NAME "${CMAKE_PROJECT_NAME}-${FULL_VERSION_SUFFIX}")

# ==================================================================================
# Compiler settings.
# ==================================================================================
set (CMAKE_CXX_FLAGS "-Wall -std=c++11")
include_directories(include)
file(GLOB sources "src/*.cpp")

if (${PROJECT_TYPE} MATCHES "EXEC")
  add_executable(${PROJECT_ARTIFACT_NAME} ${sources})
elseif (${PROJECT_TYPE} MATCHES "STATIC_LIB")
  add_library(${PROJECT_ARTIFACT_NAME} STATIC ${sources})
elseif (${PROJECT_TYPE} MATCHES "SHARED_LIB")
  add_library(${PROJECT_ARTIFACT_NAME} SHARED ${sources})
endif()

# ==================================================================================
# Test settings with Boost.Test using shared libraries.
# ==================================================================================
enable_testing()

find_package(Boost 1.67.0 COMPONENTS unit_test_framework REQUIRED)
if (Boost_FOUND)
  list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

  include_directories(${Boost_INCLUDE_DIRS})
  file(GLOB TEST_SOURCES "test/*.cpp")

  foreach(testFile ${TEST_SOURCES})
    get_filename_component(testFileName ${testFile} NAME_WE)
    add_executable(${testFileName}_test ${testFile} ${sources})
    target_link_libraries(${testFileName}_test ${Boost_LIBRARIES})
    add_test(NAME ${testFileName}_test
             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
             COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/${testFileName}_test)
  endforeach(testFile)
endif()
