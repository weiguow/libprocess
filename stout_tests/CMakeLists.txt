
include_directories(${CMAKE_SOURCE_DIR}/stout_tests)

add_executable(flags_tests flags_tests.cpp)
target_link_libraries(flags_tests ${LIBS} gtest gmock glog)

add_executable(flags_tests_mine flags_tests_mine.cpp)
target_link_libraries(flags_tests_mine ${LIBS})

add_executable(subcommand_tests subcommand_tests.cpp)
target_link_libraries(subcommand_tests ${LIBS} gtest gmock glog)

add_executable(gflagtest gflag.cpp)
target_link_libraries(gflagtest gflags)