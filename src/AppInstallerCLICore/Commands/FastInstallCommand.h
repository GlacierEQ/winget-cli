// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once
#include "Command.h"

namespace AppInstaller::CLI
{
    struct FastInstallCommand final : public Command
    {
        FastInstallCommand(std::string_view parent) : Command("fast-install", { "finstall", "quick" }, parent) {}

        std::vector<Argument> GetArguments() const override;

        Resource::LocString ShortDescription() const override;
        Resource::LocString LongDescription() const override;

        void Complete(Execution::Context& context, Execution::Args::Type valueType) const override;

        Utility::LocIndView HelpLink() const override;

    protected:
        void ValidateArgumentsInternal(Execution::Args& execArgs) const override;
        void ExecuteInternal(Execution::Context& context) const override;

    private:
        void InstallWithParallelDownloads(Execution::Context& context) const;
        void ShowProgressBar(const std::string& packageName, int progress) const;
        void OptimizeForSpeed(Execution::Context& context) const;
    };
}