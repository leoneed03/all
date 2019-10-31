#ifndef _HASH_H_INCLUDED
#define _HASH_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>
#include "list.hpp"
namespace hashtable {
    class thread_safe_hashtable {
        private:
		int factor;
		int size;
		int number_of_elements;
		std::vector<thread_safe_list*>* vect;
		std::mutex mtx;
		friend std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );
        public:
		thread_safe_hashtable(int,int);
		~thread_safe_hashtable();
		void lock();
		void unlock();
		void lock_all();
		void unlock_all();
		void push(node*);
		int extract(int);
		node* check(int);
		void push_vector(std::vector<int>);
		void extract_vector(std::vector<int>);
		void check_vector(std::vector<int>);
		void check_YES_NO(int);
		int hash(int);
    };
    std::ostream& operator << ( std::ostream& os, const thread_safe_hashtable& ht );
}
#endif
