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
        std::list<int> *table;
        std::vector<std::mutex> vect;
    public:
        thread_safe_hashtable( const int num );
        ~thread_safe_hashtable();
        void insert( int item );
        void multi_insert( std::vector<int >);
        void multi_extract( std::vector<int>);
        void extract( int key );
        int hash_function( int n );
    private:
        friend std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );
};
std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );

#endif
