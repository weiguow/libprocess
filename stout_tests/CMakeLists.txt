add_executable(flags_tests flags_tests.cpp)
target_link_libraries(flags_tests ${LIBS} gtest gmock glog)

add_executable(flags_tests_mine flags_tests_mine.cpp)
target_link_libraries(flags_tests_mine ${LIBS})