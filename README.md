## Build and Test (C++ + Python)

```bash
# Clone with submodules
git clone --recurse-submodules <repo-url> grimore-diag
cd grimoire-diag

# Build
mkdir build
cd build
cmake ..
cmake --build . --config Release

# Run C++ unit tests
ctest --output-on-failure

# Run Python tests
cd ../python/test
python test_diag.py
python test_shared_log.py
