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
        std::mutex mut;
	public:
	    thread_safe_hashtable( int num );
	    ~thread_safe_hashtable();
	    void multi_put( std::vector<int >);
	    void multi_extract( std::vector<int>);   
	    void put( int item );
	    void get( int key, std::vector<int> &vect);
	    int check( int key );
        void extract( int key );
	private: 
        int hash_function( int n );
        void rehash();
        void lock_all();
        void unlock_all();
    private:
        friend std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );
};
std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );

#endif
