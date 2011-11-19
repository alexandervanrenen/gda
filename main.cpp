
#include "time.h"
#include <iostream>

using namespace std;
using namespace gda;

int main()
{
   Time t;
   usleep(123);
   cout << t.diff() << endl;
   
   return 0;
}
