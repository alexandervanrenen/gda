#ifndef GDA_MD5HASH_HPP_
#define GDA_MD5HASH_HPP_
//---------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <stdint.h>
//-----------------------------------------------------------------------------
// Utilities - hashing
// Stefan Marcik, Alexander van Renen 2012
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
/// hashing with md5
class MD5Hash {
public:
   MD5Hash();
   MD5Hash(const std::string& str);

   void hash(const std::string& str);

   bool operator== (const MD5Hash& other) const;
   bool operator!= (const MD5Hash& other) const;

   uint64_t toNumber() const;
private:
   union {
      uint8_t value[16];
      uint32_t value32[4];
   };

   static void md5calcblocks2(MD5Hash *hash, void* data, int blocks);

   friend std::ostream& operator<< (std::ostream& os, const MD5Hash& data);
   friend std::istream& operator>> (std::istream& is, MD5Hash& data);
};
//---------------------------------------------------------------------------
} // end of namespace gda
//---------------------------------------------------------------------------
#endif
