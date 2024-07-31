add_executable(
  test_cor
  test_cor.cc
)
target_link_libraries(
  test_cor
  GTest::gtest_main
  cor
)

gtest_discover_tests(test_cor)
