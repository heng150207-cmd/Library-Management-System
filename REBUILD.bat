@echo off
echo.
echo  ============================================
echo   Library Management System - Clean Rebuild
echo  ============================================
echo.

REM ── Step 1: Delete old build folder (this is why the fix wasn't working) ──
echo  [1/3] Deleting old build cache...
if exist build (
    rmdir /s /q build
    echo        Done. Old build deleted.
) else (
    echo        No old build found. OK.
)

REM ── Step 2: Run CMake to configure ──
echo.
echo  [2/3] Configuring with CMake...
cmake -B build -S .
if errorlevel 1 (
    echo.
    echo  ERROR: CMake configure failed. Check output above.
    pause
    exit /b 1
)

REM ── Step 3: Build ──
echo.
echo  [3/3] Building...
cmake --build build --config Release
if errorlevel 1 (
    echo.
    echo  ERROR: Build failed. Check output above.
    pause
    exit /b 1
)

echo.
echo  ============================================
echo   Build SUCCESS!
echo   Run: build\Release\LibraryManagement.exe
echo  ============================================
echo.
pause
