#!/bin/bash

cd "$(dirname "$0")" || exit 1

echo "--- Start Build/Test Pipeline for Linux ---"

# Compile tests first
echo ""
echo "[1/2] Compile tests in Debug mode"

mkdir -p build_tests
cd build_tests || exit 1

# configure cmake
if ! cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DBUILD_APP=OFF -DBUILD_TESTS=ON ..; then
    echo "Error: CMake config failed."
    exit 1
fi

# compile
if ! cmake --build .; then
    echo "Error: Build failed."
    exit 1
fi

# run tests
echo ""
echo "Run unit tests..."
if ! ctest -V; then
    echo "=========================================="
    echo "Error: Tests failed."
    echo "Executeable will not be built"
    echo "=========================================="
    exit 1
fi

cd ..


# Compile application
echo ""
echo "[2/2] Compile application in Release mode"

mkdir -p build_application
cd build_application || exit 1

# configure cmake
if ! cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DBUILD_APP=ON -DBUILD_TESTS=OFF ..; then
    echo "Error: CMake config failed."
    exit 1
fi

# compile
if ! cmake --build .; then
    echo "Error: Build failed."
    exit 1
fi

cd ..

# copy executeable to main directory
echo ""
echo "Copy executeable to main directory"

if ! cp "build_application/dhbw-advanced-software-engineering" "dhbw-advanced-software-engineering"; then
    echo "Error: Copy to main failed."
    exit 1
fi

echo "=========================================="
echo "[OK] Application successfully built"
echo "Run using ./dhbw-advanced-software-engineering"
echo "=========================================="