//
// This file is part of the gda cpp utility library.
// Copyright (c) 2014 Alexander van Renen. All rights reserved.
//
// Purpose - Creates random numbers.
// -------------------------------------------------------------------------------------------------
#include "gda/cli/CommandLineInterface.hpp"
#include "gda/cli/Command.hpp"
#include <iostream>
// -------------------------------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
namespace cli {
// -------------------------------------------------------------------------------------------------
CommandLineInterface::CommandLineInterface(istream& in)
  : input(in)
{
   repeat = unique_ptr<Command>(new Command(regex("repeat ([0-9])*"), [](const vector<string> &) { return true; }));
   exit = unique_ptr<Command>(new Command(regex("exit"), [](const vector<string> &) { return true; }));
   empty = unique_ptr<Command>(new Command(regex("\\s*"), [](const vector<string> &) { return true; }));
}
// -------------------------------------------------------------------------------------------------
CommandLineInterface::~CommandLineInterface()
{
}
// -------------------------------------------------------------------------------------------------
void CommandLineInterface::add(const string &trigger, function<bool(const vector<string> &args)> action)
{
   commands.push_back(unique_ptr<Command>(new Command(trigger, action)));
}
// -------------------------------------------------------------------------------------------------
void CommandLineInterface::add(const regex &trigger, function<bool(const vector<string> &args)> action)
{
   commands.push_back(unique_ptr<Command>(new Command(trigger, action)));
}
// -------------------------------------------------------------------------------------------------
void CommandLineInterface::run()
{
   while (input.good()) {
      cout << ":> ";

      string line;
      getline(input, line);

      if (repeat->matches(line)) {
         if (lineBuffer.empty()) {
            cout << "nothing to repeat" << endl;
            continue;
         }

         string repeatCount = repeat->getArguments(line)[0];
         int repeats = stoi(repeatCount);
         PersistentCommand &persistentCommand = lineBuffer.back();
         cout << "Running " << repeats << "x '" << persistentCommand.line << "':" << endl;
         for (int i = 0; i<repeats; i++) {
            persistentCommand.command->action(persistentCommand.arguments);
         }
         continue;
      }

      if (exit->matches(line)) {
         goto end;
      }

      bool somethingMatched = false;
      for (auto &iter : commands) {
         if (iter->matches(line)) {
            somethingMatched = true;
            bool shouldContinue = iter->process(line);
            lineBuffer.push_back(PersistentCommand{iter.get(), line, iter->getArguments(line)});
            if (!shouldContinue) {
               goto end;
            }
            break;
         }
      }

      if (!somethingMatched && !empty->matches(line)) {
         cout << "Command '" << line << "' not found." << endl;
      }
   }

   end:
   cout << "bye :)" << endl;
   return;
}
// -------------------------------------------------------------------------------------------------
} // End of namespace cli
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
