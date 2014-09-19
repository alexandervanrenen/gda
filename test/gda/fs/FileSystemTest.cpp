//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Test file system class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/Color.hpp"
#include "gda/fs/Folder.hpp"
#include "gda/fs/File.hpp"
#include <iostream>
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(FileSystemtest, basics)
{
   Folder folder("test/gda/fs");
   ASSERT_TRUE(folder.exists());
   ASSERT_EQ(folder.getBaseName(), "fs");
   vector<File> files = folder.getAllFiles();
   ASSERT_EQ(files.size(), 1ul);
   File file = files[0];
   ASSERT_TRUE(file.exists());
   ASSERT_EQ(file.getBaseNameWithEnding(), "FileSystemTest.cpp");
   ASSERT_EQ(file.getBaseNameNoEnding(), "FileSystemTest");

   ASSERT_FALSE(File("non_existing_file").exists());
   ASSERT_FALSE(Folder("non_existing_folder").exists());
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
