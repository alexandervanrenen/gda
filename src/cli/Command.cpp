//
// This file is part of the gda cpp utility library.
// Copyright (c) 2017 Alexander van Renen. All rights reserved.
//
// Purpose - Helper for creating interactive user interfaces for the shell.
// -------------------------------------------------------------------------------------------------
#include "gda/cli/Command.hpp"
#include <cassert>
// -------------------------------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
namespace cli {
// -------------------------------------------------------------------------------------------------
Command::Command(const string &trigger, function<bool(const vector<string> &args)> action)
        : action(action)
{
   pattern = regex_replace(trigger, regex("\\("), "\\("); // ! trigger
   pattern_re = regex(pattern);
   pattern = regex_replace(pattern, regex("\\)"), "\\)");
   pattern_re = regex(pattern);
   pattern = regex_replace(pattern, regex("%"), "(.*)");
   pattern_re = regex(pattern);
   //   cout << "Created command. Uses '" << pattern << "' to matches input." << endl;
}
// -------------------------------------------------------------------------------------------------
Command::Command(const std::regex &trigger, std::function<bool(const std::vector<std::string> &args)> action)
        : pattern("<unknown>")
          , pattern_re(trigger)
          , action(action)
{
}
// -------------------------------------------------------------------------------------------------
bool Command::matches(const string &input) const
{
   return regex_match(input, pattern_re);
}
// -------------------------------------------------------------------------------------------------
bool Command::process(const string &input)
{
   assert(matches(input));
   return action(getArguments(input));
}
// -------------------------------------------------------------------------------------------------
const string &Command::getPattern() const
{
   return pattern;
}
// -------------------------------------------------------------------------------------------------
vector<string> Command::getArguments(const std::string &input)
{
   smatch pieces_match;
   regex_match(input, pieces_match, pattern_re);

   vector<string> arguments;
   for (size_t i = 1; i<pieces_match.size(); i++) {
      arguments.push_back(pieces_match[i].str());
   }

   return arguments;
}
// -------------------------------------------------------------------------------------------------
} // End of namespace cli
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
