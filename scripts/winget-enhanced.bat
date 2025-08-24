@echo off
REM WinGet Enhanced - Batch script for enhanced WinGet functionality
REM Usage: winget-enhanced.bat [command] [options]

setlocal enabledelayedexpansion

if "%1"=="" goto :help
if "%1"=="help" goto :help
if "%1"=="recommend" goto :recommend
if "%1"=="bundle" goto :bundle
if "%1"=="fast-install" goto :fast_install

:help
echo.
echo 🚀 WinGet Enhanced - Making Package Management Better!
echo =================================================
echo.
echo Available commands:
echo   recommend [category]  - Show recommended packages
echo   bundle [name]        - Install package bundles
echo   fast-install [pkg]   - Fast installation with optimizations
echo.
echo Categories/Bundles:
echo   essentials, developer, productivity, media, gaming, utility
echo.
echo Examples:
echo   winget-enhanced.bat recommend developer
echo   winget-enhanced.bat bundle essentials
echo   winget-enhanced.bat fast-install "Microsoft.VisualStudioCode"
echo.
goto :end

:recommend
if "%2"=="" (
    echo.
    echo 🌟 Available Package Categories:
    echo.
    echo   🚀 developer    - Essential tools for developers
    echo   💼 productivity - Boost your productivity
    echo   🎵 media        - Media creation and consumption
    echo   🎮 gaming       - Gaming platforms and tools
    echo   🔧 utility      - System utilities and tools
    echo   🌟 essentials   - Essential apps for any Windows PC
    echo.
    goto :end
)

if "%2"=="developer" (
    echo.
    echo 🚀 Best Developer Packages:
    echo.
    echo   📦 Microsoft.VisualStudioCode
    echo   📦 Git.Git
    echo   📦 Microsoft.WindowsTerminal
    echo   📦 Microsoft.PowerShell
    echo   📦 Docker.DockerDesktop
    echo   📦 Postman.Postman
    echo   📦 NodeJS.NodeJS
    echo   📦 Python.Python.3.12
    echo.
    echo Install all with:
    echo winget install Microsoft.VisualStudioCode Git.Git Microsoft.WindowsTerminal Microsoft.PowerShell Docker.DockerDesktop Postman.Postman NodeJS.NodeJS Python.Python.3.12
    echo.
)

if "%2"=="essentials" (
    echo.
    echo 🌟 Essential Packages:
    echo.
    echo   📦 Microsoft.WindowsTerminal
    echo   📦 7zip.7zip
    echo   📦 Microsoft.PowerToys
    echo   📦 Notepad++.Notepad++
    echo   📦 VideoLAN.VLC
    echo   📦 Mozilla.Firefox
    echo   📦 Microsoft.VisualStudioCode
    echo.
    echo Install all with:
    echo winget install Microsoft.WindowsTerminal 7zip.7zip Microsoft.PowerToys Notepad++.Notepad++ VideoLAN.VLC Mozilla.Firefox Microsoft.VisualStudioCode
    echo.
)

goto :end

:bundle
if "%2"=="" (
    echo.
    echo 📦 Available Package Bundles:
    echo.
    echo   🌟 essentials   - Essential apps for any Windows PC
    echo   🚀 developer    - Complete development environment
    echo   💼 productivity - Productivity and collaboration tools
    echo   🎵 media        - Media creation and consumption apps
    echo   🎮 gaming       - Gaming platforms and utilities
    echo   🔧 utility      - System utilities and maintenance tools
    echo.
    goto :end
)

echo.
echo 📦 Installing %2 bundle...
echo.

if "%2"=="essentials" (
    echo Installing essential packages...
    winget install Microsoft.WindowsTerminal --silent --accept-package-agreements --accept-source-agreements
    winget install 7zip.7zip --silent --accept-package-agreements --accept-source-agreements
    winget install Microsoft.PowerToys --silent --accept-package-agreements --accept-source-agreements
    winget install Notepad++.Notepad++ --silent --accept-package-agreements --accept-source-agreements
    winget install VideoLAN.VLC --silent --accept-package-agreements --accept-source-agreements
    winget install Mozilla.Firefox --silent --accept-package-agreements --accept-source-agreements
    winget install Microsoft.VisualStudioCode --silent --accept-package-agreements --accept-source-agreements
)

if "%2"=="developer" (
    echo Installing developer packages...
    winget install Microsoft.VisualStudioCode --silent --accept-package-agreements --accept-source-agreements
    winget install Git.Git --silent --accept-package-agreements --accept-source-agreements
    winget install Microsoft.WindowsTerminal --silent --accept-package-agreements --accept-source-agreements
    winget install Microsoft.PowerShell --silent --accept-package-agreements --accept-source-agreements
    winget install Docker.DockerDesktop --silent --accept-package-agreements --accept-source-agreements
    winget install Postman.Postman --silent --accept-package-agreements --accept-source-agreements
    winget install NodeJS.NodeJS --silent --accept-package-agreements --accept-source-agreements
    winget install Python.Python.3.12 --silent --accept-package-agreements --accept-source-agreements
)

echo.
echo ✅ Bundle installation complete!
goto :end

:fast_install
if "%2"=="" (
    echo ❌ Please specify a package to install
    goto :end
)

echo.
echo ⚡ Fast installing %2 with optimizations...
echo.
winget install %2 --silent --accept-package-agreements --accept-source-agreements --force
echo.
echo ✅ Fast installation complete!
goto :end

:end
endlocal