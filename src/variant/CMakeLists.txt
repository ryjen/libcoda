cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# add options for testing
option(ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(ENABLE_MEMCHECK "Enable testing for memory leaks." OFF)
option(ENABLE_PROFILING "Enable profiling code usage." OFF)

# define project name
project (rj_variant VERSION 0.2.0)

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# add target for code coverage
if(ENABLE_COVERAGE)
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
	setup_target_for_coverage(TARGET ${PROJECT_NAME}_coverage OUTPUT ${PROJECT_BINARY_DIR}/gen/coverage)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# create the package config install
include(CreatePackage)
create_package(DESCRIPTION "a c++11 variant/discriminated union type")

# add directories
add_subdirectory(src)
add_subdirectory(tests)

include(ValgrindTest)

add_valgrind_profile_test(MEMCHECK ${ENABLE_MEMCHECK} PROFILING ${ENABLE_PROFILING} TARGET ${TEST_PROJECT_NAME} "--suppressions=${PROJECT_SOURCE_DIR}/suppression.map")
