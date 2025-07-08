cmake_minimum_required(VERSION 3.10)
project(grimoire_diagnostics_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(grimoire_diagnostics_cpp
    src/Diagnostics.cpp
    src/FileExporter.cpp
    src/main.cpp
)

include_directories(include)

# You may need to add this if using nlohmann/json as header-only
# find_package(nlohmann_json CONFIG REQUIRED)
# target_link_libraries(grimoire_diagnostics_cpp PRIVATE nlohmann_json::nlohmann_json)
