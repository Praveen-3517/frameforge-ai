@echo off
title FrameForge AI - 24/7 Multi-Track YouTube Live Stream Engine
color 0E

echo ======================================================================
echo          🕉️  FRAMEFORGE AI — 24/7 YOUTUBE LIVE STREAM ENGINE
echo ======================================================================
echo.
echo   Mode: 100%% Continuous Multi-Bhajan Playlist Broadcast
echo   Streams all your MP4 videos and MP3 audio tracks in an infinite loop!
echo.
echo ======================================================================
echo.

:: Ensure bhajans folder exists
if not exist "bhajans" (
    mkdir "bhajans"
)

:: Check for virtual environment Python
set "PYTHON_EXE="
if exist "backend\.venv\Scripts\python.exe" (
    set "PYTHON_EXE=backend\.venv\Scripts\python.exe"
) else if exist ".venv\Scripts\python.exe" (
    set "PYTHON_EXE=.venv\Scripts\python.exe"
) else (
    set "PYTHON_EXE=python"
)

echo [✓] Using Python: %PYTHON_EXE%
echo.

:: Launch Python 24/7 Streamer Engine
"%PYTHON_EXE%" "backend\services\live_streamer.py"

echo.
echo ======================================================================
echo   Live Stream Ended.
echo ======================================================================
pause
