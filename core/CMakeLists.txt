# ==================================================
# Grimoire Core Library — CMakeLists.txt (grouped)
# ==================================================

# Gather all header and source files
file(GLOB_RECURSE CORE_HEADERS include/grimoire/*.hpp)
file(GLOB_RECURSE CORE_SOURCES src/*.cpp)

# Create core library target
add_library(grimoire_core ${CORE_HEADERS} ${CORE_SOURCES})

# Include directories
target_include_directories(grimoire_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ========================
# GoogleTest setup
# ========================
include(FetchContent)

# Fix MSVC runtime mismatch!
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
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
