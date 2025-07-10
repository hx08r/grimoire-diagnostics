cmake_minimum_required(VERSION 3.14)

project(grimoire_diag LANGUAGES CXX)

# Make sure pybind11 is found if vendored
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../external/pybind11 external/pybind11)

# Build the Python extension module
pybind11_add_module(grimoire_diag bindings.cpp)

# Link core library if needed
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../core core)
target_link_libraries(grimoire_diag PRIVATE grimoire_core)
target_include_directories(grimoire_diag PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include)
