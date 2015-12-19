cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# add options for testing
option(CODE_COVERAGE "Enable code coverage testing." OFF)
option(MEMORY_CHECK "Enable testing for memory leaks." OFF)

# define project name
project (libarg3 VERSION 0.5.0)

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# create the package config install
include(CreatePackage)
create_package("A c++11 toolkit")

find_package(MySQL)
find_package(SQLite3)
find_package(JSONC)
find_package(CURL)

# add target for code coverage
if(CODE_COVERAGE)
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
	setup_target_for_coverage(${PROJECT_NAME}-coverage ${PROJECT_BINARY_DIR}/tests/${PROJECT_NAME}_test ${PROJECT_SOURCE_DIR}/coverage)
endif()

# create config header
include(CreateConfigHeader)
create_config_header()

# add directories
add_subdirectory(src)
add_subdirectory(tests)

# Setup testing
enable_testing()


include(MemCheckTest)

add_opt_memcheck_test(MEMORY_CHECK ${PROJECT_NAME}-test ${PROJECT_BINARY_DIR}/tests/${PROJECT_NAME}-test)
add_opt_memcheck_test(MEMORY_CHECK arg3db-mysql-test ${PROJECT_BINARY_DIR}/src/db/tests/arg3db-mysql-test)
add_opt_memcheck_test(MEMORY_CHECK arg3db-sqlite-test ${PROJECT_BINARY_DIR}/src/db/tests/arg3db-sqlite-test)
add_opt_memcheck_test(MEMORY_CHECK arg3dice-test ${PROJECT_BINARY_DIR}/src/dice/tests/arg3dice-test)
add_opt_memcheck_test(MEMORY_CHECK arg3format-test ${PROJECT_BINARY_DIR}/src/format/tests/arg3format-test)
add_opt_memcheck_test(MEMORY_CHECK arg3json-test ${PROJECT_BINARY_DIR}/src/json/tests/arg3json-test)
add_opt_memcheck_test(MEMORY_CHECK arg3net-test ${PROJECT_BINARY_DIR}/src/net/tests/arg3net-test)
add_opt_memcheck_test(MEMORY_CHECK arg3variant-test ${PROJECT_BINARY_DIR}/src/variant/tests/arg3variant-test "--suppressions=${PROJECT_SOURCE_DIR}/src/variant/suppression.map")


