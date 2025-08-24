# Install Best Packages and Add to PATH
param([string]$Category = "all")

$BestPacks = @{
    dev = @("Git.Git", "Microsoft.VisualStudioCode", "NodeJS.NodeJS", "Python.Python.3.12", "Docker.DockerDesktop")
    tools = @("7zip.7zip", "Microsoft.PowerToys", "Notepad++.Notepad++", "Microsoft.WindowsTerminal")
    media = @("VideoLAN.VLC", "OBSProject.OBSStudio", "Audacity.Audacity", "GIMP.GIMP")
    gaming = @("Valve.Steam", "EpicGames.EpicGamesLauncher", "Discord.Discord")
    productivity = @("Notion.Notion", "Slack.Slack", "Zoom.Zoom", "1Password.1Password")
}

function Install-Packs($packs) {
    foreach ($pack in $packs) {
        Write-Host "⚡ Installing $pack..." -ForegroundColor Cyan
        winget install $pack --silent --accept-package-agreements --accept-source-agreements
        if ($LASTEXITCODE -eq 0) { Write-Host "✅ $pack" -ForegroundColor Green }
        else { Write-Host "❌ $pack failed" -ForegroundColor Red }
    }
}

function Add-ToPath($paths) {
    $currentPath = [Environment]::GetEnvironmentVariable("PATH", "User")
    foreach ($path in $paths) {
        if ($currentPath -notlike "*$path*") {
            $newPath = "$currentPath;$path"
            [Environment]::SetEnvironmentVariable("PATH", $newPath, "User")
            Write-Host "📁 Added to PATH: $path" -ForegroundColor Yellow
        }
    }
}

# Install packages
if ($Category -eq "all") {
    $BestPacks.Values | ForEach-Object { Install-Packs $_ }
} else {
    Install-Packs $BestPacks[$Category]
}

# Add common paths
$CommonPaths = @(
    "$env:LOCALAPPDATA\Programs\Microsoft VS Code\bin",
    "$env:ProgramFiles\Git\bin",
    "$env:ProgramFiles\7-Zip",
    "$env:ProgramFiles\Notepad++",
    "$env:LOCALAPPDATA\Programs\Python\Python312\Scripts"
)

Add-ToPath $CommonPaths
Write-Host "🎉 Done! Restart terminal to use new PATH." -ForegroundColor Green