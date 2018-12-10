#引入Protobuf静态库
set(PROTOBUF_LIBRARY libprotobuf.so)
link_directories(${PROTOBUF_LIB_DIR})
link_directories(${HWLOC_LIB_DIR})
#include_directories(${HWLOC_INCLUDE_DIR})


#添加一个库libhwloc在运行时被加载;设置库名为libhwloc,引入对应的值为${HWLOC_LIB_DIR}/libhwloc.so
add_library(libhwloc SHARED IMPORTED)
set_target_properties(libhwloc PROPERTIES IMPORTED_LOCATION ${HWLOC_LIB_DIR}/libhwloc.so)
add_dependencies(libhwloc hwloc)   #为顶层目标libhwloc引入一个依赖关系hwloc

set(HWLOC_LIBRARY hwloc)

add_executable(hwloc_example hwloc_map.cpp)
target_link_libraries(hwloc_example ${HWLOC_LIBRARY} ${PROTOBUF_LIBRARY})