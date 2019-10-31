#include <valgrind/drd.h>
#include <iostream>
#include <cstdlib>
#include "m.hpp"
#include <cstdio>
#include <gtest/gtest.h>
#include <ctime>
#include <chrono>
#include <mutex>
typedef std::chrono::high_resolution_clock Clock;
std::mutex m;
//int size = 8;
TEST(AllTests, determinant_test1)
{
    std::vector< std::vector <int> > matrix { {1,2,32,4}, {5,6,7,8}, {99,10,11,12}, {13,14,15,16} };
    int act = 0;
    calculate_multi_thread(matrix, act, 4);
    ASSERT_EQ(act, 41760);
}


TEST(AllTests, determinant_test2)
{
    std::vector< std::vector <int> > matrix { {1,7,5,2}, {5,2,5,6}, { 9,4,5,6}, {3,4,5,8} };
    int act = 0;
    calculate_multi_thread(matrix, act, 2);
    ASSERT_EQ(act, 520);
}


TEST(AllTests, determinant_test3)
{
    std::vector< std::vector <int> > matrix { {10,2,3,4}, {4,5,6,3}, { 3,5,2,1}, {6,-2,0,1} };
    int act = 0;
    calculate_multi_thread(matrix, act, 3);
    ASSERT_EQ(act, 185);
}
TEST(AllTests, determinant_test4)
{
    std::vector< std::vector <int> > matrix {{-7,1,12,15,4}, {6,34,8,67,12}, {2,4,3,5,6}, {0,5,11,3,2}, {2,54,2,1,32}};
    int act=0;
    calculate_multi_thread(matrix,act, 4);
    ASSERT_EQ(act, 1621520);
}
TEST(AllTests, determinant_test5)
{
    std::vector< std::vector <int> > matrix { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    int act = 0;
    calculate_multi_thread(matrix, act, 4);
    ASSERT_EQ(act, 0);
}


TEST(AllTests, determinant_test6)
{
    std::vector< std::vector <int> > matrix { {6,6,6,6}, {1,2,3,7}, {2,4,6,5}, {13,11,2,2} };
    int act = 0;
    calculate_multi_thread(matrix, act, 4);
    ASSERT_EQ(act,-378 );
}

TEST(AllTests, determinant_test7)
{
    std::vector< std::vector <int> > matrix { {9,2,4}, {3,7,1}, {5,6,1} };
    int act = 0;
    calculate_multi_thread(matrix, act, 4);
    ASSERT_EQ(act, -55 );
}


TEST(AllTests, determinant_test8)
{
    std::vector< std::vector <int> > matrix { {1} };
    int act = 0;
    calculate_multi_thread(matrix, act, 1);
    ASSERT_EQ(act, 1);
}


TEST(AllTests, determinant_test9)
{
    std::vector< std::vector <int> > matrix { {10,2}, {1,1}};
    int act = 0;
    calculate_multi_thread(matrix, act, 2);
    ASSERT_EQ(act, 8);
}
/*
TEST(AllTests, determinant_test10)
{
    int size = 11;
    std::vector< std::vector <int> > matrix(size,std::vector<int>(size,0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            matrix[i][j] = i + j + 500;
    }
    int act=0;
    for (int i = 1; i < 12; i++) {
        auto n_start_time = Clock::now();
        calculate_multi_thread(matrix, act, i);
        auto n_end_time = Clock::now();
        m.lock();
	    std::cout<<"MULTI THREADS@ "<<i<<" "<< std::chrono::duration_cast < std::chrono::milliseconds>(n_end_time - n_start_time).count() << "millisec" << std::endl;
	    m.unlock();
		
    }
}*/
/*
TEST(AllTests, determinant_test12)
{

    std::vector< std::vector <int> > matrix(size,std::vector<int>(size,0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            matrix[i][j] = i + j + 500;
    }
    int act=0;
    auto n_start_time = Clock::now();
    calculate_multi_thread(matrix, act, 8);
    auto n_end_time = Clock::now();
	std::cout<<"MULTI THREADS@ "<<
		std::chrono::duration_cast < std::chrono::milliseconds>(n_end_time - n_start_time).count() << "millisec" << std::endl;
		
    auto a_start_time = Clock::now();
    calculate_one_thread(matrix, act);
    auto a_end_time = Clock::now();
	std::cout<<"ONE THREAD@ "<<
		std::chrono::duration_cast < std::chrono::milliseconds>(a_end_time - a_start_time).count() << "millisec" << std::endl;
}*/

TEST(AllTests, determinant_test11)
{
    int size  = 9;
    std::vector< std::vector <int> > matrix(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++)
            matrix[i][j] = i + j + 500;
    }
    int act=0;
    auto n_start_time = Clock::now();
    calculate_multi_thread(matrix, act, 4);
    auto n_end_time = Clock::now();
   // unsigned int n_search_time = n_end_time - n_start_time;
   // std::cout << "RUNTIME M " << n_search_time/1000.0 << std::endl;
	std::cout<<"THREADS NO2@"<<
		std::chrono::duration_cast < std::chrono::milliseconds>(n_end_time - n_start_time).count() << "millisec" << std::endl;
}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









