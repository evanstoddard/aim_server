cmake_minimum_required(VERSION 3.20)

# Additional Options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/server)

# Additional compiler set up
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Sources
set(AIM_SERVER_SOURCES
    main.c
    socket_server/socket_server.c
    connection_manager.c
    connection.c
    auth_server.c
    bos_server.c
    oscar/flap_decoder.c
    oscar/snac_decoder.c
    oscar/tlv_decoder.c
    oscar/tlv_encoder.c
    oscar/flap_encoder.c
    oscar/snac_encoder.c
    oscar/tlv_encoder.c
    model/client.c
    handlers/bucp.c
    handlers/oservice.c
    memory/buffer.c
)

# Include Paths
set(AIM_SERVER_INCLUDES
    ${CMAKE_SOURCE_DIR}/src
)

# Libraries
set(AIM_SERVER_LIBS

)

include_directories(
    ${AIM_SERVER_INCLUDES}
)

# Create Executable
add_executable(aim_server_c
    ${AIM_SERVER_SOURCES}
)

# Link libraries
link_libraries(aim_server_c
    ${AIM_SERVER_LIBS}
)

add_custom_target(code_stats
    COMMAND ${CMAKE_SOURC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)