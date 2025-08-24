// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "pch.h"
#include "BundleCommand.h"
#include "InstallCommand.h"
#include "Workflows/WorkflowBase.h"
#include "Workflows/InstallFlow.h"
#include "Resources.h"

using namespace AppInstaller::CLI::Execution;

namespace AppInstaller::CLI
{
    std::vector<Argument> BundleCommand::GetArguments() const
    {
        return {
            Argument::ForType(Args::Type::BundleName),
            Argument::ForType(Args::Type::Silent),
            Argument::ForType(Args::Type::Interactive),
        };
    }

    Resource::LocString BundleCommand::ShortDescription() const
    {
        return { Resource::String::BundleCommandShortDescription };
    }

    Resource::LocString BundleCommand::LongDescription() const
    {
        return { Resource::String::BundleCommandLongDescription };
    }

    void BundleCommand::Complete(Execution::Context& context, Execution::Args::Type valueType) const
    {
        switch (valueType)
        {
        case Args::Type::BundleName:
            context.Reporter.Info() << "essentials developer productivity media gaming utility" << std::endl;
            break;
        }
    }

    Utility::LocIndView BundleCommand::HelpLink() const
    {
        return "https://aka.ms/winget-command-bundle"_liv;
    }

    void BundleCommand::ValidateArgumentsInternal(Args& execArgs) const
    {
        // No specific validation needed
    }

    void BundleCommand::ExecuteInternal(Context& context) const
    {
        auto bundleName = context.Args.GetArg(Args::Type::BundleName);
        
        if (bundleName.empty())
        {
            ShowAvailableBundles(context);
            return;
        }

        context.Reporter.Info() << "Installing " << bundleName << " bundle..." << std::endl << std::endl;

        if (bundleName == "essentials")
        {
            InstallEssentialsBundle(context);
        }
        else if (bundleName == "developer")
        {
            InstallDeveloperBundle(context);
        }
        else if (bundleName == "productivity")
        {
            InstallProductivityBundle(context);
        }
        else if (bundleName == "media")
        {
            InstallMediaBundle(context);
        }
        else if (bundleName == "gaming")
        {
            InstallGamingBundle(context);
        }
        else if (bundleName == "utility")
        {
            InstallUtilityBundle(context);
        }
        else
        {
            context.Reporter.Error() << "Unknown bundle: " << bundleName << std::endl;
            ShowAvailableBundles(context);
        }
    }

    void BundleCommand::InstallEssentialsBundle(Context& context) const
    {
        std::vector<std::string> packages = {
            "Microsoft.WindowsTerminal",
            "7zip.7zip",
            "Microsoft.PowerToys",
            "Notepad++.Notepad++",
            "VideoLAN.VLC",
            "Mozilla.Firefox",
            "Microsoft.VisualStudioCode"
        };
        InstallPackageList(context, packages, "Essentials");
    }

    void BundleCommand::InstallDeveloperBundle(Context& context) const
    {
        std::vector<std::string> packages = {
            "Microsoft.VisualStudioCode",
            "Git.Git",
            "Microsoft.WindowsTerminal",
            "Microsoft.PowerShell",
            "Docker.DockerDesktop",
            "Postman.Postman",
            "NodeJS.NodeJS",
            "Python.Python.3.12"
        };
        InstallPackageList(context, packages, "Developer");
    }

    void BundleCommand::InstallProductivityBundle(Context& context) const
    {
        std::vector<std::string> packages = {
            "Notion.Notion",
            "Slack.Slack",
            "Zoom.Zoom",
            "Adobe.Acrobat.Reader.64-bit",
            "Obsidian.Obsidian",
            "Microsoft.Teams",
            "1Password.1Password"
        };
        InstallPackageList(context, packages, "Productivity");
    }

    void BundleCommand::InstallMediaBundle(Context& context) const
    {
        std::vector<std::string> packages = {
            "VideoLAN.VLC",
            "Spotify.Spotify",
            "OBSProject.OBSStudio",
            "GIMP.GIMP",
            "Audacity.Audacity",
            "HandBrake.HandBrake",
            "Discord.Discord"
        };
        InstallPackageList(context, packages, "Media");
    }

    void BundleCommand::InstallGamingBundle(Context& context) const
    {
        std::vector<std::string> packages = {
            "Valve.Steam",
            "EpicGames.EpicGamesLauncher",
            "Microsoft.XboxApp",
            "Discord.Discord",
            "NVIDIA.GeForceExperience",
            "GOG.Galaxy"
        };
        InstallPackageList(context, packages, "Gaming");
    }

    void BundleCommand::InstallUtilityBundle(Context& context) const
    {
        std::vector<std::string> packages = {
            "7zip.7zip",
            "Microsoft.PowerToys",
            "WinDirStat.WinDirStat",
            "CCleaner.CCleaner",
            "Notepad++.Notepad++",
            "TreeSize.TreeSize",
            "Sysinternals.ProcessExplorer"
        };
        InstallPackageList(context, packages, "Utility");
    }

    void BundleCommand::ShowAvailableBundles(Context& context) const
    {
        context.Reporter.Info() << "📦 Available WinGet Bundles" << std::endl << std::endl;
        context.Reporter.Info() << "  🌟 essentials   - Essential apps for any Windows PC" << std::endl;
        context.Reporter.Info() << "  🚀 developer    - Complete development environment" << std::endl;
        context.Reporter.Info() << "  💼 productivity - Productivity and collaboration tools" << std::endl;
        context.Reporter.Info() << "  🎵 media        - Media creation and consumption apps" << std::endl;
        context.Reporter.Info() << "  🎮 gaming       - Gaming platforms and utilities" << std::endl;
        context.Reporter.Info() << "  🔧 utility      - System utilities and maintenance tools" << std::endl << std::endl;
        context.Reporter.Info() << "Usage: winget bundle <bundle-name>" << std::endl;
        context.Reporter.Info() << "Example: winget bundle developer" << std::endl;
    }

    void BundleCommand::InstallPackageList(Context& context, const std::vector<std::string>& packages, const std::string& bundleName) const
    {
        context.Reporter.Info() << "Installing " << bundleName << " bundle (" << packages.size() << " packages)..." << std::endl;
        
        size_t successCount = 0;
        size_t failureCount = 0;
        
        for (size_t i = 0; i < packages.size(); ++i)
        {
            const auto& packageId = packages[i];
            context.Reporter.Info() << std::endl << "[" << (i + 1) << "/" << packages.size() << "] Installing " << packageId << "..." << std::endl;
            
            try
            {
                // Create a new context for each package installation
                Context packageContext;
                packageContext.Args.AddArg(Args::Type::Query, packageId);
                
                // Copy relevant flags from the original context
                if (context.Args.Contains(Args::Type::Silent))
                {
                    packageContext.Args.AddArg(Args::Type::Silent);
                }
                if (context.Args.Contains(Args::Type::Interactive))
                {
                    packageContext.Args.AddArg(Args::Type::Interactive);
                }
                
                // Execute install workflow
                packageContext << Workflow::ReportExecutionStage(Workflow::ExecutionStage::Discovery);
                packageContext << Workflow::OpenSource();
                packageContext << Workflow::SearchSourceForSingle();
                packageContext << Workflow::HandleSearchResultFailures();
                packageContext << Workflow::EnsureOneMatchFromSearchResult(OperationType::Install);
                packageContext << Workflow::GetManifestFromPackage(Repository::PackageVersionKey::LatestVersion);
                packageContext << Workflow::ReportExecutionStage(Workflow::ExecutionStage::Execution);
                packageContext << Workflow::SelectInstaller();
                packageContext << Workflow::EnsureApplicableInstaller();
                packageContext << Workflow::DownloadInstaller();
                packageContext << Workflow::ExecuteInstaller();
                
                context.Reporter.Info() << "✅ " << packageId << " installed successfully" << std::endl;
                successCount++;
            }
            catch (...)
            {
                context.Reporter.Error() << "❌ Failed to install " << packageId << std::endl;
                failureCount++;
            }
        }
        
        context.Reporter.Info() << std::endl << "Bundle installation complete!" << std::endl;
        context.Reporter.Info() << "✅ Successful: " << successCount << std::endl;
        if (failureCount > 0)
        {
            context.Reporter.Info() << "❌ Failed: " << failureCount << std::endl;
        }
    }
}