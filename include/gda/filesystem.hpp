#ifndef GDA_FILESYSTEM_HPP
#define GDA_FILESYSTEM_HPP
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
// Utilities - file system access
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
class Directory {
public:
   /// ctor
   Directory(const std::string& path);

   /// access files and do filtering
   void filter(const std::string& ending);
   std::vector<std::string> getFiles(const std::string& ending) const;
   const std::vector<std::string>& getAllFiles() const;

   /// access subDirectories
   const std::vector<std::string>& getAllSubDirectories() const;

   /// acces parent
   const std::string& getParent() const;

   /// check state
   bool good() const;
private:
   std::vector<std::string> files;
   std::vector<std::string> subDirectories;
   std::string parent;
   bool isGood;

   static void filterVector(std::vector<std::string>& vec, const std::string& ending);
};
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
