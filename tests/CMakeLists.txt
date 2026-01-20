include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_link_options("$<$<CONFIG:DEBUG>:--coverage>")

add_executable(ring_buffer_test ring_buffer_TEST.cc)
add_dependencies(ring_buffer_test HexapodUtils)

target_link_libraries(ring_buffer_test
        GTest::gtest_main
        HexapodUtils
)


include(GoogleTest)

gtest_discover_tests(ring_buffer_test)
