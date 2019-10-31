#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "m.hpp"

std::mutex m1;
int number_of_threads = 4;
void thread_function(std::vector< int > &arr ) {
    int size = arr.size();
    std::thread my_threads[number_of_threads];
    for ( int i = 0; i < number_of_threads; i++) {
        my_threads[i] = std::thread ( change_arr, std::ref(arr));
    }
    for ( int i = 0; i < number_of_threads; i++) {
        my_threads[i].join(); 
    }
    print_arr(arr);
}

void print_arr (std::vector< int > &arr) {
    int size = arr.size();
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " " ;
    }
    std::cout << std::endl;
}
void change_arr( std::vector< int > &arr ) {
    m1.lock();
	int size = arr.size();
	std::vector< int > block(3,0);
	int sum = 0; 
	for ( int i = 0; i < 3; i++ ) {
	    block[i] = rand() % size;
	    sum += arr[ block[i] ];
	}
	
	for ( int i = 0; i < 3; i++ ) {
	    arr[ block[i] ] = sum;
	}
	m1.unlock();
}

