# Grimoire Diagnostics

This project provides a portable, modular diagnostics library with language bindings for Python and other ecosystems.

## Clone with Submodules

Clone this repository with its submodules:

```
git clone --recurse-submodules https://github.com/your/repo.git
```

If you forget, run:

```
git submodule update --init --recursive
```

## Build Instructions

1. Create a build directory:

```
mkdir build
cd build
```

2. Configure and build with CMake:

```
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

3. Run C++ unit tests:

```
ctest --verbose -C Debug
```

4. Build and test Python bindings:

```
cd bindings/python
pip install .
pytest test/
```

## Build Options

- To build the core library as a shared library:

  ```
  cmake .. -DBUILD_SHARED_LIBS=ON
  ```

- To disable building tests:

  ```
  cmake .. -DBUILD_TESTING=OFF
  ```

- For faster incremental builds, use Ninja:

  ```
  cmake .. -G Ninja
  ```

## Project Structure

- `core/` — C++ core library.
- `bindings/python/` — Python bindings.
- `external/pybind11/` — vendored pybind11 submodule.
- `tests/` — C++ unit tests.
- `.github/workflows/` — CI configuration.
