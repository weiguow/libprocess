cmake_minimum_required(VERSION 3.7.0)

project(libprocess-mine)



list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/stout/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake/macros)

# Macros.
include(Common)
include(External)
include(PatchCommand)
include(Versions)
include(cotire)

# Configuration.
include(StartConfigure)
include(CompilationConfigure)
include(ProcessConfigure)

include(cmake/protobuf-2.6.1.cmake)
include(cmake/hwloc-1.11.cmake)
include(cmake/gflag.cmake)

include_directories(${CMAKE_BINARY_DIR}/3rdparty/gflag-2.2.2/include)
link_directories(${CMAKE_BINARY_DIR}/3rdparty/gflag-2.2.2/lib)

set(LIBS ${PROCESS_LIBS} ${PROCESS_TARGET})

add_subdirectory(3rdparty)
add_subdirectory(stout_tests)
add_subdirectory(server_client)
add_subdirectory(resouce_limit)
add_subdirectory(sys_info_test)
add_subdirectory(hwloc)

