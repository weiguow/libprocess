include_directories(${CMAKE_CURRENT_BINARY_DIR})

link_directories(${HWLOC_LIB_DIR})

add_library(libhwloc SHARED IMPORTED)
set_target_properties(libhwloc PROPERTIES IMPORTED_LOCATION ${HWLOC_LIB_DIR}/libhwloc.so)
add_dependencies(libhwloc hwloc)   #为顶层目标libhwloc引入一个依赖关系hwloc

set(HWLOC_LIBRARY hwloc)

add_executable(show_cpu_info cpu_info_class.cpp)

add_executable(show_cpu_info_mine show_cpu_info_mine.cpp)
target_link_libraries(show_cpu_info_mine ${LIBS} ${HWLOC_LIBRARY} pthread)

add_executable(test_delimiter test_delimiter.cpp)
target_link_libraries(test_delimiter ${LIBS})