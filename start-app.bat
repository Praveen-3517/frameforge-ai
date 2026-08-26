@echo off
title FrameForge AI - Launch System
echo ========================================================
echo   Launching FrameForge AI Full-Stack (Backend + Frontend)
echo ========================================================
echo.

echo [1/2] Starting Python FastAPI Backend on http://localhost:8000 ...
start "FrameForge AI - Backend" cmd /k "cd /d %~dp0backend && .\.venv\Scripts\uvicorn.exe main:app --host 127.0.0.1 --port 8000 --reload"

timeout /t 2 >nul

echo [2/2] Starting React Vite Frontend on http://localhost:5173 ...
start "FrameForge AI - Frontend" cmd /k "cd /d %~dp0frontend && npm run dev"

timeout /t 3 >nul

echo.
echo ========================================================
echo   FrameForge AI is now RUNNING!
echo   - Frontend: http://localhost:5173
echo   - Backend:  http://localhost:8000
echo ========================================================
echo Opening browser...
start http://localhost:5173
