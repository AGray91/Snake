@echo off
echo Generate Visual Studio 2022 x86 project files
cmake -G "Visual Studio 17 2022" -A Win32 -S . -B Build/VS2022/x86