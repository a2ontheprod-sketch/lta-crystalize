LTA CRYSTALIZE VST3 — v1.0.1
================================

FIX: JUCE is now downloaded from a ZIP archive. Git is NOT required.

Requirements:
- Windows 10/11 64-bit
- Visual Studio 2022 with Desktop development with C++
- CMake 3.22+
- Internet connection for first build

Build:
1. Extract this ZIP to a normal folder.
2. Double-click BUILD_LTA_CRYSTALIZE.bat.
3. Wait for JUCE to download and the plugin to compile.
4. Find the VST3 here:
   build\LTA_Crystalize_artefacts\Release\VST3\LTA Crystalize.vst3

Install:
Copy the complete "LTA Crystalize.vst3" folder into:
C:\Program Files\Common Files\VST3\
Then restart FL Studio > Options > Manage plugins > Find installed plugins.

Audio:
One-button real-time bitcrusher: 8-bit quantisation and 4x sample-rate
reduction. Button ON = crushed, OFF = bypass. Mono and stereo supported.
