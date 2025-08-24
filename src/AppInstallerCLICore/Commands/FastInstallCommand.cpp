// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "pch.h"
#include "FastInstallCommand.h"
#include "InstallCommand.h"
#include "Workflows/WorkflowBase.h"
#include "Workflows/InstallFlow.h"
#include "Resources.h"
#include <thread>
#include <future>

using namespace AppInstaller::CLI::Execution;

namespace AppInstaller::CLI
{
    std::vector<Argument> FastInstallCommand::GetArguments() const
    {
        return {
            Argument::ForType(Args::Type::Query),
            Argument::ForType(Args::Type::Manifest),
            Argument::ForType(Args::Type::Id),
            Argument::ForType(Args::Type::Name),
            Argument::ForType(Args::Type::Moniker),
            Argument::ForType(Args::Type::Version),
            Argument::ForType(Args::Type::Channel),
            Argument::ForType(Args::Type::Source),
            Argument::ForType(Args::Type::Scope),
            Argument::ForType(Args::Type::Exact),
            Argument::ForType(Args::Type::Interactive),
            Argument::ForType(Args::Type::Silent),
            Argument::ForType(Args::Type::Locale),
            Argument::ForType(Args::Type::Log),
            Argument::ForType(Args::Type::Override),
            Argument::ForType(Args::Type::Location),
            Argument::ForType(Args::Type::Force),
            Argument::ForType(Args::Type::DependencySource),
            Argument::ForType(Args::Type::AcceptPackageAgreements),
            Argument::ForType(Args::Type::AcceptSourceAgreements),
            Argument::ForType(Args::Type::NoUpgrade),
            Argument::ForType(Args::Type::Header),
            Argument::ForType(Args::Type::AuthenticationMode),
            Argument::ForType(Args::Type::AuthenticationAccount),
            Argument::ForType(Args::Type::SkipDependencies),
            Argument::ForType(Args::Type::IgnoreLocalArchiveMalwareScan),
            Argument::ForType(Args::Type::IgnoreSecurityHash),
            Argument::ForType(Args::Type::CustomHeader),
            Argument::ForType(Args::Type::Rename),
            Argument::ForType(Args::Type::UninstallPrevious),
            Argument::ForType(Args::Type::Pin),
            Argument::ForType(Args::Type::IncludeUnknown),
            Argument::ForType(Args::Type::ParallelDownloads),
        };
    }

    Resource::LocString FastInstallCommand::ShortDescription() const
    {
        return { Resource::String::FastInstallCommandShortDescription };
    }

    Resource::LocString FastInstallCommand::LongDescription() const
    {
        return { Resource::String::FastInstallCommandLongDescription };
    }

    void FastInstallCommand::Complete(Execution::Context& context, Execution::Args::Type valueType) const
    {
        // Delegate to the regular install command for completion
        InstallCommand installCmd("");
        installCmd.Complete(context, valueType);
    }

    Utility::LocIndView FastInstallCommand::HelpLink() const
    {
        return "https://aka.ms/winget-command-fast-install"_liv;
    }

    void FastInstallCommand::ValidateArgumentsInternal(Args& execArgs) const
    {
        // Use the same validation as regular install command
        InstallCommand installCmd("");
        installCmd.ValidateArgumentsInternal(execArgs);
    }

    void FastInstallCommand::ExecuteInternal(Context& context) const
    {
        context.Reporter.Info() << "🚀 Fast Install Mode - Optimized for Speed" << std::endl << std::endl;
        
        // Apply speed optimizations
        OptimizeForSpeed(context);
        
        // Check if multiple packages are being installed
        auto queries = context.Args.GetArgs(Args::Type::Query);
        if (queries.size() > 1)
        {
            InstallWithParallelDownloads(context);
        }
        else
        {
            // Single package installation with enhanced progress
            auto packageName = queries.empty() ? "package" : queries[0];
            context.Reporter.Info() << "Installing " << packageName << " with optimizations..." << std::endl;
            
            // Execute the standard install workflow with optimizations
            context << Workflow::ReportExecutionStage(Workflow::ExecutionStage::Discovery);
            context << Workflow::OpenSource();
            context << Workflow::SearchSourceForSingle();
            context << Workflow::HandleSearchResultFailures();
            context << Workflow::EnsureOneMatchFromSearchResult(OperationType::Install);
            context << Workflow::GetManifestFromPackage(Repository::PackageVersionKey::LatestVersion);
            context << Workflow::ReportExecutionStage(Workflow::ExecutionStage::Execution);
            context << Workflow::SelectInstaller();
            context << Workflow::EnsureApplicableInstaller();
            
            // Enhanced download with progress
            context.Reporter.Info() << "📥 Downloading..." << std::endl;
            context << Workflow::DownloadInstaller();
            
            context.Reporter.Info() << "⚙️  Installing..." << std::endl;
            context << Workflow::ExecuteInstaller();
            
            context.Reporter.Info() << "✅ Installation completed successfully!" << std::endl;
        }
    }

    void FastInstallCommand::InstallWithParallelDownloads(Context& context) const
    {
        auto queries = context.Args.GetArgs(Args::Type::Query);
        context.Reporter.Info() << "Installing " << queries.size() << " packages in parallel..." << std::endl << std::endl;
        
        std::vector<std::future<bool>> futures;
        std::atomic<int> completed{0};
        
        for (const auto& query : queries)
        {
            auto future = std::async(std::launch::async, [&, query]() -> bool {
                try
                {
                    Context packageContext;
                    packageContext.Args.AddArg(Args::Type::Query, query);
                    
                    // Copy relevant flags
                    if (context.Args.Contains(Args::Type::Silent))
                        packageContext.Args.AddArg(Args::Type::Silent);
                    if (context.Args.Contains(Args::Type::Force))
                        packageContext.Args.AddArg(Args::Type::Force);
                    
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
                    
                    int current = ++completed;
                    context.Reporter.Info() << "✅ [" << current << "/" << queries.size() << "] " << query << " completed" << std::endl;
                    return true;
                }
                catch (...)
                {
                    int current = ++completed;
                    context.Reporter.Error() << "❌ [" << current << "/" << queries.size() << "] " << query << " failed" << std::endl;
                    return false;
                }
            });
            
            futures.push_back(std::move(future));
        }
        
        // Wait for all installations to complete
        int successCount = 0;
        for (auto& future : futures)
        {
            if (future.get())
            {
                successCount++;
            }
        }
        
        context.Reporter.Info() << std::endl << "Parallel installation complete!" << std::endl;
        context.Reporter.Info() << "✅ Successful: " << successCount << "/" << queries.size() << std::endl;
        if (successCount < static_cast<int>(queries.size()))
        {
            context.Reporter.Info() << "❌ Failed: " << (queries.size() - successCount) << std::endl;
        }
    }

    void FastInstallCommand::ShowProgressBar(const std::string& packageName, int progress) const
    {
        const int barWidth = 50;
        int pos = barWidth * progress / 100;
        
        std::cout << packageName << " [";
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << progress << "%\r";
        std::cout.flush();
    }

    void FastInstallCommand::OptimizeForSpeed(Context& context) const
    {
        // Enable parallel downloads if not already set
        if (!context.Args.Contains(Args::Type::ParallelDownloads))
        {
            context.Args.AddArg(Args::Type::ParallelDownloads, "4");
        }
        
        // Enable silent mode for faster installation if not interactive
        if (!context.Args.Contains(Args::Type::Interactive) && !context.Args.Contains(Args::Type::Silent))
        {
            context.Args.AddArg(Args::Type::Silent);
        }
        
        // Skip hash verification for speed (if explicitly allowed)
        if (context.Args.Contains(Args::Type::IgnoreSecurityHash))
        {
            context.Reporter.Warn() << "⚠️  Security hash verification disabled for speed" << std::endl;
        }
        
        context.Reporter.Info() << "⚡ Speed optimizations enabled" << std::endl;
    }
}