cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# add options for testing
option(CODE_COVERAGE "Enable code coverage testing." OFF)
option(MEMORY_CHECK "Enable testing for memory leaks." OFF)

# define project name
project (librj VERSION 0.5.0)

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# create the package config install
include(CreatePackage)
create_package("A c++11 toolkit")

find_package(MySQL)
find_package(SQLite3)
find_package(JSONC)
find_package(CURL)
find_package(PostgreSQL)

# add target for code coverage
if(CODE_COVERAGE)
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
	setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_SOURCE_DIR}/coverage)
endif()

# add directories
add_subdirectory(src)
add_subdirectory(tests)

# Setup testing
enable_testing()

include(ValgrindTest)

add_opt_valgrind_test(MEMORY_CHECK ${PROJECT_NAME}_test ${PROJECT_BINARY_DIR}/tests/${PROJECT_NAME}_test)
add_opt_valgrind_test(MEMORY_CHECK rj_db_test ${PROJECT_BINARY_DIR}/src/db/tests/rj_db_test)
add_opt_valgrind_test(MEMORY_CHECK rj_dice_test ${PROJECT_BINARY_DIR}/src/dice/tests/rj_dice_test)
add_opt_valgrind_test(MEMORY_CHECK rj_format_test ${PROJECT_BINARY_DIR}/src/format/tests/rj_format_test)
add_opt_valgrind_test(MEMORY_CHECK rj_json_test ${PROJECT_BINARY_DIR}/src/json/tests/rj_json_test)
add_opt_valgrind_test(MEMORY_CHECK rj_net_test ${PROJECT_BINARY_DIR}/src/net/tests/rj_net_test)
add_opt_valgrind_test(MEMORY_CHECK rj_variant_test ${PROJECT_BINARY_DIR}/src/variant/tests/rj_variant_test)


