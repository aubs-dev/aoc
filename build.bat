@echo off
setlocal
cd /D "%~dp0"

REM --- Check usage
if "%1"=="run" set TARGET_CHOSEN=1
if "%1"=="clean" set TARGET_CHOSEN=1

if not defined TARGET_CHOSEN (
    echo WARN: no build target selected: use one of the following "run" or "clean".
    exit /B 1
)

REM --- Define the compiler & linker
set CFLAGS=-std=gnu11 -Wall -Wextra -Wstrict-prototypes -Wno-missing-braces -Wno-unused-parameter -Wno-unused-function -fansi-escape-codes -fdeclspec -fdiagnostics-absolute-paths -fdiagnostics-color=always
set LFLAGS=

set DEFINES=-D_CRT_SECURE_NO_WARNINGS

set CLANG_DEBUG=call clang -g -O0 -DGEM_DEBUG %CFLAGS% %LFLAGS% %DEFINES%
set CLANG_RELEASE=call clang -g -O2 -DGEM_RELEASE %CFLAGS% %LFLAGS% %DEFINES%

REM --- Prepare directories
if "%1"=="clean" (
    echo [ Cleaning build directories ]
    if exist bin rmdir bin /S /Q
    exit /B 0
)

REM --- Set the compiler and linker's arguments based on what build-type is chosen
set LINKER=-Xlinker /SUBSYSTEM:console

if "%2"=="release" (
    set COMPILER=%CLANG_RELEASE%
) else if "%2"=="debug" (
    set COMPILER=%CLANG_DEBUG%
) else (
    echo WARN: no build type selected: use one of the following "debug" or "release".
    exit /B 1
)

REM --- Set up conditions
set DO_RUN=

if "%1"=="run" (
    set DO_RUN=1
)

if not exist bin mkdir bin

pushd bin
REM --- Compile & Run EXE: aoc
if defined DO_RUN (
    echo [ Compile EXE: aoc ]
    %COMPILER% ..\src\day_02.c -o aoc.exe %LINKER% || exit /B 1
    echo [ Running: aoc ]
    if exist aoc.exe start /WAIT /B aoc.exe
)
popd
