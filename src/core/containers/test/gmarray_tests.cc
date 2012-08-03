
#include <iostream>
#include <gtest/gtest.h>
#include <core/containers/gmarray.h>

namespace {

  TEST(ArrayTest, SizeCheck) {


    GMlib::Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);
    array.push_back(5);
    array.push_back(6);

    EXPECT_EQ( 6, array.size() );
  }

  TEST(ArrayTest, SizeCheck2) {

    GMlib::Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);
    array.push_back(5);
    array.push_back(6);

    EXPECT_EQ( 3, array.getSize() );
  }

  TEST(ArrayTest, SizeCheck3) {

    GMlib::Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    EXPECT_EQ( 3, array.getSize() );
  }
}

//int main(int argc, char* argv[])
//{

//  std::cout << "Testing!!" << std::endl;

//  testing::InitGoogleTest ( &argc, argv );
//  return RUN_ALL_TESTS();
//}
