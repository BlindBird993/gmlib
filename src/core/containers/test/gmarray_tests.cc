
#include <gtest/gtest.h>

#include <core/containers/gmarray.h>
using namespace GMlib;

namespace {

  TEST(ArrayTest, SizeCheck) {


    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);
    array.push_back(5);
    array.push_back(6);

    EXPECT_EQ( 6, array.size() );
  }

  TEST(ArrayTest, SizeCheck2) {

    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);
    array.push_back(5);
    array.push_back(6);

    EXPECT_NE( 3, array.getSize() );
  }

  TEST(ArrayTest, SizeCheck3) {

    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    EXPECT_EQ( 3, array.getSize() );
  }

}