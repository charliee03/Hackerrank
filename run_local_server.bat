@echo off
echo Starting local server for HackerRank Solutions Website
echo Press Ctrl+C to stop the server when done
echo.

REM Change to the website directory
cd %~dp0\website

REM Run Python HTTP server
echo Server running at: http://localhost:8000
echo Open this URL in your browser to view the website
echo.

python -m http.server 8000

pause 