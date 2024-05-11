cmake_minimum_required(VERSION 3.0)
project(halma-minmax-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")


file(GLOB_RECURSE SOURCE_FILES "src/*.*")
add_executable(main ${SOURCE_FILES})


