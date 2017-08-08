//
// This file is part of the gda cpp utility library.
// Copyright (c) 2017 Alexander van Renen. All rights reserved.
//
// Purpose - Helper for creating interactive user interfaces for the shell.
// -------------------------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------------------------
#include <functional>
#include <string>
#include <vector>
#include <regex>
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
namespace cli {
// -------------------------------------------------------------------------------------------------
class Command {
   std::string pattern;
   std::regex pattern_re;
   std::function<bool(const std::vector<std::string> &args)> action;

   std::vector<std::string> getArguments(const std::string &input);

   friend class CommandLineInterface;

public:
   Command(const std::string &trigger, std::function<bool(const std::vector<std::string> &args)> action);
   Command(const std::regex &trigger, std::function<bool(const std::vector<std::string> &args)> action);

   bool matches(const std::string &input) const;

   bool process(const std::string &input);
   const std::string &getPattern() const;
};
// -------------------------------------------------------------------------------------------------
} // End of namespace cli
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------