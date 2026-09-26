cmake_minimum_required(VERSION 3.21)

# Keep the historical project name during the re-charter. Renaming the public
# CMake/package surface is a separate compatibility decision tracked by the
# Seamwork migration plan.
project(coda VERSION 0.5.1 LANGUAGES CXX)

option(SEAMWORK_BUILD_STUDIES "Build Seamwork C++23 design studies." ON)
option(SEAMWORK_BUILD_TESTS "Register and run Seamwork study/component tests." ON)
option(SEAMWORK_BUILD_LEGACY "Build the archived libcoda aggregate and compatibility surface." OFF)

# Legacy build controls remain available only for the explicit compatibility
# path. They are intentionally not the primary Seamwork configuration surface.
option(CODA_BUILD_TESTS "Build legacy libcoda tests when SEAMWORK_BUILD_LEGACY=ON." ON)
option(CODA_ENABLE_COVERAGE "Enable legacy libcoda coverage integration." OFF)
option(CODA_ENABLE_MEMCHECK "Enable legacy libcoda Valgrind memory checking." OFF)
option(CODA_ENABLE_PROFILING "Enable legacy libcoda Valgrind profiling." OFF)

# Backward-compatible aliases for old build scripts.
option(ENABLE_COVERAGE "Deprecated: use CODA_ENABLE_COVERAGE." OFF)
option(ENABLE_MEMCHECK "Deprecated: use CODA_ENABLE_MEMCHECK." OFF)
option(ENABLE_PROFILING "Deprecated: use CODA_ENABLE_PROFILING." OFF)
mark_as_advanced(
    CODA_BUILD_TESTS
    CODA_ENABLE_COVERAGE
    CODA_ENABLE_MEMCHECK
    CODA_ENABLE_PROFILING
    ENABLE_COVERAGE
    ENABLE_MEMCHECK
    ENABLE_PROFILING
)

if(SEAMWORK_BUILD_TESTS OR (SEAMWORK_BUILD_LEGACY AND CODA_BUILD_TESTS))
    enable_testing()
endif()

if(SEAMWORK_BUILD_STUDIES)
    add_subdirectory(studies)
endif()

if(SEAMWORK_BUILD_LEGACY)
    if(ENABLE_COVERAGE)
        set(CODA_ENABLE_COVERAGE ON)
    endif()
    if(ENABLE_MEMCHECK)
        set(CODA_ENABLE_MEMCHECK ON)
    endif()
    if(ENABLE_PROFILING)
        set(CODA_ENABLE_PROFILING ON)
    endif()

    # Keep legacy variables available to submodule/test CMake while archived
    # code remains buildable through the compatibility path.
    set(ENABLE_COVERAGE "${CODA_ENABLE_COVERAGE}")
    set(ENABLE_MEMCHECK "${CODA_ENABLE_MEMCHECK}")
    set(ENABLE_PROFILING "${CODA_ENABLE_PROFILING}")

    if(NOT CODA_BUILD_TESTS AND
       (CODA_ENABLE_COVERAGE OR CODA_ENABLE_MEMCHECK OR CODA_ENABLE_PROFILING))
        message(FATAL_ERROR
            "Legacy coverage, memcheck, and profiling require CODA_BUILD_TESTS=ON"
        )
    endif()

    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

    include(CreatePackages)
    create_packages(
        DESCRIPTION
            "Legacy libcoda compatibility surface retained during the Seamwork transition"
    )

    find_package(MySQL)
    find_package(SQLite3)
    find_package(JSONC)
    find_package(CURL)
    find_package(PostgreSQL)

    if(CODA_BUILD_TESTS)
        # Tests are currently added before src because Bandit variables are
        # shared with legacy component test CMake.
        add_subdirectory(tests)
    endif()

    add_subdirectory(src)

    # LIBRARY_VERSION is only consumed by the legacy aggregate coda target.
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            LIBRARY_VERSION="${PROJECT_VERSION}"
    )

    # The aggregate wrapper is C++23, while archived child targets retain their
    # own historical target-local language contracts.
    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
endif()

message(STATUS "Seamwork transition version: ${PROJECT_VERSION}")
message(STATUS "Seamwork studies: ${SEAMWORK_BUILD_STUDIES}")
message(STATUS "Seamwork tests: ${SEAMWORK_BUILD_TESTS}")
message(STATUS "Legacy libcoda compatibility build: ${SEAMWORK_BUILD_LEGACY}")
