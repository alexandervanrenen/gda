//
// This file is part of the gda cpp utility library.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - General helper functions.
// -------------------------------------------------------------------------------------------------
#include "gda/utility.hpp"
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <sstream>
// -------------------------------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
vector<string> split(const string& str, char delimiter)
{
   vector<string> result;
   istringstream ss(str);
   string buffer;
   while (getline(ss, buffer, delimiter))
      result.push_back(buffer);
   return result;
}
// -------------------------------------------------------------------------------------------------
uint64_t getMemorySizeInBytes()
{
   // first line should look like this: MemTotal:       1056859000 kB
   ifstream in("/proc/meminfo", ios::in);
   string ignore;
   uint64_t maxMemory;
   in >> ignore >> maxMemory;
   return maxMemory;
}
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
