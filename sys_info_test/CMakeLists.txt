include_directories(${CMAKE_SOURCE_DIR}/sys_info_test)
include_directories(${CMAKE_BINARY_DIR}/server_client/proto)

add_executable(ip_test ip_tests.cpp)
target_link_libraries(ip_test  gmock gtest pthread)

add_executable(proc_test proc_tests.cpp)
target_link_libraries(proc_test glog  gmock gtest pthread)

add_executable(cpu_gtest cpu_gtest.cpp x86cpuinfo_test.cpp)
target_link_libraries(cpu_gtest ${LIBS} gtest gmock glog pthread)

#[[test for class cpuinfo]]
add_executable(cpuinfo_class_test cpuinfo_class_test.cpp)
target_link_libraries(cpuinfo_class_test cpuinfo_pro ${LIBS} pthread)

add_executable(weiguo_heartbeat my_heartbeat.cpp)
target_link_libraries(weiguo_heartbeat ${LIBS})

add_executable(port_range port_range.cpp)
