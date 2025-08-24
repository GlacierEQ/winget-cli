// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once
#include "Command.h"

namespace AppInstaller::CLI
{
    struct RecommendCommand final : public Command
    {
        RecommendCommand(std::string_view parent) : Command("recommend", { "suggest", "best" }, parent) {}

        std::vector<Argument> GetArguments() const override;

        Resource::LocString ShortDescription() const override;
        Resource::LocString LongDescription() const override;

        void Complete(Execution::Context& context, Execution::Args::Type valueType) const override;

        Utility::LocIndView HelpLink() const override;

    protected:
        void ValidateArgumentsInternal(Execution::Args& execArgs) const override;
        void ExecuteInternal(Execution::Context& context) const override;

    private:
        void ShowDeveloperPackages(Execution::Context& context) const;
        void ShowProductivityPackages(Execution::Context& context) const;
        void ShowMediaPackages(Execution::Context& context) const;
        void ShowGamingPackages(Execution::Context& context) const;
        void ShowUtilityPackages(Execution::Context& context) const;
        void ShowAllCategories(Execution::Context& context) const;
    };
}