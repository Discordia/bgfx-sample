cmake_minimum_required(VERSION 3.16)
project(bgfx_sample)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp)

if(APPLE)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    include_directories(/usr/local/bgfx/include)

    file(GLOB BGFX_SHARED_LIBRARY /usr/local/bgfx/libbgfx-shared-libRelease.dylib)

    add_executable(bgfx_sample ${SOURCE_FILES})
    target_link_libraries(bgfx_sample ${BGFX_SHARED_LIBRARY} ${SDL2_LIBRARIES})
    target_link_libraries(bgfx_sample "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(SDL2 REQUIRED SDL2)
    include_directories(${SDL2_INCLUDE_DIRS})

    add_executable(bgfx_sample ${SOURCE_FILES})
    target_link_libraries(bgfx_sample ${SDL2_LIBRARIES})
endif()