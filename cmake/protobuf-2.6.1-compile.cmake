function(PROTOC_COMPILE PROTO_PATH PROTO_NAME OUTPUT_PATH OUTPUT_LIBRARY)
    set(TO_INCLUDE_DIR
            --cpp_out=${OUTPUT_PATH}
            --proto_path=${PROTO_PATH}
            )
    #PROTO_PATH:proto文件存在的路径
    #导出变量的名称
    set(PROTO_VAR     ${PROTO_NAME}_PROTO)
    set(CC_VAR        ${PROTO_NAME}_PROTO_CC)
    set(H_VAR         ${PROTO_NAME}_PROTO_H)


    set(PROTO         ${PROTO_PATH}/${PROTO_NAME}.proto)
    set(CC            ${OUTPUT_PATH}/${PROTO_NAME}.pb.cc)
    set(H             ${OUTPUT_PATH}/${PROTO_NAME}.pb.h)

    #导出保存目标变量名的文件
    set(${PROTO_VAR}  ${PROTO}  PARENT_SCOPE)
    set(${CC_VAR}     ${CC}     PARENT_SCOPE)
    set(${H_VAR}      ${H}      PARENT_SCOPE)


    ADD_CUSTOM_COMMAND(
            OUTPUT   ${CC}  ${H}
            COMMAND  ${PROTOBUF_COMPILER}  ${TO_INCLUDE_DIR}  ${PROTO}
    )

    add_library(${OUTPUT_LIBRARY}  ${CC}  ${H})

endfunction()

include_directories(${CMAKE_BINARY_DIR}/server_client)