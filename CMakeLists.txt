cmake_minimum_required(VERSION 3.5.0)

set(VERSION "0.0.1")
set(PROJECT_NAME "HTTPServerInC")

project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES C)

add_executable(${PROJECT_NAME}
    main.c

    Utils/Utils.h
    Utils/HTMLReader.h Utils/HTMLReader.c
    Utils/Allocator.h Utils/Allocator.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    RESOURCES_PATH=\"${CMAKE_SOURCE_DIR}/HTMLSrc\"
)
