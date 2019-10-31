#include <valgrind/drd.h>
#include <iostream>
#include <cstdlib>
#include "m.hpp"
#include <cstdio>
#include <gtest/gtest.h>
#include <ctime>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
    
int size = 10;
TEST(AllTests, thread_test1)
{
    std::vector< int > arr { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    thread_safe_array* a = new thread_safe_array(arr);
	a->thread_function(4);
	delete a;
}


TEST(AllTests, thread_test2)
{
   
    auto n_start_time = Clock::now();
    std::vector< int > vect(10,1);
    thread_safe_array* a = new thread_safe_array(vect);
    for (int i =0 ; i < 10; i++)
	a->thread_function(1000);
    auto n_end_time = Clock::now();
    std::cout<<"THREADS NO2@"<<std::chrono::duration_cast < std::chrono::milliseconds>(n_end_time - n_start_time).count() << "millisec" << std::endl;
   
	delete a;
}

TEST(AllTests, thread_test3)
{
    std::vector< int > vect(7,1);
    thread_safe_array* a = new thread_safe_array(vect);
    a->thread_function(10);
    delete a;
}
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









