
if (NOT DEFINED BANDIT_DIR)
    include(ExternalProject)

    externalproject_add(${PROJECT_NAME}-bandit
                GIT_REPOSITORY https://github.com/banditcpp/bandit.git
                GIT_TAG v2.0.0
                INSTALL_COMMAND ""
                BUILD_COMMAND ""
                PREFIX ${CMAKE_CURRENT_BINARY_DIR}/bandit)

    ExternalProject_Get_property(${PROJECT_NAME}-bandit SOURCE_DIR)

    set(BANDIT_DIR ${SOURCE_DIR})
    set(BANDIT_DIR ${BANDIT_DIR} PARENT_SCOPE)
    set(BANDIT_TARGET ${PROJECT_NAME}-bandit)
    set(BANDIT_TARGET ${BANDIT_TARGET} PARENT_SCOPE)

    message(STATUS "Using ${BANDIT_DIR}")
endif()


add_executable(${TEST_PROJECT_NAME} main.test.cpp bigint.test.cpp collections.test.cpp string.test.cpp argument.test.cpp buffer.test.cpp log.test.cpp terminal.test.cpp)

target_include_directories(${TEST_PROJECT_NAME} SYSTEM PUBLIC ${BANDIT_DIR} PUBLIC ${PROJECT_SOURCE_DIR}/src PUBLIC ${PROJECT_SOURCE_DIR}/src/math)

target_link_libraries (${TEST_PROJECT_NAME} ${PROJECT_NAME})

if (DEFINED BANDIT_TARGET)
    add_dependencies(${TEST_PROJECT_NAME} ${BANDIT_TARGET})
endif()

include(ValgrindTest)

add_valgrind_profile_test(MEMCHECK ${ENABLE_MEMCHECK} PROFILING ${ENABLE_PROFILING} TARGET ${TEST_PROJECT_NAME})