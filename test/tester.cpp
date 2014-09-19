//
// This file is part of the gda cpp utility library.
// Copyright (c) 2011 Alexander van Renen. All rights reserved.
//
// Purpose - Starting point for the tester.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
// -------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
   srand(8128);
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
// -------------------------------------------------------------------------------------------------
