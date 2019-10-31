#include <iostream>
#include <cstdlib>
#include "m.hpp"
#include <cstdio>
#include <gtest/gtest.h>
#include <mutex>
TEST(AllTests, determinant_test1)
{
    std::vector< std::vector <int> > matrix { {1,2,32,4}, {5,6,7,8}, { 99,10,11,12}, {13,14,15,16} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, 41786);
}


TEST(AllTests, determinant_test2)
{
    std::vector< std::vector <int> > matrix { {1,7,5,2}, {5,2,5,6}, { 9,4,5,6}, {3,4,5,8} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, 520);
}


TEST(AllTests, determinant_test3)
{
    std::vector< std::vector <int> > matrix { {10,2,3,4}, {4,5,6,3}, { 3,5,2,1}, {6,-2,0,1} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, 185);
}

TEST(AllTests, determinant_test5)
{
    std::vector< std::vector <int> > matrix { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, 0);
}


TEST(AllTests, determinant_test6)
{
    std::vector< std::vector <int> > matrix { {6,6,6,6}, {1,2,3,7}, {2,4,6,5}, {13,11,2,2} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act,-378 );
}

TEST(AllTests, determinant_test7)
{
    std::vector< std::vector <int> > matrix { {9,2,4}, {3,7,1}, {5,6,1} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, -55 );
}


TEST(AllTests, determinant_test8)
{
    std::vector< std::vector <int> > matrix { {1} };
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, 1);
}


TEST(AllTests, determinant_test9)
{
    std::vector< std::vector <int> > matrix { {10,2}, {1,1}};
    int act = 0;
    calculate_multi_thread(matrix, act);
    ASSERT_EQ(act, 8);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









