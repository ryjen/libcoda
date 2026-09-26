add_library(seamwork_yahtzee_randomness INTERFACE)
target_compile_features(seamwork_yahtzee_randomness INTERFACE cxx_std_23)
target_include_directories(seamwork_yahtzee_randomness
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(seamwork_yahtzee_randomness_example example.cpp)
target_link_libraries(seamwork_yahtzee_randomness_example
    PRIVATE
        seamwork_yahtzee_randomness
)
target_compile_features(seamwork_yahtzee_randomness_example PRIVATE cxx_std_23)
set_target_properties(seamwork_yahtzee_randomness_example PROPERTIES CXX_EXTENSIONS OFF)

# Compile the deterministic study tests even in release integration builds.
# Register them with CTest only when the aggregate test layer is enabled.
add_executable(seamwork_yahtzee_randomness_test tests.cpp)
target_link_libraries(seamwork_yahtzee_randomness_test
    PRIVATE
        seamwork_yahtzee_randomness
)
target_compile_features(seamwork_yahtzee_randomness_test PRIVATE cxx_std_23)
set_target_properties(seamwork_yahtzee_randomness_test PROPERTIES CXX_EXTENSIONS OFF)

if(CODA_BUILD_TESTS)
    add_test(
        NAME seamwork_yahtzee_randomness
        COMMAND seamwork_yahtzee_randomness_test
    )
endif()
