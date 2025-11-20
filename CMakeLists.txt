cmake_minimum_required(VERSION 4.1)
project(ProjectChess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

add_executable(Chess ${SOURCES})

if(APPLE)
    target_link_libraries(Chess
        PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/apple/libglfw3.a
    )

    target_link_libraries(Chess
        PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework OpenGL"
    )
elseif(WIN32)
    target_link_options(Chess PRIVATE -static -static-libgcc -static-libstdc++ -Wl,--whole-archive -lpthread -Wl,--no-whole-archive)
    target_link_libraries(Chess
        PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/win/libglfw3.a
    )

    target_link_libraries(Chess PRIVATE opengl32 gdi32 user32 kernel32)
endif()
