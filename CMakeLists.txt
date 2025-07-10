cmake_minimum_required(VERSION 3.14)
project(GrimoireDiagnostics VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add pybind11 if vendored
add_subdirectory(external/pybind11)

# Add core library
add_subdirectory(core)

# Add Python bindings
add_subdirectory(bindings/python)
