#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>

class thread_safe_hashtable {
    private:
        int size;
        int factor;
        int number_of_elements;
        std::list<int> *table;
        std::vector<std::mutex> vect;
        std::mutex mtx;
	public:
	    thread_safe_hashtable( int num );
	    ~thread_safe_hashtable();
	    void multi_put( const std::vector<int >);
	    void put( int item );
	    void get( int key, std::vector<int> &vect);
	    int check( int key );
	private: 
	    int hash_function( int n );
	    std::list<int>::iterator get_it( int key );
	    void lock_all();
	    void unlock_all();
	    int check_help(int key);
	    void put_help ( int key);
	    void get_help( int key, std::vector<int> &v);
	    friend std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );
};
std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );

#endif
