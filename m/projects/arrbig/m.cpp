#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "m.hpp"
#include <iterator>
#include <set>
thread_safe_array::thread_safe_array( const std::vector<int> & v ): arr(v) {}
thread_safe_array::~thread_safe_array(){}
void thread_safe_array::thread_function( int number_of_threads ) {
    std::thread my_threads[ number_of_threads ];
    for ( int i = 0; i < number_of_threads; i++ ) {
        my_threads[i] = std::thread( &thread_safe_array::change_arr, this );
    }
    for ( int i = 0; i < number_of_threads; i++ ) {
        my_threads[i].join(); 
    }
    //std::cout<<*this;
}
void thread_safe_array::change_arr() {
    std::set<int> my_set;
    std::vector<int> vect (3,0);
    while (my_set.size() < 3)
	    my_set.insert( rand() % arr.size() );
	std::copy(my_set.begin(), my_set.end(), vect.begin());
	int sum = 0;
	std::lock_guard<std::mutex> lock(mtx);  
	for ( int i = 0; i < 3; i++ ) 
	    sum += arr[ vect[i] ];
	for ( int i = 0; i < 3; i++ ) 
	    arr[ vect[i] ] = sum;
}
std::ostream& operator << (std::ostream& os, const thread_safe_array& array) {
    for ( int i = 0; i < array.arr.size(); i++ ) {
    os<<array.arr[i]<<" ";
    }
    os<<std::endl;
}

