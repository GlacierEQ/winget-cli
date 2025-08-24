# Setup Enhanced WinGet
# This script sets up the enhanced WinGet functionality

param(
    [Parameter(Mandatory=$false)]
    [switch]$InstallEssentials,
    
    [Parameter(Mandatory=$false)]
    [switch]$CreateAliases,
    
    [Parameter(Mandatory=$false)]
    [switch]$UpdatePath
)

function Write-Banner {
    Write-Host ""
    Write-Host "🚀 Enhanced WinGet Setup" -ForegroundColor Cyan
    Write-Host "========================" -ForegroundColor Cyan
    Write-Host ""
}

function Test-WinGetInstalled {
    try {
        $null = Get-Command winget -ErrorAction Stop
        return $true
    }
    catch {
        return $false
    }
}

function Install-WinGet {
    Write-Host "📦 Installing WinGet..." -ForegroundColor Yellow
    
    # Check if running on Windows 10/11
    $osVersion = [System.Environment]::OSVersion.Version
    if ($osVersion.Major -lt 10) {
        Write-Host "❌ WinGet requires Windows 10 or later" -ForegroundColor Red
        return $false
    }
    
    try {
        # Try to install from Microsoft Store
        Write-Host "Installing App Installer from Microsoft Store..." -ForegroundColor Cyan
        Start-Process "ms-windows-store://pdp/?productid=9nblggh4nns1"
        
        Write-Host "⏳ Please install App Installer from the Microsoft Store and run this script again." -ForegroundColor Yellow
        return $false
    }
    catch {
        Write-Host "❌ Failed to open Microsoft Store. Please install WinGet manually." -ForegroundColor Red
        Write-Host "Visit: https://github.com/microsoft/winget-cli/releases" -ForegroundColor Cyan
        return $false
    }
}

function Setup-EnhancedCommands {
    Write-Host "⚙️  Setting up enhanced commands..." -ForegroundColor Yellow
    
    $scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Path
    $enhancedScript = Join-Path $scriptPath "WinGet-Enhanced.ps1"
    
    if (-not (Test-Path $enhancedScript)) {
        Write-Host "❌ WinGet-Enhanced.ps1 not found in script directory" -ForegroundColor Red
        return $false
    }
    
    # Create profile directory if it doesn't exist
    $profileDir = Split-Path $PROFILE -Parent
    if (-not (Test-Path $profileDir)) {
        New-Item -ItemType Directory -Path $profileDir -Force | Out-Null
    }
    
    # Add functions to PowerShell profile
    $profileContent = @"

# Enhanced WinGet Functions
function winget-recommend { 
    param([string]`$Category)
    & "$enhancedScript" -Command recommend -Category `$Category
}

function winget-bundle { 
    param([string]`$Bundle)
    & "$enhancedScript" -Command bundle -Bundle `$Bundle
}

function winget-fast { 
    param([string[]]`$Packages)
    & "$enhancedScript" -Command install -Parallel -ParallelCount 4 @Packages
}

# Aliases for convenience
Set-Alias wgr winget-recommend
Set-Alias wgb winget-bundle
Set-Alias wgf winget-fast

Write-Host "🚀 Enhanced WinGet functions loaded!" -ForegroundColor Green
"@

    if (Test-Path $PROFILE) {
        $existingContent = Get-Content $PROFILE -Raw
        if ($existingContent -notlike "*Enhanced WinGet Functions*") {
            Add-Content $PROFILE $profileContent
            Write-Host "✅ Enhanced functions added to PowerShell profile" -ForegroundColor Green
        } else {
            Write-Host "ℹ️  Enhanced functions already in PowerShell profile" -ForegroundColor Yellow
        }
    } else {
        Set-Content $PROFILE $profileContent
        Write-Host "✅ PowerShell profile created with enhanced functions" -ForegroundColor Green
    }
    
    return $true
}

function Install-EssentialPackages {
    Write-Host "📦 Installing essential packages..." -ForegroundColor Yellow
    
    $essentials = @(
        "Microsoft.WindowsTerminal",
        "7zip.7zip",
        "Microsoft.PowerToys",
        "Notepad++.Notepad++",
        "VideoLAN.VLC",
        "Mozilla.Firefox",
        "Microsoft.VisualStudioCode"
    )
    
    $successCount = 0
    $totalCount = $essentials.Count
    
    foreach ($package in $essentials) {
        Write-Host "Installing $package..." -ForegroundColor Cyan
        try {
            $result = winget install $package --silent --accept-package-agreements --accept-source-agreements 2>&1
            if ($LASTEXITCODE -eq 0) {
                Write-Host "✅ $package installed successfully" -ForegroundColor Green
                $successCount++
            } else {
                Write-Host "⚠️  $package installation had issues" -ForegroundColor Yellow
            }
        }
        catch {
            Write-Host "❌ Failed to install $package" -ForegroundColor Red
        }
    }
    
    Write-Host ""
    Write-Host "📊 Installation Summary:" -ForegroundColor Yellow
    Write-Host "✅ Successful: $successCount/$totalCount" -ForegroundColor Green
    
    if ($successCount -lt $totalCount) {
        Write-Host "⚠️  Some packages may need manual installation" -ForegroundColor Yellow
    }
}

function Show-Usage {
    Write-Host "Enhanced WinGet is now set up! Here's how to use it:" -ForegroundColor Green
    Write-Host ""
    Write-Host "📋 Available Commands:" -ForegroundColor Yellow
    Write-Host "  winget-recommend [category]  - Show package recommendations"
    Write-Host "  winget-bundle [name]         - Install package bundles"
    Write-Host "  winget-fast [packages...]    - Fast parallel installation"
    Write-Host ""
    Write-Host "🔗 Aliases:" -ForegroundColor Yellow
    Write-Host "  wgr [category]               - Short for winget-recommend"
    Write-Host "  wgb [bundle]                 - Short for winget-bundle"
    Write-Host "  wgf [packages...]            - Short for winget-fast"
    Write-Host ""
    Write-Host "📚 Examples:" -ForegroundColor Cyan
    Write-Host "  wgr developer                - Show developer packages"
    Write-Host "  wgb essentials              - Install essential apps"
    Write-Host "  wgf Git.Git Docker.DockerDesktop - Fast install multiple packages"
    Write-Host ""
    Write-Host "🔄 Restart PowerShell to use the new functions!" -ForegroundColor Yellow
}

# Main execution
Write-Banner

# Check if WinGet is installed
if (-not (Test-WinGetInstalled)) {
    Write-Host "❌ WinGet is not installed or not in PATH" -ForegroundColor Red
    if (-not (Install-WinGet)) {
        exit 1
    }
} else {
    Write-Host "✅ WinGet is installed" -ForegroundColor Green
}

# Setup enhanced commands
if (Setup-EnhancedCommands) {
    Write-Host "✅ Enhanced commands configured" -ForegroundColor Green
} else {
    Write-Host "❌ Failed to setup enhanced commands" -ForegroundColor Red
    exit 1
}

# Install essential packages if requested
if ($InstallEssentials) {
    Install-EssentialPackages
}

# Show usage information
Show-Usage

Write-Host ""
Write-Host "🎉 Enhanced WinGet setup complete!" -ForegroundColor Green
Write-Host "   Restart PowerShell to start using the enhanced features." -ForegroundColor Cyan