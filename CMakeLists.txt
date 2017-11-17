cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

# add options for testing
option(ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(ENABLE_MEMCHECK "Enable testing for memory leaks." OFF)
option(ENABLE_PROFILING "Enable profiling code usage." OFF)

# define project name
project (librj VERSION 0.5.0)

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

# Setup testing
enable_testing()

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# create the package config install
include(CreatePackage)
create_package(DESCRIPTION "A c++14 toolkit")

if (PROJECT_VERSION)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIBRARY_VERSION=\\\"${PROJECT_VERSION}\\\"")
	message(STATUS "Setting library version to ${PROJECT_VERSION}")
endif()

find_package(MySQL)
find_package(SQLite3)
find_package(JSONC)
find_package(CURL)
find_package(PostgreSQL)

# add target for code coverage
if(ENABLE_COVERAGE)
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
	setup_target_for_coverage(TARGET ${PROJECT_NAME}_coverage OUTPUT ${PROJECT_BINARY_DIR}/gen/coverage)
endif()

# add directories
add_subdirectory(src)

add_subdirectory(tests)

include(ValgrindTest)

add_valgrind_profile_test(MEMCHECK ${ENABLE_MEMCHECK} PROFILING ${ENABLE_PROFILING} TARGET ${TEST_PROJECT_NAME})


