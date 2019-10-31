#include "m.hpp"

thread_safe_array::thread_safe_array( const std::vector<int> & v ): size( v.size() ), arr( v ), vect( std::vector<std::mutex>( v.size() )) {}
thread_safe_array::~thread_safe_array(){}
void thread_safe_array::thread_function( int number_of_threads ) {
    std::thread my_threads[ number_of_threads ];
    for ( int i = 0; i < number_of_threads; i++ ) {
        my_threads[i] = std::thread( &thread_safe_array::change_arr, this );
    }
    for ( int i = 0; i < number_of_threads; i++ ) {
        my_threads[i].join(); 
    }
    std::cout<<*this;
}
void thread_safe_array::change_arr() {

	std::vector< int > block(3);
	for ( int i = 0; i < 3; i++ )
	    block[i] = i - 5;
	int sum = 0; 
	for ( int i = 0; i < 3; i++ ) {
	    block[i] = rand() % size;
	    while (  (( block[0] - block[1] ) * ( block[0] - block[2] ) * ( block[1] - block[2] )) == 0 )
	        block[i] = rand() % size;
	}
	sort( block.begin(), block.end() );
	while  (!try_lock( vect[ block[0] ], vect[ block[1] ] , vect[ block[2] ] ) );
	    
	for ( int i = 0; i < 3; i++ ) 
	    sum += arr[ block[i] ];
	    
	for ( int i = 0; i < 3; i++ ) 
	    arr[ block[i] ] = sum;
	    
	for ( int i = 0; i < 3; i++ ) 
	    vect[ block[i] ].unlock(); 
}
std::ostream& operator << ( std::ostream& os, const thread_safe_array& array ) {
    for ( int i = 0; i < array.size; i++ ) {
    os << array.arr[i] << " ";
    }
    os << std::endl;
}

