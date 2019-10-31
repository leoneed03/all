#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <iterator>
#include <set>

class thread_safe_array {
    private:
        //int size;
        std::vector<int> arr;
        std::vector<std::mutex> vect;
	public:
	    thread_safe_array( const std::vector<int>& );
	    ~thread_safe_array();
	    void thread_function( int );
        void change_arr( );
    private:
        friend std::ostream& operator << ( std::ostream& os, const thread_safe_array& arr );
};
std::ostream& operator << ( std::ostream& os, const thread_safe_array& arr );

#endif
