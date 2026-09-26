cmake_minimum_required(VERSION 3.21)

# Keep the historical target/project name during the re-charter. Renaming the
# public CMake surface is a separate compatibility decision tracked by the
# Seamwork migration plan.
project(coda VERSION 0.5.1 LANGUAGES CXX)

option(CODA_BUILD_TESTS "Build legacy libcoda/Seamwork transition tests." ON)
option(CODA_ENABLE_COVERAGE "Enable code coverage testing." OFF)
option(CODA_ENABLE_MEMCHECK "Enable Valgrind memory checking." OFF)
option(CODA_ENABLE_PROFILING "Enable Valgrind profiling." OFF)
option(SEAMWORK_BUILD_STUDIES "Build Seamwork C++23 design studies." ON)

# Backward-compatible aliases for existing build scripts. New Seamwork naming
# will be introduced deliberately rather than as a broad mechanical rename.
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

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(CreatePackages)
create_packages(
    DESCRIPTION
        "Seamwork: modern C++23 interface and architecture refinement"
)

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

if(SEAMWORK_BUILD_STUDIES)
    add_subdirectory(studies)
endif()

add_subdirectory(src)

# LIBRARY_VERSION is only consumed by the aggregate coda target's version.cpp.
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LIBRARY_VERSION="${PROJECT_VERSION}"
)

# C++23 is the baseline for active Seamwork/new aggregate code. Legacy
# submodules retain their own target-local language contracts until they are
# reviewed and migrated; do not restore a project-wide CMAKE_CXX_STANDARD.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

message(STATUS "Seamwork transition version: ${PROJECT_VERSION}")
message(STATUS "Seamwork aggregate tests: ${CODA_BUILD_TESTS}")
