# to use ExternalProject functions
include(ExternalProject)

# set up variables about dependency
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
ExternalProject_Add( # https://cmake.org/cmake/help/latest/module/ExternalProject.html#
    dep_spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
    TEST_COMMAND ""
)
# add spdlog to the dependency list and library
set(DEP_LIST ${DEP_LIST} dep_spdlog)
if (MSVC) # for Windows
  set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)
else()
  set(DEP_LIBS ${DEP_LIBS} spdlog) # for Mac
endif()