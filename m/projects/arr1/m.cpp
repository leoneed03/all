#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "m.hpp"

std::mutex m1;

std::vector< std::mutex > vect(10);
int number_of_threads = 4;
void thread_function(std::vector< int > &arr) {
    int size = arr.size();
    std::thread my_threads[ number_of_threads ];
    for ( int i = 0; i < number_of_threads; i++) {
        my_threads[i] = std::thread( change_arr, std::ref(arr) );
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
void change_arr( std::vector< int > &arr) {
    
	int size = arr.size();
	std::vector< int > block(3,-1);
	block[1]--;
	block[2] -= 2;
	int sum = 0; 
	for ( int i = 0; i < 3; i++ ) {
	    block[i] = rand() % size;
	    while (  (( block[0] - block[1] ) * ( block[0] - block[2] ) * ( block[1] - block[2] )) == 0 )
	        block[i] = rand() % size;
	}
	sort( block.begin(), block.end() );
	
	std::lock(vect[ block[0] ], vect[ block[1] ], vect[ block[2] ]);
	std::lock_guard<std::mutex> lock_a(vect[ block[0] ], std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(vect[ block[1] ], std::adopt_lock);
	std::lock_guard<std::mutex> lock_c(vect[ block[2] ], std::adopt_lock);
	
	for ( int i = 0; i < 3; i++ ) {
	    std::cout << block[i] << std::endl;
	}
	for ( int i = 0; i < 3; i++ ) {
	    sum += arr[ block[i] ];
	}
	
	for ( int i = 0; i < 3; i++ ) {
	    arr[ block[i] ] = sum;
	}
}

	/*std::lock( vect[ block[0] ], vect[ block[1] ], vect[ block[2] ] );
	std::lock_guard<std::mutex> lock_a( vect[ block[0] ], std::adopt_lock );
	std::lock_guard<std::mutex> lock_b( vect[ block[1] ], std::adopt_lock );
	std::lock_guard<std::mutex> lock_c( vect[ block[2] ], std::adopt_lock );
	*/
	/*for ( int i = 0; i < 3; i++ ) {
	    std::cout << block[i] << std::endl;
	}*/

