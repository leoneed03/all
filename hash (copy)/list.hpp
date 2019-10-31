#ifndef _LIST_H_INCLUDED
#define _LIST_H_INCLUDED

#define MAX 2147483647
#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>
#include "node.hpp"

namespace hashtable {
    class thread_safe_list {
        private:
		std::mutex mtx;
		node* head;
		int size; 
		friend std::ostream& operator << ( std::ostream& os, const thread_safe_list& list );
        public: 
		thread_safe_list( node* );
		thread_safe_list();
		~thread_safe_list();
		void lock();
		void unlock();
		void push_back(node*);
		int extract_node(int);
		node* check_for_key(int);
		void push_vector(std::vector<int>);
		void extract_vector(std::vector<int>);
		void check_vector(std::vector<int>);  
		void check(int);
		node* get_head();
    };
    std::ostream& operator << ( std::ostream& os, const thread_safe_list& list );
}
#endif
