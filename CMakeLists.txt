cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

# add options for testing
option(ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(ENABLE_MEMCHECK "Enable testing for memory leaks." OFF)
option(ENABLE_PROFILING "Enable profiling code usage." OFF)

# define project name
project (coda VERSION 0.5.1)

# Setup testing
enable_testing()

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# create distribution packages
include(CreatePackages)
create_packages(DESCRIPTION "A c++17 toolkit")

if (PROJECT_VERSION)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIBRARY_VERSION=\\\"${PROJECT_VERSION}\\\"")
	message(STATUS "Setting library version to ${PROJECT_VERSION}")
endif()

find_package(MySQL)
find_package(SQLite3)
find_package(JSONC)
find_package(CURL)
find_package(PostgreSQL)

# add test first for environment variables in submodules
add_subdirectory(tests)

# add src directory contain submodules
add_subdirectory(src)

