@echo off
setlocal

cd /d "%~dp0"

echo --- Start Build/Test Pipeline for Windows/MinGW ---

:: Compile tests first
echo.
echo [1/2] Compile tests in Debug mode

if not exist build_tests mkdir build_tests
cd build_tests

:: configure cmake
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DBUILD_APP=OFF -DBUILD_TESTS=ON ..
if %errorlevel% neq 0 (
    echo Error: CMake config failed.
    exit /b %errorlevel%
)

:: compile
cmake --build .
if %errorlevel% neq 0 (
    echo Error: Build failed.
    exit /b %errorlevel%
)

:: run tests
echo.
echo Run unit tests...
ctest -V
if %errorlevel% neq 0 (
    echo ==========================================
    echo Error: Tests failed ^(Exit Code: %errorlevel%^)
    echo Executeable will not be built
    echo ==========================================
    cd ..
    exit /b 1
)

cd ..


:: Compile application
echo.
echo [2/2] Compile application in Release mode

if not exist build_application mkdir build_application
cd build_application

:: configure cmake
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DBUILD_APP=ON -DBUILD_TESTS=OFF ..
if %errorlevel% neq 0 (
    echo Error: CMake config failed.
    exit /b %errorlevel%
)

:: compile
cmake --build .
if %errorlevel% neq 0 (
    echo Error: Build failed.
    exit /b %errorlevel%
)

cd ..

:: copy executeable to main directory
echo.
echo Copy executeable to main directory
copy /Y "build_application\dhbw-advanced-software-engineering.exe" "dhbw-advanced-software-engineering.exe" > nul

if %errorlevel% neq 0 (
    echo Error: Copy to main failed.
    exit /b %errorlevel%
)

echo ==========================================
echo [OK] Application successfully built
echo Run using "%~dp0dhbw-advanced-software-engineering.exe"
echo ==========================================