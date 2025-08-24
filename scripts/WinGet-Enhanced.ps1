# WinGet Enhanced - Additional functionality for WinGet
# This script provides enhanced features for WinGet package management

param(
    [Parameter(Mandatory=$false)]
    [string]$Command,
    
    [Parameter(Mandatory=$false)]
    [string]$Category,
    
    [Parameter(Mandatory=$false)]
    [string]$Bundle,
    
    [Parameter(Mandatory=$false)]
    [switch]$Fast,
    
    [Parameter(Mandatory=$false)]
    [switch]$Parallel,
    
    [Parameter(Mandatory=$false)]
    [int]$ParallelCount = 4
)

# Best packages configuration
$BestPackages = @{
    essentials = @(
        "Microsoft.WindowsTerminal",
        "7zip.7zip",
        "Microsoft.PowerToys",
        "Notepad++.Notepad++",
        "VideoLAN.VLC",
        "Mozilla.Firefox",
        "Microsoft.VisualStudioCode"
    )
    developer = @(
        "Microsoft.VisualStudioCode",
        "Git.Git",
        "Microsoft.WindowsTerminal",
        "Microsoft.PowerShell",
        "Docker.DockerDesktop",
        "Postman.Postman",
        "NodeJS.NodeJS",
        "Python.Python.3.12",
        "JetBrains.IntelliJIDEA.Community",
        "Microsoft.VisualStudio.2022.Community"
    )
    productivity = @(
        "Notion.Notion",
        "Slack.Slack",
        "Zoom.Zoom",
        "Adobe.Acrobat.Reader.64-bit",
        "Obsidian.Obsidian",
        "Microsoft.Teams",
        "1Password.1Password",
        "Dropbox.Dropbox",
        "RescueTime.RescueTime"
    )
    media = @(
        "VideoLAN.VLC",
        "Spotify.Spotify",
        "OBSProject.OBSStudio",
        "GIMP.GIMP",
        "Audacity.Audacity",
        "HandBrake.HandBrake",
        "Discord.Discord",
        "Kodi.Kodi",
        "Canva.Canva"
    )
    gaming = @(
        "Valve.Steam",
        "EpicGames.EpicGamesLauncher",
        "Microsoft.XboxApp",
        "Discord.Discord",
        "NVIDIA.GeForceExperience",
        "GOG.Galaxy",
        "Razer.Synapse3",
        "AMD.AMDSoftwareAdrenalinEdition",
        "Twitch.Twitch",
        "Ubisoft.Connect"
    )
    utility = @(
        "7zip.7zip",
        "Microsoft.PowerToys",
        "WinDirStat.WinDirStat",
        "CCleaner.CCleaner",
        "Notepad++.Notepad++",
        "TreeSize.TreeSize",
        "Sysinternals.ProcessExplorer",
        "Microsoft.Sysinternals.ProcessMonitor",
        "Malwarebytes.Malwarebytes",
        "WinRAR.WinRAR"
    )
}

function Show-WinGetBanner {
    Write-Host "🚀 WinGet Enhanced - Making Package Management Better!" -ForegroundColor Cyan
    Write-Host "=================================================" -ForegroundColor Cyan
    Write-Host ""
}

function Show-RecommendedPackages {
    param([string]$Category)
    
    if (-not $Category) {
        Write-Host "🌟 Available Package Categories:" -ForegroundColor Yellow
        Write-Host ""
        Write-Host "  🚀 developer    - Essential tools for developers" -ForegroundColor Green
        Write-Host "  💼 productivity - Boost your productivity" -ForegroundColor Green
        Write-Host "  🎵 media        - Media creation and consumption" -ForegroundColor Green
        Write-Host "  🎮 gaming       - Gaming platforms and tools" -ForegroundColor Green
        Write-Host "  🔧 utility      - System utilities and tools" -ForegroundColor Green
        Write-Host "  🌟 essentials   - Essential apps for any Windows PC" -ForegroundColor Green
        Write-Host ""
        Write-Host "Usage: .\WinGet-Enhanced.ps1 -Command recommend -Category <category>" -ForegroundColor Cyan
        return
    }
    
    if (-not $BestPackages.ContainsKey($Category)) {
        Write-Host "❌ Unknown category: $Category" -ForegroundColor Red
        return
    }
    
    $emoji = @{
        developer = "🚀"
        productivity = "💼"
        media = "🎵"
        gaming = "🎮"
        utility = "🔧"
        essentials = "🌟"
    }
    
    Write-Host "$($emoji[$Category]) Best $Category Packages:" -ForegroundColor Yellow
    Write-Host ""
    
    foreach ($package in $BestPackages[$Category]) {
        Write-Host "  📦 $package" -ForegroundColor Green
    }
    
    Write-Host ""
    Write-Host "Install all with: winget install " -NoNewline -ForegroundColor Cyan
    Write-Host ($BestPackages[$Category] -join " ") -ForegroundColor White
}

function Install-PackageBundle {
    param([string]$Bundle)
    
    if (-not $Bundle) {
        Write-Host "📦 Available Package Bundles:" -ForegroundColor Yellow
        Write-Host ""
        Write-Host "  🌟 essentials   - Essential apps for any Windows PC" -ForegroundColor Green
        Write-Host "  🚀 developer    - Complete development environment" -ForegroundColor Green
        Write-Host "  💼 productivity - Productivity and collaboration tools" -ForegroundColor Green
        Write-Host "  🎵 media        - Media creation and consumption apps" -ForegroundColor Green
        Write-Host "  🎮 gaming       - Gaming platforms and utilities" -ForegroundColor Green
        Write-Host "  🔧 utility      - System utilities and maintenance tools" -ForegroundColor Green
        Write-Host ""
        Write-Host "Usage: .\WinGet-Enhanced.ps1 -Command bundle -Bundle <bundle-name>" -ForegroundColor Cyan
        return
    }
    
    if (-not $BestPackages.ContainsKey($Bundle)) {
        Write-Host "❌ Unknown bundle: $Bundle" -ForegroundColor Red
        return
    }
    
    $packages = $BestPackages[$Bundle]
    Write-Host "📦 Installing $Bundle bundle ($($packages.Count) packages)..." -ForegroundColor Yellow
    Write-Host ""
    
    $successCount = 0
    $failureCount = 0
    
    for ($i = 0; $i -lt $packages.Count; $i++) {
        $package = $packages[$i]
        $progress = [math]::Round(($i / $packages.Count) * 100)
        
        Write-Progress -Activity "Installing Bundle" -Status "Installing $package" -PercentComplete $progress
        Write-Host "[$($i + 1)/$($packages.Count)] Installing $package..." -ForegroundColor Cyan
        
        try {
            $result = winget install $package --silent --accept-package-agreements --accept-source-agreements 2>&1
            if ($LASTEXITCODE -eq 0) {
                Write-Host "✅ $package installed successfully" -ForegroundColor Green
                $successCount++
            } else {
                Write-Host "❌ Failed to install $package" -ForegroundColor Red
                $failureCount++
            }
        }
        catch {
            Write-Host "❌ Failed to install $package" -ForegroundColor Red
            $failureCount++
        }
    }
    
    Write-Progress -Activity "Installing Bundle" -Completed
    Write-Host ""
    Write-Host "Bundle installation complete!" -ForegroundColor Yellow
    Write-Host "✅ Successful: $successCount" -ForegroundColor Green
    if ($failureCount -gt 0) {
        Write-Host "❌ Failed: $failureCount" -ForegroundColor Red
    }
}

function Install-PackagesParallel {
    param([string[]]$Packages)
    
    Write-Host "⚡ Installing packages in parallel (max $ParallelCount concurrent)..." -ForegroundColor Yellow
    Write-Host ""
    
    $jobs = @()
    $completed = 0
    
    foreach ($package in $Packages) {
        # Wait if we have too many jobs running
        while ((Get-Job -State Running).Count -ge $ParallelCount) {
            Start-Sleep -Milliseconds 100
            
            # Check for completed jobs
            $completedJobs = Get-Job -State Completed
            foreach ($job in $completedJobs) {
                $result = Receive-Job $job
                Remove-Job $job
                $completed++
                
                if ($result.Success) {
                    Write-Host "✅ [$completed/$($Packages.Count)] $($result.Package) completed" -ForegroundColor Green
                } else {
                    Write-Host "❌ [$completed/$($Packages.Count)] $($result.Package) failed" -ForegroundColor Red
                }
            }
        }
        
        # Start new job
        $job = Start-Job -ScriptBlock {
            param($pkg)
            try {
                $result = winget install $pkg --silent --accept-package-agreements --accept-source-agreements 2>&1
                return @{ Package = $pkg; Success = ($LASTEXITCODE -eq 0) }
            }
            catch {
                return @{ Package = $pkg; Success = $false }
            }
        } -ArgumentList $package
        
        $jobs += $job
        Write-Host "🚀 Started installation of $package" -ForegroundColor Cyan
    }
    
    # Wait for remaining jobs
    while ((Get-Job -State Running).Count -gt 0) {
        Start-Sleep -Milliseconds 100
        
        $completedJobs = Get-Job -State Completed
        foreach ($job in $completedJobs) {
            $result = Receive-Job $job
            Remove-Job $job
            $completed++
            
            if ($result.Success) {
                Write-Host "✅ [$completed/$($Packages.Count)] $($result.Package) completed" -ForegroundColor Green
            } else {
                Write-Host "❌ [$completed/$($Packages.Count)] $($result.Package) failed" -ForegroundColor Red
            }
        }
    }
    
    # Clean up any remaining jobs
    Get-Job | Remove-Job -Force
    
    Write-Host ""
    Write-Host "Parallel installation complete!" -ForegroundColor Yellow
}

function Show-Help {
    Write-Host "WinGet Enhanced - Usage:" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Recommend packages:" -ForegroundColor Cyan
    Write-Host "  .\WinGet-Enhanced.ps1 -Command recommend [-Category <category>]"
    Write-Host ""
    Write-Host "Install package bundles:" -ForegroundColor Cyan
    Write-Host "  .\WinGet-Enhanced.ps1 -Command bundle [-Bundle <bundle-name>]"
    Write-Host ""
    Write-Host "Fast parallel installation:" -ForegroundColor Cyan
    Write-Host "  .\WinGet-Enhanced.ps1 -Command install -Parallel -ParallelCount 4 package1 package2 ..."
    Write-Host ""
    Write-Host "Available categories/bundles:" -ForegroundColor Green
    Write-Host "  essentials, developer, productivity, media, gaming, utility"
    Write-Host ""
}

# Main execution
Show-WinGetBanner

switch ($Command.ToLower()) {
    "recommend" {
        Show-RecommendedPackages -Category $Category
    }
    "bundle" {
        Install-PackageBundle -Bundle $Bundle
    }
    "install" {
        if ($Parallel -and $args.Count -gt 0) {
            Install-PackagesParallel -Packages $args
        } else {
            Write-Host "❌ Please specify packages to install with -Parallel flag" -ForegroundColor Red
        }
    }
    default {
        Show-Help
    }
}