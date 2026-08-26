@echo off
title FrameForge AI - 24/7 Multi-Profile YouTube Watch Engine
echo ======================================================================
echo   Launching 24/7 Isolated YouTube Multi-Profile Engine
echo   Mode: 100% REAL Chrome Profiles (Direct on YouTube.com - NO Iframes)
echo ======================================================================
echo.

:: Detect browser executable (Chrome or Edge)
set "BROWSER_EXE="
if exist "C:\Program Files\Google\Chrome\Application\chrome.exe" (
    set "BROWSER_EXE=C:\Program Files\Google\Chrome\Application\chrome.exe"
) else if exist "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" (
    set "BROWSER_EXE=C:\Program Files (x86)\Google\Chrome\Application\chrome.exe"
) else if exist "%LOCALAPPDATA%\Google\Chrome\Application\chrome.exe" (
    set "BROWSER_EXE=%LOCALAPPDATA%\Google\Chrome\Application\chrome.exe"
) else if exist "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" (
    set "BROWSER_EXE=C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
) else (
    set "BROWSER_EXE=start"
)

echo Using Browser: %BROWSER_EXE%
echo.

:: Default to user's 5 videos chained in loop
set "DEFAULT_URL=https://www.youtube.com/watch?v=i66D5DN6nyg&list=PL7jH4yX_3gQ&loop=1&playlist=i66D5DN6nyg,d0yD2rKbxMQ,uNm4W0O6Agw,22eP7G84pkg,biO9YP67q78"

set /p INPUT_URL="Paste YouTube Video/Playlist URL (Press ENTER for your 5 Videos): "

if "%INPUT_URL%"=="" (
    set "TARGET_URL=%DEFAULT_URL%"
) else (
    set "TARGET_URL=%INPUT_URL%"
)

echo.
echo Target URL: %TARGET_URL%
echo.

set /p NUM_WINDOWS="How many Chrome Windows to launch? (e.g. 4, 8, 10, 12) [Default 8]: "
if "%NUM_WINDOWS%"=="" set "NUM_WINDOWS=8"

echo.
echo ======================================================================
echo Launching %NUM_WINDOWS% ISOLATED REAL CHROME SESSIONS...
echo ======================================================================
echo.

for /l %%i in (1, 1, %NUM_WINDOWS%) do (
    echo [%%i/%NUM_WINDOWS%] Starting Isolated Chrome Profile #%%i...
    start "" "%BROWSER_EXE%" --user-data-dir="%TEMP%\yt_profile_%%i" --no-first-run --no-default-browser-check --autoplay-policy=no-user-gesture-required --window-size=500,380 "%TARGET_URL%"
    timeout /t 2 >nul
)

echo.
echo ======================================================================
echo   ALL %NUM_WINDOWS% REAL CHROME SESSIONS ARE RUNNING ON YOUTUBE.COM!
echo.
echo   Calculated Output:
echo   - 8 Windows  = 192 Hours / Day (~20 Days to 4,000 hrs)
echo   - 12 Windows = 288 Hours / Day (~14 Days to 4,000 hrs)
echo.
echo   Keep windows open in background for 24/7 continuous watch time.
echo ======================================================================
echo.
pause
