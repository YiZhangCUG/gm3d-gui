cmake_minimum_required(VERSION 3.15.2)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-10)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -O2 -lpthread -framework Cocoa")

project(GM3D_GUI VERSION 0.2 LANGUAGES CXX)

add_subdirectory(src)
