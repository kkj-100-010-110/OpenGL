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

include(Dependency.cmake)
# Line 15 - 40 move to 'Dependency.cmake'
# # to use ExternalProject functions
# include(ExternalProject)

# # set up variables about dependency
# set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
# set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
# set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# # spdlog: fast logger library
# ExternalProject_Add( # https://cmake.org/cmake/help/latest/module/ExternalProject.html#
#     dep_spdlog
#     GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
#     GIT_TAG "v1.x"
#     GIT_SHALLOW 1
#     UPDATE_COMMAND ""
#     PATCH_COMMAND ""
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
#     TEST_COMMAND ""
# )
# # add spdlog to the dependency list and library
# set(DEP_LIST ${DEP_LIST} dep_spdlog)
# if (MSVC) # for Windows
#   set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)
# else()
#   set(DEP_LIBS ${DEP_LIBS} spdlog) # for Mac
# endif()

# to add include/lib options to the project
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

# set the dependency list to build first. If there is not this command, compilation get started in parallel.
add_dependencies(${PROJECT_NAME} ${DEP_LIST})

#
# configure : cmake -Bbuild . -DCMAKE_BUILD_TYPE=[Debug|Release]
#
# build : cmake --build build --config Debug
#