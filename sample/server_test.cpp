#include "gda_server.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace gda;


int main()
{
   Server s(8128);
   if(!s.good())
      throw;

   Connection conny;
   s.waitForConnection(conny);

   string str;
   conny.read(str);
   cout << str << endl;

   return 0;
}
