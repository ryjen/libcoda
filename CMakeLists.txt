cmake_minimum_required(VERSION 3.21)

project(coda VERSION 0.5.1 LANGUAGES CXX)

option(CODA_BUILD_TESTS "Build libcoda tests." ON)
option(CODA_ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(CODA_ENABLE_MEMCHECK "Enable Valgrind memory checking." OFF)
option(CODA_ENABLE_PROFILING "Enable Valgrind profiling." OFF)

# Backward-compatible aliases for existing build scripts. New integrations
# should use the CODA_* options above.
option(ENABLE_COVERAGE "Deprecated: use CODA_ENABLE_COVERAGE." OFF)
option(ENABLE_MEMCHECK "Deprecated: use CODA_ENABLE_MEMCHECK." OFF)
option(ENABLE_PROFILING "Deprecated: use CODA_ENABLE_PROFILING." OFF)
mark_as_advanced(ENABLE_COVERAGE ENABLE_MEMCHECK ENABLE_PROFILING)

if(ENABLE_COVERAGE)
    set(CODA_ENABLE_COVERAGE ON)
endif()
if(ENABLE_MEMCHECK)
    set(CODA_ENABLE_MEMCHECK ON)
endif()
if(ENABLE_PROFILING)
    set(CODA_ENABLE_PROFILING ON)
endif()

# Keep legacy variables available to submodule/test CMake while they migrate.
set(ENABLE_COVERAGE "${CODA_ENABLE_COVERAGE}")
set(ENABLE_MEMCHECK "${CODA_ENABLE_MEMCHECK}")
set(ENABLE_PROFILING "${CODA_ENABLE_PROFILING}")

if(NOT CODA_BUILD_TESTS AND
   (CODA_ENABLE_COVERAGE OR CODA_ENABLE_MEMCHECK OR CODA_ENABLE_PROFILING))
    message(FATAL_ERROR
        "Coverage, memcheck, and profiling require CODA_BUILD_TESTS=ON"
    )
endif()

# Set path to custom modules.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Create distribution packages.
include(CreatePackages)
create_packages(DESCRIPTION "A c++17 toolkit")

find_package(MySQL)
find_package(SQLite3)
find_package(JSONC)
find_package(CURL)
find_package(PostgreSQL)

if(CODA_BUILD_TESTS)
    enable_testing()

    # Tests are currently added before src because Bandit variables are shared
    # with legacy component test CMake. Remove this ordering dependency as the
    # test infrastructure is modernized under issue #5.
    add_subdirectory(tests)
endif()

# Add src directory containing in-tree components and submodules.
add_subdirectory(src)

# LIBRARY_VERSION is only consumed by the aggregate coda target's version.cpp.
# Keep it target-local rather than mutating CMAKE_CXX_FLAGS globally.
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LIBRARY_VERSION="${PROJECT_VERSION}"
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

message(STATUS "libcoda version: ${PROJECT_VERSION}")
message(STATUS "libcoda aggregate tests: ${CODA_BUILD_TESTS}")