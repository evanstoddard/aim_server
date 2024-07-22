cmake_minimum_required(VERSION 3.20)

find_package(SQLite3 REQUIRED)

# Additional Options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

# Additional compiler set up
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Sources
set(CREATE_USER_SOURCES
    main.c
    ${CMAKE_SOURCE_DIR}/src/backends/backend.c
    ${CMAKE_SOURCE_DIR}/src/backends/sqlite3/sqlite3_backend.c
    ${CMAKE_SOURCE_DIR}/vendor/md5-c/md5.c
)

# Include Paths
set(CREATE_USER_INCLUDES
    ${CMAKE_SOURCE_DIR}/src
)

message("Create user CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Libraries
set(CREATE_USER_LIBS
    ${SQLite3_LIBRARIES}
)
include_directories(
    ${CREATE_USER_INCLUDES}
    ${SQLite3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/vendor/md5-c
)

# Create Executable
add_executable(create_user
    ${CREATE_USER_SOURCES}
)

# Link libraries
target_link_libraries(create_user
    ${CREATE_USER_LIBS}
)

