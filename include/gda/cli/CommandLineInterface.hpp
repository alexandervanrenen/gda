//
// This file is part of the gda cpp utility library.
// Copyright (c) 2017 Alexander van Renen. All rights reserved.
//
// Purpose - Helper for creating interactive user interfaces for the shell.
// -------------------------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <regex>
#include <memory>
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
namespace cli {
// -------------------------------------------------------------------------------------------------
class Command;
// -------------------------------------------------------------------------------------------------
class CommandLineInterface {
public:
   CommandLineInterface(std::istream& in = std::cin);
   ~CommandLineInterface();

   void add(const std::string &trigger, std::function<bool(const std::vector<std::string> &args)> action);
   void add(const std::regex &trigger, std::function<bool(const std::vector<std::string> &args)> action);

   void run();

private:
   std::vector<std::unique_ptr<Command>> commands;
   std::unique_ptr<Command> repeat;
   std::unique_ptr<Command> exit;
   std::unique_ptr<Command> empty;

   std::istream& input;

   struct PersistentCommand {
      Command *command;
      std::string line;
      std::vector<std::string> arguments;
   };
   std::vector<PersistentCommand> lineBuffer;
};
// -------------------------------------------------------------------------------------------------
} // End of namespace cli
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
