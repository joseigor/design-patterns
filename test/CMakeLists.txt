include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e39786088138f2749d64e9e90e0f9902daa77c40.zip 
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  example_test
  example_test.cc
)
target_link_libraries(
  example_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(example_test)
