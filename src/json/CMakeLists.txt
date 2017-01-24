cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# add options for testing
option(ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(ENABLE_MEMCHECK "Enable testing for memory leaks." OFF)
option(ENABLE_PROFILING "Enabel profiling code usage." OFF)

# define project name
project (rj_json VERSION 0.2.0)

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(FindJSONC)

if (NOT JSON_C_FOUND)
	message(FATAL_ERROR "json-c library is required.")
endif ()

# add target for code coverage
if(ENABLE_COVERAGE)
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
	setup_target_for_coverage(TARGET ${PROJECT_NAME}_coverage OUTPUT ${PROJECT_BINARY_DIR}/coverage)
endif()

# create package config
include (CreatePackage)
create_package(DESCRIPTION "a c++ json wrapper")

# add directories
add_subdirectory(src)
add_subdirectory(tests)

# Setup testing
enable_testing()

include(ValgrindTest)
	
add_valgrind_profile_test(MEMCHECK ${ENABLE_MEMCHECK} PROFILING ${ENABLE_PROFILING} TARGET ${TEST_PROJECT_NAME})

