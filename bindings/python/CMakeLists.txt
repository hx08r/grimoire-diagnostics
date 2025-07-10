# Python bindings with pybind11
pybind11_add_module(grimoire_diag bindings.cpp)
target_link_libraries(grimoire_diag PRIVATE grimoire_core)
target_include_directories(grimoire_diag PRIVATE ${CMAKE_SOURCE_DIR}/core/include)

# This ensures the output path aligns with cmake_install_dir
set_target_properties(grimoire_diag PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src/grimoire_diag)
