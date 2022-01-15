cmake_minimum_required (VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)

# set c++ version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# project name
project (framework)

add_executable (framework main.cpp)

# Include sdl2 packages
INCLUDE(FindPkgConfig)

# searching for sdl2 package
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

# Linking SDL2 library with our project.
target_link_libraries(framework ${SDL2_LIBRARIES})
