#include <valgrind/drd.h>
#include <iostream>
#include <cstdlib>
#include "m.hpp"
#include <cstdio>
#include <gtest/gtest.h>
#include <ctime>
int size = 10;
TEST(AllTests, thread_test1)
{
	std::vector< int > arr { 1044, 123, 8 ,1223, 7, 1234, 72563, 362, 782, 2781, 10, 100, 23, 21 ,11 ,13, 12};
    thread_safe_hashtable* a = new thread_safe_hashtable(7);
    for ( int i = 0; i < arr.size(); i++  )
        a->insert(arr[i]);
    std::cout << *a;
    for ( int i = arr.size() - 1; i >= 0; i-=2)
        a->extract(arr[i]);
    std::cout << *a;
    for ( int i = arr.size() - 1; i >= 0; i--)
        a->extract(arr[i]);
    std::cout << *a;
    a->extract(100);
    delete a;
}


TEST(AllTests, thread_test2)
{
    int num = 4;
    std::vector < std::vector<int> > v (num, std::vector<int>(400,1));
    thread_safe_hashtable* a = new thread_safe_hashtable(50);
    std::thread my_threads[num];
    for ( int j = 0; j < num; j++) {
        for (int i = 0; i < v[j].size(); i++) {
            v[j][i] = rand() % 400 + 500 * j;
        }
    }
    for (int k = 0; k < num; k++) {
        my_threads[k] = std::thread( &thread_safe_hashtable::multi_insert, a, v[k] );
    }
    for ( int i = 0; i < 4; i++ ) {
        my_threads[i].join(); 
    }
    std::cout<<*a;
    std::thread my_new_threads[num];
    for (int k = 0; k < num; k++) {
        my_threads[k] = std::thread( &thread_safe_hashtable::multi_extract, a, v[k] );
    }
    for ( int i = 0 ; i < num; i++) {
        my_threads[i].join();
    }
    std::cout<<*a;
    delete a;
}
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









