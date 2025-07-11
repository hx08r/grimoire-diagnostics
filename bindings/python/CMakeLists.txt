cmake_minimum_required(VERSION 3.14)
project(grimoire_diag LANGUAGES CXX)

# Bring in pybind11 from vendored source
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../external/pybind11 external/pybind11)

# If building standalone (pip install .), add core if not already defined
if(NOT TARGET grimoire_core)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../core core)
endif()

# Build Python extension
pybind11_add_module(grimoire_diag bindings.cpp)
target_link_libraries(grimoire_diag PRIVATE grimoire_core)
target_include_directories(grimoire_diag PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include)

