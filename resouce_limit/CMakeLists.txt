
#weiguo_limit_memory
add_executable(weiguo_limit_memory weiguo_limit_memory.cpp)
target_link_libraries(weiguo_limit_memory ${LIBS} pthread)

#weiguo_limit_cpu
add_executable(weiguo_limit_cpu weiguo_limit_cpu.cpp)
target_link_libraries(weiguo_limit_cpu ${LIBS} pthread)

#weiguo_limit_blkio
add_executable(weiguo_limit_blkio weiguo_limit_blkio.cpp)
target_link_libraries(weiguo_limit_blkio ${LIBS} pthread)

#weiguo_limit_net
add_executable(weiguo_limit_net weiguo_limit_net.cpp)
target_link_libraries(weiguo_limit_net ${LIBS} pthread)