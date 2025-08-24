@echo off
REM Quick install best packages

echo 🚀 Installing Best Packages...

REM Dev essentials
winget install Git.Git --silent --accept-package-agreements --accept-source-agreements
winget install Microsoft.VisualStudioCode --silent --accept-package-agreements --accept-source-agreements
winget install NodeJS.NodeJS --silent --accept-package-agreements --accept-source-agreements
winget install Python.Python.3.12 --silent --accept-package-agreements --accept-source-agreements

REM Tools
winget install 7zip.7zip --silent --accept-package-agreements --accept-source-agreements
winget install Microsoft.PowerToys --silent --accept-package-agreements --accept-source-agreements
winget install Notepad++.Notepad++ --silent --accept-package-agreements --accept-source-agreements
winget install Microsoft.WindowsTerminal --silent --accept-package-agreements --accept-source-agreements

REM Media
winget install VideoLAN.VLC --silent --accept-package-agreements --accept-source-agreements
winget install OBSProject.OBSStudio --silent --accept-package-agreements --accept-source-agreements

echo ✅ Installation complete!
echo 🔄 Restart your terminal to use new tools.
pause