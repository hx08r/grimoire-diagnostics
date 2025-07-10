from skbuild import setup  # Uses scikit-build to call CMake
from setuptools import find_packages

setup(
    name="grimoire_diag",
    version="0.1.0",
    description="Universal Diagnostics Spine — Python bindings",
    author="Your Name",
    packages=find_packages(),
    package_dir={"": "src"},
    cmake_install_dir="src/grimoire_diag",
    python_requires=">=3.7",
)
