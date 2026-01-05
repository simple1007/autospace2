cmake_minimum_required(VERSION 3.10)
# cmake_minimum_required(VERSION 3.10)
# set(CMAKE_PREFIX_PATH "C:/Users/ty341/AppData/Roaming/Python/Python313t/site-packages/pybind11")
# set(PYTHON_INCLUDE_DIR "C:/Program Files/Python313/include")
# set(DPYTHON_LIBRAR "C:/Program Files/Python313/libs")
message("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# set(PYTHON_LIBRARY "C:/Program Files/Python313/libs")
# set(PYTHON_INCLUDE_DIR "C:/Program Files/Python313/include")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
project(auto2)
# add_library(my_library src/utils/utils.cpp)
include_directories(src)
include_directories("$ENV{VCPKG_ROOT}/installed/x64-linux/include")
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
#find_package(pybind11 CONFIG REQUIRED)
# find_package(utf8cpp REQUIRED)
# find_package(rapidjSON REQUIRED)
find_package(utf8cpp CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

# add_subdirectory(pybind11)
pybind11_add_module(
    _auto2 
    src/main.cpp
    src/utils.cpp 
    src/AutoModule.cpp 
    src/AutoSpace.cpp 
)
install(TARGETS _auto2 LIBRARY DESTINATION auto2)
# add_executable(
#     main 
#     src/AutoSpace.cpp
#     src/utils.cpp 
#     src/AutoModule.cpp 
# )
# target_link_libraries(_auto2 PRIVATE RapidJSON rapidjson)
# target_link_libraries(_auto2 PRIVATE utf8::cpp utf8cpp::utf8cpp)
#install(TARGETS auto2 DESTINATION ${SKBUILD_PROJECT_NAME})
target_link_libraries(_auto2 PRIVATE pybind11::embed) 
# target_link_libraries(_auto2 utf8::cpp utf8cpp::utf8cpp)
# target_link_libraries(_auto2 rapidjson)
