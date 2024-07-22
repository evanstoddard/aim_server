cmake_minimum_required(VERSION 3.20)

find_package(SQLite3 REQUIRED)

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
    backends/backend.c
    backends/sqlite3/sqlite3_backend.c
    ${CMAKE_SOURCE_DIR}/vendor/base32/base32.c
    ${CMAKE_SOURCE_DIR}/vendor/md5-c/md5.c
    utils/random.c
)

# Include Paths
set(AIM_SERVER_INCLUDES
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendor/
    ${CMAKE_SOURCE_DIR}/vendor/md5-c
)

# Libraries
set(AIM_SERVER_LIBS
    ${SQLite3_LIBRARIES}
)
include_directories(
    ${AIM_SERVER_INCLUDES}
    ${SQLite3_INCLUDE_DIRS}
)

# Create Executable
add_executable(aim_server_c
    ${AIM_SERVER_SOURCES}
)

# Link libraries
target_link_libraries(aim_server_c
    ${AIM_SERVER_LIBS}
)

add_custom_target(code_stats
    COMMAND ${CMAKE_SOURCE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)