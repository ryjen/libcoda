cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# add options for testing
option(CODE_COVERAGE "Enable code coverage testing." OFF)
option(MEMORY_CHECK "Enable testing for memory leaks." OFF)

# if we have a parent project, grab it first
set(PARENT_PROJECT_NAME ${PROJECT_NAME})

# define project name
project (rj_variant VERSION 0.2.0)

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# set the target
if (NOT ${PARENT_PROJECT_NAME} EQUAL "")
	message(STATUS "Found parent project ${PARENT_PROJECT_NAME} for ${PROJECT_NAME}")
	set(PARENT_PROJECT_FOUND ON)
	set(TARGET_NAME "${PARENT_PROJECT_NAME}_${PROJECT_NAME}")
else()
	set(TARGET_NAME ${PROJECT_NAME})
endif()

# add target for code coverage
if(CODE_COVERAGE)
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
	setup_target_for_coverage(${TARGET_NAME}_coverage ${PROJECT_BINARY_DIR}/gen/coverage)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# create the package config install
include(CreatePackage)
create_package("a c++11 variant/discriminated union type")

# add directories
add_subdirectory(src)
add_subdirectory(tests)

if (DEFINED PARENT_PROJECT_FOUND)
	set_property(TARGET ${TARGET_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}")
	set_property(TARGET ${TARGET_NAME}_test PROPERTY OUTPUT_NAME "${PROJECT_NAME}_test")
	set_property(TARGET ${TARGET_NAME}_binary_test PROPERTY OUTPUT_NAME "${PROJECT_NAME}_binary_test")
endif()

# Setup testing
enable_testing()

include(ValgrindTest)

add_opt_valgrind_test(MEMORY_CHECK ${TARGET_NAME}_test ${PROJECT_BINARY_DIR}/tests/${PROJECT_NAME}_test "--suppressions=${PROJECT_SOURCE_DIR}/suppression.map")
add_opt_valgrind_test(MEMORY_CHECK ${TARGET_NAME}_binary_test ${PROJECT_BINARY_DIR}/tests/${PROJECT_NAME}_binary_test)
