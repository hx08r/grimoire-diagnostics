cmake_minimum_required(VERSION 3.14)
project(grimoire_diagnostics_cpp)

set(CMAKE_CXX_STANDARD 17)

# === Include our headers ===
include_directories(include)

# === Core library ===
add_library(diagnostics_lib
  src/Diagnostics.cpp
  src/FileExporter.cpp
  src/DiagnosticAggregator.cpp
)
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
add_executable(unit_tests
  tests/DiagnosticsTests.cpp
  tests/FileExporterTests.cpp
)
target_link_libraries(unit_tests
  diagnostics_lib
  gtest
  gtest_main
)

add_test(NAME AllTests COMMAND unit_tests)

add_subdirectory(external/pybind11)

pybind11_add_module(grimoire_diag python/bindings.cpp)
target_link_libraries(grimoire_diag PRIVATE diagnostics_lib)

add_custom_command(TARGET grimoire_diag POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:grimoire_diag> ${CMAKE_SOURCE_DIR}/python/
)


