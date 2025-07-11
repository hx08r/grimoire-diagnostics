# ==================================================
# Grimoire Core Library — CMakeLists.txt (grouped)
# ==================================================

cmake_minimum_required(VERSION 3.14)
project(grimoire_core LANGUAGES CXX)

file(GLOB_RECURSE CORE_HEADERS include/grimoire/*.hpp)
file(GLOB_RECURSE CORE_SOURCES src/*.cpp)

# Remove any driver files
list(REMOVE_ITEM CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(grimoire_core ${CORE_HEADERS} ${CORE_SOURCES})
target_include_directories(grimoire_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(grimoire_core PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_executable(grimoire_demo src/main.cpp)
target_link_libraries(grimoire_demo PRIVATE grimoire_core)

# ========================
# GoogleTest setup
# ========================
include(FetchContent)

# Fix MSVC runtime mismatch!
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)




FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ========================
# Define test groups
# ========================

# Diagnostics tests
set(DIAGNOSTIC_TESTS
  tests/DiagnosticsTests.cpp
)

add_executable(diagnostics_tests ${DIAGNOSTIC_TESTS})
target_link_libraries(diagnostics_tests PRIVATE grimoire_core gtest_main)
add_test(NAME DiagnosticsTests COMMAND diagnostics_tests)

# Correlation graph tests
set(CORRELATION_TESTS
  tests/CorrelationGraphTests.cpp
)

add_executable(correlation_tests ${CORRELATION_TESTS})
target_link_libraries(correlation_tests PRIVATE grimoire_core gtest_main)
add_test(NAME CorrelationTests COMMAND correlation_tests)

# File exporter tests
set(EXPORTER_TESTS
  tests/FileExporterTests.cpp
)

add_executable(exporter_tests ${EXPORTER_TESTS})
target_link_libraries(exporter_tests PRIVATE grimoire_core gtest_main)
add_test(NAME ExporterTests COMMAND exporter_tests)
