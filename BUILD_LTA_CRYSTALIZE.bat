@echo off
setlocal
cd /d "%~dp0"
title LTA Crystalize v1.0.1 Builder
echo.
echo  LTA CRYSTALIZE v1.0.1 - WINDOWS VST3 BUILDER
echo  JUCE will be downloaded as a ZIP. Git is NOT required.
echo.

where cmake >nul 2>nul
if errorlevel 1 (
  echo ERROR: CMake was not found. Install CMake 3.22+ and enable Add to PATH.
  pause
  exit /b 1
)

if not exist build mkdir build
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 goto failed

cmake --build build --config Release --target LTA_Crystalize_VST3
if errorlevel 1 goto failed

echo.
echo BUILD COMPLETE.
echo VST3 output:
echo %CD%\build\LTA_Crystalize_artefacts\Release\VST3\LTA Crystalize.vst3
echo.
echo Copy that complete folder into:
echo C:\Program Files\Common Files\VST3\
echo.
pause
exit /b 0

:failed
echo.
echo BUILD FAILED. Send ChatGPT a screenshot of the error above.
pause
exit /b 1
