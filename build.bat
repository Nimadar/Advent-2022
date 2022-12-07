@echo off

rem windows sdk version
set CPFLAGS=-nologo -FC -Od -Zi

where cl /q
if %ERRORLEVEL% NEQ 0 (
    call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

if not exist build mkdir build
pushd build
echo compile...
cl %CPFLAGS% ..\src\main.cpp
popd