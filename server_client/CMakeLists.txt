#CMake处理当前目录
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(WEIGUOW_INCLUDE_DIRS
        ${MESOS_PUBLIC_INCLUDE_DIR}
        ${PROJECT_BINARY_DIR}/server_client/proto/
        )

set(WEIGUOW_3RDPARTY_INCLUDE_DIRS
        ${PROCESS_INCLUDE_DIRS}
        ${PROCESS_3RDPARTY_INCLUDE_DIRS}
        ${LEVELDB_INCLUDE_DIR}
        )

set(WEIGUOW_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )

set(WEIGUOW_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET})

include_directories(SYSTEM
        ${WEIGUOW_3RDPARTY_INCLUDE_DIRS})

include_directories(${WEIGUOW_INCLUDE_DIRS})

link_directories(${WEIGUOW_LIB_DIRS})

add_subdirectory(StudentManage)
add_subdirectory(proto)

include(${CMAKE_SOURCE_DIR}/cmake/protobuf-2.6.1-compile.cmake)

PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/server_client/proto   student_pro        ${CMAKE_BINARY_DIR}/server_client/proto  student_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/server_client/proto   teacher_pro        ${CMAKE_BINARY_DIR}/server_client/proto  teacher_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/server_client/proto   transfile          ${CMAKE_BINARY_DIR}/server_client/proto  transfile_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/server_client/proto   cpuinfo_pro        ${CMAKE_BINARY_DIR}/server_client/proto  cpuinfo_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/server_client/proto   singleinfo_pro     ${CMAKE_BINARY_DIR}/server_client/proto  singleinfo_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/server_client/proto   slaveinfo_pro      ${CMAKE_BINARY_DIR}/server_client/proto  slaveinfo_pro)

add_executable(student_client student_slave.cpp)
target_link_libraries(student_client student_pro
        transfile_pro
        cpuinfo_pro
        singleinfo_pro
        slaveinfo_pro ${WEIGUOW_LIBS})

add_executable(teacher_server teacher_master.cpp)
target_link_libraries(teacher_server
        student_pro
        teacher_pro
        transfile_pro
        cpuinfo_pro
        slaveinfo_pro
        singleinfo_pro ${WEIGUOW_LIBS})