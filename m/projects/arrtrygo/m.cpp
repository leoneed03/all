#include "m.hpp"
std::mutex mtx;
thread_safe_array::thread_safe_array( const std::vector<int> &v ): arr( v ), vect( std::vector<std::mutex>( v.size() )) {}
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
	int size = arr.size();
	std::vector<int> block(3);
	int sum = 0;
	std::set<int> my_set;
    while (my_set.size() < 3)
	    my_set.insert( rand() % arr.size() );
	std::vector<int> it(3,0);
	std::copy(my_set.begin(), my_set.end(),it.begin());
	while (true) {
        if (!( vect[ it[0] ]).try_lock())
            continue;
        else {
            if (!( vect[it[1] ]).try_lock()) {
               vect[ it[0] ].unlock();
               continue;
            }
            else 
            {
               if (!( vect[ it[2] ]).try_lock()) {
                   vect[ it[0] ].unlock();
                   vect[ it[1] ].unlock(); 
                   continue;
               }
               else
                   break;
           }
        }
    }
	for ( int i = 0; i < 3; i++ ) 
	    sum += arr[ it[i] ];
	    
	for ( int i = 0; i < 3; i++ ) 
	    arr[ it[i] ] = sum;
	    
	for ( int i = 0; i < 3; i++ ) 
	    vect[ it[i] ].unlock(); 
}
std::ostream& operator << ( std::ostream& os, const thread_safe_array& array ) {
    for ( int i = 0; i < array.arr.size(); i++ ) {
    os << array.arr[i] << " ";
    }
    os << std::endl;
}

