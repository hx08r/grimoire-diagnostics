cmake_minimum_required(VERSION 3.14)
project(grimoire_diagnostics_cpp)

set(CMAKE_CXX_STANDARD 17)

# === Include our headers ===
include_directories(include)

# === Core library ===
add_library(diagnostics_lib STATIC
  src/Diagnostics.cpp
  src/FileExporter.cpp
  src/DiagnosticAggregator.cpp
  src/CorrelationGraph.cpp
)
set_target_properties(diagnostics_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(diagnostics_lib PUBLIC include)

# === Main executable ===
add_executable(grimoire_diagnostics_cpp
  src/main.cpp
)
target_link_libraries(grimoire_diagnostics_cpp diagnostics_lib)

# === GoogleTest ===
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For MSVC: force same runtime library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# === Unit tests ===
add_executable(DiagnosticsTests tests/DiagnosticsTests.cpp)
target_link_libraries(DiagnosticsTests diagnostics_lib gtest gtest_main)
add_test(NAME DiagnosticsTests COMMAND DiagnosticsTests)

add_executable(FileExporterTests tests/FileExporterTests.cpp)
target_link_libraries(FileExporterTests diagnostics_lib gtest gtest_main)
add_test(NAME FileExporterTests COMMAND FileExporterTests)

add_executable(CorrelationGraphTests tests/CorrelationGraphTests.cpp)
target_link_libraries(CorrelationGraphTests diagnostics_lib gtest gtest_main)
add_test(NAME CorrelationGraphTests COMMAND CorrelationGraphTests)

add_subdirectory(external/pybind11)

pybind11_add_module(grimoire_diag python/bindings.cpp)
target_link_libraries(grimoire_diag PRIVATE diagnostics_lib)

add_custom_command(TARGET grimoire_diag POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:grimoire_diag> ${CMAKE_SOURCE_DIR}/python/test
)


