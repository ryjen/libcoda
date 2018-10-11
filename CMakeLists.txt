cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

# add options for testing
option(ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(ENABLE_MEMCHECK "Enable testing for memory leaks." OFF)
option(ENABLE_PROFILING "Enable profiling code usage." OFF)

# define project name
project (coda VERSION 0.5.1)

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

# Setup testing
enable_testing()

# set path to custom modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# create the package config install
include(CreatePackage)
create_package(DESCRIPTION "A c++17 toolkit")

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

# add test first for environment variables in submodules
add_subdirectory(tests)

# add src directory contain submodules
add_subdirectory(src)

  ############################################################
  # Create DEB
  ############################################################

  # Tell CPack to generate a .deb package
  set(CPACK_GENERATOR "DEB")

  # Set a Package Maintainer.
  # This is required
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ryan Jennings <ryan@micrantha.com>")

  set(CPACK_PACKAGE_VENDOR "Micrantha Software Solutions")

  # Set a Package Version
  set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A c++ toolkit")

  set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")

  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

  set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

  # Include CPack
  include(CPack)

