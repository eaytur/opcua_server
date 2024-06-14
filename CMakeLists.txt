cmake_minimum_required(VERSION 3.22)

project(
    opcua_server
    VERSION 0.1.0
    LANGUAGES C
)

find_package(open62541 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.c
    src/opcua.c
)

add_executable(opcua_server ${SOURCES})

target_link_libraries(opcua_server open62541::open62541)





