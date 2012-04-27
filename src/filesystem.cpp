#include "gda/filesystem.hpp"
#include "gda/string.hpp"
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------
// Utilities - file system access
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
Directory::Directory(const string& path)
: isGood(true)
{
   DIR* directory = opendir(path.c_str());
   dirent* entry = readdir(directory);
   while(entry) {
      if(entry->d_type == 8)
         files.push_back(entry->d_name); else
         subDirectories.push_back(entry->d_name);
      entry = readdir(directory);
   }
   closedir(directory);
}
//-----------------------------------------------------------------------------
void Directory::filter(const string& ending)
{
   filterVector(files, ending);
}
//-----------------------------------------------------------------------------
vector<string> Directory::getFiles(const string& ending) const
{
   vector<string> result = files;
   filterVector(result, ending);
   return result;
}
//-----------------------------------------------------------------------------
const vector<string>& Directory::getAllFiles() const
{
   return files;
}
//-----------------------------------------------------------------------------
const vector<string>& Directory::getAllSubDirectories() const
{
   return subDirectories;
}
//-----------------------------------------------------------------------------
const string& Directory::getParent() const
{
   string* a = new string("asd");
   return *a;
}
//-----------------------------------------------------------------------------
bool Directory::good() const
{
   return isGood;
}
//-----------------------------------------------------------------------------
void Directory::filterVector(vector<string>& vec, const string& ending)
{
   // removes all strings from "vec" with "ending" at the end
   for(vector<string>::iterator iter=vec.begin(); iter!=vec.end(); /*inside*/)
      if(!endsWith(*iter, ending))
         iter=vec.erase(iter); else
         iter++;
}
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
