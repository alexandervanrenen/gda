//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Test command line interface class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/cli/CommandLineInterface.hpp"
#include <iostream>
#include <sstream>
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(CommandLineIterface, basics)
{
   int a = 0;
   int b = 0;

   istringstream in("insert 1\ninsert 3\nremove(-4)\nrepeat 3\nexit\n");
   cli::CommandLineInterface cli(in);
   cli.add("insert %", [&](const vector<string>& args){ assert(args.size() == 1); a += stoi(args[0]); return true; });
   cli.add("remove(%)", [&](const vector<string>& args){ assert(args.size() == 1); b += stoi(args[0]); return true; });
   cli.run();

   ASSERT_EQ(a, 4);
   ASSERT_EQ(b, -16);
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
