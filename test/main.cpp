
#include "gtest/gtest.h"

int main(int argc, char** argv)
{
   srand(8128);
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
