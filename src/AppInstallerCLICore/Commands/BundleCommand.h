// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once
#include "Command.h"

namespace AppInstaller::CLI
{
    struct BundleCommand final : public Command
    {
        BundleCommand(std::string_view parent) : Command("bundle", { "pack", "collection" }, parent) {}

        std::vector<Argument> GetArguments() const override;

        Resource::LocString ShortDescription() const override;
        Resource::LocString LongDescription() const override;

        void Complete(Execution::Context& context, Execution::Args::Type valueType) const override;

        Utility::LocIndView HelpLink() const override;

    protected:
        void ValidateArgumentsInternal(Execution::Args& execArgs) const override;
        void ExecuteInternal(Execution::Context& context) const override;

    private:
        void InstallDeveloperBundle(Execution::Context& context) const;
        void InstallProductivityBundle(Execution::Context& context) const;
        void InstallMediaBundle(Execution::Context& context) const;
        void InstallGamingBundle(Execution::Context& context) const;
        void InstallUtilityBundle(Execution::Context& context) const;
        void InstallEssentialsBundle(Execution::Context& context) const;
        void ShowAvailableBundles(Execution::Context& context) const;
        void InstallPackageList(Execution::Context& context, const std::vector<std::string>& packages, const std::string& bundleName) const;
    };
}