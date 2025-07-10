# Contributing Guide

## General Guidelines

- Use C++20.
- Keep core logic language-agnostic in the `core/` directory.
- Python bindings must stay isolated in `bindings/python/` and link only to the `grimoire_core` library.
- The `pybind11` dependency is managed as a submodule under `external/`.

## Submodules

Whenever you clone or pull changes, run:

```
git submodule update --init --recursive
```

This ensures `pybind11` is available for building the Python bindings.

## Building

To build the project, run:

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

To build the core library as a shared library for faster linking:

```
cmake .. -DBUILD_SHARED_LIBS=ON
```

To disable tests if you only want the library and bindings:

```
cmake .. -DBUILD_TESTING=OFF
```

## Testing

Run C++ unit tests:

```
ctest --verbose -C Debug
```

Run Python bindings tests:

```
cd bindings/python
pytest test/
```

## Pull Request Requirements

- Include unit tests for new features.
- All C++ unit tests must pass.
- All Python tests must pass.
- Keep CMake targets modular and consistent.
- Use clear naming for new bindings and test files.
