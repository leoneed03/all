#include <valgrind/drd.h>
#include <iostream>
#include <cstdlib>
#include "m.hpp"
#include <cstdio>
#include <gtest/gtest.h>
#include <ctime>
int size = 10;
TEST(AllTests, determinant_test1)
{
    std::vector< int > arr { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	thread_function(arr);
}

/*
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
TEST(AllTests, determinant_test4)
{
    std::vector< std::vector <int> > matrix {{-7,1,12,15,4}, {6,34,8,67,12}, {2,4,3,5,6}, {0,5,11,3,2}, {2,54,2,1,32}};
    int act=0;
    calculate_multi_thread(matrix,act);
    ASSERT_EQ(act, 1621520);
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

TEST(AllTests, determinant_test10)
{
    //int size = 5;
    std::vector< std::vector <int> > matrix(size,std::vector<int>(size,0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            matrix[i][j] = i + j + 500;
    }
    int act=0;
    //matrix[i][j] = 1 + rand() & 100;
    unsigned int start_time = clock();
    calculate_multi_thread(matrix,act);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    std::cout << "RUNTIME WITH THREADS: " << search_time/1000.0 << std::endl;
    act = 0;
    unsigned int v_start_time = clock();
    calculate_one_thread(matrix,act);
    unsigned int v_end_time = clock();
    unsigned int v_search_time = v_end_time - v_start_time;
    std::cout << "RUNTIME ONE THREAD: " << v_search_time/1000.0 << std::endl;
}
TEST(AllTests, determinant_test12)
{
    //int size = 5;
    std::vector< std::vector <int> > matrix(size,std::vector<int>(size,0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            matrix[i][j] = i + j + 500;
    }
    int act=0;
    unsigned int v_start_time = clock();
    calculate_one_thread(matrix,act);
    unsigned int v_end_time = clock();
    unsigned int v_search_time = v_end_time - v_start_time;
    std::cout << "RUNTIME ONE THREAD: " << v_search_time/1000.0 << std::endl;
}

TEST(AllTests, determinant_test11)
{
   // int size  = 5;
    std::vector< std::vector <int> > matrix(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++)
            matrix[i][j] = i + j + 500;
    }
    int act=0;
    unsigned int n_start_time = clock();
    calculate_multi_thread(matrix, act);
    unsigned int n_end_time = clock();
    unsigned int n_search_time = n_end_time - n_start_time;
    std::cout << "RUNTIME M " << n_search_time/1000.0 << std::endl;
}
*/
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









