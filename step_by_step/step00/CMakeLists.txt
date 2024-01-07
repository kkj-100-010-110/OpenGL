# To learn more about CMake
# https://cmake.org/
# https://cmake.org/getting-started/ 

# must-do, a command that specifies minimum CMake version  
cmake_minimum_required(VERSION 3.13)
# set variables
set(PROJECT_NAME cmake_project_example) # PROJECT_NAME = "cmake_project_example"
set(CMAKE_CXX_STANDARD 17) # variables beginning with "CMAKE_" is global

project(${PROJECT_NAME}) # set the name of the project
add_executable(${PROJECT_NAME} src/main.cpp) # add an executable to the project using the specified source files.

#
# configure : cmake -Bbuild . -DCMAKE_BUILD_TYPE=[Debug|Release]
#
# build : cmake --build build --config Debug
#