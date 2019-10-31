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
        a->put(arr[i]);
    std::cout << *a;
    std::vector<int> v(0,0);
    a->get(2, v);
    for ( int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<a->check(1044)<<std::endl;
    std::cout<<a->check(1023)<<std::endl;
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
        my_threads[k] = std::thread( &thread_safe_hashtable::multi_put, a, v[k] );
    }
    for ( int i = 0; i < 4; i++ ) {
        my_threads[i].join(); 
    }
    std::cout<<*a;
    std::vector< std::vector<int>> vectors(num, std::vector<int>(0,0));
    std::thread my_new_threads[num];
    std::thread my_other_threads[num];
    for (int k = 0; k < num; k++) {
        int r = rand() % v.size();
        int h = rand() % v[r].size();
        my_other_threads[k] = std::thread ( &thread_safe_hashtable::check, a, v[k][h] );
        my_new_threads[k] = std::thread ( &thread_safe_hashtable::get, a, v[k][h], std::ref(vectors[k]) );
        
    }
    for ( int i = 0 ; i < num; i++) {
        my_other_threads[i].join();
        my_new_threads[i].join();
    }
	std::cout<<*a;
	std::cout<<*a;
	std::cout<<"KEK"<<std::endl;
	
	for (int j = 0; j < vectors.size(); j++) {
	    for (int i = 0; i < vectors[j].size(); i++) {
	        std::cout << vectors[j][i] << " ";
	    }
	    std::cout << std::endl;
	}
	delete a;
}
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









