#include "gda_client.hpp"
#include <iostream>

using namespace std;
using namespace gda;


int main()
{
   Client c("127.0.0.1", 8129);
   if(!c.good())
      throw;
   c.write("hello");

   return 0;
}
