//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Test sript utility.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/script/ScriptLanguage.hpp"
#include "gda/script/Expression.hpp"
#include "gda/script/Environment.hpp"
#include "gda/Utility.hpp"
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(ColorTest, basics)
{
   harriet::Environment env(nullptr);
   env.add("M", make_unique<harriet::IntegerValue>(1ul << 20));

   auto first = harriet::Expression::parse("20 * M + 1")->evaluate(env);
   if (first->getResultType() != harriet::VariableType::TInteger)
      throw harriet::Exception("need integer type for numTuples");
   ASSERT_EQ(reinterpret_cast<harriet::IntegerValue*>(first.get())->result, 20l * (1l << 20) + 1l);
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
