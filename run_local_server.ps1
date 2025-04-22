# PowerShell script to run a local HTTP server
Write-Host "Starting local server for HackerRank Solutions Website" -ForegroundColor Green
Write-Host "Press Ctrl+C to stop the server when done" -ForegroundColor Yellow
Write-Host ""

# Change to the website directory
Set-Location -Path "$PSScriptRoot\website"

# Run Python HTTP server
Write-Host "Server running at: http://localhost:8000" -ForegroundColor Cyan
Write-Host "Open this URL in your browser to view the website" -ForegroundColor Cyan
Write-Host ""

python -m http.server 8000 