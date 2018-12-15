include(ExternalProject)

set(PROTOBUF_ROOT_DIR            ${CMAKE_BINARY_DIR}/3rdparty/protobuf-2.6.1.1)
set(PROTOBUF_LIB_DIR         ${PROTOBUF_ROOT_DIR}/lib)
set(PROTOBUF_INCLUDE_DIR     ${PROTOBUF_ROOT_DIR}/include)

set(PROTOBUF_URL             https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz)
set(PROTOBUF_CONFIGURE       cd ${PROTOBUF_ROOT_DIR}/src/protobuf-2.6.1.1 && ./autogen.sh && ./configure --prefix=${PROTOBUF_ROOT_DIR})
set(PROTOBUF_MAKE            cd ${PROTOBUF_ROOT_DIR}/src/protobuf-2.6.1.1 && make)
set(PROTOBUF_INSTALL         cd ${PROTOBUF_ROOT_DIR}/src/protobuf-2.6.1.1 && make install)
set(PROTOBUF_COMPILER        ${PROTOBUF_ROOT_DIR}/bin/protoc)

ExternalProject_Add(protobuf-2.6.1.1
        URL                  ${PROTOBUF_URL}
        DOWNLOAD_NAME        protobuf-2.6.1.zip
        PREFIX               ${PROTOBUF_ROOT_DIR}
        CONFIGURE_COMMAND    ${PROTOBUF_CONFIGURE}
        BUILD_COMMAND        ${PROTOBUF_MAKE}
        INSTALL_COMMAND      ${PROTOBUF_INSTALL}
)





