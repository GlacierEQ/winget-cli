// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "pch.h"
#include "RecommendCommand.h"
#include "Workflows/WorkflowBase.h"
#include "Resources.h"

using namespace AppInstaller::CLI::Execution;

namespace AppInstaller::CLI
{
    std::vector<Argument> RecommendCommand::GetArguments() const
    {
        return {
            Argument::ForType(Args::Type::RecommendCategory),
        };
    }

    Resource::LocString RecommendCommand::ShortDescription() const
    {
        return { Resource::String::RecommendCommandShortDescription };
    }

    Resource::LocString RecommendCommand::LongDescription() const
    {
        return { Resource::String::RecommendCommandLongDescription };
    }

    void RecommendCommand::Complete(Execution::Context& context, Execution::Args::Type valueType) const
    {
        switch (valueType)
        {
        case Args::Type::RecommendCategory:
            context.Reporter.Info() << "developer productivity media gaming utility" << std::endl;
            break;
        }
    }

    Utility::LocIndView RecommendCommand::HelpLink() const
    {
        return "https://aka.ms/winget-command-recommend"_liv;
    }

    void RecommendCommand::ValidateArgumentsInternal(Args& execArgs) const
    {
        // No specific validation needed
    }

    void RecommendCommand::ExecuteInternal(Context& context) const
    {
        auto category = context.Args.GetArg(Args::Type::RecommendCategory);
        
        if (category.empty())
        {
            ShowAllCategories(context);
        }
        else if (category == "developer")
        {
            ShowDeveloperPackages(context);
        }
        else if (category == "productivity")
        {
            ShowProductivityPackages(context);
        }
        else if (category == "media")
        {
            ShowMediaPackages(context);
        }
        else if (category == "gaming")
        {
            ShowGamingPackages(context);
        }
        else if (category == "utility")
        {
            ShowUtilityPackages(context);
        }
        else
        {
            context.Reporter.Error() << "Unknown category: " << category << std::endl;
            context.Reporter.Info() << "Available categories: developer, productivity, media, gaming, utility" << std::endl;
        }
    }

    void RecommendCommand::ShowDeveloperPackages(Context& context) const
    {
        context.Reporter.Info() << "🚀 Best Developer Packages:" << std::endl << std::endl;
        
        struct Package { std::string id; std::string name; std::string description; };
        std::vector<Package> packages = {
            {"Microsoft.VisualStudioCode", "Visual Studio Code", "Lightweight but powerful source code editor"},
            {"Git.Git", "Git", "Distributed version control system"},
            {"Microsoft.WindowsTerminal", "Windows Terminal", "Modern terminal application"},
            {"Microsoft.PowerShell", "PowerShell", "Cross-platform automation and configuration tool"},
            {"Docker.DockerDesktop", "Docker Desktop", "Containerization platform"},
            {"Postman.Postman", "Postman", "API development environment"},
            {"JetBrains.IntelliJIDEA.Community", "IntelliJ IDEA Community", "Java IDE"},
            {"Microsoft.VisualStudio.2022.Community", "Visual Studio Community", "Full-featured IDE"},
            {"NodeJS.NodeJS", "Node.js", "JavaScript runtime"},
            {"Python.Python.3.12", "Python", "Programming language"}
        };

        for (const auto& pkg : packages)
        {
            context.Reporter.Info() << "  📦 " << pkg.name << " (" << pkg.id << ")" << std::endl;
            context.Reporter.Info() << "     " << pkg.description << std::endl << std::endl;
        }
        
        context.Reporter.Info() << "Install all with: winget install " << packages[0].id;
        for (size_t i = 1; i < packages.size(); ++i)
        {
            context.Reporter.Info() << " " << packages[i].id;
        }
        context.Reporter.Info() << std::endl;
    }

    void RecommendCommand::ShowProductivityPackages(Context& context) const
    {
        context.Reporter.Info() << "💼 Best Productivity Packages:" << std::endl << std::endl;
        
        struct Package { std::string id; std::string name; std::string description; };
        std::vector<Package> packages = {
            {"Microsoft.Office", "Microsoft Office", "Complete office suite"},
            {"Notion.Notion", "Notion", "All-in-one workspace"},
            {"Slack.Slack", "Slack", "Team communication platform"},
            {"Zoom.Zoom", "Zoom", "Video conferencing"},
            {"Adobe.Acrobat.Reader.64-bit", "Adobe Acrobat Reader", "PDF viewer and editor"},
            {"Obsidian.Obsidian", "Obsidian", "Knowledge management"},
            {"Microsoft.Teams", "Microsoft Teams", "Collaboration platform"},
            {"Dropbox.Dropbox", "Dropbox", "Cloud storage"},
            {"1Password.1Password", "1Password", "Password manager"},
            {"RescueTime.RescueTime", "RescueTime", "Time tracking"}
        };

        for (const auto& pkg : packages)
        {
            context.Reporter.Info() << "  📦 " << pkg.name << " (" << pkg.id << ")" << std::endl;
            context.Reporter.Info() << "     " << pkg.description << std::endl << std::endl;
        }
    }

    void RecommendCommand::ShowMediaPackages(Context& context) const
    {
        context.Reporter.Info() << "🎵 Best Media Packages:" << std::endl << std::endl;
        
        struct Package { std::string id; std::string name; std::string description; };
        std::vector<Package> packages = {
            {"VideoLAN.VLC", "VLC Media Player", "Universal media player"},
            {"Spotify.Spotify", "Spotify", "Music streaming service"},
            {"OBSProject.OBSStudio", "OBS Studio", "Live streaming and recording"},
            {"Adobe.Photoshop", "Adobe Photoshop", "Image editing software"},
            {"GIMP.GIMP", "GIMP", "Free image editor"},
            {"Audacity.Audacity", "Audacity", "Audio editing software"},
            {"HandBrake.HandBrake", "HandBrake", "Video transcoder"},
            {"Kodi.Kodi", "Kodi", "Media center"},
            {"Discord.Discord", "Discord", "Voice and text chat"},
            {"Canva.Canva", "Canva", "Graphic design platform"}
        };

        for (const auto& pkg : packages)
        {
            context.Reporter.Info() << "  📦 " << pkg.name << " (" << pkg.id << ")" << std::endl;
            context.Reporter.Info() << "     " << pkg.description << std::endl << std::endl;
        }
    }

    void RecommendCommand::ShowGamingPackages(Context& context) const
    {
        context.Reporter.Info() << "🎮 Best Gaming Packages:" << std::endl << std::endl;
        
        struct Package { std::string id; std::string name; std::string description; };
        std::vector<Package> packages = {
            {"Valve.Steam", "Steam", "Gaming platform"},
            {"EpicGames.EpicGamesLauncher", "Epic Games Launcher", "Game store and launcher"},
            {"Microsoft.XboxApp", "Xbox App", "Xbox gaming on PC"},
            {"Discord.Discord", "Discord", "Gaming communication"},
            {"Razer.Synapse3", "Razer Synapse", "Gaming peripherals software"},
            {"NVIDIA.GeForceExperience", "GeForce Experience", "NVIDIA graphics optimization"},
            {"AMD.AMDSoftwareAdrenalinEdition", "AMD Software", "AMD graphics software"},
            {"Twitch.Twitch", "Twitch", "Game streaming platform"},
            {"GOG.Galaxy", "GOG Galaxy", "DRM-free gaming platform"},
            {"Ubisoft.Connect", "Ubisoft Connect", "Ubisoft game launcher"}
        };

        for (const auto& pkg : packages)
        {
            context.Reporter.Info() << "  📦 " << pkg.name << " (" << pkg.id << ")" << std::endl;
            context.Reporter.Info() << "     " << pkg.description << std::endl << std::endl;
        }
    }

    void RecommendCommand::ShowUtilityPackages(Context& context) const
    {
        context.Reporter.Info() << "🔧 Best Utility Packages:" << std::endl << std::endl;
        
        struct Package { std::string id; std::string name; std::string description; };
        std::vector<Package> packages = {
            {"7zip.7zip", "7-Zip", "File archiver"},
            {"Microsoft.PowerToys", "PowerToys", "Windows system utilities"},
            {"WinDirStat.WinDirStat", "WinDirStat", "Disk usage analyzer"},
            {"Malwarebytes.Malwarebytes", "Malwarebytes", "Anti-malware protection"},
            {"CCleaner.CCleaner", "CCleaner", "System cleaner"},
            {"Notepad++.Notepad++", "Notepad++", "Advanced text editor"},
            {"WinRAR.WinRAR", "WinRAR", "Archive manager"},
            {"TreeSize.TreeSize", "TreeSize", "Disk space manager"},
            {"Sysinternals.ProcessExplorer", "Process Explorer", "Advanced task manager"},
            {"Microsoft.Sysinternals.ProcessMonitor", "Process Monitor", "System monitoring tool"}
        };

        for (const auto& pkg : packages)
        {
            context.Reporter.Info() << "  📦 " << pkg.name << " (" << pkg.id << ")" << std::endl;
            context.Reporter.Info() << "     " << pkg.description << std::endl << std::endl;
        }
    }

    void RecommendCommand::ShowAllCategories(Context& context) const
    {
        context.Reporter.Info() << "🌟 WinGet Package Recommendations" << std::endl << std::endl;
        context.Reporter.Info() << "Choose a category to see the best packages:" << std::endl << std::endl;
        context.Reporter.Info() << "  🚀 developer    - Essential tools for developers" << std::endl;
        context.Reporter.Info() << "  💼 productivity - Boost your productivity" << std::endl;
        context.Reporter.Info() << "  🎵 media        - Media creation and consumption" << std::endl;
        context.Reporter.Info() << "  🎮 gaming       - Gaming platforms and tools" << std::endl;
        context.Reporter.Info() << "  🔧 utility      - System utilities and tools" << std::endl << std::endl;
        context.Reporter.Info() << "Usage: winget recommend <category>" << std::endl;
        context.Reporter.Info() << "Example: winget recommend developer" << std::endl;
    }
}