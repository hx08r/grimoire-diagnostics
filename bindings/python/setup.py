from skbuild import setup  # Uses scikit-build to call CMake
from setuptools import find_packages

setup(
    name="grimoire_diag",
    version="0.1.0",
    description="Universal Diagnostics Spine — Python bindings",
    author="Mayank Tewari",
    packages=[],
    cmake_install_dir="grimoire_diag",
    python_requires=">=3.7",
)
